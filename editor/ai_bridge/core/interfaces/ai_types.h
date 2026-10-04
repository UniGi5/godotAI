/**************************************************************************/
/*  ai_types.h                                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/
/* Copyright (c) 2026 UniGi5.                                            */
/**************************************************************************/

#pragma once

#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "core/variant/dictionary.h"

#include <cstdint>

enum class AIMessageRole : uint8_t {
	SYSTEM,
	USER,
	ASSISTANT,
	TOOL,
};

struct AIMessage {
	AIMessageRole role = AIMessageRole::USER;
	String content;
};

struct AIRequest {
	uint64_t request_id = 0;
	StringName model;
	Vector<AIMessage> messages;
	double temperature = 0.7;
	int64_t max_tokens = 0;
	Dictionary extra_parameters;
};

enum class AIStreamEventType : uint8_t {
	DELTA,
	COMPLETED,
	ERROR,
	CANCELLED,
};

struct AIStreamEvent {
	AIStreamEventType type = AIStreamEventType::DELTA;
	uint64_t request_id = 0;
	String delta;
	String finish_reason;
	String error_code;
	String error_message;
};

struct AIProviderCapabilities {
	bool streaming = false;
	bool cancellation = false;
	bool tool_calls = false;
	bool vision = false;
	bool model_listing = false;
};
