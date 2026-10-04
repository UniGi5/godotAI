/**************************************************************************/
/*  nim_editor_panel.h                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_types.h"
#include "scene/gui/box_container.h"

class AIBridgeRuntime;
class Button;
class Label;
class LineEdit;
class RichTextLabel;
class TextEdit;

class NIMEditorPanel : public VBoxContainer {
	GDCLASS(NIMEditorPanel, VBoxContainer);

	AIBridgeRuntime *runtime = nullptr;
	LineEdit *api_key_edit = nullptr;
	TextEdit *prompt_edit = nullptr;
	Label *status_label = nullptr;
	RichTextLabel *output = nullptr;
	Button *test_button = nullptr;
	Button *send_button = nullptr;
	Button *close_button = nullptr;
	Button *copy_button = nullptr;
	Button *clear_button = nullptr;
	Button *retry_button = nullptr;
	Button *stop_button = nullptr;
	Button *copy_code_button = nullptr;

	Vector<AIMessage> conversation;
	uint64_t active_request_id = 0;
	bool active_is_chat = false;
	String current_response;
	String last_prompt;
	String last_code_block;
	bool retry_available = false;
	bool active_is_test_connection = false;

	void _test_connection();
	void _close_panel();
	void _send_chat();
	void _copy_chat();
	void _clear_chat();
	void _retry_chat();
	void _cancel_chat();
	bool _start_chat_request(const String &p_prompt, bool p_append_user_message);
	void _copy_code();
	String _escape_bbcode(const String &p_text) const;
	String _markdown_to_bbcode(const String &p_text);
	void _rebuild_chat_output();
	void _handle_event(uint64_t p_request_id, int p_type, const String &p_delta, const String &p_finish_reason, const String &p_error_code, const String &p_error_message, bool p_reasoning);

protected:
	static void _bind_methods();

public:
	explicit NIMEditorPanel(AIBridgeRuntime *p_runtime);
	~NIMEditorPanel();
};
