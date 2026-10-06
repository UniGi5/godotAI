/**************************************************************************/
/*  ai_types.h                                                            */
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

#include "editor/ai_bridge/core/interfaces/ai_analysis.h"
#include "core/variant/variant.h"

namespace {
int _field_value_end(const String &p_line, int p_start) {
	const int space = p_line.find(" ", p_start);
	return space < 0 ? p_line.length() : space;
}

bool _has_nonempty_field(const String &p_line, const String &p_key) {
	const int key_start = p_line.find(p_key);
	if (key_start < 0) {
		return false;
	}
	const int value_start = key_start + p_key.length();
	const int value_end = _field_value_end(p_line, value_start);
	return !p_line.substr(value_start, value_end - value_start).strip_edges().is_empty();
}

bool _is_finding_line(const String &p_line) {
	if (p_line.begins_with("- [INFO]") || p_line.begins_with("- [WARNING]") || p_line.begins_with("- [ERROR]") || p_line.begins_with("- [CRITICAL]")) {
		return _has_nonempty_field(p_line, "category=") &&
				_has_nonempty_field(p_line, "node=") &&
				_has_nonempty_field(p_line, "issue=") &&
				_has_nonempty_field(p_line, "recommendation=");
	}
	return false;
}
} // namespace

AIAnalysisValidation AIAnalysisReportValidator::validate(const String &p_response) {
	AIAnalysisValidation result;
	const String response = p_response.strip_edges();
	if (response.is_empty()) {
		result.error = "Report is empty.";
		return result;
	}

	const auto lines = response.split("\n");
	int summary_line = -1;
	int findings_line = -1;
	int limitations_line = -1;

	for (int i = 0; i < lines.size(); i++) {
		const String line = lines[i].strip_edges();
		if (summary_line < 0 && line.begins_with("SUMMARY:")) {
			summary_line = i;
		} else if (findings_line < 0 && line == "FINDINGS:") {
			findings_line = i;
		} else if (limitations_line < 0 && line.begins_with("LIMITATIONS:")) {
			limitations_line = i;
		}
	}

	if (summary_line < 0 || findings_line < 0 || limitations_line < 0) {
		result.error = "Required SUMMARY/FINDINGS/LIMITATIONS sections are missing.";
		return result;
	}
	if (summary_line >= findings_line || findings_line >= limitations_line) {
		result.error = "Report sections are out of order.";
		return result;
	}
	if (lines[summary_line].substr(8).strip_edges().is_empty()) {
		result.error = "SUMMARY is empty.";
		return result;
	}

	for (int i = findings_line + 1; i < limitations_line; i++) {
		const String line = lines[i].strip_edges();
		if (line.is_empty()) {
			continue;
		}
		if (line.begins_with("- [") && !_is_finding_line(line)) {
			result.error = vformat("Malformed finding line at line %d.", i + 1);
			return result;
		}
		if (_is_finding_line(line)) {
			result.finding_count++;
		}
	}

	result.valid = true;
	return result;
}
