# DEVELOPMENT_ROADMAP.md

## Current position — 2026-10-06

Основная ветка: `fix/p1-nim-mobile-chat-ui`.

**v0.2 COMPLETE → v0.3 AUTONOMOUS SCENE ANALYSIS FOUNDATION**

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

### 3. SCENE ANALYSIS — v0.3
🟨🟨 Next development target.
- 3.1 structured scene snapshot: 🟩🟨 CI verified; exact APK physical verification pending;
- 3.2 node hierarchy + properties relevant to analysis;
- 3.3 diagnostic/report schema;
- 3.4 context budget and truncation;
- 3.5 Nemotron analysis request using the existing stable transport.

### 4. SAFE EDITING
🟥🟥 Locked until Scene Analysis is verified.

### 5. AGENT
🟥🟥 Locked until analysis/reporting is reliable.

### 6. RELEASE ENGINEERING
- 6.1 Automated regression: 🟩🟩 integration CI passed
- 6.2 Physical Android smoke workflow: 🟩🟩 candidate physically verified
- 6.3 Versioning: 🟩🟩 4.7.2 Stable enforced
- 6.4 Release APK: 🟨🟨 verified prerelease candidate retained
- 6.5 Release notes/migration: 🟩🟩 synchronized

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

**Foundation → NIM baseline → v0.2 context → chat regression rework → exact APK physical PASS → repository integration CLOSED → v0.3 snapshot CI PASS → exact APK physical PASS → Analysis Orchestrator**

Do not:
- change the working NIM transport without reproducible evidence;
- reopen the cleared chat regression without new evidence;
- switch to Godot master;
- unlock Safe Editing/autonomous mutation;
- publish a public non-prerelease release before final checklist completion.

### Next engineering action
Physically validate exact APK `build-9338f0d6002e`. After PASS, continue on `feat/v0.3-analysis-orchestrator` with provider-independent diagnostic/report schema and a bounded Nemotron analysis request. Keep Safe Editing/autonomous mutation locked.
