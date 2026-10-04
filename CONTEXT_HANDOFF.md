# CONTEXT_HANDOFF.md

## Project

- Repository: `UniGi5/godotAI`
- Project: Godot 4.x Android Editor fork with integrated NVIDIA NIM / Nemotron support.
- Development branch: `fix/p1-nim-mobile-chat-ui`
- PR: #1 — `fix(ui): keep NIM chat visible on mobile editor`
- Current PR head: `6c053080822dd42b2b2fdea08daca13e7510a6d7`

## Confirmed physical Android baseline

The latest physically confirmed baseline is commit `0201ff8138d89a265176c1a79c1c6e8f918f05fd`.

- CI Run: #156
- Run ID: `37057401793`
- Result: SUCCESS
- APK: `godot-android-editor-arm64.apk`
- Release tag: `build-0201ff8138d`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

### Confirmed on physical Android

- Android Editor starts normally.
- NVIDIA API key persists.
- NVIDIA NIM connection test succeeds.
- Nemotron request/response works.
- Test Connection no longer remains stuck after success.
- Copy Chat copies the conversation history.
- Mobile UI remains usable.

This is the stable functional baseline. Do not regress to the old broken Test Connection or Copy Chat behavior.

## Stable NIM transport baseline

The verified non-stream path remains the safety baseline:

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Do not replace this baseline with streaming without a separate implementation and verification gate.

## v0.2 context implementation

Current HEAD contains code-level context support for:

- project identity;
- project resource path;
- current edited scene;
- selected node name/type/path;
- selected node script path;
- selected script source;
- 12,000-character source limit;
- explicit `[Script source truncated]` marker.

Relevant commits:
- `87b0722bbf8e051a5b081c9feb692016efc0a8cd` — selected node script path;
- `9af5cce90023511874ba96d63c1cb154227a9a91` — selected script source;
- `ac19c9bbcaf519f67507116920f71f5ebe580682` — indentation normalization;
- `84587d909a46f609d602aafa58d2d6afac12b15b` — roadmap checkpoint;
- `3a0311be11d071312bc2c608163644702f6308e6` — scoped context assembly;
- `42bd9b9c1aab1fa34df901129f93cde63ad16cf0` — debugger/error summary scope.

These changes are code-level state, not a new physical verification. The physically verified baseline remains `0201ff8`.

## CI status for current HEAD

For `6c053080822dd42b2b2fdea08daca13e7510a6d7`:

- Android build artifact is confirmed by GitHub Release `build-6c053080822d`.
- Release target commit: `6c053080822dd42b2b2fdea08daca13e7510a6d7`.
- APK: `godot-android-editor-arm64.apk`.
- APK size: 192,454,271 bytes.
- GitHub asset SHA-256 digest: `fae87f32468f61d15d12b4f17d96c91849c57d0f66c1b5fd5e9ab350840e29f4`.
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-6c053080822d/godot-android-editor-arm64.apk
- Release is published as a prerelease artifact.
- The available workflow-run endpoint may not enumerate the push run, but the release artifact is evidence that the Android build/publish job completed for this commit.

This does **not** prove physical runtime behavior. The current HEAD is now ready for one focused physical Android regression test.

## Current readiness

| Area | State |
|---|---|
| Android Editor startup | 🟩🟩 verified on baseline |
| NIM authentication / TLS | 🟩🟩 verified |
| API key persistence | 🟩🟩 verified |
| Mobile NIM UI | 🟩🟩 verified on baseline |
| Nemotron chat | 🟩🟩 verified on baseline |
| Test Connection lifecycle | 🟩🟩 verified on baseline |
| Copy Chat | 🟩🟩 verified on baseline |
| Project/scene/selected-node context | 🟩🟩 code implemented |
| Selected script path/source | 🟩🟩 code implemented |
| Current HEAD CI | 🟩🟩 confirmed by published APK |
| Current HEAD APK | 🟩🟩 available |
| Physical verification of current HEAD | 🟡🟡 REQUIRED NEXT |
| Debugger/errors context | 🟩🟩 code implemented |
| Controlled context assembly | 🟩🟩 code implemented |
| v0.2 readiness | 🟩🟥 partial — physical regression pending |
| Product/release readiness | 🟥🟥 not ready |

## Next gate

1. Run one focused physical Android regression on `6c053080822dd42b2b2fdea08daca13e7510a6d7`.
2. Record actual results for context injection/scopes and preserve the confirmed Safe Core behaviors.
3. If physical regression passes, mark the current checkpoint green.
4. Prepare the v0.2 verification gate, then the v0.2/release package.

## Physical-test protocol

When a new physical test is actually required, provide:

- exact commit;
- exact CI run;
- direct APK link;
- SHA-256;
- minimal test steps;
- expected result;
- clear readiness marker.

Never mark a code-only checkpoint as physically verified.

## Architecture invariant

Keep provider-independent architecture:

`Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`

Do not couple Godot Core directly to NVIDIA APIs.

## Handoff rule

Treat this document as a factual checkpoint. Do not repeat already-confirmed setup or ask the user to retest an older baseline without a concrete reason.

**Current checkpoint: NIM Android baseline GREEN; v0.2 Project Context + debugger + granular context scopes GREEN; current HEAD `6c05308` has a published Android APK; focused physical regression is REQUIRED NEXT; release NOT READY.**
