/**************************************************************************/
/*  ai_analysis.h                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/

#pragma once

#include "core/string/ustring.h"
#include "core/templates/vector.h"

#include <cstdint>

enum class AIAnalysisSeverity : uint8_t {
	INFO,
	WARNING,
	ERROR,
	CRITICAL,
};

struct AIAnalysisFinding {
	AIAnalysisSeverity severity = AIAnalysisSeverity::INFO;
	String category;
	String title;
	String node_path;
	String details;
	String recommendation;
};

struct AIAnalysisReport {
	String summary;
	Vector<AIAnalysisFinding> findings;
	String limitations;
};