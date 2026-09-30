/**************************************************************************/
/*  configuration_manager.h                                                */
/**************************************************************************/
/*                         This file is part of:                            */
/*                           Godot AI Bridge                                */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"
#include "core/variant/variant.h"

class IConfigurationManager {
public:
	virtual ~IConfigurationManager() = default;

	virtual bool has_value(const StringName &p_key) const = 0;
	virtual Variant get_value(const StringName &p_key, const Variant &p_default = Variant()) const = 0;
	virtual void set_value(const StringName &p_key, const Variant &p_value) = 0;
	virtual void erase_value(const StringName &p_key) = 0;
};
