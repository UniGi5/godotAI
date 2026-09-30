# GODOT AI BRIDGE — ARCHITECTURE

## Dependency map

```
┌──────────────────────────┐
│     Godot Editor UI      │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│     AI Orchestrator      │
└─────┬─────────┬──────────┘
      │         │
      │         ├──────────────────┐
      ▼         ▼                  ▼
 Context     Tool Registry    Configuration
 Engine           │             / Secrets
                  ▼
          Permission Manager
                  │
                  ▼
┌──────────────────────────┐
│      Provider Layer      │
│       AIProvider         │
└────────────┬─────────────┘
             │
      ┌──────┼───────────────┐
      ▼      ▼               ▼
   NVIDIA  OpenAI          Ollama
   Nemotron
```

## Layer responsibilities

### Editor/UI layer

Responsible for:

- user interaction;
- editor panels/docks;
- displaying state;
- cancellation controls;
- presenting errors and tool approval requests.

It does not implement vendor-specific HTTP logic.

### Orchestrator layer

Responsible for:

- request lifecycle;
- conversation/session state;
- provider selection;
- streaming aggregation;
- tool routing;
- permission checks;
- retries/cancellation policy.

### Provider interface

Responsible for presenting a stable provider contract.

Candidate concerns:

- send request;
- stream response;
- cancel;
- normalize provider errors;
- expose model capabilities.

### Concrete providers

Each provider owns its own protocol details.

The NVIDIA provider is the initial implementation.

### Context engine

Produces bounded context from project/editor state according to policy.

### Tool registry

Defines what the AI may ask the system to do.

### Permission manager

Decides whether requested tools may execute.

### Configuration and secrets

Configuration is separated from secrets.

Secrets must never be included in ordinary configuration files or logs.

## Proposed v0.1 boundaries

The first implementation should prefer interfaces at these boundaries:

```
IAIOrchestrator
IAIProvider
IContextProvider
ITool
IToolRegistry
IPermissionManager
IConfigurationManager
ISecretStorage
ILogger
IErrorHandler
```

Exact interface names may be revised by the architecture task, but dependency direction must remain unchanged.

## Runtime request flow

```
User
 ↓
Editor UI
 ↓
AI Orchestrator
 ↓
Context Engine
 ↓
Tool/Permission checks
 ↓
AIProvider
 ↓
HTTP API
 ↓
streamed response
 ↓
Orchestrator
 ↓
Editor UI
```

## Security flow

```
AI request
   ↓
declared tool
   ↓
schema validation
   ↓
permission evaluation
   ↓
execution sandbox/boundary
   ↓
sanitized result
   ↓
AI
```

## Architectural decisions to preserve

1. Godot Core does not depend on NVIDIA.
2. AI access to privileged operations is mediated.
3. Secrets are isolated.
4. Providers are replaceable.
5. Streaming and asynchronous behavior are first-class.
6. Tests cover both success and expected failure paths.
7. Architecture decisions are documented instead of living only in agent prompts.
