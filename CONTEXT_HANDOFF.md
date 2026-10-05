# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Canonical checkpoint
- Repository: `UniGi5/godotAI`
- Product branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable** — do not switch.
- Product: native Godot Editor fork with integrated NVIDIA NIM / Nemotron.
- Architecture: `Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## Stable physical baseline — VERIFIED
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI #156 / Run ID `37057401793`
- APK SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`
- Confirmed: launch, NIM connection, API-key persistence, Nemotron response, Test Connection recovery, Copy Chat, mobile UI and project context.

## v0.2 RELEASE CANDIDATE — REGRESSION REWORK REQUIRED
- Runtime candidate: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Change: debugger/context fields use real newline separators.
- Scope: context/diagnostic formatting only.
- No NIM transport, TLS, secret-storage or provider-contract change.
- CI #188 / Run ID `37225291853`: **SUCCESS**
- APK tag: `build-c35fc592b3a2`
- APK size: **192,454,271 bytes**
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk
- Physical status: **FAIL — final `build-ccaaebf77531` showed HTTP 503 during connection check and then silent chat response.**

## v0.2 context implemented
- project identity/name/path;
- current edited scene;
- selected node name/type/path;
- selected node script path/source;
- 12,000-character script limit with explicit truncation marker;
- debugger/error context;
- granular context scopes;
- provider-independent context assembly.

## Safe transport contract — FROZEN
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Do not replace this contract during v0.2 verification.

## Development zones
### SAFE CORE
Protected: engine baseline, provider architecture, HTTPS/TLS, key persistence, stable NIM path, Test Connection, Copy Chat, Android packaging.

### UI TRACK
`ui/p1-chat-ux` remains isolated until its own CI + physical verification. Do not add Android keyboard hacks before observing real device behavior.

### DEVELOPMENT TRACK
Current: v0.2 context verification and diagnostic-quality reporting.

### EXPERIMENTAL
MCP Bridge, streaming replacement, Agent mode and Safe Editing are **FROZEN until v0.2 Release Lock**.

## Physical test checklist — Run #188
1. Install APK.
2. Launch editor.
3. Open NIM panel.
4. Confirm API-key persistence.
5. Test NIM connection.
6. Send context-aware request.
7. Verify project/scene/selection/script/debugger context.
8. Confirm Test Connection, Copy Chat and mobile UI have no regression.
9. Restart editor and confirm persistence.

## Gate policy

**Current transition:** the physical gate for Run #188 / `build-c35fc592b3a2` is PASS. Release engineering found a version metadata blocker (`version.py` was 4.8.0-dev); commit `28d72c9` restores 4.7.2 Stable. Run #250 produced the final verification candidate. The Android workflow now fails fast unless `version.py` is exactly 4.7.2 Stable.
- Physical PASS → recorded in `DEBUG_VERSIONS.md`; next step is `DEBUG-v0.2-RELEASE-CANDIDATE`, then v0.2 lock.
- Regression → mark REWORK, smallest targeted fix, new CI APK, new physical test.
- Release packaging only after v0.2 lock.
- MCP / Agent / Safe Editing remain isolated from release engineering and require a separate development track.

## Release engineering
- Verification record: `RELEASE_NOTES_v0.2.md`
- v0.2 release lock is **REOPENED** due to physical chat regression; release engineering is paused.
- Do not turn the existing prerelease build into a public release until final release checks pass.

## Gemini rules
- Read `DEVELOPMENT_STATE.md`, `DEVELOPMENT_ROADMAP.md`, `DEBUG_VERSIONS.md` first.
- Never switch Godot version.
- Never blindly merge/rebase master.
- Never claim physical verification from CI.
- Preserve Safe Core.
- Keep UI/Development/Experimental changes isolated.
- Every major transition gets a DEBUG checkpoint.

## Current status
- SAFE CORE: 🟢
- v0.2 candidate: 🔴 **PHYSICAL REGRESSION — CHAT RESPONSE SILENCE**
- ANDROID TEST: 🔴 **REGRESSION CONFIRMED ON `build-ccaaebf77531`**
- v0.2 RELEASE LOCK: 🟡 **FINAL RELIABILITY REVIEW**
- RELEASE: 🟡 pending final 503 review and release checklist


## Regression checkpoint — 2026-10-05
- Physical report: Test Connection initially returned HTTP 503, then UI showed Connected; sending a simple greeting produced no Nemotron answer.
- Android Debugger > Errors: empty.
- Output: only Debug adapter server port 6006 and GDScript language server port 6005.
- Fixes applied: `959ba1c` exposes malformed/empty non-stream responses; `f3dce5f` preserves provider reasoning flag into UI; `7a4600e` rejects empty non-stream content explicitly.
- CI #260 / Run ID `37341176576`: **SUCCESS**.
- Exact current branch HEAD APK: `build-24215c0ae9d1`.
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`.
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk
- Physical status: **PASS** — greeting + ECHO-1..ECHO-5 verified on the exact APK.
- Remaining gate: review the intermittent first-attempt HTTP 503 before final v0.2 release lock.


## Exact fixed APK checkpoint — 2026-10-05
The runtime fixes `959ba1c`, `f3dce5f` and `7a4600e` are now packaged in the current branch HEAD build. CI validates the APK structurally/signature-wise, but this is not physical verification. The only remaining v0.2 gate is the physical Android smoke test of `build-24215c0ae9d1`.


## Physical Android verification — 2026-10-05
- Exact APK `build-24215c0ae9d1` physically tested by the user.
- Greeting: **PASS** — Nemotron responded with project identity.
- ECHO smoke-test: **PASS** — all five requested outputs returned correctly.
- This confirms the previous silent-chat regression is resolved in the physical Android build.
- Separate observation: first Test Connection attempt again returned HTTP 503; retry connected and chat worked. Keep this as an open reliability observation, not as a proven code defect yet.
- Investigation checkpoint: current `Test Connection` performs one visible POST transaction; the historical anti-redundant-request fix remains present. NVIDIA's public LLM API documentation lists 200/202/422/500 for the chat-completions operation and does not document 503 as a normal API response. Therefore no transport/UI code change is justified yet. Treat the observed first-attempt 503 as an unresolved upstream/gateway reliability observation.
- Next gate: final v0.2 reliability/release review. No experimental MCP/Agent work until the release gate is closed.
