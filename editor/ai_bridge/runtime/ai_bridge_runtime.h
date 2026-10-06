/**************************************************************************/
/*  ai_bridge_runtime.h                                                   */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/config/in_memory_configuration_manager.h"
#include "editor/ai_bridge/core/config/file_secret_storage.h"
#include "editor/ai_bridge/core/context/editor_context_provider.h"
#include "editor/ai_bridge/core/orchestrator/ai_analysis_orchestrator.h"
#include "editor/ai_bridge/core/orchestrator/ai_orchestrator.h"
#include "editor/ai_bridge/core/providers/openai_compatible_provider.h"
#include "editor/ai_bridge/core/providers/provider_registry.h"

class AIBridgeRuntime {
	AIInMemoryConfigurationManager configuration;
	AIFileSecretStorage secrets;
	AIEditorContextProvider context_provider;
	AIProviderRegistry provider_registry;
	AINVIDIAProvider nvidia_provider;
	AIOrchestrator orchestrator;
	AIAnalysisOrchestrator analysis_orchestrator;

public:
	AIBridgeRuntime();

	AIOrchestrator &get_orchestrator();
	AIAnalysisOrchestrator &get_analysis_orchestrator();
	AIProviderRegistry &get_provider_registry();
	IConfigurationManager &get_configuration();
	ISecretStorage &get_secret_storage();
	IContextProvider &get_context_provider();
};
