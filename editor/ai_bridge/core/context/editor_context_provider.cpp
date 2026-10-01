/**************************************************************************/
/*  editor_context_provider.cpp                                          */
/**************************************************************************/

#include "editor_context_provider.h"

#include "core/config/project_settings.h"
#include "core/string/ustring.h"

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
		identity += vformat("
Project name: %s", project_name);
	}
	if (!project_path.is_empty()) {
		identity += vformat("
Project path: %s", project_path);
	}

	AIMessage message;
	message.role = AIMessageRole::SYSTEM;
	message.content = identity;
	context.messages.push_back(message);

	return context;
}
