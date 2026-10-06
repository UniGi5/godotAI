# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Canonical checkpoint — 2026-10-06

- Repository: `UniGi5/godotAI`
- Product branch: `fix/p1-nim-mobile-chat-ui`
- Product branch HEAD: `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170`
- Godot baseline: **4.7.2 Stable** — do not switch.
- Architecture: `Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## v0.2 baseline

**VERIFIED / INTEGRATED — PRERELEASE CANDIDATE**

## v0.3 current position

**SCENE ANALYSIS FOUNDATION — CI + PHYSICAL TEST VERIFIED**

### Safe Core
- Engine baseline: 🟢
- Provider architecture: 🟢
- NIM non-stream chat: 🟢
- API-key persistence: 🟢
- Mobile NIM UI: 🟢
- Android ARM64 packaging: 🟢
- Physical NIM chat: 🟢

## Exact fixed APK — PHYSICALLY VERIFIED

- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- Packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- CI #260 / Run ID `37341176576`: **SUCCESS**
- APK: `godot-android-editor-arm64.apk`
- Tag: `build-24215c0ae9d1`
- Size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk

### Physical result
The exact APK was tested on a real Android device:
- NIM panel: PASS
- Nemotron greeting: PASS
- ECHO-1: `NIM CHAT OK`
- ECHO-2: `Nemotron 3 Ultra`
- ECHO-3: `391`
- ECHO-4 project context: PASS
- ECHO-5: `END-OF-TEST`
- Previous **“Connected but silent chat”** regression: **CLEARED**
- Chat response path: **PASS**

## Open reliability observation

First Test Connection attempt again returned **HTTP 503**; retry succeeded and the same APK then passed chat.

Evidence:
- Test Connection issues one visible POST.
- Historical anti-redundant-request protection is present.
- No deterministic duplicate-request cause found.
- 503 is not proven to be a code defect.

**Do not claim 503 fixed. Do not modify working NIM transport/UI solely by guesswork.**

## Stable transport contract — FROZEN

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Preserve the working non-stream path during release review.

## v0.2 context

Implemented:
- project identity/name/path;
- current edited scene;
- selected node name/type/path;
- selected node script path/source;
- 12,000-character script limit + truncation marker;
- debugger/error context;
- granular context scopes;
- provider-independent context assembly.

## Development zones

### SAFE CORE
Protected. Behavior-changing Android/runtime modifications require minimal patch, CI, and a fresh physical test of the exact APK.

### UI TRACK
Mobile UI experiments remain isolated from the release candidate. No keyboard hacks or redesign without real-device evidence.

### DEVELOPMENT TRACK
v0.3 snapshot is integrated, CI-verified and physically tested. Continue implementation on `feat/v0.3-analysis-orchestrator`.

### EXPERIMENTAL
MCP Bridge, streaming replacement and Agent mode may be developed in isolation. Safe Editing/autonomous mutation remain locked until Scene Analysis and reporting are verified.

## Gemini / Superpowers rules

- Read `DEVELOPMENT_STATE.md`, `DEVELOPMENT_ROADMAP.md`, `DEBUG_VERSIONS.md` first.
- Never switch from Godot 4.7.2 Stable.
- Never blindly merge/rebase `master`.
- Never claim physical verification from CI alone.
- Preserve Safe Core.
- Keep UI/Development/Experimental changes isolated.
- Every major transition gets a DEBUG checkpoint.
- If a physical test is required, use only the exact APK named in the current checkpoint.

## Repository integration status — 2026-10-06

- PR #3: **CLOSED / MERGED** (merge commit `04505a3815a539a293cfb6e67ced11662fa40dbf`).
- PR base: `master` at `2a69de75186a28a1503ea9f1d0eb2d28505dbd92`.
- Product/integration divergence merge-base: `165856f82fd01ef34d24a272e224a36ab75d3c01`.
- Product branch was reconciled through controlled file-level synchronization; no blind merge/rebase was used.
- PR #6: **CLOSED / MERGED** into `fix/p1-nim-mobile-chat-ui` with squash merge commit `b9cdd98e0c8f22326858c7cde40bc562d9679433`.
- PR #8: **CLOSED / MERGED** into `fix/p1-nim-mobile-chat-ui` with squash merge commit `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170`.
- Reconciliation CI #151 / Run ID `37405054580`: **SUCCESS**.
- Ruleset-required checks are now represented by the protected CI gate jobs.
- PR #8 required CI: Static, Android ARM64 and Security — **PASS**.
- Android CI #337 / Run ID `37410662064`: **SUCCESS**; exact APK `build-9338f0d6002e`, SHA-256 `05f95288fae9555cc15f5ae4ed44d7e1c7d9fdccc58aca945814380134d53fa8`.
- Physical verification of this exact v0.3 APK: **PASS**.
- Exact physical APK `build-24215c0ae9d1` remains the v0.2 regression baseline; v0.3 snapshot APK `build-9338f0d6002e` is now physically verified.

## Release gate

- Chat regression: **PASS**
- Exact APK physical verification: **PASS**
- First-attempt HTTP 503: **OPEN OBSERVATION**
- v0.2 repository integration: **CLOSED — PR #3 and PR #6 merged**
- Public non-prerelease release: **NOT YET — current artifact remains a prerelease candidate**

### Next action
Exact v0.3 snapshot physical gate passed. Continue on `feat/v0.3-analysis-orchestrator` with provider-independent analysis/reporting; keep stable chat and Safe Editing/autonomous mutation locked.


## v0.3 Physical Verification — 2026-10-06

- Exact APK tested: `build-9338f0d6002e`
- Result: **PASS**
- Nemotron response was available after an initial HTTP 503 and application restart.
- No deterministic code regression identified; transport remains frozen.
- Next: diagnostic/report schema → bounded analysis request → physical verification of resulting runtime.
