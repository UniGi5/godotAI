/**************************************************************************/
/*  provider_registry.h                                                   */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_provider.h"

#include "core/templates/hash_map.h"
#include "core/templates/vector.h"

class AIProviderRegistry {
	HashMap<StringName, IAIProvider *> providers;

public:
	bool register_provider(IAIProvider *p_provider);
	bool unregister_provider(const StringName &p_provider_id);
	IAIProvider *get_provider(const StringName &p_provider_id) const;
	bool has_provider(const StringName &p_provider_id) const;
	Vector<StringName> get_provider_ids() const;
};
