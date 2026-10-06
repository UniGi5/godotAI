/**************************************************************************/
/*  ai_analysis_orchestrator.h                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_orchestrator.h"
#include "editor/ai_bridge/core/interfaces/context_provider.h"

#include <cstdint>

class AIAnalysisOrchestrator {
	IAIOrchestrator *orchestrator = nullptr;
	IContextProvider *context_provider = nullptr;

	static String _build_report_instructions();

public:
	AIAnalysisOrchestrator(IAIOrchestrator *p_orchestrator, IContextProvider *p_context_provider);

	uint64_t analyze_scene(const String &p_instruction, IAIOrchestrator::StreamCallback p_callback);
};