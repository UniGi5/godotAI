/**************************************************************************/
/*  openai_compatible_provider.cpp                                       */
/**************************************************************************/

#include "editor/ai_bridge/core/providers/openai_compatible_provider.h"

#include "core/io/http_client.h"
#include "core/crypto/crypto.h"
#include "core/io/json.h"
#include "core/os/os.h"
#include "core/string/ustring.h"

namespace {

static String _role_to_string(AIMessageRole p_role) {
	switch (p_role) {
		case AIMessageRole::SYSTEM:
			return "system";
		case AIMessageRole::ASSISTANT:
			return "assistant";
		case AIMessageRole::TOOL:
			return "tool";
		case AIMessageRole::USER:
		default:
			return "user";
	}
}

static bool _parse_url(const String &p_url, String &r_host, int &r_port, String &r_path, bool &r_https) {
	String url = p_url.strip_edges();
	int scheme_end = url.find("://");
	if (scheme_end <= 0) {
		return false;
	}

	String scheme = url.substr(0, scheme_end).to_lower();
	if (scheme != "http" && scheme != "https") {
		return false;
	}
	r_https = scheme == "https";

	String authority_and_path = url.substr(scheme_end + 3);
	int path_pos = authority_and_path.find_char('/');
	String authority = path_pos >= 0 ? authority_and_path.substr(0, path_pos) : authority_and_path;
	r_path = path_pos >= 0 ? authority_and_path.substr(path_pos) : "/";

	if (authority.is_empty()) {
		return false;
	}

	int port_pos = authority.rfind(":");
	if (port_pos > 0 && authority.substr(port_pos + 1).is_valid_int()) {
		r_host = authority.substr(0, port_pos);
		r_port = authority.substr(port_pos + 1).to_int();
	} else {
		r_host = authority;
		r_port = r_https ? 443 : 80;
	}

	return !r_host.is_empty();
}

static String _error_from_http(int p_code) {
	return vformat("http_%d", p_code);
}
} // namespace

AIOpenAICompatibleProvider::AIOpenAICompatibleProvider(
		const StringName &p_provider_id,
		IConfigurationManager *p_configuration,
		ISecretStorage *p_secrets,
		const String &p_default_base_url,
		const String &p_default_model) :
		provider_id(p_provider_id),
		configuration(p_configuration),
		secrets(p_secrets),
		default_base_url(p_default_base_url),
		default_model(p_default_model) {
}

AIOpenAICompatibleProvider::~AIOpenAICompatibleProvider() {
	cancel_requested.store(true);
	if (request_thread.is_started()) {
		request_thread.wait_to_finish();
	}
}

StringName AIOpenAICompatibleProvider::get_provider_id() const {
	return provider_id;
}

AIProviderCapabilities AIOpenAICompatibleProvider::get_capabilities() const {
	AIProviderCapabilities capabilities;
	capabilities.streaming = true;
	capabilities.cancellation = true;
	return capabilities;
}

String AIOpenAICompatibleProvider::_get_base_url() const {
	String key = vformat("ai.providers.%s.base_url", String(provider_id));
	if (configuration && configuration->has_value(key)) {
		Variant value = configuration->get_value(key);
		if (value.get_type() == Variant::STRING && !String(value).is_empty()) {
			return String(value).strip_edges();
		}
	}
	return default_base_url;
}

String AIOpenAICompatibleProvider::_get_model(const AIRequest &p_request) const {
	if (!p_request.model.is_empty()) {
		return p_request.model;
	}
	String key = vformat("ai.providers.%s.model", String(provider_id));
	if (configuration && configuration->has_value(key)) {
		Variant value = configuration->get_value(key);
		if (value.get_type() == Variant::STRING && !String(value).is_empty()) {
			return String(value);
		}
	}
	return default_model;
}

String AIOpenAICompatibleProvider::_get_api_key() const {
	if (!secrets) {
		return String();
	}
	String key = vformat("ai.providers.%s.api_key", String(provider_id));
	return secrets->get_secret(key);
}

void AIOpenAICompatibleProvider::_emit_error(const String &p_code, const String &p_message) {
	AIStreamEvent event;
	event.type = AIStreamEventType::ERROR;
	event.request_id = active_request.request_id;
	event.error_code = p_code;
	event.error_message = p_message;
	if (active_callback) {
		active_callback(event);
	}
}

void AIOpenAICompatibleProvider::_emit_event(AIStreamEventType p_type, const String &p_delta, const String &p_finish_reason, bool p_reasoning) {
	AIStreamEvent event;
	event.type = p_type;
	event.request_id = active_request.request_id;
	event.delta = p_delta;
	event.finish_reason = p_finish_reason;
	event.reasoning = p_reasoning;
	if (active_callback) {
		active_callback(event);
	}
}

bool AIOpenAICompatibleProvider::start_chat(const AIRequest &p_request, StreamCallback p_callback) {
	if (!p_callback || p_request.request_id == 0) {
		return false;
	}

	if (request_thread.is_started()) {
		request_thread.wait_to_finish();
	}

	active_request = p_request;
	active_callback = p_callback;
	if (_get_api_key().is_empty()) {
		_emit_error("missing_api_key", "Provider API key is not configured.");
		return false;
	}
	cancel_requested.store(false);
	request_thread.start(_thread_entry, this);
	return true;
}

void AIOpenAICompatibleProvider::cancel(uint64_t p_request_id) {
	if (p_request_id == active_request.request_id) {
		cancel_requested.store(true);
	}
}

void AIOpenAICompatibleProvider::_thread_entry(void *p_userdata) {
	static_cast<AIOpenAICompatibleProvider *>(p_userdata)->_run_request();
}

void AIOpenAICompatibleProvider::_run_request() {
	String base_url = _get_base_url();
	String model = _get_model(active_request);
	String api_key = _get_api_key();

	String host;
	String path;
	int port = -1;
	bool https = false;
	if (!_parse_url(base_url, host, port, path, https)) {
		_emit_error("invalid_base_url", "Provider base URL must be an absolute http:// or https:// URL.");
		return;
	}

	if (path.ends_with("/")) {
		path = path.substr(0, path.length() - 1);
	}
	path += "/chat/completions";

	const bool stream_response = active_request.extra_parameters.has("stream") ? bool(active_request.extra_parameters["stream"]) : true;
	Dictionary body;
	body["model"] = model;
	body["stream"] = stream_response;
	Array messages;
	for (const AIMessage &message : active_request.messages) {
		Dictionary item;
		item["role"] = _role_to_string(message.role);
		item["content"] = message.content;
		messages.push_back(item);
	}
	body["messages"] = messages;

	if (active_request.temperature >= 0.0) {
		body["temperature"] = active_request.temperature;
	}
	if (active_request.max_tokens > 0) {
		body["max_tokens"] = active_request.max_tokens;
	}

	for (const KeyValue<Variant, Variant> &entry : active_request.extra_parameters) {
		body[entry.key] = entry.value;
	}

	String json_body = JSON::stringify(body);
	String pending_sse;
	String pending_sse_event;
	String pending_body;

	Ref<HTTPClient> client = Ref<HTTPClient>(HTTPClient::create());
	client->set_blocking_mode(false);
	client->set_read_chunk_size(64 * 1024);

	Ref<TLSOptions> tls_options;
	if (https) {
		tls_options = TLSOptions::client();
	}
	Error err = client->connect_to_host(host, port, tls_options);
	if (err != OK) {
		_emit_error("connect_failed", vformat("Unable to start connection to %s:%d (error %d).", host, port, err));
		return;
	}

	const uint64_t connect_started_msec = OS::get_singleton()->get_ticks_msec();
	const uint64_t connect_timeout_msec = 20000;

	while (true) {
		if (cancel_requested.load()) {
			client->close();
			_emit_event(AIStreamEventType::CANCELLED);
			return;
		}

		err = client->poll();
		HTTPClient::Status status = client->get_status();
		if (status == HTTPClient::STATUS_CONNECTED) {
			break;
		}

		if (status == HTTPClient::STATUS_CANT_RESOLVE) {
			_emit_error("dns_failed", vformat("DNS resolution failed for %s.", host));
			client->close();
			return;
		}
		if (status == HTTPClient::STATUS_TLS_HANDSHAKE_ERROR) {
			_emit_error("tls_failed", vformat("TLS handshake failed for %s:%d.", host, port));
			client->close();
			return;
		}
		if (status == HTTPClient::STATUS_CANT_CONNECT || status == HTTPClient::STATUS_CONNECTION_ERROR) {
			_emit_error("connect_failed", vformat("Connection failed to %s:%d (status %d, error %d).", host, port, status, err));
			client->close();
			return;
		}
		if (connect_timeout_msec < OS::get_singleton()->get_ticks_msec() - connect_started_msec) {
			_emit_error("connect_timeout", vformat("Timed out connecting to %s:%d after %d seconds.", host, port, int(connect_timeout_msec / 1000)));
			client->close();
			return;
		}
		Thread::yield();
	}

	Vector<String> headers;
	headers.push_back("Content-Type: application/json");
	headers.push_back(stream_response ? "Accept: text/event-stream" : "Accept: application/json");
	headers.push_back("Authorization: Bearer " + api_key);

	CharString body_utf8 = json_body.utf8();
	err = client->request(
			HTTPClient::METHOD_POST,
			path,
			headers,
			reinterpret_cast<const uint8_t *>(body_utf8.get_data()),
			body_utf8.length());
	if (err != OK) {
		_emit_error("request_failed", vformat("HTTP request failed: %d.", err));
		client->close();
		return;
	}

	const uint64_t response_started_msec = OS::get_singleton()->get_ticks_msec();
	uint64_t last_data_msec = response_started_msec;
	const uint64_t response_timeout_msec = 120000;
	const uint64_t idle_timeout_msec = 45000;

	while (true) {
		if (cancel_requested.load()) {
			client->close();
			_emit_event(AIStreamEventType::CANCELLED);
			return;
		}

		err = client->poll();
		if (err != OK) {
			_emit_error("poll_failed", vformat("HTTP polling failed: %d.", err));
			client->close();
			return;
		}

		const uint64_t now_msec = OS::get_singleton()->get_ticks_msec();
		if (now_msec - response_started_msec > response_timeout_msec) {
			_emit_error("response_timeout", "NVIDIA NIM did not complete a response within 120 seconds.");
			client->close();
			return;
		}

		HTTPClient::Status status = client->get_status();
		if (status == HTTPClient::STATUS_BODY) {
			int response_code = client->get_response_code();
			if (response_code < 200 || response_code >= 300) {
				PackedByteArray error_body = client->read_response_body_chunk();
				String error_text = String::utf8((const char *)error_body.ptr(), error_body.size());
				_emit_error(_error_from_http(response_code), error_text);
				client->close();
				return;
			}

			PackedByteArray chunk = client->read_response_body_chunk();
			if (!chunk.is_empty()) {
				last_data_msec = now_msec;
				String chunk_text = String::utf8((const char *)chunk.ptr(), chunk.size());
				if (stream_response) {
					pending_sse += chunk_text;
				} else {
					pending_body += chunk_text;
				}
			}

			if (!stream_response) {
				if (pending_body.is_empty()) {
					continue;
				}
				Variant parsed = JSON::parse_string(pending_body);
				if (parsed.get_type() == Variant::DICTIONARY) {
					Dictionary payload = parsed;
					Array choices = payload.get("choices", Array());
					if (!choices.is_empty()) {
						Dictionary choice = choices[0];
						Dictionary message = choice.get("message", Dictionary());
						Variant reasoning_value = message.get("reasoning_content", Variant());
						Variant content_value = message.get("content", Variant());
						if (reasoning_value.get_type() == Variant::STRING) {
							String reasoning = reasoning_value;
							if (!reasoning.is_empty()) {
								_emit_event(AIStreamEventType::DELTA, reasoning, String(), true);
							}
						}
						if (content_value.get_type() == Variant::STRING) {
							String content = content_value;
							if (!content.is_empty()) {
								_emit_event(AIStreamEventType::DELTA, content);
							}
						}
						_emit_event(AIStreamEventType::COMPLETED, String(), choice.get("finish_reason", String("stop")));
						client->close();
						return;
					}
				}
				continue;
			}

			while (true) {
				int newline = pending_sse.find("\n");
				if (newline < 0) {
					break;
				}

				String line = pending_sse.substr(0, newline);
				pending_sse = pending_sse.substr(newline + 1);
				line = line.strip_edges();

				// SSE events are terminated by a blank line. Keep data fields
				// together so JSON is parsed only after the complete event arrives.
				if (line.is_empty()) {
					if (pending_sse_event.is_empty()) {
						continue;
					}
					String data = pending_sse_event;
					pending_sse_event = String();

					if (data == "[DONE]") {
						_emit_event(AIStreamEventType::COMPLETED, String(), "stop");
						client->close();
						return;
					}

					Variant parsed = JSON::parse_string(data);
					if (parsed.get_type() != Variant::DICTIONARY) {
						continue;
					}

					Dictionary payload = parsed;
					Array choices = payload.get("choices", Array());
					if (choices.is_empty()) {
						continue;
					}

					Dictionary choice = choices[0];
					Dictionary delta = choice.get("delta", Dictionary());
					Variant reasoning_value = delta.get("reasoning_content", Variant());
					Variant content_value = delta.get("content", Variant());
					String finish_reason = choice.get("finish_reason", String());

					if (reasoning_value.get_type() == Variant::STRING) {
						String reasoning = reasoning_value;
						if (!reasoning.is_empty()) {
							_emit_event(AIStreamEventType::DELTA, reasoning, String(), true);
						}
					}
					if (content_value.get_type() == Variant::STRING) {
						String content = content_value;
						if (!content.is_empty()) {
							_emit_event(AIStreamEventType::DELTA, content, String(), false);
						}
					}

					if (!finish_reason.is_empty()) {
						_emit_event(AIStreamEventType::COMPLETED, String(), finish_reason);
						client->close();
						return;
					}
					continue;
				}

				if (!line.begins_with("data:")) {
					continue;
				}
			String data_line = line.substr(5).strip_edges();
			if (!pending_sse_event.is_empty()) {
				pending_sse_event += "\\n";
			}
			pending_sse_event += data_line;
			}

		} else if (status == HTTPClient::STATUS_DISCONNECTED) {
			_emit_error("connection_lost", "NVIDIA NIM connection closed before a complete response was received.");
			client->close();
			return;
		}

		if (now_msec - last_data_msec > idle_timeout_msec) {
			_emit_error("response_idle_timeout", "NVIDIA NIM stopped sending data for 45 seconds.");
			client->close();
			return;
		}

		Thread::yield();
	}

	client->close();
	_emit_error("connection_lost", "NVIDIA NIM connection closed before a complete response was received.");
}

AINVIDIAProvider::AINVIDIAProvider(IConfigurationManager *p_configuration, ISecretStorage *p_secrets) :
		AIOpenAICompatibleProvider(
				"nvidia_nemotron",
				p_configuration,
				p_secrets,
				"https://integrate.api.nvidia.com/v1",
				"nvidia/nemotron-3-ultra-550b-a55b") {
}
