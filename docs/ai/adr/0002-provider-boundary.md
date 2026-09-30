# ADR-0002: Provider Isolation

## Status

Accepted

## Decision

Godot Core/editor foundations depend on an `IAIProvider` abstraction rather than a concrete vendor.

The initial implementation is NVIDIA Nemotron, but provider-specific HTTP, authentication, payload, streaming, and error behavior remain behind the provider boundary.

## Rationale

This preserves replaceability for OpenAI, Gemini, Ollama, generic OpenAI-compatible APIs, and local models without coupling the core to a vendor.

## Consequence

Orchestration, context, tools, permissions, configuration, secrets, logging, and UI are designed against stable internal contracts.

