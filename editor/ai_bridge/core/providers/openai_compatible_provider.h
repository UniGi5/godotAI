/**************************************************************************/
/*  openai_compatible_provider.h                                         */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_provider.h"
#include "editor/ai_bridge/core/interfaces/configuration_manager.h"
#include "editor/ai_bridge/core/interfaces/secret_storage.h"

#include "core/os/thread.h"

#include <atomic>

class AIOpenAICompatibleProvider : public IAIProvider {
	StringName provider_id;
	IConfigurationManager *configuration = nullptr;
	ISecretStorage *secrets = nullptr;
	String default_base_url;
	String default_model;

	Thread request_thread;
	std::atomic<bool> cancel_requested{ false };
	AIRequest active_request;
	StreamCallback active_callback;

	static void _thread_entry(void *p_userdata);
	void _run_request();

	void _emit_error(const String &p_code, const String &p_message);
	void _emit_event(AIStreamEventType p_type, const String &p_delta = String(), const String &p_finish_reason = String(), bool p_reasoning = false);

	String _get_base_url() const;
	String _get_model(const AIRequest &p_request) const;
	String _get_api_key() const;

public:
	AIOpenAICompatibleProvider(
			const StringName &p_provider_id,
			IConfigurationManager *p_configuration,
			ISecretStorage *p_secrets,
			const String &p_default_base_url,
			const String &p_default_model);
	~AIOpenAICompatibleProvider() override;

	StringName get_provider_id() const override;
	AIProviderCapabilities get_capabilities() const override;
	bool start_chat(const AIRequest &p_request, StreamCallback p_callback) override;
	void cancel(uint64_t p_request_id) override;
};

class AINVIDIAProvider : public AIOpenAICompatibleProvider {
public:
	AINVIDIAProvider(IConfigurationManager *p_configuration, ISecretStorage *p_secrets);
};
