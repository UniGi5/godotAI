/**************************************************************************/
/*  ai_orchestrator.h                                                     */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_provider.h"

class IAIOrchestrator {
public:
	using StreamCallback = IAIProvider::StreamCallback;

	virtual ~IAIOrchestrator() = default;

	virtual uint64_t submit(const AIRequest &p_request, StreamCallback p_callback) = 0;
	virtual void cancel(uint64_t p_request_id) = 0;
};
