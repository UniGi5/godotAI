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
**1.7 — First physical smoke test**

Status:
- 1.1 Provider transport: 🟩🟩
- 1.2 NVIDIA configuration: 🟩🟩
- 1.3 NIM Editor UI: 🟩🟥
- 1.4 Secret storage: 🟩🟥
- 1.5 Chat: 🟩🟥
- 1.6 Runtime/UI event bridge: 🟩🟥
- 1.7 Physical smoke test: 🟥🟥 READY TO TEST
- 1.8 First milestone gate: 🟥🟥
- v0.2: 🟥🟥 NOT READY
- Release: 🟥🟥 NOT READY

## Last verified CI
- Run #58: 🟩 success
- Commit: 4f5028ef9f87447ab71f75bbef6f925f9e63d220
- Build: Android ARM64 release APK
- APK SHA-256: 33332749c987ad64707022008bb898bc641b71d0c92e6629597a7fca2353dbe4
- APK size: 22,273,508 bytes
- Direct release tag: build-4f5028ef9f87
- Direct APK:
  https://github.com/UniGi5/godotAI/releases/download/build-4f5028ef9f87/godot-android-editor-arm64.apk

## Important recent fixes
- Native NIM panel with API key, Test Connection, Send and streaming chat.
- Chat response buffer reset per turn.
- Secret storage compile issues fixed.
- Deferred provider events delivered to the editor/UI thread.
- UI ignores stale events whose request_id does not match the active request.
- EditorNode destroys NIMEditorPanel before AIBridgeRuntime.
- Cross-window handoff state is stored in this file.

## Physical test gate — 1.7
Use exactly the APK from the direct release link above.

Required verification:
1. Install APK on a real ARM64 Android device.
2. Launch Godot Editor.
3. Confirm the editor reaches the main UI without startup crash.
4. Open the NVIDIA NIM panel.
5. Enter and save an NVIDIA API key.
6. Press Test Connection.
7. Verify the response is exactly NIM_OK.
8. Send a second coding request.
9. Verify streamed response arrives progressively.
10. Verify a deliberately invalid API key produces a clear error without crashing.
11. Verify network failure/disconnection produces a clear error without crashing.
12. Close/reopen the editor and verify the stored key remains available through the current local storage implementation.

Record the actual result for each item before marking 1.7 complete.

## v0.2 gate
Only after:
BUILD + INSTALL + LAUNCH + NIM REQUEST + RESPONSE on physical Android device.

Additional first-milestone evidence should include:
- streaming works;
- invalid-key handling works;
- network-error handling works;
- no startup/request crash.

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
