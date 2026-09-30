/**************************************************************************/
/*  in_memory_secret_storage.h                                            */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/secret_storage.h"

#include "core/templates/hash_map.h"

class AIInMemorySecretStorage : public ISecretStorage {
	HashMap<StringName, String> secrets;

public:
	bool has_secret(const StringName &p_key) const override;
	String get_secret(const StringName &p_key) const override;
	bool set_secret(const StringName &p_key, const String &p_value) override;
	void erase_secret(const StringName &p_key) override;
};
