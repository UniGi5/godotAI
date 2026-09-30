# AGENTS.md — Godot AI Bridge Agent Contract

This repository is a Godot Engine fork being extended toward **Godot AI Bridge**.
This file is the entry point for any AI agent working in this repository.

## Source of truth

Before changing code, an agent must read:

1. `docs/ai/MASTER_PROJECT_CONTEXT.md` — global project context, architecture rules, security model, roadmap, and non-negotiable requirements.
2. `docs/ai/DEVELOPMENT_WORKFLOW.md` — development, testing, Git, CI/CD, and Android build rules.
3. Relevant architecture documentation under `docs/ai/` for the subsystem being changed.

The master context is additive: new agent instructions may clarify or extend it, but must not silently remove or weaken existing project requirements.

## Core architecture

The intended dependency direction is:

```
Godot Core
  ↓
AI Orchestrator
  ↓
AIProvider interface
  ↓
NvidiaProvider / OpenAIProvider / GeminiProvider / OllamaProvider / ...
```

Godot Core must remain independent from any concrete AI provider.

The intended safety boundary is:

```
UI
 ↓
AI Orchestrator
 ↓
Context Engine / Tool Registry / Permission Manager
 ↓
Provider Layer
 ↓
AI Provider
```

AI is not trusted with arbitrary filesystem, shell, Git, GitHub, or network access. Powerful operations must be exposed through explicit tools and permissions.

## Agent operating rules

- Inspect the current repository state before editing.
- Preserve existing functionality unless a change is intentionally required by the project plan.
- Prefer small, coherent, reviewable commits.
- Keep architecture/provider boundaries explicit.
- Add or update tests when behavior changes.
- Do not put API keys, tokens, passwords, private certificates, or signing credentials in the repository.
- Never assume a runtime problem is expected. Reproduce it, collect evidence, and document the finding.
- For Android work, verify the produced APK as an actual installable APK and separate build validation from device runtime validation.
- Do not bypass the Tool/Permission boundary for convenience.
- When changing the workflow, preserve direct APK delivery: the user-facing build result is a raw `.apk`, not an Actions artifact ZIP and not an AAB.

## Current delivery target

For the current development phase, CI is intentionally Android-only:

- Godot Editor
- Android
- ARM64
- Release
- APK

Every push is a build checkpoint. Successful push builds publish a direct APK Release asset linked from the workflow summary.

## Continuing the roadmap

Continue from the master roadmap rather than inventing an unrelated architecture. When work is complete, update the relevant project documentation and record important architectural decisions.
