# DEVELOPMENT_ROADMAP.md

## Current position — 2026-10-05

Основная ветка: `fix/p1-nim-mobile-chat-ui`.

**v0.2 → FINAL RELEASE / INTEGRATION REVIEW**

### 0. FOUNDATION
- 0.1 Godot 4.7.2 Stable: 🟩🟩
- 0.2 Android ARM64 CI: 🟩🟩
- 0.3 Direct APK distribution: 🟩🟩
- 0.4 AI Bridge runtime/provider lifecycle: 🟩🟩

### 1. NIM FIRST MILESTONE
- 1.1 HTTPS + OpenAI-compatible transport: 🟩🟩
- 1.2 NVIDIA configuration: 🟩🟩
- 1.3 Mobile NIM UI: 🟩🟩 physical baseline verified
- 1.4 API-key persistence: 🟩🟩 physical verification
- 1.5 Non-stream chat: 🟩🟩 physical verification
- 1.6 Runtime/UI event bridge: 🟩🟩 physical verification
- 1.7 First milestone gate: 🟩🟩 PASSED

### 2. PROJECT CONTEXT — v0.2
- 2.1 Project identity: 🟩🟩
- 2.2 Current scene: 🟩🟩
- 2.3 Selected node: 🟩🟩
- 2.4 Current script + 12,000-char limit/truncation: 🟩🟩
- 2.5 Debugger/errors context: 🟩🟩
- 2.6 Controlled context scopes: 🟩🟩

### 3. SAFE EDITING
🟥🟥 Frozen until v0.2 release lock.

### 4. AGENT
🟥🟥 Frozen until v0.2 release lock.

### 5. RELEASE ENGINEERING
- 5.1 Automated regression: 🟡🟡 candidate checks passed; fresh PR integration check still required
- 5.2 Physical Android smoke workflow: 🟨🟨 manual physical verification completed
- 5.3 Versioning: 🟩🟩 4.7.2 Stable enforced
- 5.4 Release APK: 🟡🟡 exact candidate physically verified; release blocked by repository integration
- 5.5 Release notes/migration: 🟡🟡 synchronized to candidate; final integration state pending

## Exact verification checkpoint

- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- Packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- CI #260 / Run ID `37341176576`: **SUCCESS**
- APK: `build-24215c0ae9d1`
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Physical Android chat smoke test: **PASS**
- Greeting + ECHO-1..ECHO-5: **PASS**
- Previous “Connected but silent chat” regression: **CLEARED**
- First Test Connection HTTP 503: **OPEN RELIABILITY OBSERVATION — non-blocking; not reproduced as a deterministic code defect**
- Deterministic code cause for 503: **NOT PROVEN**

## Release gate

Current flow:

**Foundation → NIM baseline → v0.2 context → chat regression rework → exact APK physical PASS → final reliability/release review**

Do not:
- change the working NIM transport without reproducible evidence;
- reopen the cleared chat regression without new evidence;
- switch to Godot master;
- unlock MCP/Agent/Safe Editing;
- publish a public non-prerelease release before final checklist completion.

### Next engineering action
Reconcile PR #3 against current `master` using an explicit three-way review. Preserve the verified NIM runtime and do not blind merge/rebase.
