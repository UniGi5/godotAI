/**************************************************************************/
/*  ai_orchestrator.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/**************************************************************************/

#include "editor/ai_bridge/core/orchestrator/ai_orchestrator.h"

AIOrchestrator::AIOrchestrator(IAIProvider *p_provider) {
	provider = p_provider;
}

uint64_t AIOrchestrator::submit(const AIRequest &p_request, StreamCallback p_callback) {
	if (!provider || !p_callback) {
		return 0;
	}

	AIRequest request = p_request;
	if (request.request_id == 0) {
		request.request_id = next_request_id++;
	}

	if (!provider->start_chat(request, p_callback)) {
		return 0;
	}
	return request.request_id;
}

void AIOrchestrator::cancel(uint64_t p_request_id) {
	if (provider && p_request_id != 0) {
		provider->cancel(p_request_id);
	}
}

void AIOrchestrator::set_provider(IAIProvider *p_provider) {
	provider = p_provider;
}
