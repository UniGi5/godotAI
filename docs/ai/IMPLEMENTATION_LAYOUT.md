# Godot AI Bridge — v0.1 Implementation Layout

This is the implementation map for the architecture described in the master context.

The repository is a Godot Engine source fork. The AI Bridge should be integrated with the editor without contaminating provider-neutral core contracts with vendor-specific behavior.

## Proposed source layout

```
editor/
└── ai_bridge/
    ├── core/
    │   ├── interfaces/
    │   │   ├── ai_provider.h
    │   │   ├── ai_orchestrator.h
    │   │   ├── context_provider.h
    │   │   ├── tool.h
    │   │   ├── tool_registry.h
    │   │   ├── permission_manager.h
    │   │   ├── configuration_manager.h
    │   │   ├── secret_storage.h
    │   │   ├── logger.h
    │   │   └── error_handler.h
    │   ├── orchestrator/
    │   ├── context/
    │   ├── tools/
    │   ├── permissions/
    │   ├── configuration/
    │   ├── secrets/
    │   ├── logging/
    │   └── errors/
    ├── providers/
    │   ├── nvidia/
    │   ├── openai/
    │   ├── gemini/
    │   ├── ollama/
    │   └── openai_compatible/
    ├── ui/
    │   └── dock/
    └── tests/
```

This tree is an architectural target, not a requirement to create every file immediately.

## Responsibility split

### `editor/ai_bridge/core`

Provider-neutral orchestration and security contracts.

This layer must not import NVIDIA/OpenAI/Gemini/Ollama implementation headers.

### `editor/ai_bridge/providers`

Concrete provider adapters.

The NVIDIA adapter is the first implementation.

### `editor/ai_bridge/ui`

Godot Editor presentation and lifecycle integration.

The UI talks to the orchestrator rather than to a provider directly.

### `editor/ai_bridge/tests`

Provider-independent tests, integration tests, and editor-facing regression tests.

## Godot integration point

The editor-facing entry point should use Godot's existing `EditorPlugin`/editor lifecycle facilities where appropriate.

The exact registration mechanism must be selected after inspecting the existing editor plugin initialization path. Do not patch arbitrary startup code when an existing extension/plugin seam can host the feature.

## Language boundary

The implementation may use C++ for engine/editor integration and low-level transport primitives, with GDScript where it materially simplifies editor-facing behavior.

The language choice must not change the dependency direction or security model.

## Provider boundary

The provider implementation may know:

- endpoint URLs;
- HTTP headers;
- payload formats;
- streaming protocol;
- provider error codes.

It must not know:

- dock widgets;
- editor menus;
- project settings UI;
- tool approval UI;
- concrete orchestrator UI state.

## First implementation slice

The first code slice should be deliberately small:

1. define provider-neutral contracts;
2. create orchestrator lifecycle skeleton;
3. add a no-op/mock provider for deterministic tests;
4. wire a minimal editor dock;
5. add request/stream/cancel state handling;
6. only then add NVIDIA transport.

This avoids coupling UI work to a provider implementation that may still change.

## Security implementation order

1. Secret boundary.
2. Permission boundary.
3. Tool registry.
4. Context boundary.
5. Provider transport.
6. UI.

No privileged tool should be exposed before the permission boundary exists.

## Testing seams

Every major interface should be replaceable in tests.

At minimum:

- mock provider;
- mock context provider;
- mock tool registry;
- deterministic permission manager;
- in-memory secret storage for tests only;
- test logger;
- deterministic error injection.

## Naming

Use stable, descriptive names. Prefer subsystem names over vendor names outside the provider subtree.

Examples:

```
AIOrchestrator
AIProvider
NvidiaProvider
ToolRegistry
PermissionManager
ContextEngine
SecretStorage
```

## Migration rule

As implementation begins, update this file with the real paths. Do not let architectural documentation and source layout drift apart.
