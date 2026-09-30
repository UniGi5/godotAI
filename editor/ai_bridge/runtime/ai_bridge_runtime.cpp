/**************************************************************************/
/*  ai_bridge_runtime.cpp                                                 */
/**************************************************************************/

#include "editor/ai_bridge/runtime/ai_bridge_runtime.h"

#include "core/os/mutex.h"

AIBridgeRuntime::AIBridgeRuntime() :
		nvidia_provider(&configuration, &secrets),
		orchestrator(&nvidia_provider) {
	provider_registry.register_provider(&nvidia_provider);
}

AIOrchestrator &AIBridgeRuntime::get_orchestrator() {
	return orchestrator;
}

uint64_t AIBridgeRuntime::submit(const AIRequest &p_request) {
	return orchestrator.submit(p_request, [this](const AIStreamEvent &p_event) {
		MutexLock lock(event_mutex);
		pending_events.push_back(p_event);
	});
}

void AIBridgeRuntime::cancel(uint64_t p_request_id) {
	orchestrator.cancel(p_request_id);
}

void AIBridgeRuntime::poll_events(IAIOrchestrator::StreamCallback p_callback) {
	if (!p_callback) {
		return;
	}

	Vector<AIStreamEvent> events;
	{
		MutexLock lock(event_mutex);
		events = pending_events;
		pending_events.clear();
	}

	for (const AIStreamEvent &event : events) {
		p_callback(event);
	}
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
