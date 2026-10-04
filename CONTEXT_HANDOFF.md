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
- Current branch HEAD: `cddc925026c77554dbcf84ce5e27ab8206e75b0d`
- Current HEAD is a governance/documentation commit whose parent is `387c546d315088cb54d84bb41883a64b41835879`, whose parent is the exact stable commit.
- `version.py` on the controlled branch is naturally:
  `4.7.2 / stable / docs 4.7`.
- The previous incorrect 4.8-dev controlled branch state was preserved as:
  `archive/controlled-baseline-4.8-dev-2026-10-04`.

### Core
🟩🟩 **PROTECTED / NOT YET TRANSPLANTED**

Safe transport contract remains frozen for v0.2:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

No Safe Core implementation was silently copied from the 4.8-dev line during the baseline repair.

### UI
🟡🟡 **ISOLATED**

The mobile UI commit set is identified and verified to exist, but it is not yet transplanted onto the clean 4.7.2 baseline.

### Release
🟥🟥 **NOT READY**

No current release candidate exists from this newly corrected baseline.

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

### Historical physical baseline
Previously verified physical Android baseline remains protected for reference:
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI: #156 / Run ID `37057401793`
- APK SHA-256:
  `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

This historical package is **not** the new 4.7.2 controlled-baseline candidate.

## BACKLOG STATE

- Step 0 — clean 4.7.2 Stable baseline: 🟩🟩 COMPLETE
- Step 1 — targeted Safe Core/context transplant: 🟨🟨 NEXT
- Step 2 — mobile chat UI transplant: 🟥🟥 QUEUED
- Step 3 — Android CI + APK + SHA-256: 🟥🟥 QUEUED
- Step 4 — real-device Android validation: 🟥🟥 QUEUED
- Step 5 — v0.2 Candidate Lock: 🟥🟥 QUEUED
- Experimental MCP / Agent / Safe Editing: 🟥🟥 FROZEN until v0.2 lock

## PHYSICAL TEST GATE

**READY FOR PHYSICAL TEST: NOT ACTIVE**

A physical test is not requested for this baseline/documentation operation. It becomes mandatory when a behavior-changing Android APK is built from the corrected baseline.

Do not infer physical verification from CI.

## NEXT IMMEDIATE STEP

Perform exactly one dependency-safe Step 1 action: audit the parent/dependency chain of the first context candidate `6b7c7e558e4809ec1532013174d5b16bdd445447` against the clean 4.7.2 baseline before attempting any cherry-pick.

## Handoff Rules
- Never switch to Godot master / 4.8-dev.
- Never change only `version.py` to simulate a baseline.
- Never blindly merge/rebase the former 4.8-dev product/UI branches.
- Keep Safe Core protected.
- Keep MCP/Agent/Safe Editing frozen until v0.2 lock.
- Record exact commit, CI run, APK, SHA-256, and actual device result for every behavior-changing Android package.
