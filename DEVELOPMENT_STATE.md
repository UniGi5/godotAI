# DEVELOPMENT_STATE.md

## Project
- Repository: UniGi5/godotAI
- Branch: master
- Product: native Android Godot Editor fork with built-in NVIDIA NIM
- Godot target: 4.7.2 stable
- Provider: NVIDIA NIM / Nemotron 3 Ultra 550B
- Model: nvidia/nemotron-3-ultra-550b-a55b
- Base URL: https://integrate.api.nvidia.com/v1
- Android target: ARM64

## Current position
**1.6 — Runtime/UI event bridge**

Status:
- 1.1 Provider transport: 🟩🟩
- 1.2 NVIDIA configuration: 🟩🟩
- 1.3 NIM Editor UI: 🟩🟥
- 1.4 Secret storage: 🟩🟥
- 1.5 Chat: 🟩🟥
- 1.6 Runtime/UI event bridge: 🟩🟥
- 1.7 Physical smoke test: 🟥🟥
- 1.8 First milestone gate: 🟥🟥
- v0.2: 🟥🟥 NOT READY
- Release: 🟥🟥 NOT READY

## Last verified CI
- Run #56: 🟩 success
- Commit: a8526e6c51c354693f9ae20e65aa25723c888a1e
- Fix: destroy NIM panel before AI runtime.
- Previous run #55: 🟩 success — request-id protection for UI events.

## Important recent fixes
- Native NIM panel with API key, Test Connection, Send and streaming chat.
- Chat response buffer reset per turn.
- Secret storage compile issues fixed.
- Deferred provider events delivered to the editor/UI thread.
- UI ignores stale events whose request_id does not match the active request.
- EditorNode destroys NIMEditorPanel before AIBridgeRuntime.

## Physical test gate
Do NOT mark 1.7 or 1.8 complete without a real Android device.
Required verification:
1. Install APK.
2. Launch Godot Editor.
3. Open NVIDIA NIM panel.
4. Enter/save API key.
5. Test Connection.
6. Verify NIM_OK response.
7. Send a second coding request.
8. Verify streaming.
9. Verify invalid-key/network error handling.

## v0.2 gate
Only after:
BUILD + INSTALL + LAUNCH + NIM REQUEST + RESPONSE on physical Android device.

## Handoff rule for a new chat/window
Read this file and DEVELOPMENT_ROADMAP.md first.
Continue from the numbered current position.
Do not redo completed work.
Do not mark physical testing as complete from CI alone.
Do not prepare release packaging until the 1.8 gate is verified.

## User progress format
Every substantial continuation should end with:
- 📍 POSITION
- 🟩🟩 / 🟩🟥 / 🟥🟥 status
- ➡️ NEXT
- 📱 PHYSICAL TEST
- 🚀 v0.2
- 📦 RELEASE
