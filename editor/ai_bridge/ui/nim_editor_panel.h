/**************************************************************************/
/*  nim_editor_panel.h                                                    */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_types.h"
#include "scene/gui/box_container.h"

class AIBridgeRuntime;
class Button;
class Label;
class Label;
class LineEdit;
class RichTextLabel;

class NIMEditorPanel : public VBoxContainer {
	GDCLASS(NIMEditorPanel, VBoxContainer);

	AIBridgeRuntime *runtime = nullptr;
	LineEdit *api_key_edit = nullptr;
	LineEdit *prompt_edit = nullptr;
	Label *status_label = nullptr;
	RichTextLabel *output = nullptr;
	Button *test_button = nullptr;
	Button *send_button = nullptr;
	Button *close_button = nullptr;

	Vector<AIMessage> conversation;
	uint64_t active_request_id = 0;
	bool active_is_chat = false;
	String current_response;

	void _test_connection();
	void _close_panel();
	void _send_chat();
	void _handle_event(uint64_t p_request_id, int p_type, const String &p_delta, const String &p_finish_reason, const String &p_error_code, const String &p_error_message);

protected:
	static void _bind_methods();

public:
	explicit NIMEditorPanel(AIBridgeRuntime *p_runtime);
	~NIMEditorPanel();
};
