# DEVELOPMENT_BASELINE.md

# ENGINE BASELINE
**Target:** Godot 4.7.2 Stable

## Current audit result

The repository currently reports:

- `version.py`: `major=4`, `minor=8`, `patch=0`, `status="dev"`
- Therefore the current source tree is **Godot 4.8 development**, not a verified 4.7.2 Stable source baseline.
- Upstream Godot 4.7.2 Stable tag resolves to commit `ed1daf0bf001b61586d9930840f2f1394092c079`.
- This mismatch must not be hidden by changing only the displayed version string.

## Baseline policy

The product target remains **Godot 4.7.2 Stable**.

Before v0.2 release locking, the development base must be established from the verified 4.7.2 Stable source and the existing godotAI changes must be reapplied or reconciled deliberately.

**Do not:**
- edit `version.py` merely to make the UI say 4.7.2;
- blindly rebase/merge `master`;
- move Safe Core changes onto an unverified engine base;
- declare release readiness while the engine baseline is unresolved.

## Development zones

### DEVELOPMENT BASE
Branch: `development/controlled-baseline`

Purpose:
- establish the verified engine base;
- keep architecture and documentation organized;
- isolate baseline work from the release candidate;
- prepare controlled promotion into product/release branches.

### SAFE CORE
Protected:
- API key persistence;
- TLS/HTTPS;
- NIM transport;
- NvidiaProvider;
- AI Orchestrator;
- verified non-stream chat;
- Android packaging.

### RELEASE BASE
Target: **v0.2 candidate**

Promotion requires:
`DEVELOPMENT → CI → physical Android test → review → v0.2 candidate → release`

### UI TRACK
Branch: `ui/p1-chat-ux`

UI changes remain isolated until physically verified.

### EXPERIMENTAL
Use `exp/*` for:
- MCP Bridge;
- Agent;
- future autonomous tools;
- Safe Editing experiments;
- other changes not required for v0.2.

## Promotion gates

1. **Engine Baseline Gate** — source ancestry and version verified against Godot 4.7.2 Stable.
2. **Safe Core Gate** — NIM/TLS/key persistence/non-stream chat remain intact.
3. **CI Gate** — Android ARM64 APK succeeds.
4. **Physical Gate** — real-device behavior verified.
5. **Review Gate** — no unexplained regression or branch contamination.
6. **Candidate Gate** — exact commit + APK + SHA-256 recorded.
7. **Release Gate** — only after v0.2 candidate is physically verified.

## Versioning rule

The displayed application version must be treated as build evidence, not cosmetic text.

For every candidate record:
- engine version;
- source commit;
- branch;
- CI run;
- APK release tag;
- SHA-256.

If the app displays `v4.8.dev.gh [commit]` while the documented baseline says 4.7.2, the candidate is **BASELINE MISMATCH** until the source ancestry is resolved.

## Current status

- ENGINE BASELINE: 🔴 **MISMATCH — 4.8-dev source detected**
- DEVELOPMENT BASE: 🟢 **created**
- SAFE CORE: 🟢 protected
- UI TRACK: 🟡 isolated
- RELEASE BASE: 🟡 v0.2 candidate, not locked
- EXPERIMENTAL: 🔴 frozen until v0.2 lock
- RELEASE: 🔴 not ready

## Next engineering action

Establish a real 4.7.2 Stable development base first. Then compare/reconcile the existing AI/NIM changes against that base in small, reviewable steps.

No physical Android test is requested by this baseline documentation change.
