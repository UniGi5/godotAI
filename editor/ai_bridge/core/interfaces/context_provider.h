/**************************************************************************/
/*  context_provider.h                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_types.h"

struct AIContext {
	Vector<AIMessage> messages;
	String source;
};

class IContextProvider {
public:
	virtual ~IContextProvider() = default;

	virtual AIContext build_context(const String &p_scope) = 0;
};
