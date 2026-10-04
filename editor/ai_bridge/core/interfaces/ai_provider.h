/**************************************************************************/
/*  ai_provider.h                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                           Godot AI Bridge                              */
/**************************************************************************/
/* Copyright (c) 2026 UniGi5.                                            */
/**************************************************************************/

#pragma once

#include "editor/ai_bridge/core/interfaces/ai_types.h"

#include <functional>
#include <cstdint>

class IAIProvider {
public:
	using StreamCallback = std::function<void(const AIStreamEvent &)>;

	virtual ~IAIProvider() = default;

	virtual StringName get_provider_id() const = 0;
	virtual AIProviderCapabilities get_capabilities() const = 0;

	// Starts an asynchronous request. The provider owns transport details and
	// reports incremental results through the callback.
	virtual bool start_chat(const AIRequest &p_request, StreamCallback p_callback) = 0;

	// Cancellation is best-effort and must be safe to call for an unknown or
	// already-completed request ID.
	virtual void cancel(uint64_t p_request_id) = 0;
};
