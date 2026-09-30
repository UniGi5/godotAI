/**************************************************************************/
/*  in_memory_secret_storage.cpp                                          */
/**************************************************************************/

#include "editor/ai_bridge/core/config/in_memory_secret_storage.h"

bool AIInMemorySecretStorage::has_secret(const StringName &p_key) const {
	return secrets.has(p_key);
}

String AIInMemorySecretStorage::get_secret(const StringName &p_key) const {
	const String *secret = secrets.getptr(p_key);
	return secret ? *secret : String();
}

bool AIInMemorySecretStorage::set_secret(const StringName &p_key, const String &p_value) {
	if (p_key.is_empty()) {
		return false;
	}

	secrets.insert(p_key, p_value);
	return true;
}

void AIInMemorySecretStorage::erase_secret(const StringName &p_key) {
	secrets.erase(p_key);
}
