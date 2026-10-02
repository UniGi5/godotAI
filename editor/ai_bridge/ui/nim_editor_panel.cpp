/**************************************************************************/
/*  nim_editor_panel.cpp                                                  */
/**************************************************************************/

#include "nim_editor_panel.h"

#include "core/object/class_db.h"
#include "editor/editor_node.h"
#include "editor/gui/editor_bottom_panel.h"
#include "editor/ai_bridge/runtime/ai_bridge_runtime.h"
#include "editor/docks/editor_dock.h"
#include "editor/themes/editor_scale.h"
#include "editor/ai_bridge/core/interfaces/context_provider.h"
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
\truntime = p_runtime;
\tset_name("NIMEditorPanel");
\tset_v_size_flags(SIZE_EXPAND_FILL);
\tset_h_size_flags(SIZE_EXPAND_FILL);

\tclose_button = memnew(Button);
\tclose_button->set_text(TTRC("Close NIM Panel"));
\tclose_button->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
\tclose_button->connect(SceneStringName(pressed), Callable(this, "_close_panel"));
\tadd_child(close_button);

\tLabel *title = memnew(Label);
\ttitle->set_text(TTRC("NVIDIA NIM"));
\ttitle->add_theme_font_size_override("font_size", 18 * EDSCALE);
\tadd_child(title);

\tLabel *project = memnew(Label);
\tAIContext project_context = runtime ? runtime->get_context_provider().build_context("project_identity") : AIContext();
\tString project_name;
\tif (!project_context.messages.is_empty()) {
\t\tconst String identity = project_context.messages[0].content;
\t\tconst int name_marker = identity.find("\\nProject name: ");
\t\tif (name_marker >= 0) {
\t\t\tproject_name = identity.substr(name_marker + 15).get_slice("\\n", 0);
\t\t}
\t}
\tproject->set_text(project_name.is_empty() ? TTRC("Project context unavailable") : vformat(TTRC("Project: %s"), project_name));
\tproject->set_modulate(Color(1, 1, 1, 0.7));
\tadd_child(project);

\tLabel *model = memnew(Label);
\tmodel->set_text(TTRC("Nemotron 3 Ultra 550B"));
\tmodel->set_modulate(Color(1, 1, 1, 0.7));
\tadd_child(model);

\tstatus_label = memnew(Label);
\tstatus_label->set_text(TTRC("Idle"));
\tadd_child(status_label);

\t// Keep connection settings in their own bounded scroll region. On small
\t// Android viewports this prevents the chat controls from being pushed
\t// below the visible bottom-panel area.
\tScrollContainer *settings_scroll = memnew(ScrollContainer);
\tsettings_scroll->set_custom_minimum_size(Vector2(0, 88 * EDSCALE));
\tsettings_scroll->set_h_size_flags(SIZE_EXPAND_FILL);
\tsettings_scroll->set_horizontal_scroll_mode(ScrollContainer::SCROLL_MODE_DISABLED);
\tsettings_scroll->set_vertical_scroll_mode(ScrollContainer::SCROLL_MODE_AUTO);
\tadd_child(settings_scroll);

\tVBoxContainer *settings = memnew(VBoxContainer);
\tsettings->set_h_size_flags(SIZE_EXPAND_FILL);
\tsettings_scroll->add_child(settings);

\tLabel *key_label = memnew(Label);
\tkey_label->set_text(TTRC("NVIDIA API key"));
\tsettings->add_child(key_label);

\tapi_key_edit = memnew(LineEdit);
\tapi_key_edit->set_placeholder(TTRC("Enter your NVIDIA API key"));
\tString stored_key = runtime ? runtime->get_secret_storage().get_secret("ai.providers.nvidia_nemotron.api_key") : String();
\tif (!stored_key.is_empty()) {
\t\tapi_key_edit->set_text(stored_key);
\t}
\tapi_key_edit->set_secret(true);
\tapi_key_edit->set_clear_button_enabled(true);
\tapi_key_edit->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
\tsettings->add_child(api_key_edit);

\ttest_button = memnew(Button);
\ttest_button->set_text(TTRC("Test Connection"));
\ttest_button->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
\ttest_button->connect(SceneStringName(pressed), Callable(this, "_test_connection"));
\tsettings->add_child(test_button);

\toutput = memnew(RichTextLabel);
\toutput->set_fit_content(false);
\toutput->set_scroll_active(true);
\toutput->set_selection_enabled(true);
\toutput->set_h_size_flags(SIZE_EXPAND_FILL);
\toutput->set_v_size_flags(SIZE_EXPAND_FILL);
\toutput->set_custom_minimum_size(Vector2(0, 60 * EDSCALE));
\tadd_child(output);

\tHBoxContainer *input_row = memnew(HBoxContainer);
\tinput_row->set_h_size_flags(SIZE_EXPAND_FILL);
\tadd_child(input_row);

\tprompt_edit = memnew(LineEdit);
\tprompt_edit->set_placeholder(TTRC("Ask Nemotron..."));
\tprompt_edit->set_clear_button_enabled(true);
\tprompt_edit->set_h_size_flags(SIZE_EXPAND_FILL);
\tprompt_edit->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
\tinput_row->add_child(prompt_edit);

\tsend_button = memnew(Button);
\tsend_button->set_text(TTRC("Send"));
\tsend_button->set_custom_minimum_size(Vector2(92 * EDSCALE, 42 * EDSCALE));
\tsend_button->connect(SceneStringName(pressed), Callable(this, "_send_chat"));
\tinput_row->add_child(send_button);
}

NIMEditorPanel::~NIMEditorPanel() {
	if (runtime && active_request_id != 0) {
		runtime->get_orchestrator().cancel(active_request_id);
		active_request_id = 0;
	}
}

void NIMEditorPanel::_close_panel() {
	EditorBottomPanel *bottom_panel = EditorNode::get_bottom_panel();
	if (bottom_panel) {
		bottom_panel->hide_bottom_panel();
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
	Dictionary chat_template_kwargs;
	chat_template_kwargs["enable_thinking"] = false;
	chat_template_kwargs["force_nonempty_content"] = true;
	request.extra_parameters["chat_template_kwargs"] = chat_template_kwargs;

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
	const ObjectID panel_id = get_instance_id();
	active_request_id = runtime->get_orchestrator().submit(request, [panel_id](const AIStreamEvent &p_event) {
		Object *object = ObjectDB::get_instance(panel_id);
		NIMEditorPanel *panel = Object::cast_to<NIMEditorPanel>(object);
		if (!panel) {
			return;
		}
		panel->call_deferred(
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
	AIContext project_context = runtime->get_context_provider().build_context("editor_context");
	request.messages = project_context.messages;
	for (const AIMessage &message : conversation) {
		request.messages.push_back(message);
	}

	active_is_chat = true;
	const ObjectID panel_id = get_instance_id();
	active_request_id = runtime->get_orchestrator().submit(request, [panel_id](const AIStreamEvent &p_event) {
		Object *object = ObjectDB::get_instance(panel_id);
		NIMEditorPanel *panel = Object::cast_to<NIMEditorPanel>(object);
		if (!panel) {
			return;
		}
		panel->call_deferred(
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
