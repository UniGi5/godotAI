/**************************************************************************/
/*  editor_context_provider.cpp                                          */
/**************************************************************************/

#include "editor_context_provider.h"

#include "core/config/project_settings.h"
#include "core/string/ustring.h"
#include "editor/editor_node.h"
#include "editor/editor_data.h"
#include "scene/main/node.h"

AIContext AIEditorContextProvider::build_context(const String &p_scope) {
	AIContext context;
	context.source = p_scope;

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

	if (EditorNode::get_singleton()) {
		Node *scene_root = EditorNode::get_editor_data().get_edited_scene_root();
		if (scene_root) {
			String scene_context = "Current edited scene:";
			const String scene_path = scene_root->get_scene_file_path();
			if (!scene_path.is_empty()) {
				scene_context += vformat("\\nScene path: %s", scene_path);
			}
			scene_context += vformat("\\nRoot node: %s (%s)", scene_root->get_name(), scene_root->get_class());
			if (scene_root->is_inside_tree()) {
				scene_context += vformat("\\nRoot node path: %s", scene_root->get_path());
			}
			AIMessage scene_message;
			scene_message.role = AIMessageRole::SYSTEM;
			scene_message.content = scene_context;
			context.messages.push_back(scene_message);
		}

		EditorSelection *editor_selection = EditorNode::get_editor_selection();
		if (editor_selection) {
			List<Node *> selected_nodes = editor_selection->get_top_selected_node_list();
			if (!selected_nodes.is_empty()) {
				Node *selected_node = selected_nodes.front()->get();
				if (selected_node) {
					String selected_context = "Selected node:";
					selected_context += vformat("\\nName: %s", selected_node->get_name());
					selected_context += vformat("\\nType: %s", selected_node->get_class());
					selected_context += vformat("\\nPath: %s", selected_node->get_path());
					AIMessage selected_message;
					selected_message.role = AIMessageRole::SYSTEM;
					selected_message.content = selected_context;
					context.messages.push_back(selected_message);
				}
			}
		}
	}

	return context;
}
