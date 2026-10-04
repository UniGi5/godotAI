# DEVELOPMENT_BASELINE.md

## ENGINE BASELINE

**Target:** Godot 4.7.2 Stable

### Verified evidence
- Upstream tag: `4.7.2-stable`
- Root commit: `ed1daf0bf001b61586d9930840f2f1394092c079`
- Upstream tag resolves exactly to the root commit.
- The commit is present in `UniGi5/godotAI`.
- `version.py` on `development/controlled-baseline` reports 4.7.2 Stable.
- `development/controlled-baseline` compare result against the stable root is currently **ahead 3 / behind 0**.
- The previous 4.8-dev control tip is preserved at `archive/controlled-baseline-4.8-dev-2026-10-04`.

### Baseline policy
The engine baseline is source ancestry, not a cosmetic version string.

Do not:
- edit only `version.py` to simulate 4.7.2;
- merge/rebase the former 4.8-dev product line blindly;
- import 4.8-dev engine commits into the controlled baseline;
- claim release readiness while the baseline is unresolved.

## DEVELOPMENT ZONES

### DEVELOPMENT BASE
Branch: `development/controlled-baseline`

Purpose:
- verified 4.7.2 engine root;
- controlled port of required godotAI project changes;
- isolation from experimental work.

### SAFE CORE
Protected:
- API-key persistence;
- TLS/HTTPS;
- NIM transport;
- NvidiaProvider;
- AI Orchestrator;
- verified non-stream chat;
- Android packaging.

### UI TRACK
Mobile NIM UI remains isolated until deliberately ported and physically verified.

### EXPERIMENTAL
Frozen until v0.2 lock:
- MCP Bridge
- Agent
- Safe Editing
- autonomous/future tool execution

## CURRENT STEP 1 FINDING

The six approved context commits cannot be transplanted independently onto a clean 4.7.2 checkout because the clean baseline contains no `editor/ai_bridge/` foundation.

The first requested context commit:
`6b7c7e558e4809ec1532013174d5b16bdd445447`

depends on existing AI Bridge infrastructure. Its dependency chain includes:
- `c37a1e52471696085fd03e7fc4386964275c2643` — provider-neutral AI Bridge contracts
- subsequent AI Bridge runtime/provider/configuration/NIM UI work
- editor lifecycle and build-system integration

Those commits were developed from the old development line, so the dependency chain must be **ported deliberately** onto 4.7.2 rather than blindly cherry-picked as a large range.

## CONTROLLED PORT STRATEGY

### Step 1-A — Dependency audit
🟩🟩 COMPLETE

Verified:
- clean baseline has no AI Bridge files;
- requested context commits modify existing AI Bridge files;
- direct standalone cherry-pick is therefore invalid;
- AI Bridge foundation begins at `c37a1e5…`;
- old branch ancestry must not be imported wholesale.

### Step 1-B — AI Bridge foundation port
🟨🟨 NEXT

Port the minimum provider-neutral/runtime/NIM foundation required for the approved context layer.

Rules:
1. Start from 4.7.2 Stable.
2. Port project-specific files and integration points only.
3. Do not import unrelated 4.8-dev engine changes.
4. Preserve the Safe NIM transport contract.
5. Perform source/compile review before moving to context commits.
6. Run Android CI after a buildable foundation exists.

### Step 1-C — Approved context layer
🟥🟥 QUEUED

Approved:
- `6b7c7e558e4809ec1532013174d5b16bdd445447`
- `96f6237853179a4153f0f7f527949cb8f02e0b42`
- `d6ef7c89241d30e528ced66ce1e87d9851da222e`
- `17be11cf31664181f7dcf5cc3e3b12926eb7ae40`
- `489a99ed6e92a11d0c3c792239ab890ffae620f5`
- `3079a2b013213deba0376372fb6bba2c7ca4a010`

### Step 2 — Mobile chat UI
🟥🟥 QUEUED

### Step 3 — Android CI / APK / SHA-256
🟥🟥 QUEUED

### Step 4 — Physical Android validation
🟥🟥 QUEUED

### Step 5 — v0.2 Candidate Lock
🟥🟥 QUEUED

## SAFE TRANSPORT CONTRACT

Frozen through v0.2 lock:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

## GATES

Promotion order:

`4.7.2 baseline → foundation port → context/UI integration → CI → physical Android test → v0.2 lock → release`

CI success alone is never physical verification.

## CURRENT STATUS

- ENGINE BASELINE: 🟩🟩 VERIFIED
- DEVELOPMENT BASE: 🟩🟩 ESTABLISHED
- SAFE CORE: 🟨🟨 FOUNDATION PORT IN PROGRESS
- UI TRACK: 🟡🟡 ISOLATED
- EXPERIMENTAL: 🟥🟥 FROZEN
- PHYSICAL TEST: 🟥🟥 NOT REQUESTED
- v0.2: 🟡🟡 HOLD
- RELEASE: 🟥🟥 NOT READY

No physical Android test is requested by this baseline/dependency audit.

## CURRENT POSITION

**Step 1-A COMPLETE → Step 1-B NEXT**

The next engineering action is to port the minimum AI Bridge/NIM foundation required by `6b7c7e5…`, beginning with the provider-neutral contract layer, while preserving the verified 4.7.2 engine root.
