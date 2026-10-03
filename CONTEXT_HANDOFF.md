# CONTEXT_HANDOFF.md

## Project
- Repository: `UniGi5/godotAI`
- Project: Godot 4.x Android Editor fork with integrated NVIDIA NIM / Nemotron support.
- Current development branch: `fix/p1-nim-mobile-chat-ui`
- PR: #1 — `fix(ui): keep NIM chat visible on mobile editor`
- PR head verified: `5fb6a891b7e47a9c55c36f909d138ddac8ac95ba`

## Verified physical Android checkpoint — 2026-10-02

The latest Android ARM64 release build was installed and tested on physical Android hardware.

### Confirmed
- Android Editor starts normally.
- NVIDIA API key persists across app/project restart.
- A newly created project can use the stored NVIDIA API key.
- NVIDIA NIM connection test succeeds.
- Hosted model: `nvidia/nemotron-3-ultra-550b-a55b`.
- Chat request completes immediately.
- Nemotron receives editor/project context.
- Nemotron identified the project name and offered help based on the context.
- The previous apparent timeout/silent-response problem is resolved by the deterministic non-stream request path.

### Important implementation state
The stable chat diagnostic path currently uses:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

This is now the physically verified baseline. Do not remove or replace it with streaming until the streaming path is implemented and tested separately.

## CI checkpoint
- Latest verified Android CI run: #63
- Run ID: `36959838023`
- Result: success.
- Android ARM64 release APK validation, build, payload audit and SHA-256 generation passed.
- Latest physical-test APK SHA-256:
  `ac953cf5256f4a344a6c1ee047b8d1931378db4b756dfac8c5aa8cb632ce38f2`
- Release tag used for that APK: `build-fc9398d43b98`

## Readiness state

| Area | State |
|---|---|
| Android Editor startup | 🟩🟩 verified |
| NIM authentication / TLS | 🟩🟩 verified |
| API key persistence | 🟩🟩 verified |
| New-project key availability | 🟩🟩 verified |
| Mobile NIM panel layout | 🟩🟩 verified |
| Nemotron chat generation | 🟩🟩 verified |
| Editor/project context injection | 🟩🟩 physically verified |
| Deterministic non-stream path | 🟩🟩 verified |
| Streaming response path | 🟥 not yet physically verified |
| Full agent/tool actions in editor | 🟥 not yet complete |
| v0.2 readiness | 🟩🟥 partial |
| Product/release readiness | 🟥 not yet |

## Next development gate

Continue development without requesting another physical test until a new test-dependent milestone is reached.

Priority order:
1. Preserve the working non-stream path as the stable fallback.
2. Implement robust streaming/SSE handling as a separate path.
3. Parse both normal content and reasoning content where supplied by Nemotron.
4. Make streaming explicitly selectable or safely fall back to non-stream.
5. Keep the UI status lifecycle observable: request started → HTTP response → first content → completed/error.
6. Build Android CI.
7. Only then request a physical Android streaming test with APK + direct link + SHA-256.
8. After streaming is physically verified, continue toward v0.2 packaging.

## Architecture invariant

Keep provider-independent architecture:

`Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`

Do not couple Godot Core directly to NVIDIA APIs.

## Handoff rule for Gemini / future agents

Treat this document as a factual checkpoint, not as a speculative plan.

The most important fact is:

**NVIDIA NIM + Nemotron 3 Ultra 550B chat is physically working on Android, including editor/project context.**

The previous timeout/silence issue must not be reintroduced by replacing the verified non-stream path prematurely.

Streaming is the next engineering task, not a prerequisite for the current verified baseline.

## Context transition

This file is intended to allow a new chat/agent to continue from the verified state without repeating the physical setup or asking the user to re-test already confirmed functionality.

Before asking for a new physical test, provide:
- exact reason for the test;
- exact APK;
- direct download link;
- SHA-256;
- minimal test steps;
- expected result;
- clear readiness marker.

Current checkpoint: **PHYSICAL ANDROID NIM CHAT BASELINE — GREEN / STABLE**.

## Current development checkpoint — 2026-10-03

- Current PR head: `9af5cce90023511874ba96d63c1cb154227a9a91`.
- v0.2 context work now exposes project identity, current edited scene, selected node, and the selected node's script path/source to the AI context provider.
- Script source is capped at 12,000 characters and explicitly marked when truncated.
- The verified non-stream NIM chat path remains unchanged: `stream=false`, thinking disabled, forced non-empty content.
- This context change is code-level verified only; CI for the new head is still pending/not reported by the available status endpoint.
- Do not request physical Android testing yet. First require a successful Android CI build for `9af5cce9`. Then provide the resulting APK, direct link and SHA-256 for physical regression testing.
- Physical regression target after CI: Test Connection → send `Привет` → visible user message → loading state → Nemotron response or explicit error → Retry/Copy Chat behavior.
- v0.2 remains 🟩🟥 partial. Release remains 🟥🟥.
