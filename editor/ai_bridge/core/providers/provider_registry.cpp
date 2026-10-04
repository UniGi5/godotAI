/**************************************************************************/
/*  provider_registry.cpp                                                 */
/**************************************************************************/

#include "editor/ai_bridge/core/providers/provider_registry.h"

bool AIProviderRegistry::register_provider(IAIProvider *p_provider) {
	if (!p_provider) {
		return false;
	}

	const StringName provider_id = p_provider->get_provider_id();
	if (provider_id.is_empty() || providers.has(provider_id)) {
		return false;
	}

	providers.insert(provider_id, p_provider);
	return true;
}

bool AIProviderRegistry::unregister_provider(const StringName &p_provider_id) {
	if (!providers.has(p_provider_id)) {
		return false;
	}

	providers.erase(p_provider_id);
	return true;
}

IAIProvider *AIProviderRegistry::get_provider(const StringName &p_provider_id) const {
	IAIProvider *const *provider = providers.getptr(p_provider_id);
	return provider ? *provider : nullptr;
}

bool AIProviderRegistry::has_provider(const StringName &p_provider_id) const {
	return providers.has(p_provider_id);
}

Vector<StringName> AIProviderRegistry::get_provider_ids() const {
	Vector<StringName> ids;
	ids.reserve(providers.size());

	for (const KeyValue<StringName, IAIProvider *> &entry : providers) {
		ids.push_back(entry.key);
	}

	return ids;
}
