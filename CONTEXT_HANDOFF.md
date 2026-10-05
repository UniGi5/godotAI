# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Purpose
Factual checkpoint for continuation. Update after baseline repairs, important implementation changes, CI/package milestones, physical Android tests, discovered blockers, branch promotions, or v0.2/release gate decisions.

## CURRENT STATUS

### Baseline
🟩🟩 **VERIFIED**

- Target engine: **Godot 4.7.2 Stable**
- Upstream tag: `4.7.2-stable`
- Exact stable commit: `ed1daf0bf001b61586d9930840f2f1394092c079`
- `development/controlled-baseline` remains based directly on the exact stable root.
- Current UI patch branch: `ui/v0.2-ux-fixes`
- Current UI patch HEAD at candidate packaging: `b5c0624b72f4fea19e0b9d12c0a657b9a010921a`
- The former incorrect 4.8-dev controlled branch remains archived as:
  `archive/controlled-baseline-4.8-dev-2026-10-04`.
- The legacy `fix/p1-nim-mobile-chat-ui` / PR #1 remains isolated because it is based on `master`.

### Core
🟩🟩 **PROTECTED / CI VALIDATED**

Safe transport contract remains frozen for v0.2:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

The current Safe Core transport contract remains frozen and was preserved during the controlled final-state port. Android Editor compilation succeeded in run #86.

### UI
🟨🟨 **V0.2 UX PATCH IN PROGRESS**

PR #2:
- title: `fix(ui): stabilize mobile chat UX for v0.2`
- base: `development/controlled-baseline`
- head: `ui/v0.2-ux-fixes`
- current source head at candidate packaging: `b5c0624b72f4fea19e0b9d12c0a657b9a010921a`

UX fixes included:
1. Preserve visible chat output during connection/reconnect checks.
2. Move Clear Chat away from adjacent touch controls and require confirmation.
3. Expand/wrap the chat viewport for readable mobile history/code.

The patch changes only:
- `editor/ai_bridge/ui/nim_editor_panel.cpp`
- `editor/ai_bridge/ui/nim_editor_panel.h`

### Release
🟨🟨 **READY FOR PHYSICAL TEST**

The UX patch has a successful push CI run with Android Editor ARM64 packaging. v0.2 still remains on HOLD until the exact APK passes real-device regression and the PR-wide Linux diagnostics are resolved or explicitly accepted.

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

### Previous Android candidate — superseded

The earlier controlled candidate from CI run #90 was physically tested and is no longer the v0.2 candidate because the physical test found three UX issues.

Verified physical result from that package:
1. Network reconnect / connection checks did not crash the editor.
2. Copy code inside generated blocks worked.
3. Project / scene / selected-node context injection worked.

Required UX corrections:
- preserve chat history during connection state changes;
- confirmation before Clear Chat;
- readable full-width/full-height chat viewport.

The old run #90 APK must not be presented as **READY FOR PHYSICAL TEST** for the current UX patch. Its previously recorded SHA is intentionally not repeated because it was not independently reverified.

### Current UX patch CI gate

- PR #2 head: `ui/v0.2-ux-fixes`
- Current source head: `e70f4fcf3f569321a3be022638d0d4a3e2a17d19`
- Earlier PR check run #99 / Run ID `37249141697`: **FAIL**
- Failure location: `prek` style checks
- Android stage was skipped after the static-check failure.
- Root cause identified in the touched C++: include ordering and whitespace-only line.
- Style correction commit: `0122eac9a2556ca72bc7474ceae5e54374fb4879`
- CI concurrency experiment commits were reverted after log diagnosis showed the cancellations were caused by the external GitHub Actions incident, not repository concurrency.
- CI #128 / Run ID `37374009155`: **FAIL / cancelled before Static Checks**
- CI #129 / Run ID `37374014584`: **FAIL / cancelled before Static Checks**
- CI #126/#127 and #128/#129 were affected by the same hosted-runner assignment degradation window.
- GitHub Status reported an active Actions incident on 2026-10-05: delayed assignment of GitHub-hosted runners.
- The earlier Android `Error -15` was separately traced to a runner shutdown signal, not a C++ compile error.
- Push CI #138 / Run ID `37376302809`: **SUCCESS**
- Android Editor ARM64: **SUCCESS**
- Android Template ARM64: **SUCCESS**
- Android Template arm32: **SUCCESS**
- Direct artifact: `android-editor-arm64-apk` / ID `11371533448`
- APK size: `179,514,605` bytes
- Independently verified APK SHA-256: `6da437400a59f6ffcd19b609c0674ba9d024e0e81300bf95c84f76652227d3c9`
- Artifact ZIP digest: `sha256:292e8031b6fd46b36c92f783a90c09e74987ab63ba0c2d38f47f271c6bdc05e4`
- PR CI #139 / Run ID `37376309566`: **FAIL** only in generic Linux diagnostics; Android path is not implicated.
- PR failures: Linux ASAN `heap-use-after-free` in the generic project test and Linux Mono export log-check failure (`current_edited_scene = -1`).
- These failures reproduce outside the Android packaging path and the ASAN issue was already present on earlier UI-track runs; no workaround was added to the UI code.

### Historical physical baseline

Previously verified physical Android baseline:
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI: #156 / Run ID `37057401793`
- APK SHA-256:
  `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

This package is historical reference only and is not the current 4.7.2 UX candidate.

## BACKLOG STATE

- Step 0 — clean 4.7.2 Stable baseline: 🟩🟩 COMPLETE
- Step 1-A — dependency audit: 🟩🟩 COMPLETE
- Step 1-B — AI Bridge foundation port: 🟩🟩 COMPLETE
- Step 1-C — approved context transplant: 🟩🟩 COMPLETE
- Step 2 — mobile chat UI transplant: 🟩🟩 COMPLETE
- Step 3 — Android CI candidate packaging: 🟩🟩 COMPLETE (historical candidate)
- Step 4 — real-device Android validation: 🟨🟨 COMPLETE WITH UX BACKLOG
- Step 4B — v0.2 UX patch: 🟨🟨 IN PROGRESS / CI RETRY
- Step 5 — v0.2 Candidate Lock: 🟥🟥 QUEUED
- Experimental MCP / Agent / Safe Editing: 🟥🟥 FROZEN until v0.2 lock

## PHYSICAL TEST GATE

**READY FOR PHYSICAL TEST: ACTIVE**

Use only the exact APK recorded below. The required device sequence is:
1. successful CI for the current `ui/v0.2-ux-fixes` head;
2. exact direct ARM64 APK artifact;
3. independent APK SHA-256 verification;
4. fresh `CONTEXT_HANDOFF.md` with those exact package details;
5. real-device regression test.

The physical-test report already established the three UX defects on the previous candidate. A new test must use only the newly built UX-fix APK.

## EXACT STEP 1 EVIDENCE

- First requested context commit: `6b7c7e558e4809ec1532013174d5b16bdd445447`
- Direct parent: `1e65ff3f7d4246e9258874dac84fb033d3b4c103`
- Parent chain includes:
  - `c37a1e52471696085fd03e7fc4386964275c2643` — provider-neutral AI Bridge contracts
  - `383e035d9e442f2e2348ab55a04653c2599fc30c` — AI Bridge build integration on the old development line
- Clean 4.7.2 baseline contains no `editor/ai_bridge/` tree.

## ADDITIONAL VALIDATION EVIDENCE — STEP 1

The latest supplied validation checkpoint confirms the Safe Core/context behavior independently at runtime:
- Test prompt on `nvidia/nemotron-3-ultra-550b-a55b`: PASS
- Echo handshake: PASS — `NIM Transport Core Active [4.7.2-stable]`
- Scene/Node Context Injection: PASS
- `CharacterBody2D` was detected and valid GDScript 2.0 was generated

This evidence strengthens Step 1 / Safe Core validation. It does **not** replace the Android physical-test gate for the current controlled candidate.

## FOUNDATION / FINAL-STATE PORT EVIDENCE

- 4.7.2-compatible AI Bridge contracts are present.
- Full project-specific bridge/runtime/context/provider/UI final state was ported without replaying the old 4.8-dev ancestry.
- Android run #215 validated the minimal foundation.
- Android run #216 validated the expanded bridge/runtime/context/UI base.
- Android run #86 validated the controlled branch state at product commit `46ba6a621007aefc3c4a8f649230b680246749ac`.
- The six approved context behaviors are present in final state: project identity, context string fixes, current scene, scene formatting/injection, selected node, selected-node API fix.


## NEXT IMMEDIATE STEP

Run the exact physical regression against source checkpoint `b5c0624b72f4fea19e0b9d12c0a657b9a010921a` and APK SHA-256 `6da437400a59f6ffcd19b609c0674ba9d024e0e81300bf95c84f76652227d3c9`. Record the device result here after testing.

Do not unlock MCP/Agent/Safe Editing.

## Handoff Rules
- Never switch to Godot master / 4.8-dev.
- Never change only `version.py` to simulate a baseline.
- Never blindly merge/rebase the former 4.8-dev product/UI branches.
- Keep Safe Core protected.
- Keep MCP/Agent/Safe Editing frozen until v0.2 lock.
- Record exact commit, CI run, APK, SHA-256, and actual device result for every behavior-changing Android package.
