# ADR-0003: Direct APK Release Asset

## Status

Accepted

## Decision

The current user-facing build output is a raw Android APK attached directly to a GitHub Release.

GitHub Actions artifact ZIPs are not the user-facing delivery mechanism.

## Current target

- Godot Editor
- Android
- ARM64
- Release
- APK

No AAB or unrelated platform binaries are required for the current development loop.

## Rationale

The development loop targets a single Android phone. Direct release assets make the result immediately downloadable and installable.

