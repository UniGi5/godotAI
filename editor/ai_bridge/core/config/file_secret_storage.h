/**************************************************************************/
/*  file_secret_storage.h                                                 */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/secret_storage.h"

class AIFileSecretStorage : public ISecretStorage {
	String storage_path;

public:
	explicit AIFileSecretStorage(const String &p_storage_path = "user://godot_ai_secrets.cfg");

	bool has_secret(const StringName &p_key) const override;
	String get_secret(const StringName &p_key) const override;
	bool set_secret(const StringName &p_key, const String &p_value) override;
	void erase_secret(const StringName &p_key) override;
};
