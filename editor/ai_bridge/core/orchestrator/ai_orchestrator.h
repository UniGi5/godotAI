/**************************************************************************/
/*  ai_orchestrator.h                                                      */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_orchestrator.h"

#include <cstdint>

class AIOrchestrator : public IAIOrchestrator {
	IAIProvider *provider = nullptr;
	uint64_t next_request_id = 1;

public:
	explicit AIOrchestrator(IAIProvider *p_provider);

	uint64_t submit(const AIRequest &p_request, StreamCallback p_callback) override;
	void cancel(uint64_t p_request_id) override;

	void set_provider(IAIProvider *p_provider);
};
