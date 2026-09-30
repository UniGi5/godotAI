# Android Runtime Diagnostics

This repository currently produces the Godot Editor as an ARM64 Android APK.

A launch crash must be investigated from runtime evidence, not inferred from build success.

## Expected development package

When CI builds without a release signing keystore, the Gradle configuration adds the release suffix:

```
org.godotengine.editor.v4.release
```

If a real release signing configuration is supplied later, verify the final application ID from the generated APK instead of assuming the suffix.

## Manual diagnosis

Connect the Android phone with USB debugging enabled.

Run:

```
adb devices
adb install -r -d path/to/godot-android-editor-arm64.apk
adb logcat -c
adb shell monkey -p org.godotengine.editor.v4.release 1
adb logcat -d > godot-ai-bridge-startup.log
```

Useful focused extraction:

```
adb logcat -d | grep -E "FATAL EXCEPTION|AndroidRuntime|SIGSEGV|SIGABRT|libgodot|godot"
```

Do not paste API keys, authorization headers, tokens, or unrelated private data into project issues or logs.

## Automated helper

Use:

```
tools/android/diagnose_editor_startup.sh path/to/godot-android-editor-arm64.apk
```

The helper:

1. checks that `adb` is available;
2. installs the APK;
3. clears old log output;
4. starts the expected release package;
5. waits briefly for startup;
6. reports whether a process is present;
7. writes a timestamped log file locally;
8. prints likely crash indicators.

The helper does not upload diagnostics anywhere.

## Classification

Use evidence to classify the failure as:

- installation/package problem;
- ABI/native library problem;
- renderer initialization;
- Android activity/lifecycle;
- release configuration;
- engine initialization;
- editor initialization;
- AI Bridge initialization;
- other runtime failure.

The first AI Bridge code slice is deliberately not activated at startup, so an early crash occurring before the bridge is registered should be treated as an engine/Android baseline problem.

## Regression rule

Once the crash is understood, add the narrowest regression check possible and keep build, install, launch, and feature smoke tests as separate signals.
