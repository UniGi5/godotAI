# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Purpose
Factual checkpoint for continuation. Update after baseline repairs, important implementation changes, CI/package milestones, physical Android tests, discovered blockers, branch promotions, or v0.2/release gate decisions.

## CURRENT STATUS

### Baseline
🟩🟩 **VERIFIED**

- Target engine: **Godot 4.7.2 Stable**
- Upstream tag: `4.7.2-stable`
- Exact stable commit: `ed1daf0bf001b61586d9930840f2f1394092c079`
- `development/controlled-baseline` was reset directly to the exact stable commit.
- Current branch HEAD: `389c980f9556c25d6719275f3a6d9b2d16b71d07`
- Latest product-code checkpoint: `46ba6a621007aefc3c4a8f649230b680246749ac`
- Latest CI-only APK publication commit: `6e6ecc067bce46e93cd1f14c4429d40745834751`
- Current HEAD is a governance/documentation commit whose ancestry reaches the exact stable commit.
- `version.py` on the controlled branch is naturally:
  `4.7.2 / stable / docs 4.7`.
- The previous incorrect 4.8-dev controlled branch state was preserved as:
  `archive/controlled-baseline-4.8-dev-2026-10-04`.

### Core
🟩🟩 **PROTECTED / CI VALIDATED**

Safe transport contract remains frozen for v0.2:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

The current Safe Core transport contract remains frozen and was preserved during the controlled final-state port. Android Editor compilation succeeded in run #86.

### UI
🟩🟩 **FINAL STATE PORTED / CI VALIDATED**

The NIM mobile panel state, context display, test flow, copy-chat, retry and stop controls are present in the controlled branch and compiled successfully.

### Release
🟥🟥 **NOT READY**

A behavior-changing Android candidate exists, but real-device validation has not yet been recorded.

## EXACT EVIDENCE

### Baseline mismatch that was corrected
Before repair:
- `development/controlled-baseline` HEAD = `952c9c494ba74c1df2a6c5c7a2e3c39f1a284d1d`
- `version.py` = 4.8.0-dev
- compare against 4.7.2 stable reported a divergent history rather than a stable-based ancestry.

After repair:
- `development/controlled-baseline` root = `ed1daf0bf001b61586d9930840f2f1394092c079`
- upstream `godotengine/godot` tag `4.7.2-stable` resolves to the same SHA;
- the exact commit is present in `UniGi5/godotAI`;
- upstream commit verification is valid;
- current `version.py` is 4.7.2 stable.

### Verified Step 1 commit inventory
The requested AI/context commits exist in the repository:
- `6b7c7e558e4809ec1532013174d5b16bdd445447`
- `96f6237853179a4153f0f7f527949cb8f02e0b42`
- `d6ef7c89241d30e528ced66ce1e87d9851da222e`
- `17be11cf31664181f7dcf5cc3e3b12926eb7ae40`
- `489a99ed6e92a11d0c3c792239ab890ffae620f5`
- `3079a2b013213deba0376372fb6bba2c7ca4a010`

Verified mobile UI commit inventory:
- `07f5454c0f5a6420def7a2c56d82f25bc9fc6d69`
- `eeeb6b0858205b158f3c433096950fab9d8433c1`
- `3cc9cfdb22935d0859aeef0948a6d616e168019a`
- `424c1789b0a0e24c7eb1dccb882c7ed197d647ad`
- `2c065277d76fd4ee041b6a3e6527c02331330dbb`
- `679425959764caa2966b697a6dd1ee30b7d5eedc`
- `5908d16db5a42d739ae2fb8780bfb7c9b2ccb762`

### Current Android candidate

- Product commit: `46ba6a621007aefc3c4a8f649230b680246749ac`
- CI run: #86 / Run ID `37241554466`
- Android Editor ARM64 job: SUCCESS
- GitHub artifact: `android-editor`
- Installable APK extracted from that exact artifact: `godot-android-editor-arm64-46ba6a621.apk`
- APK size: 179,514,605 bytes
- APK SHA-256: `8eb107305910a0413939176b8bb2e9e780e26fa5af408b54a91a8e7634851279`
- Direct APK-only CI publication was added in `6e6ecc067bce46e93cd1f14c4429d40745834751`.
- CI run #87 was superseded/cancelled by the subsequent handoff checkpoint before its Android job completed.
- Run #86 remains the authoritative physical-test package because it completed successfully at product commit `46ba6a621007aefc3c4a8f649230b680246749ac`.

### Historical physical baseline
Previously verified physical Android baseline remains protected for reference:
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI: #156 / Run ID `37057401793`
- APK SHA-256:
  `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

This historical package is **not** the new 4.7.2 controlled-baseline candidate.

## BACKLOG STATE

- Step 0 — clean 4.7.2 Stable baseline: 🟩🟩 COMPLETE
- Step 1-A — dependency audit: 🟩🟩 COMPLETE
- Step 1-B — AI Bridge foundation port: 🟩🟩 COMPLETE
- Step 1-C — approved context transplant: 🟩🟩 COMPLETE — final state ported
- Step 2 — mobile chat UI transplant: 🟩🟩 COMPLETE — final state ported
- Step 3 — Android CI + APK + SHA-256: 🟩🟩 COMPLETE
- Step 4 — real-device Android validation: 🟨🟨 READY FOR PHYSICAL TEST
- Step 5 — v0.2 Candidate Lock: 🟥🟥 QUEUED
- Experimental MCP / Agent / Safe Editing: 🟥🟥 FROZEN until v0.2 lock

## PHYSICAL TEST GATE

**READY FOR PHYSICAL TEST: ACTIVE**

Test the exact package:
- commit `46ba6a621007aefc3c4a8f649230b680246749ac`
- CI run #86 / `37241554466`
- APK SHA-256 `8eb107305910a0413939176b8bb2e9e780e26fa5af408b54a91a8e7634851279`

Required real-device checks: editor startup, NIM panel opening/closing, API-key persistence, Test Connection recovery, chat send/response, Copy Chat, Retry/Stop, and project/scene/selected-node context. Do not infer physical verification from CI.

## EXACT STEP 1 EVIDENCE

- First requested context commit: `6b7c7e558e4809ec1532013174d5b16bdd445447`
- Direct parent: `1e65ff3f7d4246e9258874dac84fb033d3b4c103`
- Parent chain includes:
  - `c37a1e52471696085fd03e7fc4386964275c2643` — provider-neutral AI Bridge contracts
  - `383e035d9e442f2e2348ab55a04653c2599fc30c` — AI Bridge build integration on the old development line
- Clean 4.7.2 baseline contains no `editor/ai_bridge/` tree.

## FOUNDATION / FINAL-STATE PORT EVIDENCE

- 4.7.2-compatible AI Bridge contracts are present.
- Full project-specific bridge/runtime/context/provider/UI final state was ported without replaying the old 4.8-dev ancestry.
- Android run #215 validated the minimal foundation.
- Android run #216 validated the expanded bridge/runtime/context/UI base.
- Android run #86 validated the controlled branch state at product commit `46ba6a621007aefc3c4a8f649230b680246749ac`.
- The six approved context behaviors are present in final state: project identity, context string fixes, current scene, scene formatting/injection, selected node, selected-node API fix.


## NEXT IMMEDIATE STEP

Physical validation of the exact CI APK from run #86 is the next gate. After the device result is recorded, either fix regressions in an atomic commit or promote the candidate toward v0.2 lock.

Do not unlock MCP/Agent/Safe Editing.

## Handoff Rules
- Never switch to Godot master / 4.8-dev.
- Never change only `version.py` to simulate a baseline.
- Never blindly merge/rebase the former 4.8-dev product/UI branches.
- Keep Safe Core protected.
- Keep MCP/Agent/Safe Editing frozen until v0.2 lock.
- Record exact commit, CI run, APK, SHA-256, and actual device result for every behavior-changing Android package.
