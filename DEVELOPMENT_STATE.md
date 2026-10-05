# DEVELOPMENT_STATE.md

## Project Identity
- Repository: `UniGi5/godotAI`
- Active product branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- Product: native Godot Android Editor fork with integrated NVIDIA NIM / Nemotron
- Target: Android ARM64 + Desktop
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## Current Position
**v0.2 — FINAL RELIABILITY REVIEW AFTER PHYSICAL CHAT PASS**

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
- v0.2 release lock: 🟡🟡 **FINAL RELIABILITY REVIEW**
- Release: 🟡🟡 pending final release checklist

## Confirmed Physical Baseline
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- APK: `godot-android-editor-arm64.apk`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`
- Confirmed: launch, API-key persistence, NIM connection, Nemotron response, Test Connection recovery, Copy Chat, mobile UI.

## Current v0.2 Candidate
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

## Safe Transport Contract
Do not change during v0.2 lock:
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
Current focus: v0.2 context verification and diagnostic-quality reporting.

### EXPERIMENTAL
MCP / Agent / Safe Editing remain **FROZEN** until v0.2 Release Lock.

## Physical Test Gate
The active physical gate is the exact packaged candidate **Run #260 / build-24215c0ae9d1**. Run #188 / build-c35fc592b3a2 is historical and superseded.

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

**Physical result has now been reported by the user; this gate is PASS. CI alone is never treated as physical verification.**

## Release engineering
- v0.2 release verification record: `RELEASE_NOTES_v0.2.md`
- Current task: final v0.2 reliability/release consistency review after physical verification of `build-24215c0ae9d1`.
- First-attempt HTTP 503 remains an open observation; no deterministic code cause is proven.
- Do not create a non-prerelease public release until the final checklist is explicitly closed.

## v0.2 / Release Rules
- Physical PASS on the current candidate → record DEBUG checkpoint, update handoff/roadmap, then proceed to v0.2 release lock.
- Physical regression → keep Safe Core protected, apply smallest targeted fix, rebuild, retest.
- Release packaging starts only after v0.2 lock.
- v0.2 lock is reopened by physical regression. Release engineering is paused; experimental MCP / Agent / Safe Editing remain frozen.

## Handoff Rules
- Never switch away from Godot 4.7.2 stable.
- Never blindly merge/rebase `master`.
- Do not claim physical verification from CI.
- Keep experimental work frozen.
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
- Release remains pending final reliability/release review.


## Physical Android verification — 2026-10-05
- Exact APK tested: `build-24215c0ae9d1` (CI #260 / Run ID `37341176576`).
- Chat smoke test: **PASS**.
- Nemotron returned all 5 requested ECHO results, including `NIM CHAT OK`, model identification, `17 × 23 = 391`, project-context phrase, and `END-OF-TEST`.
- Simple greeting also received a normal Nemotron response.
- Therefore the previous physical regression **“Connected but silent chat” is fixed** on the tested APK.
- Initial Test Connection still showed **HTTP 503 on the first attempt**, then connected successfully on retry. Treat this as a separate connection-reliability observation; do not claim it fixed or release-blocking without further evidence.
- Release gate: chat regression gate **PASS**; v0.2 remains in final reliability/release review.
- Investigation: `Test Connection` issues one POST request; historical redundant-request protection is present. NVIDIA's public API docs document 200/202/422/500 for this operation, not 503. No transport change is justified without reproducible evidence tying the 503 to our code.
