# CONTEXT_HANDOFF.md — Gemini / Superpowers

## 1. Project identity

- Repository: `UniGi5/godotAI`
- Product: official Godot Engine fork with integrated NVIDIA NIM / Nemotron support.
- Base engine: **Godot 4.7.2 stable**. Do not switch to Godot master.
- Product branch: `fix/p1-nim-mobile-chat-ui`
- Main PR: #1 — `fix(ui): keep NIM chat visible on mobile editor`
- Product branch HEAD: `319e9f2be2e89c8dd9d332c25b1c6bf002471f09`
- Current working UI branch: `ui/p1-chat-ux`
- Current UI branch HEAD: `46cdeef1846990a96a5ec99a2fb0839c2d43076e`
- UI branch is **5 commits ahead / 0 behind** the product branch.
- DEBUG control branch: `debug/versions`
- Latest known DEBUG HEAD before the UI checkpoint: `8a0fa0ee56e6a18fd915c623b9c419d2fbe80c2d`

Architecture invariant:

`Godot Core → AI Orchestrator → AIProvider → NvidiaProvider → NVIDIA NIM`

Current model:
`nvidia/nemotron-3-ultra-550b-a55b`

Endpoint:
`https://integrate.api.nvidia.com/v1/chat/completions`

---

## 2. Stable physical Android baseline — VERIFIED

Known good physical baseline:

- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- Result: SUCCESS
- APK: `godot-android-editor-arm64.apk`
- Release tag: `build-0201ff8138d`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`

Physical Android verification confirmed:

- Editor launches.
- NVIDIA NIM connection works.
- API key persists after restart.
- Nemotron responds.
- Test Connection no longer hangs after success.
- Copy Chat works.
- Mobile NIM UI is usable.
- Project identity/context reaches Nemotron.

Do not regress these behaviors.

---

## 3. v0.2 context candidate — HOLD

Runtime code candidate:

- Commit: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Change: debugger context fields use real newline separators instead of literal \\n.
- Scope: diagnostics/context formatting only.
- No NIM transport, TLS, secret-storage, or provider-contract change.

Product branch contains 3 documentation-only commits after that candidate; the current product HEAD is `319e9f2`.

Implemented v0.2 context:

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
- provider-independent context assembly.

Relevant implementation history:

- `87b0722` — selected node script path;
- `9af5cce` — selected script source;
- `ac19c9b` — indentation normalization;
- `84587d9` — roadmap checkpoint;
- `3a0311b` — scoped context assembly;
- `42bd9b9` — debugger/error summary scope;
- `d4bced3` — debugger fields use real newlines.

---

## 4. Android CI / APK for v0.2 candidate

Known successful candidate package:

- CI Run: #188
- Run ID: `37225291853`
- Android Editor ARM64 Release APK: SUCCESS
- APK tag: `build-c35fc592b3a2`
- APK size: `192,454,271 bytes`
- SHA-256: `d87c189794942cf84ea7aca1c3bcf83889c5b5e5691e7620143b2863effe84ce`

Direct APK:

`https://github.com/UniGi5/godotAI/releases/download/build-c35fc592b3a2/godot-android-editor-arm64.apk`

**Run #188 physical Android verification is still pending.**

Important: CI success is not physical verification.

---

## 5. Safe NIM transport baseline

Keep this as the Safe Core transport contract:

- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

Do not replace this with streaming as part of the v0.2 lock.

---

## 6. Development zones

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

Any Safe Core change requires a minimal patch, CI, regression check and physical Android validation when the package changes.

### UI TRACK

Current branch: `ui/p1-chat-ux`

Purpose: improve mobile NIM usability without changing the NIM API contract.

Current UI prototype changes only:

- `editor/ai_bridge/ui/nim_editor_panel.cpp`
- `editor/ai_bridge/ui/nim_editor_panel.h`

Prototype goal:

- multiline prompt instead of single-line composer;
- taller input/send area;
- larger response viewport;
- better text wrapping;
- keep the composer visually above the lower mobile boundary as far as the existing layout allows.

UI branch commit history:

- `5149dad` — make NIM prompt multiline on mobile;
- `fcf12f2` — enlarge mobile chat input and response area;
- `070dc62` — replace single-line mobile prompt with multiline composer;
- `07c9d6d` — include TextEdit for mobile composer;
- `46cdeef` — preserve Godot header metadata in NIM panel.

Verified against the repository's bundled Godot source:

- `TextEdit::LINE_WRAPPING_BOUNDARY` exists;
- `TextEdit::set_placeholder()` exists;
- `TextEdit::get_text()` exists;
- `TextEdit::clear()` exists.

No Android-specific keyboard hack has been added yet. Do not add one blindly. First observe the real Android keyboard/resize behavior.

Current UI physical state: **NOT TESTED**.

### DEVELOPMENT TRACK

Next after v0.2 lock:

- Diagnostic Report based on context v0.2;
- clearly distinguish collected editor facts from model inference.

### EXPERIMENTAL

Use `exp/*`.

MCP Bridge, streaming replacement, Agent mode and Safe Editing remain frozen until the v0.2 release lock.

### DEBUG VERSIONS

Branch: `debug/versions`

Purpose:

`change → DEBUG checkpoint → CI/physical verification → record result → next major change`

---

## 7. Current status

Required state:

- SAFE CORE: 🟢
- UI TRACK: 🟡
- DEVELOPMENT TRACK: 🟡
- EXPERIMENTAL: 🟡 frozen
- DEBUG VERSIONS: 🟢
- CI: 🟡 UI branch build/status not confirmed through the current connector
- APK: 🔴 no confirmed APK for UI HEAD
- ANDROID TEST: 🟡 v0.2 candidate pending; UI prototype also untested
- v0.2: 🟡 HOLD
- RELEASE: 🔴 NOT READY

Current blockers:

1. Run #188 APK still requires physical Android verification for the v0.2 candidate.
2. UI branch `ui/p1-chat-ux` requires CI/package verification before any physical test.
3. Android keyboard/viewport behavior must be observed physically before adding platform-specific adjustments.

---

## 8. Physical-test rules

When a new package is ready for physical testing, report all of:

- exact commit;
- CI run and run ID;
- direct APK;
- SHA-256;
- minimal smoke checklist;
- readiness status.

Do not mark PASS from code review or CI alone.

For the current v0.2 candidate, use:

- package tag: `build-c35fc592b3a2`;
- direct APK above;
- SHA-256 above.

For the UI prototype, no APK is currently declared ready.

---

## 9. After v0.2 physical PASS

When Run #188 passes physically:

1. Record the result in `DEBUG_VERSIONS.md`.
2. Promote the checkpoint to `DEBUG-v0.2-RELEASE-CANDIDATE`.
3. Update roadmap and handoff with the exact tested package.
4. Lock v0.2.
5. Only then resolve PR/master divergence carefully.
6. Prepare release packaging only after the lock.
7. Only after v0.2 release lock start MCP / Agent / Safe Editing work.

If physical testing finds a regression:

- mark the checkpoint REWORK;
- keep Safe Core protected;
- apply the smallest targeted fix;
- rebuild;
- require a new physical APK test.

---

## 10. Gemini operating rules

- Treat this document as a factual checkpoint, not permission to invent verification.
- Read `DEVELOPMENT_STATE.md`, `DEVELOPMENT_ROADMAP.md` and `DEBUG_VERSIONS.md` before changing release gates.
- Do not switch Godot version.
- Do not merge/rebase master blindly.
- Keep UI, Development and Experimental work isolated from Safe Core.
- Do not change the NIM API contract while working on UI.
- Do not start MCP/Agent/Safe Editing before v0.2 lock.
- Do not call an APK “ready for physical test” until CI and package identity are confirmed.
- Every major transition gets a DEBUG checkpoint.
- Never claim physical verification from CI.

---

## 11. Immediate engineering action

Current engineering branch:

`ui/p1-chat-ux`

Current HEAD:

`46cdeef1846990a96a5ec99a2fb0839c2d43076e`

First safe UI prototype is complete at source level.

Next safe step:

**obtain/confirm Android CI for the UI HEAD, then physically test the UI only if that APK is confirmed.**

Physical UI observations to capture:

1. NIM panel opens normally.
2. Multiline composer is comfortable to edit.
3. Send area remains visible above the Android keyboard.
4. Keyboard does not hide the composer.
5. Response area shows multiple lines without forced one-line-at-a-time reading.
6. Long responses wrap and scroll correctly.
7. Send remains touch-friendly.
8. Existing connection, chat, copy and context behavior does not regress.

Until the UI package is built and physically verified:

**UI TRACK = HOLD / prototype**
**v0.2 = HOLD**
**RELEASE = NOT READY**
