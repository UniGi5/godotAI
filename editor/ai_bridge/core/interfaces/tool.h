/**************************************************************************/
/*  tool.h                                                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"
#include "core/variant/variant.h"

enum class AIToolRisk : uint8_t {
	READ_ONLY,
	MUTATING,
	DESTRUCTIVE,
};

struct AIToolDescriptor {
	StringName id;
	String name;
	String description;
	String permission;
	AIToolRisk risk = AIToolRisk::READ_ONLY;
};

struct AIToolResult {
	bool success = false;
	Variant value;
	String error_code;
	String error_message;
};

class ITool {
public:
	virtual ~ITool() = default;

	virtual AIToolDescriptor get_descriptor() const = 0;
	virtual AIToolResult execute(const Dictionary &p_input) = 0;
};
