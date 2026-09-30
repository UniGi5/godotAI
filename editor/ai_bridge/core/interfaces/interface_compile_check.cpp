/**************************************************************************/
/*  interface_compile_check.cpp                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/

#include "editor/ai_bridge/core/interfaces/ai_orchestrator.h"
#include "editor/ai_bridge/core/interfaces/configuration_manager.h"
#include "editor/ai_bridge/core/interfaces/context_provider.h"
#include "editor/ai_bridge/core/interfaces/error_handler.h"
#include "editor/ai_bridge/core/interfaces/logger.h"
#include "editor/ai_bridge/core/interfaces/permission_manager.h"
#include "editor/ai_bridge/core/interfaces/secret_storage.h"
#include "editor/ai_bridge/core/interfaces/tool_registry.h"

static_assert(sizeof(AIProviderCapabilities) > 0);
static_assert(sizeof(AIRequest) > 0);
static_assert(sizeof(AIError) > 0);
static_assert(sizeof(AIToolDescriptor) > 0);
