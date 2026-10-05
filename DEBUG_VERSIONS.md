# DEBUG_VERSIONS.md — Verification Ledger

## DEBUG-v0.2-CANDIDATE-188

- Date: 2026-10-04
- Branch: `fix/p1-nim-mobile-chat-ui`
- Runtime candidate: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- CI Run: #188
- Run ID: `37225291853`
- Result: **SUCCESS**
- APK tag: `build-c35fc592b3a2`
- APK: `godot-android-editor-arm64.apk`
- Size: 192,454,271 bytes
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk

### Source scope
Debugger/context formatting only. Debugger fields use real newline separators. No NIM transport, TLS, secret-storage or provider-contract changes.

### CI evidence
- Android native editor build: PASS
- Release APK build: PASS
- Runtime payload audit: PASS
- APK validation/signing: PASS
- SHA-256: PASS
- Direct APK publication: PASS

### Physical status
**PASS — PHYSICAL ANDROID TEST CONFIRMED**

CI does not count as physical verification.

### Required device result
- [x] Install
- [x] Launch
- [x] NIM panel
- [x] API-key persistence
- [ ] Test Connection
- [x] Context-aware request
- [x] Project/scene/selection/script/debugger context
- [x] Test Connection regression check
- [x] Copy Chat regression check
- [x] Mobile UI regression check
- [x] Restart/persistence check

### Gate
- v0.2: 🟡 VERSION METADATA REBUILD REQUIRED
- Release: 🟡 RELEASE ENGINEERING PENDING
- Experimental MCP / Agent / Safe Editing: FROZEN

## Physical verification result

User confirmed the Run #188 / `build-c35fc592b3a2` APK passed the required Android physical regression checklist. This supersedes the previous PENDING state.

## Next checkpoint
`DEBUG-v0.2-RELEASE-CANDIDATE` was completed before the release metadata correction; new CI verification is required before re-lock. Next: release engineering.

If regression:
`REWORK` → smallest targeted fix → new CI APK → new physical test.


## DEBUG-v0.2-RELEASE-CANDIDATE

- Physical Android verification: PASS
- CI candidate: #188 / `build-c35fc592b3a2`
- v0.2 release lock: **LOCKED**
- Safe transport contract: unchanged
- Next phase: release engineering


## VERSION-METADATA-REWORK-28D72C9

- Commit: `28d72c9351b0940e754e85654182ee8c1d3f4167`
- Change: restore `version.py` to Godot 4.7.2 Stable (`major=4`, `minor=7`, `patch=2`, `status=stable`, `docs=4.7`).
- CI: **PENDING**
- Physical package verification: **PENDING**
- v0.2 re-lock: **PENDING**
