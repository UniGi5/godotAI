/**************************************************************************/
/*  ai_bridge_runtime.h                                                   */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/config/in_memory_configuration_manager.h"
#include "editor/ai_bridge/core/config/in_memory_secret_storage.h"
#include "editor/ai_bridge/core/orchestrator/ai_orchestrator.h"
#include "editor/ai_bridge/core/providers/openai_compatible_provider.h"
#include "editor/ai_bridge/core/providers/provider_registry.h"

class AIBridgeRuntime {
	AIInMemoryConfigurationManager configuration;
	AIInMemorySecretStorage secrets;
	AIProviderRegistry provider_registry;
	AINVIDIAProvider nvidia_provider;
	AIOrchestrator orchestrator;

public:
	AIBridgeRuntime();

	AIOrchestrator &get_orchestrator();
	AIProviderRegistry &get_provider_registry();
	IConfigurationManager &get_configuration();
	ISecretStorage &get_secret_storage();
};
