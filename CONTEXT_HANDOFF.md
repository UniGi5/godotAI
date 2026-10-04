# CONTEXT_HANDOFF.md

## 1. Project identity

- Repository: `UniGi5/godotAI`
- Product: official Godot Engine fork with integrated NVIDIA NIM / Nemotron support.
- Base engine: Godot 4.7.2 stable. **Do not switch to Godot master.**
- Main product branch: `fix/p1-nim-mobile-chat-ui`
- PR: #1 — `fix(ui): keep NIM chat visible on mobile editor`
- Current product HEAD before this handoff update: `c35fc592b3a2b85139be9bb24464ea3a5f023bad`
- DEBUG control branch: `debug/versions`
- DEBUG HEAD: `8a0fa0ee56e6a18fd915c623b9c419d2fbe80c2d`

Architecture invariant:

`Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`

Current model:
`nvidia/nemotron-3-ultra-550b-a55b`

Endpoint:
`https://integrate.api.nvidia.com/v1/chat/completions`

## 2. Stable physical Android baseline

Confirmed physical baseline:

- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- Result: SUCCESS
- APK: `godot-android-editor-arm64.apk`
- Release tag: `build-0201ff8138d`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

Physically confirmed:
- Android Editor launches.
- NVIDIA NIM connection works.
- API key persists after restart.
- Nemotron responds.
- Test Connection no longer hangs after success.
- Copy Chat works.
- Mobile NIM UI is usable.
- Project identity/context reaches Nemotron.

Do not regress these behaviors.

## 3. Current v0.2 candidate

Code candidate:

- Commit: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Change: debugger context fields now use real newline separators instead of literal \\n.
- Scope: diagnostics/context formatting only. No NIM transport, TLS, secret storage, or core UI contract change.

Documentation HEAD:
- `c35fc592b3a2b85139be9bb24464ea3a5f023bad`

The documentation commits after `d4bced3` do not change the candidate runtime code.

## 4. Android CI / APK for current candidate

Current candidate has a successful Android build represented by:

- CI Run: #188
- Run ID: `37225291853`
- Android Editor ARM64 Release APK job: SUCCESS
- APK tag: `build-c35fc592b3a2`
- APK size: `192,454,271 bytes`
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`

Direct APK:
`https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk`

**Important:** CI success is not physical verification. The APK above is the package that must be physically tested before v0.2 is locked.

## 5. v0.2 context implemented

Current code contains provider-independent editor context support for:

- project identity/name;
- project resource path;
- current edited scene;
- selected node name;
- selected node type/path;
- selected node script path;
- selected script source;
- 12,000-character source limit;
- explicit `[Script source truncated]` marker;
- debugger/error context;
- granular context scopes;
- context assembly through the AI bridge rather than direct NVIDIA coupling.

Relevant implementation history includes:
- `87b0722` — selected node script path;
- `9af5cce` — selected script source;
- `ac19c9b` — indentation normalization;
- `84587d9` — roadmap checkpoint;
- `3a0311b` — scoped context assembly;
- `42bd9b9` — debugger/error summary scope;
- `d4bced3` — debugger fields use real newlines.

## 6. Stable NIM transport baseline

Keep the deterministic non-stream path as the Safe Core baseline:

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Do not replace this with streaming as part of the v0.2 lock. Streaming is a separate experimental/development gate.

## 7. Development zones

### SAFE CORE
Protected production zone:
- Godot base;
- provider architecture;
- HTTPS/TLS;
- API key persistence;
- stable NIM request path;
- Test Connection;
- Copy Chat;
- Android packaging.

Any Safe Core modification requires minimal patch + CI + regression + physical Android validation.

### UI TRACK
Recommended branch: `ui/p1-chat-ux`

Allowed:
- mobile layout;
- word wrapping;
- code readability;
- scrolling;
- connection indicators.

Must not alter the NIM API contract.

### DEVELOPMENT TRACK
Recommended branch: `dev/p1-context-diagnostics`

Next logical development after v0.2 lock:
- Diagnostic Report based on Context v0.2;
- distinguish collected facts from model inference.

### EXPERIMENTAL
Use `exp/*`.

MCP Bridge, streaming replacement, Agent mode and Safe Editing remain **FROZEN until v0.2 release lock**.

### DEBUG VERSIONS
Branch: `debug/versions`

Purpose:
`change → DEBUG checkpoint → CI/physical verification → record result → next major change`

Current DEBUG checkpoint:
`DEBUG-v0.2-CANDIDATE`

It must record exact commit, CI, APK, checksum, physical test result and PASS/HOLD/REWORK.

## 8. Current readiness

| Area | Status |
|---|---|
| SAFE CORE | 🟢 |
| UI TRACK | 🟢 baseline verified; further UX changes separate |
| DEVELOPMENT TRACK | 🟡 v0.2 context implemented; diagnostic report next |
| EXPERIMENTAL | 🟡 frozen until v0.2 lock |
| DEBUG VERSIONS | 🟢 active |
| CI | 🟢 Run #188 successful |
| APK | 🟢 current candidate available |
| ANDROID TEST | 🟡 physical test pending for Run #188 APK |
| v0.2 | 🟡 candidate / not locked |
| RELEASE | 🟡 not ready |

## 9. Required physical test before v0.2 lock

Use exactly the Run #188 APK above.

Check:
1. Editor launches without crash.
2. API key persists after restart.
3. Test Connection succeeds and does not hang.
4. Nemotron chat responds promptly.
5. Project name/context is visible to Nemotron.
6. Current scene / selected node / type / path context is sensible.
7. Selected script path/source context is sensible.
8. Debugger/error context is rendered as real separate lines, not literal `\\n`.
9. Markdown/code blocks remain readable.
10. Copy Chat works.
11. No regression of the stable baseline.

**Readiness rule:** do not mark v0.2 PASS from CI alone. Physical Android confirmation is required.

## 10. After physical PASS

If the Run #188 APK passes:
1. Record the physical result in `DEBUG_VERSIONS.md`.
2. Promote checkpoint to `DEBUG-v0.2-RELEASE-CANDIDATE`.
3. Update roadmap/handoff with the exact tested commit/package.
4. Prepare v0.2 lock.
5. Carefully resolve PR/master divergence; do not blindly merge/rebase because PR #1 is currently dirty and behind master.
6. Prepare release package only after the v0.2 lock.
7. Only after v0.2 release lock begin MCP/Agent/Safe Editing work.

If physical testing finds a regression:
- mark DEBUG checkpoint REWORK;
- keep Safe Core protected;
- create the smallest targeted fix;
- rebuild CI;
- require a new physical APK test.

## 11. Gemini operating rules

- Treat this document as a factual checkpoint, not as permission to invent verification.
- Do not retest old APKs unless a concrete regression requires it.
- Do not claim physical verification from CI.
- Do not switch Godot version.
- Do not merge/rebase master blindly.
- Do not start MCP/Agent/Safe Editing before v0.2 lock.
- Keep UI, Development and Experimental changes isolated from Safe Core.
- Every major transition must be recorded in DEBUG Versions.
- When a new Android physical test is required, report: exact commit, CI run, direct APK, SHA-256, minimal test list and readiness state.

## 12. Immediate next action

**PHYSICAL ANDROID TEST REQUIRED**

Test:
`build-c35fc592b3a2`

APK:
`https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk`

SHA-256:
`d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`

Until this physical test is reported, the correct state is:

**v0.2 = HOLD — candidate ready, physical verification pending.**
**RELEASE = NOT READY.**
