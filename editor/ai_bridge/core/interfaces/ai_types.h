/**************************************************************************/
/*  ai_types.h                                                            */
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
	bool reasoning = false;
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
