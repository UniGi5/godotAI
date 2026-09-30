# Godot AI Bridge — Living Roadmap

## Phase 0 — Engineering foundation

Status: in progress

- [x] Canonical agent context in Git.
- [x] Development workflow contract.
- [x] Architecture overview.
- [x] Direct Android ARM64 APK delivery.
- [x] Push-triggered CI.
- [x] Remove unrelated platform build workflows.
- [x] Record Android startup crash as an unresolved runtime defect.
- [x] Add v0.1 interface contracts.
- [x] Add ADR documentation policy.
- [ ] Add automated APK structural/signature checks.
- [ ] Add reproducible Android runtime diagnostics.
- [ ] Resolve startup crash with evidence and regression coverage.

## Phase 1 — Architecture

Status: next active phase

- [x] Provider/core dependency rule.
- [x] Subsystem boundaries.
- [x] v0.1 interface contracts.
- [ ] Decide concrete implementation layout.
- [ ] Decide GDScript vs C++ responsibilities.
- [ ] Define request/response event model.
- [ ] Define cancellation model.
- [ ] Define provider capability model.
- [ ] Define configuration schema.
- [ ] Define secret-storage adapter contract.
- [ ] Define tool schema and permission model.
- [ ] Define testing seams and mocks.
- [ ] Record decisions in ADRs.

## Phase 2 — Godot Editor Core

- [ ] Editor lifecycle integration.
- [ ] Dock/panel shell.
- [ ] Orchestrator lifecycle.
- [ ] Signals/events.
- [ ] Async request handling.
- [ ] Cancellation UI.
- [ ] Error presentation.

## Phase 3 — NVIDIA Nemotron

- [ ] OpenAI-compatible request model.
- [ ] Authentication integration.
- [ ] Streaming parser.
- [ ] Timeout/cancellation.
- [ ] Error normalization.
- [ ] Provider conformance tests.

## Phase 4 — Context, Tools, Permissions

- [ ] Bounded context providers.
- [ ] Tool registry.
- [ ] Permission manager.
- [ ] First safe read-only tools.
- [ ] Auditing.

## Phase 5 — Security and Reliability

- [ ] Secret storage implementation.
- [ ] Security regression tests.
- [ ] Failure/retry policies.
- [ ] Runtime diagnostics.
- [ ] Performance/budget controls.

## Phase 6 — Additional Providers

- [ ] OpenAI.
- [ ] Gemini.
- [ ] Ollama.
- [ ] Generic OpenAI-compatible provider.
- [ ] Local model adapter.

## Phase 7 — Controlled Git/GitHub

- [ ] Git tool layer.
- [ ] GitHub tool layer.
- [ ] Fine-grained permissions.
- [ ] Review/audit UI.
