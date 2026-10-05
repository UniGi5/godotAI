# GodotAI v0.2 — Release Notes / Verification Record

## Status

- Release line: **v0.2**
- v0.2 state: **RELEASE LOCKED**
- Branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- Android target: **ARM64 Editor APK**
- AI provider: NVIDIA NIM
- Model: `nvidia/nemotron-3-ultra-550b-a55b`

## Locked candidate

- Runtime commit: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- CI Run: **#188**
- Run ID: `37225291853`
- APK tag: `build-c35fc592b3a2`
- APK: `godot-android-editor-arm64.apk`
- Size: **192,454,271 bytes**
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk

## v0.2 scope

- Project identity context.
- Current edited scene context.
- Selected node context.
- Selected script path/source with 12,000-character limit and truncation marker.
- Debugger/error context.
- Explicit context scopes.
- Debugger fields formatted with real newline separators.

## Verification

CI #188 passed:

- Android native editor build.
- Release APK generation.
- Runtime payload audit.
- APK validation/signing.
- SHA-256 generation.
- Direct APK publication.

Physical Android regression was subsequently **confirmed PASS by the user** for the locked candidate, including the existing NIM/mobile baseline checks and v0.2 context path.

## Safe transport contract

Locked for the v0.2 release candidate:

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

## Protected areas

The v0.2 lock does not permit casual changes to:

- Godot 4.7.2 baseline.
- Provider architecture.
- HTTPS/TLS transport.
- API-key persistence.
- Stable NIM request/response path.
- Existing Test Connection behavior.
- Existing Copy Chat behavior.
- Android packaging pipeline.

Any change to these areas requires a new verification cycle.

## Release gate

v0.2 is locked, but the product is **not yet the final public release**.

Remaining release-engineering work:

1. Final release metadata/versioning.
2. Final release build from the locked candidate.
3. Final install/launch/regression verification.
4. Final release notes and distribution check.
5. Only then publish the non-prerelease release.

## Experimental tracks

MCP Bridge, Agent mode, Safe Editing and streaming replacement remain separate development tracks and must not be mixed into the v0.2 release path.
