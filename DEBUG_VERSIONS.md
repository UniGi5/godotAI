# DEBUG_VERSIONS.md — Verification Ledger

## CANONICAL RELEASE CHECKPOINT — 2026-10-06

- Branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- v0.2 position: **INTEGRATION CLOSED / VERIFIED**
- v0.3 position: **SCENE SNAPSHOT CI + PHYSICAL PASS**
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
- PR #3 integration: **CLOSED / MERGED** (`04505a3815a539a293cfb6e67ced11662fa40dbf`)
- Product reconciliation PR #6: **CLOSED / MERGED** (`b9cdd98e0c8f22326858c7cde40bc562d9679433`)
- Reconciliation CI #151: **SUCCESS**
- MCP / Agent / Safe Editing / streaming replacement: **AVAILABLE FOR ISOLATED DEVELOPMENT; MUTATION FEATURES REMAIN LOCKED**

## v0.3 implementation checkpoint

### DEBUG-v0.3-SNAPSHOT-9338

- Date: 2026-10-06
- Product branch HEAD: `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170`
- PR: #8 — **CLOSED / MERGED**
- CI #337 / Run ID `37410662064`: **SUCCESS**
- APK: `build-9338f0d6002e`
- SHA-256: `05f95288fae9555cc15f5ae4ed44d7e1c7d9fdccc58aca945814380134d53fa8`
- Size: **192,470,651 bytes**
- Scope: bounded provider-independent hierarchy snapshot; 128 nodes / depth 16; no property values; no mutation.
- Physical Android verification: **PASS** — exact APK verified on a real Android device.
- Next branch: `feat/v0.3-analysis-orchestrator` (created from product HEAD).

- Branch: `feat/v0.3-scene-analysis-foundation`
- Commit: `3e3c8b4d39e5540876b851d23af5fc34658a6d14`
- Scope: provider-independent bounded scene snapshot + `scene_analysis` context scope.
- Bounds: 128 nodes, depth 16; hierarchy/node metadata only; no property values yet.
- Stable NIM transport: unchanged.

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

The v0.2 repository integration lock is closed. The v0.3 snapshot candidate is now physically verified. The intermittent HTTP 503/recovery remains a documented non-blocking observation and is not treated as a deterministic application defect.

If a new physical regression appears:
`REWORK` → smallest targeted fix → new CI APK → exact physical retest → new DEBUG checkpoint.

CI success alone never counts as physical verification.


### DEBUG-v0.3-SNAPSHOT-ANDROID-PASS-20261006

- Date: 2026-10-06
- Exact APK: `build-9338f0d6002e`
- CI #337 / Run ID `37410662064`: **SUCCESS**
- SHA-256: `05f95288fae9555cc15f5ae4ed44d7e1c7d9fdccc58aca945814380134d53fa8`
- Physical Android: **PASS**
- Observed: initial HTTP 503 on the same v0.3 build; after application restart, Nemotron response returned normally.
- Classification: **intermittent connection/API reliability observation; no deterministic code cause proven**.
- Development gate: Analysis Orchestrator implementation is active on `feat/v0.3-analysis-orchestrator`.
- CI #174 / PR #9: Static checks passed; Android compile failed only on `Dictionary::operator[]` in `ai_analysis_orchestrator.cpp`.
- Fix `becd02b6`: switch analysis request dictionaries to `Dictionary::set(StringName(...), ...)`.
- Fix `1603ea67`: preserve `Scene analysis complete` terminal status.
- Current Android push run: #360 / run ID `37504553764`, HEAD `1603ea67`, **IN PROGRESS**.
- Physical verification: pending for the resulting exact APK.
