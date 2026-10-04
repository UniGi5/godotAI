/**************************************************************************/
/*  editor_context_provider.cpp                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "editor_context_provider.h"

#include "core/config/project_settings.h"
#include "core/string/ustring.h"
#include "editor/debugger/editor_debugger_node.h"
#include "editor/debugger/script_editor_debugger.h"
#include "editor/editor_data.h"
#include "editor/editor_node.h"
#include "scene/main/node.h"

AIContext AIEditorContextProvider::build_context(const String &p_scope) {
	AIContext context;
	context.source = p_scope;
	const bool identity_only = p_scope == "project_identity";
	const bool debugger_only = p_scope == "debugger_context";
	const bool scene_only = p_scope == "scene_context";
	const bool selection_only = p_scope == "selection_context";
	const bool script_only = p_scope == "script_context";

	const ProjectSettings *settings = ProjectSettings::get_singleton();
	if (!settings) {
		return context;
	}

	const String project_name = settings->get_setting("application/config/name", String());
	const String project_path = settings->get_resource_path();

	String identity = "You are assisting inside the Godot Editor.";
	if (!project_name.is_empty()) {
		identity += vformat("\nProject name: %s", project_name);
	}
	if (!project_path.is_empty()) {
		identity += vformat("\nProject path: %s", project_path);
	}

	AIMessage message;
	message.role = AIMessageRole::SYSTEM;
	message.content = identity;
	context.messages.push_back(message);

	if (identity_only) {
		return context;
	}

	if (debugger_only) {
		EditorDebuggerNode *debugger_node = EditorDebuggerNode::get_singleton();
		if (debugger_node) {
			ScriptEditorDebugger *debugger = debugger_node->get_current_debugger();
			if (debugger) {
				String debugger_context = "Debugger context:";
				debugger_context += vformat("\\nSession active: %s", debugger->is_session_active() ? "true" : "false");
				debugger_context += vformat("\\nPaused: %s", debugger->is_breaked() ? "true" : "false");
				debugger_context += vformat("\\nErrors: %d", debugger->get_error_count());
				debugger_context += vformat("\\nWarnings: %d", debugger->get_warning_count());
				AIMessage debugger_message;
				debugger_message.role = AIMessageRole::SYSTEM;
				debugger_message.content = debugger_context;
				context.messages.push_back(debugger_message);
			}
		}
		return context;
	}

	if (EditorNode::get_singleton()) {
		Node *scene_root = EditorNode::get_editor_data().get_edited_scene_root();
		if (scene_root) {
			String scene_context = "Current edited scene:";
			const String scene_path = scene_root->get_scene_file_path();
			if (!scene_path.is_empty()) {
				scene_context += vformat("\nScene path: %s", scene_path);
			}
			scene_context += vformat("\nRoot node: %s (%s)", scene_root->get_name(), scene_root->get_class());
			if (scene_root->is_inside_tree()) {
				scene_context += vformat("\nRoot node path: %s", scene_root->get_path());
			}
			AIMessage scene_message;
			scene_message.role = AIMessageRole::SYSTEM;
			scene_message.content = scene_context;
			context.messages.push_back(scene_message);
		}
		if (scene_only) {
			return context;
		}

		EditorSelection *editor_selection = EditorNode::get_singleton()->get_editor_selection();
		if (editor_selection) {
			List<Node *> selected_nodes = editor_selection->get_top_selected_node_list();
			if (!selected_nodes.is_empty()) {
				Node *selected_node = selected_nodes.front()->get();
				if (selected_node) {
					String selected_context = "Selected node:";
					selected_context += vformat("\nName: %s", selected_node->get_name());
					selected_context += vformat("\nType: %s", selected_node->get_class());
					selected_context += vformat("\nPath: %s", selected_node->get_path());
					Ref<Script> selected_script = selected_node->get_script();
					if (selected_script.is_valid()) {
					selected_context += vformat("\nScript path: %s", selected_script->get_path());
					}
					AIMessage selected_message;
					selected_message.role = AIMessageRole::SYSTEM;
					selected_message.content = selected_context;
					context.messages.push_back(selected_message);
					if (selection_only) {
						return context;
					}

					if (selected_script.is_valid()) {
						String script_context = vformat("Current script:\nPath: %s", selected_script->get_path());
						String source = selected_script->get_source_code();
						if (!source.is_empty()) {
							const int max_source_chars = 12000;
							if (source.length() > max_source_chars) {
								source = source.substr(0, max_source_chars) + "\n[Script source truncated]";
							}
							script_context += "\nSource:\n" + source;
						}
						AIMessage script_message;
						script_message.role = AIMessageRole::SYSTEM;
						script_message.content = script_context;
						context.messages.push_back(script_message);
						if (script_only) {
							return context;
						}
					}
				}
			}
		}
	}

	return context;
}
