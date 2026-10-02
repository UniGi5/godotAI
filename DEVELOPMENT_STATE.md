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
**2.3 — Selected node context implementation ready; physical verification pending**

Status:
- 1.1 Provider transport: 🟩🟩
- 1.2 NVIDIA configuration: 🟩🟩
- 1.3 NIM Editor UI: 🟩🟥
- 1.4 Secret storage: 🟩🟥
- 1.5 Chat: 🟩🟥
- 1.6 Runtime/UI event bridge: 🟩🟥
- 1.7 Physical smoke test: 🟩🟩 verified on corrected Android build
- 1.8 First milestone gate: 🟩🟥 partial — NIM chat/context baseline physically verified; streaming/error regression remains
- v0.2: 🟩🟥 PARTIAL — stable NIM chat baseline verified; context expansion/streaming regression remain
- Release: 🟥🟥 NOT READY

## Last verified CI
- Latest successful documented CI: #64 🟩 success
- Latest code fix: `cd8b31cc0e6191967282e4dd0e790a41dbedee19` — chat explicitly uses the verified non-stream baseline
- Diagnostic code commit: 025846eaa556f187035f2f0f56df6171464c0ffc
- Commit: 11e68e28cfc80d7d705e0cccb0a29b96cb8d9cb6
- Build: Android ARM64 release APK
- APK SHA-256: 33332749c987ad64707022008bb898bc641b71d0c92e6629597a7fca2353dbe4
- APK size: 192,421,503 bytes
- Direct release tag: build-11e68e28cfc8
- Direct APK:
  https://github.com/UniGi5/godotAI/releases/download/build-11e68e28cfc8/godot-android-editor-arm64.apk

## Important recent fixes
- Native NIM panel with API key, Test Connection, Send and streaming chat.
- Chat response buffer reset per turn.
- Secret storage compile issues fixed.
- Deferred provider events delivered to the editor/UI thread.
- UI ignores stale events whose request_id does not match the active request.
- EditorNode destroys NIMEditorPanel before AIBridgeRuntime.
- Cross-window handoff state is stored in this file.

## Physical test result — verified NIM chat baseline

Observed on the user's real Android device:
- Android Editor starts normally.
- NVIDIA API key persists across app/project restart.
- A newly created project can use the stored NVIDIA API key.
- NVIDIA NIM connection test succeeds.
- Chat request completes and returns an immediate Nemotron response.
- Nemotron receives editor/project context and identified the project name.
- The verified baseline is the deterministic non-stream request path with thinking disabled.


## Physical test gate — next regression test
A new physical test is required only after CI produces the APK containing the chat-baseline fix `cd8b31cc0e6191967282e4dd0e790a41dbedee19`.

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
The launch/NIM baseline is already physically verified. Before v0.2 packaging:
- selected-node context must be verified on physical Android;
- streaming must be implemented/tested as a separate path;
- invalid-key and network-error behavior must be regression-tested on the current APK;
- context assembly must be documented and stable.

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


## Corrected Android packaging — CI #64

The silent early exit was traced to the release APK being assembled without the main native Godot editor library. SCons had produced the library but the old workflow consumed the wrong packaging path.

Fixes:
- SCons builds release native editor library with `store_release=yes`.
- Gradle uses `generateGodotEditor`.
- Workflow consumes the canonical Gradle APK output.
- CI #64 audit confirms `lib/arm64-v8a/libgodot_android.so` is present.
- Native library size in APK: 168,766,080 bytes.
- APK size: 192,421,503 bytes.
- zipalign and apksigner validation: passed.
- Direct prerelease APK: https://github.com/UniGi5/godotAI/releases/download/build-11e68e28cfc8/godot-android-editor-arm64.apk

The previous 22 MB APK must not be used for physical testing. Physical validation is now required on the corrected 192 MB APK.
