#!/usr/bin/env bash
set -euo pipefail

APK="${1:-}"
PACKAGE_ID="${PACKAGE_ID:-org.godotengine.editor.v4.release}"
LOG_FILE="${2:-godot-ai-bridge-startup-$(date +%Y%m%d-%H%M%S).log}"

if [[ -z "$APK" ]]; then
  echo "Usage: $0 path/to/godot-android-editor-arm64.apk [log_file]" >&2
  exit 2
fi

if [[ ! -f "$APK" ]]; then
  echo "APK not found: $APK" >&2
  exit 2
fi

if ! command -v adb >/dev/null 2>&1; then
  echo "adb is required but was not found in PATH." >&2
  exit 2
fi

echo "Waiting for Android device..."
adb wait-for-device >/dev/null

echo "Installing: $APK"
adb install -r -d "$APK"

echo "Clearing previous logcat..."
adb logcat -c

echo "Launching package: $PACKAGE_ID"
if ! adb shell monkey -p "$PACKAGE_ID" 1 >/dev/null 2>&1; then
  echo "Failed to send launch intent for $PACKAGE_ID." >&2
  exit 1
fi

sleep 8

PID="$(adb shell pidof "$PACKAGE_ID" 2>/dev/null | tr -d "\r" || true)"
if [[ -n "$PID" ]]; then
  echo "Process is running. PID: $PID"
else
  echo "No running process found for $PACKAGE_ID."
fi

echo "Collecting logcat -> $LOG_FILE"
adb logcat -d > "$LOG_FILE"

echo
echo "Potential crash indicators:"
grep -E "FATAL EXCEPTION|AndroidRuntime|SIGSEGV|SIGABRT|Abort message|Fatal signal|libgodot|Godot Engine|godot" "$LOG_FILE" || true

echo
echo "Diagnostic log saved to: $LOG_FILE"
