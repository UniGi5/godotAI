/**************************************************************************/
/*  in_memory_configuration_manager.cpp                                  */
/**************************************************************************/

#include "editor/ai_bridge/core/config/in_memory_configuration_manager.h"

bool AIInMemoryConfigurationManager::has_value(const StringName &p_key) const {
	return values.has(p_key);
}

Variant AIInMemoryConfigurationManager::get_value(const StringName &p_key, const Variant &p_default) const {
	const Variant *value = values.getptr(p_key);
	return value ? *value : p_default;
}

void AIInMemoryConfigurationManager::set_value(const StringName &p_key, const Variant &p_value) {
	values.insert(p_key, p_value);
}

void AIInMemoryConfigurationManager::erase_value(const StringName &p_key) {
	values.erase(p_key);
}
