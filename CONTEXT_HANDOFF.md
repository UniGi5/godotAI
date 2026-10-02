# CONTEXT_HANDOFF.md

## Project
- Repository: `UniGi5/godotAI`
- Product: native Android Godot Editor fork with built-in NVIDIA NIM / Nemotron.
- Godot target: 4.7.2 stable.
- Provider: NVIDIA NIM / Nemotron 3 Ultra 550B.
- Model: `nvidia/nemotron-3-ultra-550b-a55b`.
- Architecture invariant: `Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`.

## Verified physical checkpoint — 2026-10-02
The current development line has a physically verified NIM chat baseline:
- Android Editor starts normally.
- NVIDIA API key persists across app/project restart.
- A newly created project can use the stored NVIDIA API key.
- NIM connection succeeds.
- Chat request returns an immediate Nemotron response.
- Nemotron receives editor/project context and identified the project name.
- The verified reliable request shape is non-streaming with thinking disabled.
- Streaming is now implemented as a separate SSE path and must not replace the verified fallback.

## Important implementation rule
Keep the verified chat path stable:
- `stream=false`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Commit `cd8b31cc0e6191967282e4dd0e790a41dbedee19` explicitly applies this baseline to normal chat Send requests.

Do not replace the stable non-stream path with SSE until streaming is implemented and regression-tested separately.

## Current context implementation
- Project identity: implemented and physically verified.
- Current edited scene context: implemented.
- Selected node context: implemented.
- Latest selected-node API/lifecycle fixes are on master, including `EditorNode::get_singleton()->get_editor_selection()`.
- Selected-node context still requires physical verification on the APK containing the latest code.

## v0.2 SSE checkpoint
- SSE parser keeps incomplete network data buffered until an SSE event boundary.
- Multiple `data:` lines are accumulated per event.
- `[DONE]` produces `COMPLETED`.
- `finish_reason` also produces `COMPLETED`, preventing UI from remaining in a waiting state.
- `reasoning_content` is emitted with `AIStreamEvent.reasoning=true`; final `content` remains separate.
- Provider work runs on the request thread, not the Android UI thread.
- Malformed completed SSE JSON now emits `ERROR` immediately instead of waiting for timeout.
- Android compact-layout regression found: chat input/Send were below the expandable transcript; controls were moved before the transcript and transcript minimum height reduced to keep chat reachable.
- Missing API key now emits `ERROR` through the callback before `start_chat()` returns false.
- Normal chat remains explicitly `stream=false` with `enable_thinking=false` and `force_nonempty_content=true`.

## Current position
**v0.2 — Robust NVIDIA NIM Streaming / SSE implementation — Android UI regression fix pending CI**

Status:
- 1.7 physical Android launch/NIM baseline: 🟩🟩
- 1.8 first milestone: 🟩🟥 partial
- 2.1 project identity: 🟩🟩
- 2.2 current scene: 🟩🟥
- 2.3 selected node: 🟩🟥
- 2.4 current script: 🟩🟥 implemented
- v0.2 SSE: 🟩🟥 implementation complete; CI verified on `f38894b8`; compact Android chat UI fix `3105b223` pending CI
- 2.5 debugger/errors: 🟥🟥
- 2.6 controlled context assembly: 🟥🟥
- v0.2: 🟩🟥 partial
- release: 🟥🟥

## Next engineering order
1. Keep non-stream chat baseline unchanged.
2. Complete current-script context.
3. Add debugger/error context.
4. Consolidate context assembly and scope control.
5. Build Android CI.
6. Request physical test only for the resulting behavior-changing APK:
   - launch;
   - NIM connection;
   - normal chat response;
   - project/scene context;
   - selected-node context;
   - invalid-key/network error regression.
7. Verify the current Android CI build.
8. Physically test streaming on the resulting APK.
9. Then move toward v0.2 packaging.

## Physical-test rule
Do not ask the user to repeat already verified launch/API-key/NIM-chat setup without a new behavior change. When a new physical test is required, provide:
- exact APK;
- direct download link;
- SHA-256;
- minimal steps;
- expected result;
- readiness marker.

## Release rule
v0.2 and release are not declared ready from CI alone. Release packaging waits for physical functional verification and regression evidence.
