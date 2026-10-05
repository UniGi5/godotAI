# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Canonical checkpoint — 2026-10-05

- Repository: `UniGi5/godotAI`
- Product branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable** — do not switch.
- Architecture: `Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## v0.2 current position

**FINAL RELIABILITY / RELEASE REVIEW**

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
Final v0.2 reliability/release review and documentation consistency.

### EXPERIMENTAL
MCP Bridge, streaming replacement, Agent mode and Safe Editing remain **FROZEN until v0.2 Release Lock**.

## Gemini / Superpowers rules

- Read `DEVELOPMENT_STATE.md`, `DEVELOPMENT_ROADMAP.md`, `DEBUG_VERSIONS.md` first.
- Never switch from Godot 4.7.2 Stable.
- Never blindly merge/rebase `master`.
- Never claim physical verification from CI alone.
- Preserve Safe Core.
- Keep UI/Development/Experimental changes isolated.
- Every major transition gets a DEBUG checkpoint.
- If a physical test is required, use only the exact APK named in the current checkpoint.

## Release gate

- Chat regression: **PASS**
- Exact APK physical verification: **PASS**
- First-attempt HTTP 503: **OPEN OBSERVATION**
- Final v0.2 reliability/release review: **IN PROGRESS**
- Public non-prerelease release: **NOT YET**

### Next action
Complete final repository/release consistency review. Do not unlock MCP/Agent/Safe Editing until the v0.2 release gate is explicitly closed.
