/**************************************************************************/
/*  in_memory_configuration_manager.h                                    */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/configuration_manager.h"

#include "core/templates/hash_map.h"

class AIInMemoryConfigurationManager : public IConfigurationManager {
	HashMap<StringName, Variant> values;

public:
	bool has_value(const StringName &p_key) const override;
	Variant get_value(const StringName &p_key, const Variant &p_default = Variant()) const override;
	void set_value(const StringName &p_key, const Variant &p_value) override;
	void erase_value(const StringName &p_key) override;
};
