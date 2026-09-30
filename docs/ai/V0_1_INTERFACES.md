# Godot AI Bridge — v0.1 Interface Contracts

This document defines the first stable contracts. It is intentionally provider-neutral and implementation-language neutral. Concrete GDScript/C++ types may adapt the syntax without changing the responsibilities.

## IAIProvider

Purpose: abstract one AI backend.

Required responsibilities:

- identify provider and capabilities;
- submit a chat request;
- stream response events;
- cancel an in-flight request;
- normalize transport/provider failures;
- expose model metadata when supported.

The provider must not depend on editor UI, tool UI, or concrete orchestration classes.

Conceptual contract:

```
IAIProvider
  id() -> ProviderId
  capabilities() -> ProviderCapabilities
  send(request, cancellation) -> AIResponseStream
  cancel(request_id) -> void
```

## IAIOrchestrator

Purpose: own the request lifecycle above providers.

Responsibilities:

- create request/session IDs;
- select provider;
- obtain bounded context;
- route tool requests;
- enforce permissions before execution;
- aggregate streaming events;
- support cancellation;
- normalize errors;
- emit lifecycle events for the UI.

Conceptual contract:

```
IAIOrchestrator
  start(request) -> RequestHandle
  cancel(request_id) -> void
  subscribe(listener) -> Subscription
```

The orchestrator may depend on interfaces for context, tools, permissions, configuration, logging, and providers. It must not hard-code NVIDIA.

## IContextProvider

Purpose: produce bounded, policy-controlled context.

Responsibilities:

- identify the requested context scope;
- collect only permitted data;
- enforce size/token limits;
- label source/type of context;
- reject unavailable or disallowed context.

No arbitrary filesystem dump is allowed.

## ITool

Purpose: one explicitly defined action available to the AI.

Required properties:

- stable tool ID;
- human-readable name/description;
- input schema;
- output schema;
- risk classification;
- permission requirement;
- deterministic validation.

Conceptual contract:

```
ITool
  descriptor() -> ToolDescriptor
  validate(input) -> ValidationResult
  execute(input, execution_context) -> ToolResult
```

Tools are the only intended bridge from AI intent to privileged host operations.

## IToolRegistry

Purpose: discover and resolve available tools.

Responsibilities:

- register tools;
- unregister tools;
- list enabled tools;
- resolve tool IDs;
- validate descriptors;
- prevent duplicate/ambiguous registrations.

## IPermissionManager

Purpose: decide whether an operation is allowed.

A permission decision must be explicit and auditable.

Conceptual contract:

```
IPermissionManager
  evaluate(tool, request_context) -> PermissionDecision
  record(decision) -> void
```

Possible decisions:

- allow;
- deny;
- ask-user;
- require-elevated-confirmation.

## IConfigurationManager

Purpose: manage non-secret configuration.

Examples:

- provider ID;
- base URL;
- model ID;
- generation parameters;
- feature flags;
- UI preferences.

Secrets are not configuration values and must not be stored here.

## ISecretStorage

Purpose: store and retrieve credentials through a secure boundary.

Examples:

- API keys;
- OAuth refresh tokens;
- signing credentials where explicitly required.

Rules:

- never log secret values;
- never serialize secrets into ordinary project config;
- never send secrets to an AI model as context;
- distinguish unavailable secret from invalid secret.

## ILogger

Purpose: structured observability.

Log fields should favor:

- timestamp;
- subsystem;
- severity;
- request ID;
- tool ID;
- provider ID;
- duration;
- normalized error code.

Secret values and raw authorization headers are forbidden.

## IErrorHandler

Purpose: normalize actionable failures.

Minimum categories:

- configuration;
- secret;
- transport;
- authentication;
- authorization;
- rate-limit;
- timeout;
- cancellation;
- parsing;
- provider;
- tool;
- permission;
- editor/runtime.

An error should preserve enough structured context for UI and logs without leaking sensitive payloads.

## Dependency rule

The dependency graph remains:

```
Editor UI
   ↓
IAIOrchestrator
   ↓
{IContextProvider, IToolRegistry, IPermissionManager, IConfigurationManager, ISecretStorage, ILogger, IErrorHandler, IAIProvider}
   ↓
Concrete provider(s)
```

Concrete providers must never become dependencies of the Godot core/editor foundations.

## Compatibility rule

Future providers must implement the same provider contract without requiring changes to the core dependency direction.

The first implementation is NVIDIA Nemotron. OpenAI, Gemini, Ollama, and other OpenAI-compatible/local providers remain future implementations.
