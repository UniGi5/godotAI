/**************************************************************************/
/*  mock_provider.cpp                                                      */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/**************************************************************************/

#include "editor/ai_bridge/core/providers/mock_provider.h"

StringName AIMockProvider::get_provider_id() const {
	return "mock";
}

AIProviderCapabilities AIMockProvider::get_capabilities() const {
	AIProviderCapabilities capabilities;
	capabilities.streaming = true;
	capabilities.cancellation = true;
	return capabilities;
}

bool AIMockProvider::start_chat(const AIRequest &p_request, StreamCallback p_callback) {
	if (!enabled || !p_callback) {
		return false;
	}

	AIStreamEvent delta;
	delta.type = AIStreamEventType::DELTA;
	delta.request_id = p_request.request_id;
	delta.delta = "mock";
	p_callback(delta);

	AIStreamEvent completed;
	completed.type = AIStreamEventType::COMPLETED;
	completed.request_id = p_request.request_id;
	completed.finish_reason = "stop";
	p_callback(completed);
	return true;
}

void AIMockProvider::cancel(uint64_t p_request_id) {
	// The mock completes synchronously, so cancellation is intentionally a no-op.
}

void AIMockProvider::set_enabled(bool p_enabled) {
	enabled = p_enabled;
}
