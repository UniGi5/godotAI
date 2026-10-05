# DEVELOPMENT_STATE.md — Controlled Baseline / v0.2 Governance

## 0. Audit Identity
- Audit date: 2026-10-05
- Repository: `UniGi5/godotAI`
- Controlled development branch: `development/controlled-baseline`
- Product: official Godot Engine fork with integrated NVIDIA NIM / Nemotron
- Target product milestone: v0.2 Candidate
- Android target: ARM64
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`

## 1. ENGINE BASELINE — VERIFIED

### Target
**Godot 4.7.2 Stable**

- Upstream tag: `4.7.2-stable`
- Upstream tag target commit: `ed1daf0bf001b61586d9930840f2f1394092c079`
- Verified upstream tag → commit mapping: PASS
- Verified commit signature: PASS
- Verified fork commit exists at the same SHA: PASS

### Corrected branch root
`development/controlled-baseline` was previously contaminated by the 4.8-dev source line.

Previous incorrect state:
- Previous branch HEAD: `952c9c494ba74c1df2a6c5c7a2e3c39f1a284d1d`
- Previous `version.py`: 4.8.0-dev
- Previous branch did not have `ed1daf0bf001b61586d9930840f2f1394092c079` as its merge base.

Remediation:
- Previous controlled-baseline HEAD was preserved in:
  `archive/controlled-baseline-4.8-dev-2026-10-04`
- `development/controlled-baseline` was force-reset directly to:
  `ed1daf0bf001b61586d9930840f2f1394092c079`
- The branch therefore has a verified 4.7.2 Stable engine root.
- Documentation commits added after this point are governance commits only; they must not be confused with the engine baseline commit.

### version.py verification
Expected and verified source:
```
major = 4
minor = 7
patch = 2
status = "stable"
docs = "4.7"
```

**Acceptance rule:** changing only `version.py` is never sufficient to establish the 4.7.2 baseline.

## 2. SAFE CORE — PROTECTED

The following NIM transport contract is frozen through the v0.2 release lock:

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Protected areas:
- HTTPS/TLS transport
- NvidiaProvider
- AI Orchestrator / provider routing
- API-key persistence
- verified non-stream request path
- Android packaging/build contract

Any Safe Core modification requires:
1. minimal targeted patch;
2. CI success;
3. regression review;
4. physical Android validation when runtime/package behavior changes.

## 3. DEVELOPMENT ZONES

### ENGINE BASELINE
🟩🟩 VERIFIED

### DEVELOPMENT BASE
🟩🟩 ESTABLISHED

The branch root is the exact upstream Godot 4.7.2 Stable commit. No 4.8-dev source is permitted on this branch.

### SAFE CORE
🟩🟩 PROTECTED

### UI TRACK
🟩🟩 FINAL STATE PORTED / CI VALIDATED

The final mobile NIM UI state is intentionally included in the controlled baseline and is protected from experimental MCP/Agent work.

### EXPERIMENTAL
🟥🟥 FROZEN

The following stay frozen until the v0.2 release lock:
- `exp/*`
- MCP
- Autonomous Agents
- Safe Editing / agent execution layers

## 4. TASK BACKLOG — v0.2

### Step 0 — Clean 4.7.2 Stable baseline
🟩🟩 COMPLETE

Evidence:
- upstream tag `4.7.2-stable` → `ed1daf0bf001b61586d9930840f2f1394092c079`
- controlled branch reset directly to that commit
- `version.py` verified as 4.7.2 stable
- former 4.8-dev branch preserved as archive

### Step 1-A — Dependency audit for Safe Core/context transplant
🟩🟩 COMPLETE

Finding:
- The clean 4.7.2 baseline does not contain `editor/ai_bridge/`.
- The first requested context commit `6b7c7e558e4809ec1532013174d5b16bdd445447` modifies existing AI Bridge files and therefore cannot be cherry-picked independently.
- Its direct parent chain reaches the AI Bridge foundation beginning at `c37a1e52471696085fd03e7fc4386964275c2643`, whose parent is `383e035d9e442f2e2348ab55a04653c2599fc30c` on the old development line.
- The old development line itself diverges from 4.7.2 Stable, so blindly importing that ancestry would reintroduce the baseline problem.

### Step 1-B — Controlled AI Bridge foundation port
🟩🟩 COMPLETE

Goal:
- Port only the required project-specific AI Bridge/NIM foundation onto the verified 4.7.2 root.
- Do not merge/rebase the old 4.8-dev line.
- Establish the minimum foundation needed for the six approved context commits.
- Validate source compatibility before adding context behavior.

Foundation evidence:
- `c37a1e52471696085fd03e7fc4386964275c2643` — provider-neutral AI Bridge contracts.
- The AI Bridge path currently contains 34 project files at the reference implementation.
- NIM integration also requires selected editor lifecycle/build integration commits; these must be ported deliberately rather than inherited from the 4.8-dev ancestry.

Promotion evidence:
- controlled 4.7.2 compatibility fixes applied without importing old 4.8-dev history;
- Android build run #215 succeeded after the foundation compatibility fixes;
- the complete project-specific bridge/runtime/context/UI layer was then ported from the previously physical-verified final state, preserving the current transport contract;
- Android build run #218 succeeded for the resulting product state.

### Step 1-C — Approved AI/context commits
🟩🟩 COMPLETE — FINAL STATE PORTED

Approved context commits, each verified to exist in the repository:
- `6b7c7e558e4809ec1532013174d5b16bdd445447` — project identity
- `96f6237853179a4153f0f7f527949cb8f02e0b42` — project context string fixes
- `d6ef7c89241d30e528ced66ce1e87d9851da222e` — current scene context
- `17be11cf31664181f7dcf5cc3e3b12926eb7ae40` — current scene formatting/injection
- `489a99ed6e92a11d0c3c792239ab890ffae620f5` — selected node context
- `3079a2b013213deba0376372fb6bba2c7ca4a010` — selected node API fix

Promotion evidence:
- the net result of all six approved context changes is present in the controlled branch;
- project identity, project path, current edited scene, scene formatting, selected node context, and selected-node API compatibility are present;
- these changes were applied as a controlled final-state port rather than replaying the old branch ancestry;
- the v0.2 NIM transport contract remains unchanged.

### Step 2 — Mobile chat UI transplant
🟩🟩 COMPLETE — FINAL STATE PORTED

Approved UI commits:
- `07f5454c0f5a6420def7a2c56d82f25bc9fc6d69`
- `eeeb6b0858205b158f3c433096950fab9d8433c1`
- `3cc9cfdb22935d0859aeef0948a6d616e168019a`
- `424c1789b0a0e24c7eb1dccb882c7ed197d647ad`
- `2c065277d76fd4ee041b6a3e6527c02331330dbb`
- `679425959764caa2966b697a6dd1ee30b7d5eedc`
- `5908d16db5a42d739ae2fb8780bfb7c9b2ccb762`

Promotion evidence:
- mobile NIM panel, fixed test state, copy-chat, retry and stop behavior from the previously physical-verified final state is present;
- NIM panel is attached to the EditorNode lifecycle;
- experimental MCP/Agent work remains frozen.

### Step 3 — Android CI package
🟩🟩 COMPLETE — CANDIDATE PACKAGE GENERATED

Evidence:
- CI run #86 / Run ID `37241554466`
- head: `46ba6a621007aefc3c4a8f649230b680246749ac`
- Android Editor ARM64 job: SUCCESS
- GitHub artifact: `android-editor`
- extracted installable APK: `godot-android-editor-arm64-46ba6a621.apk`
- APK size: 179,514,605 bytes
- Run #90 / Run ID `37245928600` at controlled HEAD `4e2126a3ef0024e1865d213ea0c85ec2d9dfcfa6` — SUCCESS
- Android Editor ARM64 job: SUCCESS
- Direct artifact: `android-editor-arm64-apk` (artifact ID `11318848305`)
- Published APK filename: `godot-android-editor-arm64.apk`
- APK size: 179,514,605 bytes
- APK SHA-256: `63db6fdd7337eef282cfa9c2c4fd66c7f6d99563dac92cc35d84417f0a204dfe`
- APK archive integrity: PASS

Run #86 remains a prior successful product-code build checkpoint; run #90 proves the direct APK-only publication path end-to-end.

### Step 4 — Physical Android validation
🟨🟨 READY FOR PHYSICAL TEST

Use the exact APK published by CI run #90 from controlled HEAD `4e2126a3ef0024e1865d213ea0c85ec2d9dfcfa6`. The product-code checkpoint remains `46ba6a621007aefc3c4a8f649230b680246749ac`; the four commits after it are workflow/documentation-only.

Marker:
**READY FOR PHYSICAL TEST**

Current package evidence:
- source HEAD: `4e2126a3ef0024e1865d213ea0c85ec2d9dfcfa6`
- product-code checkpoint: `46ba6a621007aefc3c4a8f649230b680246749ac`
- run: #90 / `37245928600`
- direct artifact: `android-editor-arm64-apk` / `11318848305`
- APK SHA-256: `63db6fdd7337eef282cfa9c2c4fd66c7f6d99563dac92cc35d84417f0a204dfe`

CI success is not physical verification.

### Step 5 — v0.2 Candidate Lock
🟥🟥 QUEUED

Required before lock:
- current candidate physically passes;
- Safe Core remains unchanged or separately revalidated;
- mobile chat behavior is stable;
- context behavior is verified;
- no experimental zone has leaked into the release candidate.

## 5. GIT BASELINE VERIFICATION ALGORITHM

Run conceptually in this order:

1. Resolve upstream tag:
   `godotengine/godot:4.7.2-stable`
2. Confirm tag resolves to:
   `ed1daf0bf001b61586d9930840f2f1394092c079`
3. Confirm the same commit exists in `UniGi5/godotAI`.
4. Read `version.py` at the target commit and require:
   4.7.2 + `status="stable"`.
5. Resolve `development/controlled-baseline` and require its root commit to be the exact stable SHA before governance commits.
6. Check branch ancestry/compare against the stable SHA; a control baseline must not be based on the 4.8-dev line.
7. Read `version.py` on the controlled branch; require 4.7.2 stable.
8. Record any documentation-only commits separately from the engine baseline SHA.
9. Preserve any displaced branch tip in a named archive ref before force-moving a control branch.
10. Only after these checks begin Step 1 cherry-picks.

## 6. PHYSICAL TEST / PACKAGE RULES

Current state:
- A behavior-changing Android candidate is published from source HEAD `4e2126a3ef0024e1865d213ea0c85ec2d9dfcfa6`; product code is unchanged since checkpoint `46ba6a621007aefc3c4a8f649230b680246749ac`.
- **READY FOR PHYSICAL TEST: ACTIVE**
- Package: `godot-android-editor-arm64.apk`
- APK SHA-256: `63db6fdd7337eef282cfa9c2c4fd66c7f6d99563dac92cc35d84417f0a204dfe`
- CI run: #90 / `37245928600`
- Direct artifact: `android-editor-arm64-apk` / `11318848305`
- No physical result has been recorded yet.

## 7. RELEASE READINESS

- v0.2 Candidate: 🟡🟡 HOLD
- Release: 🟥🟥 NOT READY

Release packaging is prohibited until:
1. Step 1 and Step 2 are integrated and validated;
2. Step 3 produces the candidate APK;
3. Step 4 is a real-device PASS;
4. Step 5 locks v0.2.

## 8. HANDOFF RULE

For every substantial continuation, finish with:
- 📍 POSITION
- 🟩🟩 / 🟩🟥 / 🟥🟥 status
- ➡️ NEXT
- 📱 PHYSICAL TEST
- 🚀 v0.2
- 📦 RELEASE

Never:
- switch the engine baseline to Godot master/4.8-dev;
- modify only `version.py` to fake the version;
- blindly merge/rebase the former product branch;
- claim physical verification from CI;
- unlock MCP/Agent/Safe Editing before v0.2.

## 9. CURRENT POSITION

**Step 0 COMPLETE → Step 1-A COMPLETE → Step 1-B COMPLETE → Step 1-C COMPLETE → Step 2 COMPLETE → Step 3 COMPLETE → READY FOR PHYSICAL TEST**

### Final status
- ENGINE BASELINE: 🟩🟩 4.7.2 Stable verified
- DEVELOPMENT BASE: 🟩🟩 corrected and isolated
- SAFE CORE: 🟩🟩 protected / validated by CI
- UI TRACK: 🟩🟩 final mobile UI state ported / CI validated
- PHYSICAL TEST: 🟨🟨 **READY FOR PHYSICAL TEST**
- v0.2: 🟡🟡 hold pending real-device PASS
- RELEASE: 🟥🟥 not ready

### NEXT IMMEDIATE STEP
Physically test the exact direct APK from run #90 on the Android device, then record PASS/FAIL and any UI/NIM regressions before v0.2 Candidate Lock.
