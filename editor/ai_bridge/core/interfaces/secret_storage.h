/**************************************************************************/
/*  secret_storage.h                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"

class ISecretStorage {
public:
	virtual ~ISecretStorage() = default;

	virtual bool has_secret(const StringName &p_key) const = 0;
	virtual String get_secret(const StringName &p_key) const = 0;
	virtual bool set_secret(const StringName &p_key, const String &p_value) = 0;
	virtual void erase_secret(const StringName &p_key) = 0;
};
