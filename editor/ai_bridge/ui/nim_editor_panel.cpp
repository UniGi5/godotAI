/**************************************************************************/
/*  nim_editor_panel.cpp                                                  */
/**************************************************************************/

#include "nim_editor_panel.h"

#include "editor/ai_bridge/core/interfaces/ai_types.h"
#include "editor/ai_bridge/runtime/ai_bridge_runtime.h"
#include "editor/themes/editor_scale.h"
#include "scene/gui/button.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/rich_text_label.h"

void NIMEditorPanel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_test_connection"), &NIMEditorPanel::_test_connection);
	ClassDB::bind_method(D_METHOD("_handle_event", "type", "delta", "finish_reason", "error_code", "error_message"), &NIMEditorPanel::_handle_event);
}

NIMEditorPanel::NIMEditorPanel(AIBridgeRuntime *p_runtime) {
	runtime = p_runtime;
	set_name("NIMEditorPanel");
	set_custom_minimum_size(Vector2(0, 260 * EDSCALE));
	set_v_size_flags(SIZE_EXPAND_FILL);
	set_h_size_flags(SIZE_EXPAND_FILL);

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
	api_key_edit->set_secret(true);
	api_key_edit->set_clear_button_enabled(true);
	api_key_edit->set_expand_to_text_length(false);
	api_key_edit->set_custom_minimum_size(Vector2(0, 42 * EDSCALE));
	add_child(api_key_edit);

	test_button = memnew(Button);
	test_button->set_text(TTRC("Test Connection"));
	test_button->set_custom_minimum_size(Vector2(0, 46 * EDSCALE));
	test_button->connect(SceneStringName(pressed), callable_mp(this, &NIMEditorPanel::_test_connection));
	add_child(test_button);

	status_label = memnew(Label);
	status_label->set_text(TTRC("Idle"));
	add_child(status_label);

	output = memnew(RichTextLabel);
	output->set_fit_content(false);
	output->set_scroll_active(true);
	output->set_selection_enabled(true);
	output->set_v_size_flags(SIZE_EXPAND_FILL);
	output->set_custom_minimum_size(Vector2(0, 120 * EDSCALE));
	add_child(output);
}

NIMEditorPanel::~NIMEditorPanel() {
	if (runtime && active_request_id != 0) {
		runtime->get_orchestrator().cancel(active_request_id);
		active_request_id = 0;
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

	AIMessage message;
	message.role = AIMessageRole::USER;
	message.content = "Hello. Reply with exactly: NIM_OK";
	request.messages.push_back(message);

	output->clear();
	output->append_text(TTRC("Waiting for NVIDIA NIM..."));
	status_label->set_text(TTRC("Connecting..."));
	test_button->set_disabled(true);

	active_request_id = runtime->get_orchestrator().submit(request, [this](const AIStreamEvent &p_event) {
		call_deferred(
				"_handle_event",
				(int)p_event.type,
				p_event.delta,
				p_event.finish_reason,
				p_event.error_code,
				p_event.error_message);
	});

	if (active_request_id == 0) {
		test_button->set_disabled(false);
		status_label->set_text(TTRC("Request could not be started"));
	}
}

void NIMEditorPanel::_handle_event(int p_type, const String &p_delta, const String &p_finish_reason, const String &p_error_code, const String &p_error_message) {
	if (p_type == (int)AIStreamEventType::DELTA) {
		if (output->get_text().contains(TTRC("Waiting for NVIDIA NIM..."))) {
			output->clear();
		}
		output->append_text(p_delta);
		return;
	}

	active_request_id = 0;
	test_button->set_disabled(false);

	switch ((AIStreamEventType)p_type) {
		case AIStreamEventType::COMPLETED:
			status_label->set_text(TTRC("Connected"));
			if (!p_finish_reason.is_empty() && output->get_text().is_empty()) {
				output->append_text(TTRC("NIM returned an empty response."));
			}
			break;
		case AIStreamEventType::ERROR:
			status_label->set_text(vformat(TTRC("Error: %s"), p_error_code));
			output->clear();
			output->append_text(p_error_message.is_empty() ? TTRC("NVIDIA NIM request failed.") : p_error_message);
			break;
		case AIStreamEventType::CANCELLED:
			status_label->set_text(TTRC("Cancelled"));
			break;
		default:
			break;
	}
}
