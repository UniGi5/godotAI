/**************************************************************************/
/*  ai_analysis_orchestrator.cpp                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/

#include "editor/ai_bridge/core/orchestrator/ai_analysis_orchestrator.h"

namespace {
constexpr int32_t MAX_SCENE_ANALYSIS_CONTEXT_CHARS = 24000;

String _bound_context(const String &p_content) {
	if (p_content.length() <= MAX_SCENE_ANALYSIS_CONTEXT_CHARS) {
		return p_content;
	}

	int truncate_at = p_content.rfind("\n", MAX_SCENE_ANALYSIS_CONTEXT_CHARS);
	if (truncate_at <= 0) {
		truncate_at = MAX_SCENE_ANALYSIS_CONTEXT_CHARS;
	}

	return p_content.substr(0, truncate_at) + "\n[Scene analysis context truncated]";
}
} // namespace

AIAnalysisOrchestrator::AIAnalysisOrchestrator(IAIOrchestrator *p_orchestrator, IContextProvider *p_context_provider) {
	orchestrator = p_orchestrator;
	context_provider = p_context_provider;
}

String AIAnalysisOrchestrator::_build_report_instructions() {
	return "You are the Godot scene analysis assistant. Analyze only the supplied current scene snapshot. "
			"Do not invent nodes, properties, scripts, or runtime behavior that are not present in the supplied context. "
			"Do not modify the project or suggest that you already changed anything. "
			"Return a concise diagnostic report using this structure:\n"
			"SUMMARY: <overall assessment>\n"
			"FINDINGS:\n"
			"- [INFO|WARNING|ERROR|CRITICAL] category=<category> node=<node path or <scene>> issue=<specific issue> recommendation=<concrete recommendation>\n"
			"LIMITATIONS: <missing or truncated information that affects confidence>\n"
			"Prioritize actionable findings over generic advice.";
}

uint64_t AIAnalysisOrchestrator::analyze_scene(const String &p_instruction, IAIOrchestrator::StreamCallback p_callback) {
	if (!orchestrator || !context_provider || !p_callback) {
		return 0;
	}

	AIContext context = context_provider->build_context("scene_analysis");
	if (context.messages.is_empty()) {
		return 0;
	}

	AIRequest request;
	request.model = "nvidia/nemotron-3-ultra-550b-a55b";
	request.temperature = 0.2;
	request.max_tokens = 256;
	request.extra_parameters["stream"] = false;

	Dictionary chat_template_kwargs;
	chat_template_kwargs["enable_thinking"] = false;
	chat_template_kwargs["force_nonempty_content"] = true;
	request.extra_parameters["chat_template_kwargs"] = chat_template_kwargs;

	for (const AIMessage &message : context.messages) {
		AIMessage bounded_message = message;
		bounded_message.content = _bound_context(bounded_message.content);
		request.messages.push_back(bounded_message);
	}

	AIMessage instruction;
	instruction.role = AIMessageRole::SYSTEM;
	instruction.content = _build_report_instructions();
	request.messages.push_back(instruction);

	AIMessage user_message;
	user_message.role = AIMessageRole::USER;
	user_message.content = p_instruction.is_empty() ? "Analyze the current Godot scene." : p_instruction;
	request.messages.push_back(user_message);

	return orchestrator->submit(request, p_callback);
}