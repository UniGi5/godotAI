/**************************************************************************/
/*  ai_bridge_runtime.cpp                                                 */
/**************************************************************************/

#include "editor/ai_bridge/runtime/ai_bridge_runtime.h"

AIBridgeRuntime::AIBridgeRuntime() :
		nvidia_provider(&configuration, &secrets),
		orchestrator(&nvidia_provider),
		analysis_orchestrator(&orchestrator, &context_provider) {
	provider_registry.register_provider(&nvidia_provider);
}

AIOrchestrator &AIBridgeRuntime::get_orchestrator() {
	return orchestrator;
}

AIAnalysisOrchestrator &AIBridgeRuntime::get_analysis_orchestrator() {
	return analysis_orchestrator;
}

AIProviderRegistry &AIBridgeRuntime::get_provider_registry() {
	return provider_registry;
}

IConfigurationManager &AIBridgeRuntime::get_configuration() {
	return configuration;
}

ISecretStorage &AIBridgeRuntime::get_secret_storage() {
	return secrets;
}

IContextProvider &AIBridgeRuntime::get_context_provider() {
	return context_provider;
}
