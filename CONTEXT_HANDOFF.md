# CONTEXT_HANDOFF.md — Gemini / Superpowers

## Purpose
Factual checkpoint for Gemini. Update after important implementation changes, CI/package milestones, physical Android tests, discovered blockers, branch promotions, or v0.2/release gate decisions. Do not rewrite for every ordinary commit.

## Project
- Repository: `UniGi5/godotAI`
- Product: official Godot Engine fork with integrated NVIDIA NIM / Nemotron.
- Target engine baseline: **Godot 4.7.2 Stable**
- Controlled development branch: `development/controlled-baseline`
- Architecture: `Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`
- Model: `nvidia/nemotron-3-ultra-550b-a55b`
- Endpoint: `https://integrate.api.nvidia.com/v1/chat/completions`
- Android target: ARM64

## CRITICAL ENGINE BASELINE FINDING
Repository audit shows `version.py` currently contains:
`major=4, minor=8, patch=0, status="dev"`.

The same 4.8-dev metadata is present on the inspected product/UI branches.

Therefore the current source tree is **Godot 4.8 development**, not a verified 4.7.2 Stable source tree.

Upstream Godot 4.7.2 Stable:
- tag: `4.7.2-stable`
- commit: `ed1daf0bf001b61586d9930840f2f1394092c079`

This is a **BASELINE MISMATCH**, not a cosmetic label issue.

**Do not change only `version.py` to make the app display 4.7.2.**
**Do not declare the engine baseline verified until source ancestry is established.**

## DEVELOPMENT ZONES

### ENGINE BASELINE
Target: **Godot 4.7.2 Stable**

### DEVELOPMENT BASE
Branch: `development/controlled-baseline`
Purpose: establish the verified engine base and organize development without contaminating the release candidate.

### SAFE CORE
Protected:
- API key persistence
- TLS/HTTPS
- NIM transport
- NvidiaProvider
- AI Orchestrator
- verified non-stream chat
- Android packaging

### RELEASE BASE
Target: **v0.2 candidate**

### UI TRACK
Branch: `ui/p1-chat-ux`
Mobile UI changes stay isolated until physical verification.

### EXPERIMENTAL
Use `exp/*` for MCP / Agent / Safe Editing / future autonomous capabilities. Frozen until v0.2 lock.

## KNOWN GOOD PHYSICAL ANDROID BASELINE
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156 / Run ID `37057401793`
- Release: `build-0201ff8138d`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

Physically verified:
- Editor launches
- API key persists
- NIM connection succeeds
- Nemotron responds
- Test Connection works
- Copy Chat works
- mobile NIM UI is usable
- project identity/context reaches Nemotron

Protect this baseline.

## SAFE NIM TRANSPORT CONTRACT
Keep:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

SSE/streaming must remain independently verifiable and must not replace the known-good path without a gate.

## PROMOTION PIPELINE
`DEVELOPMENT → source verification → CI → physical Android test → review → v0.2 candidate → release`

Never promote directly from development to release.

For every physical-test package record:
1. exact commit;
2. CI run;
3. direct APK;
4. SHA-256;
5. short checklist;
6. expected result;
7. **READY FOR PHYSICAL TEST** marker.

CI success alone is never physical verification.

## CURRENT STATUS
- ENGINE BASELINE: 🔴 **MISMATCH — 4.8-dev source detected**
- DEVELOPMENT BASE: 🟢 **ACTIVE**
- SAFE CORE: 🟢 **PROTECTED**
- UI TRACK: 🟡 **ISOLATED**
- v0.2: 🟡 **HOLD**
- RELEASE: 🔴 **NOT READY**
- PHYSICAL TEST: 🟢 **NOT REQUESTED by this documentation/baseline change**

## IMMEDIATE NEXT STEP
1. Establish the real Godot 4.7.2 Stable source base.
2. Identify the exact AI/NIM commits that must survive.
3. Reconcile those changes onto the verified 4.7.2 base in small steps.
4. Run Android CI.
5. Request one focused physical regression for the resulting behavior-changing APK.
6. Record the actual result here.
7. Only then advance toward v0.2 candidate locking.

Do not blindly merge/rebase existing branches.

## GEMINI RULES
- Read this handoff plus `DEVELOPMENT_BASELINE.md`, `DEVELOPMENT_STATE.md`, and `DEVELOPMENT_ROADMAP.md` before release decisions.
- Never invent physical verification.
- Never infer release readiness from CI alone.
- Do not change engine version casually.
- Keep Safe Core isolated from UI/baseline work.
- Keep MCP/Agent/Safe Editing frozen until v0.2 lock.
- Update this handoff after important changes or tests with exact commit/package evidence.
