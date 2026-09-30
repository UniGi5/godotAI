/**************************************************************************/
/*  logger.h                                                              */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"

enum class AILogSeverity : uint8_t {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

class ILogger {
public:
	virtual ~ILogger() = default;

	virtual void log(AILogSeverity p_severity, const String &p_subsystem, const String &p_message) = 0;
};
