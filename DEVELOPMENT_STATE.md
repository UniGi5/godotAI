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
**v0.2 — PHYSICAL VERIFICATION PENDING ON FINAL 4.7.2 APK**

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
- Current v0.2 physical regression: 🟩🟩 PASS — user confirmed physical Android test
- v0.2 release lock: 🟡🟡 pending physical verification of final 4.7.2 APK
- Release: 🟡🟡 release engineering pending; final candidate APK is available

## Confirmed Physical Baseline
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- APK: `godot-android-editor-arm64.apk`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`
- Confirmed: launch, API-key persistence, NIM connection, Nemotron response, Test Connection recovery, Copy Chat, mobile UI.

## Current v0.2 Candidate
- Runtime candidate: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Scope: debugger/context formatting; real newline separators.
- CI Run: #188
- Run ID: `37225291853`
- Result: **SUCCESS**
- APK tag: `build-c35fc592b3a2`
- APK size: **192,454,271 bytes**
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk

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
The physical test gate for **Run #188 / build-c35fc592b3a2** has been completed successfully.

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
- Current task: physical-test `build-ccaaebf77531`; if PASS, re-lock v0.2 and proceed to final release engineering.
- Do not create a non-prerelease public release until the final build/regression checks are recorded.

## v0.2 / Release Rules
- Physical PASS on the current candidate → record DEBUG checkpoint, update handoff/roadmap, then proceed to v0.2 release lock.
- Physical regression → keep Safe Core protected, apply smallest targeted fix, rebuild, retest.
- Release packaging starts only after v0.2 lock.
- v0.2 is locked. Release engineering is now the primary path; experimental work remains isolated.

## Handoff Rules
- Never switch away from Godot 4.7.2 stable.
- Never blindly merge/rebase `master`.
- Do not claim physical verification from CI.
- Keep experimental work frozen.
- Every major transition gets a DEBUG checkpoint.
- Current checkpoint: Run #250 PASS with 4.7.2 guard; APK `build-ccaaebf77531` is the only current physical-test candidate.
