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
- CI: **PASS — Run #250**
- Physical package verification: **PENDING — `build-ccaaebf77531`**
- CI version guard: `18783595397c15f69364811af0d04dc2452a1df9`
- v0.2 re-lock: **PENDING**


## DEBUG-v0.2-NIM-CHAT-REWORK-260

- Date: 2026-10-05
- Branch: `fix/p1-nim-mobile-chat-ui`
- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- Branch HEAD packaged: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- CI Run: #260 / Run ID `37341176576`
- Result: **SUCCESS**
- APK tag: `build-24215c0ae9d1`
- APK: `godot-android-editor-arm64.apk`
- Size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk

### Physical status
**PASS — exact APK physically verified.**

### Focused device checklist
- [x] Install exact APK
- [x] Launch Godot Editor
- [x] Open NIM panel
- [x] Test Connection
- [x] Send greeting
- [x] Verify Nemotron response appears
- [x] Verify no silent/stuck response
- [x] Verify ECHO-1..ECHO-5
- [x] Verify physical chat recovery

### Gate
- v0.2 chat regression gate: **PASS**
- Remaining: final reliability/release review; first-attempt HTTP 503 is still an open observation.


## DEBUG checkpoint — 2026-10-05 — physical NIM chat recovery
- Exact APK: `build-24215c0ae9d1`
- CI: #260 / Run ID `37341176576` / SUCCESS
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Physical Android: **PASS** for greeting + 5-step ECHO smoke-test.
- Result: Nemotron responded normally; prior silent-chat regression is cleared.
- Observation: first Test Connection attempt returned HTTP 503, retry succeeded. Track separately before final release decision.
- Investigation: one POST is issued by Test Connection; no duplicate-request cause found. No code change justified yet.
