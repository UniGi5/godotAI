# Godot AI Bridge — Current Status

## Completed

- Canonical agent instructions stored in `AGENTS.md`.
- Master project context stored in `docs/ai/MASTER_PROJECT_CONTEXT.md`.
- Development workflow stored in `docs/ai/DEVELOPMENT_WORKFLOW.md`.
- Architecture overview stored in `docs/ai/ARCHITECTURE.md`.
- v0.1 interface contracts defined.
- Living roadmap defined.
- ADRs established.
- Android-only CI established.
- Android ARM64 Release APK build established.
- Direct APK Release asset delivery established.
- Unrelated platform build workflows removed.
- GitHub App write access verified with real repository mutations.
- Android startup crash recorded as an unresolved runtime defect.
- CODEOWNERS updated for AI Bridge documentation.

## Active

- Stabilize CI after adding the agent documentation.
- Add structural APK/signature validation.
- Investigate Android startup crash.
- Implement v0.1 architecture contracts in source.
- Add deterministic provider mock and first editor integration seam.

## Not yet implemented

- AI Orchestrator source implementation.
- AIProvider source implementation.
- NVIDIA provider.
- Configuration manager.
- Secret storage.
- Context engine.
- Tool registry.
- Permission manager.
- AI Bridge editor dock.
- Runtime device smoke automation.

## Rule

Do not mark a feature complete because its files exist. Completion requires validation appropriate to the feature.
