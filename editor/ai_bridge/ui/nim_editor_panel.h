/**************************************************************************/
/*  nim_editor_panel.h                                                    */
/**************************************************************************/

#pragma once

#include "scene/gui/box_container.h"

class AIBridgeRuntime;
class Button;
class Label;
class LineEdit;
class RichTextLabel;

class NIMEditorPanel : public VBoxContainer {
	GDCLASS(NIMEditorPanel, VBoxContainer);

	AIBridgeRuntime *runtime = nullptr;
	LineEdit *api_key_edit = nullptr;
	Label *status_label = nullptr;
	RichTextLabel *output = nullptr;
	Button *test_button = nullptr;

	uint64_t active_request_id = 0;

	void _test_connection();
	void _handle_event(int p_type, const String &p_delta, const String &p_finish_reason, const String &p_error_code, const String &p_error_message);

protected:
public:
	explicit NIMEditorPanel(AIBridgeRuntime *p_runtime);
	~NIMEditorPanel();
};
