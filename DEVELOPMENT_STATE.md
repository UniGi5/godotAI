# DEVELOPMENT_STATE.md

## Project Identity
- Repository: `UniGi5/godotAI`
- Active product branch: `fix/p1-nim-mobile-chat-ui` (stable product baseline)
- Active v0.3 development branch: `feat/v0.3-analysis-orchestrator`
- Godot baseline: **4.7.2 Stable**
- Product: native Godot Android Editor fork with integrated NVIDIA NIM / Nemotron
- Target: Android ARM64 + Desktop
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## Current Position
**v0.3 — SCENE ANALYSIS FOUNDATION — PHYSICAL VERIFICATION PASSED**

### Safe Core
- Provider transport: 🟩🟩
- NVIDIA configuration: 🟩🟩
- NIM mobile UI baseline: 🟩🟩
- API-key persistence: 🟩🟩
- Chat: 🟩🟩
- Runtime/UI bridge: 🟩🟩
- Android packaging pipeline: 🟩🟩

### v0.2 Context
- Project identity: 🟩🟩
- Current scene: 🟩🟩
- Selected node: 🟩🟩
- Selected script path/source: 🟩🟩
- Script source limit + truncation marker: 🟩🟩
- Debugger/error context: 🟩🟩
- Controlled context scopes: 🟩🟩

### Verification
- Previous physical baseline: 🟩🟩 confirmed at `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- v0.2 candidate CI: 🟩🟩 confirmed
- Current v0.2 physical chat regression: 🟢🟢 **CLEARED — exact fixed APK passed Android chat smoke test**
- First Test Connection 503: 🟡🟡 **OPEN RELIABILITY OBSERVATION — retry succeeds; no code cause proven**
- v0.2 release lock: 🟢🟢 **CLOSED — physical PASS + repository integration complete**
- Release: 🟡🟡 **PRERELEASE VERIFIED — v0.3 snapshot physically verified; public non-prerelease release not yet published**

## Confirmed Physical Baseline
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- APK: `godot-android-editor-arm64.apk`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`
- Confirmed: launch, API-key persistence, NIM connection, Nemotron response, Test Connection recovery, Copy Chat, mobile UI.

## Verified v0.2 Baseline
- Packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- CI Run: #260
- Run ID: `37341176576`
- Result: **SUCCESS**
- APK tag: `build-24215c0ae9d1`
- APK size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk
- Physical Android verification: **PASS** — exact APK passed greeting + ECHO-1..ECHO-5.

CI job verified:
- Build native Android editor libraries: success
- Build release APK: success
- Runtime payload audit: success
- APK validation: success
- SHA-256 generation: success
- Direct APK publication: success

## Current v0.3 Packaged Candidate
- Branch HEAD: `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170`
- CI Run: #337 / Run ID `37410662064` — **SUCCESS**
- APK tag: `build-9338f0d6002e`
- APK: `godot-android-editor-arm64.apk`
- APK size: **192,470,651 bytes**
- SHA-256: `05f95288fae9555cc15f5ae4ed44d7e1c7d9fdccc58aca945814380134d53fa8`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-9338f0d6002e/godot-android-editor-arm64.apk
- Scope: bounded provider-independent scene snapshot; 128 nodes / depth 16; hierarchy/node metadata only; no property mutation.
- Physical Android verification: **PASS** — exact APK was tested on a real Android device; NIM chat responded after the transient connection failure.

## Safe Transport Contract
Preserve during v0.3 analysis work unless reproducible evidence justifies a change:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

## Development Zones
### SAFE CORE
Protected. Changes require minimal patch, CI, regression review and physical Android validation when the package changes.

### UI TRACK
Experimental mobile UI improvements remain isolated from Safe Core until physically verified. Do not add Android keyboard hacks without observing real device behavior first.

### DEVELOPMENT TRACK
Current focus: v0.3 Analysis Orchestrator / diagnostic reporting; keep Safe Editing/autonomous mutation locked.

### EXPERIMENTAL
MCP / Agent / Safe Editing are available for isolated development; Safe Editing/autonomous mutation remain locked until Scene Analysis is verified.

## Physical Test Gate
The exact v0.3 packaged candidate **Run #337 / build-9338f0d6002e** is physically verified and becomes the v0.3 analysis baseline. The previously verified v0.2 candidate remains the regression baseline.

Minimum checklist:
1. Install APK.
2. Launch Godot Editor.
3. Open NIM panel.
4. Confirm API key persistence.
5. Test NIM connection.
6. Send a context-aware request.
7. Verify project/scene/selection/script/debugger context is represented correctly.
8. Confirm no regression in Test Connection, Copy Chat and mobile UI.
9. Restart editor and confirm persistence.

**Physical result for this exact v0.3 APK: PASS. The first observed HTTP 503 later recovered on the same APK after restart. This is treated as an intermittent connection reliability observation, not a proven application regression.**

## Release engineering
- v0.2 release verification record: `RELEASE_NOTES_v0.2.md`
- Repository integration: **CLOSED** via PR #3 + PR #6 + PR #8.
- PR #3 merge commit: `04505a3815a539a293cfb6e67ced11662fa40dbf`.
- PR #6 squash commit: `b9cdd98e0c8f22326858c7cde40bc562d9679433`.
- Product branch HEAD after v0.3 snapshot integration: `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170`.
- v0.3 foundation branch: `feat/v0.3-scene-analysis-foundation` — integrated via PR #8.
- Next development branch: `feat/v0.3-analysis-orchestrator` — created from product HEAD for analysis/reporting work.
- v0.3 snapshot implementation commit: `3e3c8b4d39e5540876b851d23af5fc34658a6d14`.
- v0.3 snapshot integration commit: `9338f0d6002ecf2d2c24bac8f1e6b59ee2660170` (PR #8, squash; CI #337 SUCCESS).
- First-attempt HTTP 503 remains an open observation; no deterministic code cause is proven.
- Do not publish a public non-prerelease release until a release-specific checklist is completed; the current prerelease artifact remains the verified physical candidate.

## v0.3 / Release Rules
- The v0.2 physical PASS remains the protected baseline; its integration lock is closed.
- v0.3 snapshot CI is **PASS** and exact APK `build-9338f0d6002e` is **physically verified**.
- Physical regression → keep Safe Core protected, apply smallest targeted fix, rebuild, retest.
- The previously physically verified v0.2 APK remains the protected regression baseline; future v0.3 packaged-runtime changes require CI and fresh physical verification of the exact resulting APK.
- Keep Safe Editing/autonomous mutation locked. Do not advance to mutation before Scene Analysis/reporting is physically validated.

## Handoff Rules
- Never switch away from Godot 4.7.2 stable.
- Never blindly merge/rebase `master`.
- Do not claim physical verification from CI.
- Keep Safe Editing/autonomous mutation locked; isolated analysis work is permitted.
- Every major transition gets a DEBUG checkpoint.
- Regression checkpoint: final APK `build-ccaaebf77531` physically failed chat smoke test. Fix commits: `959ba1cf7983d705645bd4a4d88213efdd62afa9`, `f3dce5fddbcc41de0c193d6cabf2b00f2b9d17b3`, `7a4600e8b8a5b00b268f1d447fd16cfdbf6afc2b`. CI #260 is the current Android packaging verification run; exact APK for current branch HEAD is `build-24215c0ae9d1`.


## Exact fixed APK gate — 2026-10-05
- Packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- Branch HEAD: `b4b0dad71cbd79ee29fd0fd3144751b34cc89c2d` (documentation-only release reconciliation after the packaged runtime)
- Runtime fixes included: `959ba1c`, `f3dce5f`, `7a4600e`
- Android CI Run: #260 / Run ID `37341176576` — **SUCCESS**
- APK: `godot-android-editor-arm64.apk`
- APK size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk
- Physical Android status: **PASS** — exact APK passed greeting + ECHO-1..ECHO-5 smoke test.
- v0.2 release lock is closed; prerelease artifact remains the verified candidate.


## Physical Android verification — 2026-10-05
- Exact APK tested: `build-24215c0ae9d1` (CI #260 / Run ID `37341176576`).
- Chat smoke test: **PASS**.
- Nemotron returned all 5 requested ECHO results, including `NIM CHAT OK`, model identification, `17 × 23 = 391`, project-context phrase, and `END-OF-TEST`.
- Simple greeting also received a normal Nemotron response.
- Therefore the previous physical regression **“Connected but silent chat” is fixed** on the tested APK.
- Initial Test Connection still showed **HTTP 503 on the first attempt**, then connected successfully on retry. Treat this as a separate connection-reliability observation; do not claim it fixed or release-blocking without further evidence.
- Release gate: v0.2 integration is **CLOSED**; v0.3 snapshot foundation is **CI VERIFIED** and awaits exact-APK physical verification.
- Investigation: `Test Connection` issues one POST request; historical redundant-request protection is present. NVIDIA's public API docs document 200/202/422/500 for this operation, not 503. No transport change is justified without reproducible evidence tying the 503 to our code.


## v0.3 Physical Android Verification — 2026-10-06

- Exact APK: `build-9338f0d6002e`
- CI: #337 / Run ID `37410662064` — **SUCCESS**
- SHA-256: `05f95288fae9555cc15f5ae4ed44d7e1c7d9fdccc58aca945814380134d53fa8`
- Physical result: **PASS**
- Same exact APK recovered after an initial HTTP 503 and application restart; Nemotron response was available afterward.
- 503 remains **non-blocking / not reproduced as a deterministic code defect**.
- Analysis orchestrator implementation is active on `feat/v0.3-analysis-orchestrator`.
- Latest development commits: `eb6ea13e`, `e778becf`.
- Scene snapshot now includes a bounded diagnostic property subset (process mode/priority, unique-name flag, optional editor description); arbitrary properties remain excluded.
