/**************************************************************************/
/*  permission_manager.h                                                   */
/**************************************************************************/
/*                         This file is part of:                            */
/*                           Godot AI Bridge                                */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/tool.h"
#include "core/string/ustring.h"

enum class AIPermissionDecision : uint8_t {
	ALLOW,
	DENY,
	ASK_USER,
	REQUIRE_ELEVATED_CONFIRMATION,
};

struct AIPermissionContext {
	uint64_t request_id = 0;
	StringName tool_id;
	String reason;
};

class IPermissionManager {
public:
	virtual ~IPermissionManager() = default;

	virtual AIPermissionDecision evaluate(const AIToolDescriptor &p_tool, const AIPermissionContext &p_context) = 0;
	virtual void record_decision(const AIPermissionContext &p_context, AIPermissionDecision p_decision) = 0;
};
