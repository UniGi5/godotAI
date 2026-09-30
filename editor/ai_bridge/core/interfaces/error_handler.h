/**************************************************************************/
/*  error_handler.h                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"

struct AIError {
	String category;
	String code;
	String message;
	bool retryable = false;
};

class IErrorHandler {
public:
	virtual ~IErrorHandler() = default;

	virtual void report(const AIError &p_error) = 0;
};
