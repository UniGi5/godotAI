# DEBUG_VERSIONS.md — Verification Ledger

## CANONICAL RELEASE CHECKPOINT — 2026-10-05

- Branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- v0.2 position: **RELEASE LOCK CLOSED / PRERELEASE READY**
- Current packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- CI Run: **#260 / Run ID `37341176576` — SUCCESS**
- APK tag: `build-24215c0ae9d1`
- APK: `godot-android-editor-arm64.apk`
- Size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk

### Physical Android result

**PASS — exact APK physically verified.**

- [x] Install exact APK
- [x] Launch Godot Editor
- [x] Open NIM panel
- [x] Test Connection recovery
- [x] Send greeting
- [x] Nemotron response appears
- [x] No silent/stuck response
- [x] ECHO-1..ECHO-5
- [x] Project context response
- [x] Previous “Connected but silent chat” regression cleared

### Reliability observation

- First Test Connection attempt returned **HTTP 503**.
- Retry succeeded and the same APK then passed the full chat smoke test.
- Test Connection currently issues one visible POST.
- Historical anti-redundant-request protection is present.
- No deterministic code cause for the 503 has been proven.

**503 remains OPEN and is not marked fixed. Do not change the working NIM transport by guesswork.**

### Release gate

- v0.2 chat regression: **PASS**
- Exact candidate APK physical verification: **PASS**
- First-attempt HTTP 503: **OPEN OBSERVATION**
- Final reliability/release review: **COMPLETE**
- Public non-prerelease release: **NOT YET — explicit release action required**
- MCP / Agent / Safe Editing / streaming replacement: **FROZEN by release-lock policy**

## Historical checkpoints

### DEBUG-v0.2-CANDIDATE-188

- Date: 2026-10-04
- Runtime candidate: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- CI Run: #188 / Run ID `37225291853`
- APK tag: `build-c35fc592b3a2`
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`
- Historical physical result: PASS.
- This checkpoint is **superseded** by the current #260 candidate.

### VERSION-METADATA-REWORK-28D72C9

- Commit: `28d72c9351b0940e754e85654182ee8c1d3f4167`
- Change: restore `version.py` to Godot 4.7.2 Stable.
- CI: **PASS — Run #250**
- Physical package verification at that time: **PENDING** for `build-ccaaebf77531`.
- This state was superseded by the subsequent NIM chat rework.

### DEBUG-v0.2-NIM-CHAT-REWORK-260

- Date: 2026-10-05
- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- Packaged checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- CI #260: **SUCCESS**
- APK: `build-24215c0ae9d1`
- Physical Android: **PASS**
- Focus: recovery from the previous silent-chat regression.
- First-attempt 503 remained an open reliability observation.

## Release handling rule

The v0.2 release lock is now closed after exact physical PASS. The intermittent first-attempt 503 remains a documented non-blocking observation and is not treated as fixed.

If a new physical regression appears:
`REWORK` → smallest targeted fix → new CI APK → exact physical retest → new DEBUG checkpoint.

CI success alone never counts as physical verification.
