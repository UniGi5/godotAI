/**************************************************************************/
/*  editor_context_provider.h                                             */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/context_provider.h"

class AIEditorContextProvider : public IContextProvider {
public:
	AIContext build_context(const String &p_scope) override;
	AISceneSnapshot build_scene_snapshot() override;
};
