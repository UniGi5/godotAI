/**************************************************************************/
/*  test_ai_analysis.cpp                                                  */
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
/* the rights to use, copy, modify, merge, publish, distribute, sublicense */
/* and/or sell copies of the Software, and to permit persons to whom the  */
/* Software is furnished to do so, subject to the following conditions:   */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT      */
/* SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES */
/* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR   */
/* OTHER DEALINGS IN THE SOFTWARE.                                       */
/**************************************************************************/

#include "tests/test_macros.h"

TEST_FORCE_LINK(test_ai_analysis)

#include "editor/ai_bridge/core/interfaces/ai_analysis.h"

namespace TestAIAnalysis {

TEST_CASE("[AIAnalysis] Valid report") {
	const String report =
			"SUMMARY: Scene structure looks consistent.\n"
			"FINDINGS:\n"
			"- [WARNING] category=layout node=/root/Canvas issue=anchoring may drift recommendation=review container layout\n"
			"LIMITATIONS: Runtime behavior is not included.";

	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(report);
	CHECK(validation.valid);
	CHECK(validation.finding_count == 1);
	CHECK(validation.error.is_empty());
}

TEST_CASE("[AIAnalysis] Valid report with no findings") {
	const String report =
			"SUMMARY: No structural issues detected.\n"
			"FINDINGS:\n"
			"LIMITATIONS: Snapshot contains editor-time information only.";

	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(report);
	CHECK(validation.valid);
	CHECK(validation.finding_count == 0);
}

TEST_CASE("[AIAnalysis] Missing required section") {
	const String report =
			"SUMMARY: Scene looks consistent.\n"
			"FINDINGS:\n"
			"- [INFO] category=structure node=/root issue=ok recommendation=none";

	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(report);
	CHECK(!validation.valid);
}

TEST_CASE("[AIAnalysis] Empty finding field") {
	const String report =
			"SUMMARY: Scene has a problem.\n"
			"FINDINGS:\n"
			"- [ERROR] category=layout node=/root issue=missing recommendation=\n"
			"LIMITATIONS: None.";

	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(report);
	CHECK(!validation.valid);
}

TEST_CASE("[AIAnalysis] Malformed severity line") {
	const String report =
			"SUMMARY: Scene has a problem.\n"
			"FINDINGS:\n"
			"- [SEVERE] category=layout node=/root issue=bad recommendation=fix it\n"
			"LIMITATIONS: None.";

	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(report);
	CHECK(!validation.valid);
}

TEST_CASE("[AIAnalysis] Empty report") {
	const AIAnalysisValidation validation = AIAnalysisReportValidator::validate(String());
	CHECK(!validation.valid);
	CHECK(validation.finding_count == 0);
}

} // namespace TestAIAnalysis
