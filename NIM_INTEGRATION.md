# NVIDIA NIM Integration

## Scope

This fork integrates NVIDIA NIM directly into the Godot Android Editor. The first milestone is intentionally limited to:

- NVIDIA NIM provider configuration.
- API key entry and local secret storage.
- Test Connection.
- Simple chat with streamed responses.
- Android Editor APK build and real-device verification.

Agent tools, project editing, RAG, MCP, shell execution, and autonomous loops are outside the first milestone.

## Provider

- Provider ID: `nvidia_nemotron`
- Base URL: `https://integrate.api.nvidia.com/v1`
- API endpoint: `POST /v1/chat/completions`
- Default model: `nvidia/nemotron-3-ultra-550b-a55b`
- Authentication: HTTP Bearer token supplied by the user.

The API key must never be committed to Git, embedded in the APK, written to a project file, or emitted into logs.

## Current architecture

```
Godot Editor
  -> AIBridgeRuntime
  -> AIOrchestrator
  -> AINVIDIAProvider
  -> OpenAI-compatible HTTPS client
  -> NVIDIA NIM
```

The provider performs HTTP work on a worker thread so network operations do not block the editor UI.

## Build

The repository workflow builds an Android ARM64 release APK on every push. The resulting file is:

`dist/godot-android-editor-arm64.apk`

The workflow also validates APK alignment/signature and publishes a direct APK release asset.

## Verification states

A successful CI build proves compilation and APK packaging only. It does not prove that the Android Editor launches or that a real NVIDIA request succeeds.

The physical smoke test for the first milestone is:

1. Install the generated APK on a real Android ARM64 device.
2. Launch the Godot Editor.
3. Open the NVIDIA NIM UI.
4. Enter the NVIDIA API key locally.
5. Save the key.
6. Run Test Connection.
7. Send: `Hello. Reply with exactly: NIM_OK`
8. Verify the response is `NIM_OK`.
9. Send a second normal coding question.
10. Verify streamed response handling.
11. Check error handling with an invalid key or unavailable network.

Only after this test passes should the first milestone be marked functionally verified and work on v0.2 begin.

## Status

- CI Android APK: ready.
- NVIDIA provider transport: implemented.
- Nemotron 3 Ultra 550B default model: configured.
- NIM Editor panel: not yet implemented.
- Persistent secure Android key storage: not yet implemented.
- Test Connection UI: not yet implemented.
- Simple Chat UI: not yet implemented.
- Real-device functional verification: pending.

