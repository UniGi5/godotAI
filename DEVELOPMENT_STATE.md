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
**1.7 — First physical smoke test / corrected APK ready**

Status:
- 1.1 Provider transport: 🟩🟩
- 1.2 NVIDIA configuration: 🟩🟩
- 1.3 NIM Editor UI: 🟩🟥
- 1.4 Secret storage: 🟩🟥
- 1.5 Chat: 🟩🟥
- 1.6 Runtime/UI event bridge: 🟩🟥
- 1.7 Physical smoke test: 🟥🟥 BLOCKED — previous APK failure diagnosed; corrected APK ready for physical retest
- 1.8 First milestone gate: 🟥🟥
- v0.2: 🟥🟥 NOT READY
- Release: 🟥🟥 NOT READY

## Last verified CI
- Latest successful CI: #64 🟩 success
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

## Physical test result — 1.7

Observed on the user's real Android device:
- APK installed successfully.
- APK size was approximately 22 MB.
- Tapping the launcher icon caused the application to immediately close/minimize.
- No visible crash dialog or on-screen error appeared.
- This is classified as **silent/clean early exit — diagnostic required**; it is not treated as a proven crash.

## Physical test gate — 1.7
Use the new diagnostic APK produced from commit `025846eaa556f187035f2f0f56df6171464c0ffc` or its later documentation-only descendant. Do not reuse the old #58 APK for diagnosis.

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
