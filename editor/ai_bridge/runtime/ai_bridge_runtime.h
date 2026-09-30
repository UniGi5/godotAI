/**************************************************************************/
/*  ai_bridge_runtime.h                                                   */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/config/in_memory_configuration_manager.h"
#include "editor/ai_bridge/core/config/in_memory_secret_storage.h"
#include "editor/ai_bridge/core/orchestrator/ai_orchestrator.h"
#include "editor/ai_bridge/core/providers/openai_compatible_provider.h"
#include "editor/ai_bridge/core/providers/provider_registry.h"

#include "core/os/mutex.h"
#include "core/templates/vector.h"

class AIBridgeRuntime {
	Mutex event_mutex;
	Vector<AIStreamEvent> pending_events;
	AIInMemoryConfigurationManager configuration;
	AIInMemorySecretStorage secrets;
	AIProviderRegistry provider_registry;
	AINVIDIAProvider nvidia_provider;
	AIOrchestrator orchestrator;

public:
	AIBridgeRuntime();

	AIOrchestrator &get_orchestrator();
	uint64_t submit(const AIRequest &p_request);
	void cancel(uint64_t p_request_id);
	void poll_events(IAIOrchestrator::StreamCallback p_callback);
	AIProviderRegistry &get_provider_registry();
	IConfigurationManager &get_configuration();
	ISecretStorage &get_secret_storage();
};
