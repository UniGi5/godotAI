# ADR-0001: Agent Context Is Repository Source

## Status

Accepted

## Decision

Project-wide AI-agent instructions are stored in version-controlled Markdown files in the repository.

The entry point is `AGENTS.md`. Detailed context lives under `docs/ai/`.

## Rationale

Chat history is not a durable project interface. Repository-local documentation lets independent agents start from the same current contract and makes architectural changes reviewable.

## Rule

Additive clarification is allowed. Silent removal or weakening of master requirements is not allowed. Superseding requirements must be documented as a new decision.

