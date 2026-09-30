# GODOT AI BRIDGE — MASTER PROJECT CONTEXT

## 1. Project identity

**Project name:** Godot AI Bridge

**Repository:** `UniGi5/godotAI`

**Purpose:** build an extensible AI integration inside the Godot 4 Editor, starting with NVIDIA Nemotron through an official OpenAI-compatible API and designed from the beginning for multiple providers.

This repository is currently a Godot Engine source fork. The AI Bridge work must be layered into the engine/editor architecture without coupling the Godot core to a concrete AI vendor.

---

## 2. Primary goal

Create a production-oriented AI system for the Godot 4 Editor that can:

- communicate with AI providers;
- stream responses asynchronously;
- provide useful editor-facing AI features;
- expose controlled tools to the AI;
- maintain context safely;
- manage permissions explicitly;
- keep secrets out of source control;
- log operations and errors;
- eventually integrate Git/GitHub through explicit permissioned tools;
- support multiple remote and local providers without redesigning Godot Core.

The current provider is NVIDIA Nemotron via the official OpenAI-compatible endpoint:

- Base URL: `https://integrate.api.nvidia.com/v1`
- Chat endpoint: `POST /chat/completions`

The provider implementation must not become a dependency of the Godot core.

---

## 3. Non-negotiable architecture rule

The following dependency direction is mandatory:

```
Godot Core
  ↓
AI Orchestrator
  ↓
AIProvider interface
  ↓
NvidiaProvider
```

Not:

```
Godot Core
  ↓
NVIDIA API
```

The core must know only stable internal interfaces. Concrete provider details belong behind the provider layer.

---

## 4. Target provider architecture

The design must support, without breaking the core:

- NVIDIA NIM / Nemotron
- OpenAI
- Gemini
- Ollama
- other OpenAI-compatible APIs
- local models
- future providers

The provider layer should normalize provider-specific transport and response behavior behind a common interface.

---

## 5. Core subsystems

The long-term project architecture includes:

### UI

Godot Editor-facing presentation layer, including dock/panel/editor integration.

### AI Orchestrator

Coordinates conversations, requests, streaming, context, tools, permissions, cancellation, retries, and provider selection.

### Provider Layer

Contains the provider interface plus concrete providers.

### Configuration Manager

Stores non-secret configuration such as:

- provider selection;
- base URL;
- model name;
- generation parameters;
- feature flags;
- UI preferences.

### Secret Storage

Owns API keys and other secrets. Secrets must never be committed to the repository or exposed through normal logs.

### Context Engine

Builds controlled AI context from editor/project state.

Context must be explicit and bounded rather than passing arbitrary filesystem contents.

### Tool Registry

Registers available AI tools with explicit schemas, descriptions, validation, and permissions.

### Permission Manager

Controls whether a tool may execute. High-impact operations require explicit permission boundaries.

### Logging

Structured logs for requests, tool execution, timings, state transitions, and failures while avoiding secret leakage.

### Error Handling

Normalizes transport, provider, timeout, parsing, permission, tool, and editor errors into actionable internal error states.

### Future Git Layer

Git/GitHub access is a future subsystem and must go through the Tool Registry and Permission Manager.

---

## 6. Security model

AI is not fully trusted.

The AI must not receive unrestricted direct access to:

- arbitrary filesystem operations;
- shell/terminal;
- Git;
- GitHub;
- network access;
- secrets.

Instead, all privileged actions must pass through explicit tools and permissions.

Example:

```
AI
 ↓
Tool request
 ↓
Tool Registry
 ↓
Permission Manager
 ↓
Validated execution
 ↓
Result
 ↓
AI
```

Permissions should be narrow, explainable, auditable, and revocable.

---

## 7. Godot 4 direction

The project targets Godot 4 Editor integration.

Godot-facing engineering should use appropriate Godot 4 mechanisms such as:

- `EditorPlugin`
- editor dock/panel UI
- signals
- asynchronous request handling
- editor lifecycle integration
- safe interaction with editor/project APIs

The Godot-specific layer must not know provider-specific HTTP details.

---

## 8. Initial NVIDIA provider

The first concrete provider is NVIDIA Nemotron over the OpenAI-compatible API.

The provider is responsible for:

- HTTP transport;
- authentication headers from Secret Storage input;
- request serialization;
- response parsing;
- streaming;
- cancellation;
- timeout handling;
- retry classification;
- provider-specific error normalization.

The provider must not depend on Godot UI.

---

## 9. Planned task architecture

The project was initially decomposed into these major work areas:

### 00 — MASTER / Architect

Maintain global project context, architecture rules, roadmap, ADRs, unresolved decisions, and agent coordination.

### 01 — Architecture

Define:

- v0.1 directory structure;
- core interfaces;
- provider architecture;
- orchestrator;
- configuration;
- SecretStorage;
- Context Engine;
- Tool Registry;
- Permission Manager;
- Logging;
- Error Handling;
- testing architecture;
- future Git integration;
- multi-provider architecture.

Expected outputs include:

- architecture diagram;
- directory tree;
- interfaces;
- dependency map;
- unresolved decisions;
- ADRs.

### 02 — Godot Core

Senior Godot 4 plugin/editor engineering:

- `EditorPlugin`;
- GDScript/editor code;
- dock UI;
- lifecycle;
- signals;
- async integration;
- editor APIs.

### 03 — NVIDIA Nemotron

Senior API/backend engineering:

- NVIDIA NIM/Nemotron;
- OpenAI-compatible HTTP;
- streaming;
- asynchronous requests;
- timeouts;
- cancellation;
- error handling;
- provider abstraction.

The provider must remain independent of Godot UI.

---

## 10. Testing architecture

Testing must exist at multiple layers:

### Unit tests

Pure logic, serializers, parsers, configuration, permissions, context assembly, and provider normalization.

### Integration tests

Provider transport and orchestrator interactions with deterministic or mocked endpoints where practical.

### Editor tests

Godot Editor lifecycle and UI-facing functionality.

### Security tests

Permission enforcement, secret handling, denied tool execution, and audit/logging behavior.

### CI tests

Every push should exercise the project's configured checks. Runtime failures must be distinguished from build failures.

### Android runtime validation

A successfully built APK is not proof that the application launches.

The project must track separately:

1. APK build success;
2. APK structural/signature validation;
3. installation success;
4. application launch success;
5. crash/ANR evidence;
6. feature smoke tests.

A device launch crash must never be dismissed as "expected" without evidence.

---

## 11. Git and GitHub working model

GitHub is part of the engineering workflow.

Agents may use Git/GitHub through the available integration, but changes must remain auditable.

Preferred flow:

```
inspect
 → implement
 → test
 → commit
 → push
 → CI
 → inspect results
 → fix
 → repeat
```

Avoid unrelated drive-by changes.

---

## 12. CI/CD target for the current phase

The current user-facing build target is deliberately narrow:

```
Push
 ↓
Static checks
 ↓
Android ARM64 Godot Editor Release
 ↓
raw APK
 ↓
GitHub Release asset
```

The project currently does not need desktop, Web, iOS, visionOS, ARM32, HorizonOS, PICO OS, or AAB build outputs.

The raw APK should be available through a direct download link from the workflow summary.

Actions artifact ZIP packaging is not the user-facing delivery mechanism.

---

## 13. APK runtime issue tracking

The latest user-reported result is:

- the direct APK delivery mechanism works;
- the APK can be downloaded by the explicit direct link;
- the resulting application crashes when launched on the user's phone.

This is recorded as a runtime investigation item, not as an accepted behavior.

The next diagnostic evidence should distinguish:

- packaging/install issue;
- missing native library;
- ABI issue;
- renderer/device issue;
- Android lifecycle issue;
- release-only behavior;
- initialization failure;
- provider/AI Bridge code failure.

Exact cause must be established from logs or a reproducible runtime test before changing architecture.

---

## 14. Agent extension rule

Agents may add:

- clarifications;
- implementation conventions;
- new ADRs;
- testing requirements;
- security controls;
- CI improvements;
- provider-specific documentation.

Agents must not silently remove the requirements in this master context. When a requirement becomes obsolete, record the replacement and rationale in an ADR rather than silently deleting history.

---

## 15. Current roadmap

The implementation should continue in this order unless evidence requires a change:

1. stabilize the project/agent documentation contract;
2. stabilize CI and direct APK delivery;
3. investigate and resolve Android runtime crash;
4. establish v0.1 architecture and interfaces;
5. implement Godot Core integration;
6. implement NVIDIA Nemotron provider;
7. connect provider through the orchestrator;
8. implement configuration and secret storage;
9. implement context engine;
10. implement tool registry and permission manager;
11. add tests and diagnostics;
12. add additional providers;
13. add controlled Git/GitHub tooling;
14. improve editor UX and developer automation.

---

## 16. Important principle

Do not rebuild functionality that already exists in Godot or standard tooling unless there is a clear project-specific reason.

Prefer:

- stable existing APIs;
- existing build mechanisms;
- existing test mechanisms;
- narrow adapters;
- documented extension points.

The goal is a maintainable AI Bridge, not an unnecessary replacement of the Godot ecosystem.
