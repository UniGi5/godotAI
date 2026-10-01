/**************************************************************************/
/*  file_secret_storage.cpp                                               */
/**************************************************************************/

#include "editor/ai_bridge/core/config/file_secret_storage.h"

#include "core/config/config_file.h"

AIFileSecretStorage::AIFileSecretStorage(const String &p_storage_path) :
		storage_path(p_storage_path) {
}

bool AIFileSecretStorage::has_secret(const StringName &p_key) const {
	if (p_key.is_empty()) {
		return false;
	}

	ConfigFile config;
	if (config.load(storage_path) != OK) {
		return false;
	}
	return config.has_section_key("secrets", String(p_key));
}

String AIFileSecretStorage::get_secret(const StringName &p_key) const {
	if (p_key.is_empty()) {
		return String();
	}

	ConfigFile config;
	if (config.load(storage_path) != OK) {
		return String();
	}

	Variant value = config.get_value("secrets", String(p_key), String());
	return value.get_type() == Variant::STRING ? String(value) : String();
}

bool AIFileSecretStorage::set_secret(const StringName &p_key, const String &p_value) {
	if (p_key.is_empty()) {
		return false;
	}

	ConfigFile config;
	Error load_error = config.load(storage_path);
	if (load_error != OK && load_error != ERR_FILE_NOT_FOUND) {
		return false;
	}

	config.set_value("secrets", String(p_key), p_value);
	return config.save(storage_path) == OK;
}

void AIFileSecretStorage::erase_secret(const StringName &p_key) {
	if (p_key.is_empty()) {
		return;
	}

	ConfigFile config;
	if (config.load(storage_path) != OK) {
		return;
	}

	config.erase_section_key("secrets", String(p_key));
	config.save(storage_path);
}
