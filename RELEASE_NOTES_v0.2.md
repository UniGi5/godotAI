# GodotAI v0.2 — Release Notes / Verification Record

## Status

- Release line: **v0.2**
- v0.2 state: **FINAL PHYSICAL VERIFICATION PENDING**
- Branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- Android target: **ARM64 Editor APK**
- AI provider: NVIDIA NIM
- Model: `nvidia/nemotron-3-ultra-550b-a55b`

## Locked candidate

- Previous locked runtime commit: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Release metadata correction commit: `28d72c9351b0940e754e85654182ee8c1d3f4167`
- Android CI version guard: `18783595397c15f69364811af0d04dc2452a1df9`
- CI run #250: **SUCCESS**
- Final verification APK: `build-ccaaebf77531`
- APK size: **192,454,267 bytes**
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-ccaaebf77531/godot-android-editor-arm64.apk
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

Physical Android regression was **confirmed PASS by the user** for the previous locked candidate. Because version metadata was corrected afterward, the resulting rebuilt APK must pass the focused package/install regression gate before re-lock.

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

1. Rebuild the candidate after the `version.py` correction.
2. Verify the new APK's version metadata and CI integrity; the Android workflow now enforces 4.7.2 Stable.
3. Reconfirm install/launch and focused regression on the new package.
4. Re-lock v0.2.
5. Continue final release engineering.
3. Final install/launch/regression verification.
4. Final release notes and distribution check.
5. Only then publish the non-prerelease release.

## Experimental tracks

MCP Bridge, Agent mode, Safe Editing and streaming replacement remain separate development tracks and must not be mixed into the v0.2 release path.
