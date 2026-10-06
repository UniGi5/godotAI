/**************************************************************************/
/*  ai_bridge_runtime.h                                                   */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/config/file_secret_storage.h"
#include "editor/ai_bridge/core/config/in_memory_configuration_manager.h"
#include "editor/ai_bridge/core/context/editor_context_provider.h"
#include "editor/ai_bridge/core/orchestrator/ai_analysis_orchestrator.h"
#include "editor/ai_bridge/core/orchestrator/ai_orchestrator.h"
#include "editor/ai_bridge/core/providers/openai_compatible_provider.h"
#include "editor/ai_bridge/core/providers/provider_registry.h"

class AIBridgeRuntime {
	AIInMemoryConfigurationManager configuration;
	AIFileSecretStorage secrets;
	AIEditorContextProvider context_provider;
	AIProviderRegistry provider_registry;
	AINVIDIAProvider nvidia_provider;
	AIOrchestrator orchestrator;
	AIAnalysisOrchestrator analysis_orchestrator;

public:
	AIBridgeRuntime();

	AIOrchestrator &get_orchestrator();
	AIAnalysisOrchestrator &get_analysis_orchestrator();
	AIProviderRegistry &get_provider_registry();
	IConfigurationManager &get_configuration();
	ISecretStorage &get_secret_storage();
	IContextProvider &get_context_provider();
};
