/**************************************************************************/
/*  tool_registry.h                                                        */
/**************************************************************************/
/*                         This file is part of:                           */
/*                           Godot AI Bridge                               */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/tool.h"
#include "core/templates/vector.h"

class IToolRegistry {
public:
	virtual ~IToolRegistry() = default;

	virtual bool register_tool(ITool *p_tool) = 0;
	virtual void unregister_tool(const StringName &p_tool_id) = 0;
	virtual ITool *resolve(const StringName &p_tool_id) const = 0;
	virtual Vector<AIToolDescriptor> list_tools() const = 0;
};
