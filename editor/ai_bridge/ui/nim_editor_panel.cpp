/**************************************************************************/
/*  nim_editor_panel.cpp                                                  */
/**************************************************************************/

#include "nim_editor_panel.h"

#include "core/object/class_db.h"
#include "editor/ai_bridge/runtime/ai_bridge_runtime.h"
#include "editor/docks/editor_dock.h"
#include "editor/themes/editor_scale.h"
#include "scene/gui/button.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/rich_text_label.h"

void NIMEditorPanel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_test_connection"), &NIMEditorPanel::_test_connection);
	ClassDB::bind_method(D_METHOD("_close_panel"), &NIMEditorPanel::_close_panel);
	ClassDB::bind_method(D_METHOD("_send_chat"), &NIMEditorPanel::_send_chat);
	ClassDB::bind_method(
			D_METHOD("_handle_event", "request_id", "type", "delta", "finish_reason", "error_code", "error_message"),
			&NIMEditorPanel::_handle_event);
}

NIMEditorPanel::NIMEditorPanel(AIBridgeRuntime *p_runtime) {
	runtime = p_runtime;
	set_name("NIMEditorPanel");
	set_custom_minimum_size(Vector2(0, 340 * EDSCALE));
	set_v_size_flags(SIZE_EXPAND_FILL);
	set_h_size_flags(SIZE_EXPAND_FILL);

	close_button = memnew(Button);
	close_button->set_text(TTRC("Close NIM Panel"));
	close_button->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	close_button->connect(SceneStringName(pressed), Callable(this, "_close_panel"));
	add_child(close_button);

	Label *title = memnew(Label);
	title->set_text(TTRC("NVIDIA NIM"));
	title->add_theme_font_size_override("font_size", 18 * EDSCALE);
	add_child(title);

	Label *model = memnew(Label);
	model->set_text(TTRC("Nemotron 3 Ultra 550B"));
	model->set_modulate(Color(1, 1, 1, 0.7));
	add_child(model);

	Label *key_label = memnew(Label);
	key_label->set_text(TTRC("NVIDIA API key"));
	add_child(key_label);

	api_key_edit = memnew(LineEdit);
	api_key_edit->set_placeholder(TTRC("Enter your NVIDIA API key"));
	String stored_key = runtime ? runtime->get_secret_storage().get_secret("ai.providers.nvidia_nemotron.api_key") : String();
	if (!stored_key.is_empty()) {
		api_key_edit->set_text(stored_key);
	}
	api_key_edit->set_secret(true);
	api_key_edit->set_clear_button_enabled(true);
	api_key_edit->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	add_child(api_key_edit);

	test_button = memnew(Button);
	test_button->set_text(TTRC("Test Connection"));
	test_button->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	test_button->connect(SceneStringName(pressed), Callable(this, "_test_connection"));
	add_child(test_button);

	status_label = memnew(Label);
	status_label->set_text(TTRC("Idle"));
	add_child(status_label);

	output = memnew(RichTextLabel);
	output->set_fit_content(false);
	output->set_scroll_active(true);
	output->set_selection_enabled(true);
	output->set_v_size_flags(SIZE_EXPAND_FILL);
	output->set_custom_minimum_size(Vector2(0, 150 * EDSCALE));
	add_child(output);

	prompt_edit = memnew(LineEdit);
	prompt_edit->set_placeholder(TTRC("Ask Nemotron..."));
	prompt_edit->set_clear_button_enabled(true);
	prompt_edit->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	add_child(prompt_edit);

	send_button = memnew(Button);
	send_button->set_text(TTRC("Send"));
	send_button->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	send_button->connect(SceneStringName(pressed), Callable(this, "_send_chat"));
	add_child(send_button);
}

NIMEditorPanel::~NIMEditorPanel() {
	if (runtime && active_request_id != 0) {
		runtime->get_orchestrator().cancel(active_request_id);
		active_request_id = 0;
	}
}

void NIMEditorPanel::_close_panel() {
	Node *parent = get_parent();
	EditorDock *dock = parent ? Object::cast_to<EditorDock>(parent) : nullptr;
	if (dock) {
		dock->close();
	}
}

void NIMEditorPanel::_test_connection() {
	if (!runtime) {
		status_label->set_text(TTRC("Error: NIM runtime unavailable"));
		return;
	}

	String api_key = api_key_edit->get_text().strip_edges();
	if (api_key.is_empty()) {
		status_label->set_text(TTRC("API key required"));
		return;
	}

	runtime->get_secret_storage().set_secret("ai.providers.nvidia_nemotron.api_key", api_key);

	AIRequest request;
	request.model = "nvidia/nemotron-3-ultra-550b-a55b";
	request.temperature = 0.0;
	request.max_tokens = 16;
	request.extra_parameters["stream"] = false;

	AIMessage message;
	message.role = AIMessageRole::USER;
	message.content = "Hello. Reply with exactly: NIM_OK";
	request.messages.push_back(message);

	output->clear();
	output->append_text(TTRC("Waiting for NVIDIA NIM..."));
	status_label->set_text(TTRC("Connecting..."));
	test_button->set_disabled(true);
	send_button->set_disabled(true);

	active_is_chat = false;
	active_request_id = runtime->get_orchestrator().submit(request, [this](const AIStreamEvent &p_event) {
		call_deferred(
				"_handle_event",
				(uint64_t)p_event.request_id,
				(int)p_event.type,
				p_event.delta,
				p_event.finish_reason,
				p_event.error_code,
				p_event.error_message);
	});

	if (active_request_id == 0) {
		test_button->set_disabled(false);
		send_button->set_disabled(false);
		status_label->set_text(TTRC("Request could not be started"));
	}
}

void NIMEditorPanel::_send_chat() {
	if (!runtime || active_request_id != 0) {
		return;
	}

	String prompt = prompt_edit->get_text().strip_edges();
	if (prompt.is_empty()) {
		return;
	}

	String api_key = api_key_edit->get_text().strip_edges();
	if (api_key.is_empty()) {
		status_label->set_text(TTRC("API key required"));
		return;
	}

	runtime->get_secret_storage().set_secret("ai.providers.nvidia_nemotron.api_key", api_key);

	current_response = String();
	AIMessage user_message;
	user_message.role = AIMessageRole::USER;
	user_message.content = prompt;
	conversation.push_back(user_message);

	output->append_text(vformat("\n\nYou: %s\nNemotron: ", prompt));
	prompt_edit->clear();
	status_label->set_text(TTRC("Connecting..."));
	test_button->set_disabled(true);
	send_button->set_disabled(true);

	AIRequest request;
	request.model = "nvidia/nemotron-3-ultra-550b-a55b";
	request.temperature = 0.7;
	request.max_tokens = 512;
	request.messages = conversation;

	active_is_chat = true;
	active_request_id = runtime->get_orchestrator().submit(request, [this](const AIStreamEvent &p_event) {
		call_deferred(
				"_handle_event",
				(uint64_t)p_event.request_id,
				(int)p_event.type,
				p_event.delta,
				p_event.finish_reason,
				p_event.error_code,
				p_event.error_message);
	});

	if (active_request_id == 0) {
		conversation.remove_at(conversation.size() - 1);
		test_button->set_disabled(false);
		send_button->set_disabled(false);
		status_label->set_text(TTRC("Request could not be started"));
	}
}

void NIMEditorPanel::_handle_event(uint64_t p_request_id, int p_type, const String &p_delta, const String &p_finish_reason, const String &p_error_code, const String &p_error_message) {
	if (p_request_id == 0 || p_request_id != active_request_id) {
		return;
	}

	if (p_type == (int)AIStreamEventType::DELTA) {
		if (output->get_text().contains(TTRC("Waiting for NVIDIA NIM..."))) {
			output->clear();
		}
		if (active_is_chat) {
			current_response += p_delta;
		}
		output->append_text(p_delta);
		return;
	}

	active_request_id = 0;
	test_button->set_disabled(false);
	send_button->set_disabled(false);

	switch ((AIStreamEventType)p_type) {
		case AIStreamEventType::COMPLETED:
			status_label->set_text(active_is_chat ? TTRC("Connected") : TTRC("Connected"));
			if (active_is_chat) {
				AIMessage assistant_message;
				assistant_message.role = AIMessageRole::ASSISTANT;
				assistant_message.content = current_response;
				if (!assistant_message.content.is_empty()) {
					conversation.push_back(assistant_message);
				}
			}
			break;
		case AIStreamEventType::ERROR:
			status_label->set_text(vformat(TTRC("Error: %s"), p_error_code));
			output->clear();
			output->append_text(vformat(TTRC("NVIDIA NIM request failed.\n%s"), p_error_message.is_empty() ? TTRC("No additional error details.") : p_error_message));
			if (active_is_chat && !conversation.is_empty()) {
				conversation.remove_at(conversation.size() - 1);
			}
			break;
		case AIStreamEventType::CANCELLED:
			status_label->set_text(TTRC("Cancelled"));
			if (active_is_chat && !conversation.is_empty()) {
				conversation.remove_at(conversation.size() - 1);
			}
			break;
		default:
			break;
	}
	active_is_chat = false;
}
