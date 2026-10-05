# GodotAI v0.2 — Release Notes / Verification Record

## Status

- Release line: **v0.2**
- State: **FINAL RELIABILITY / RELEASE REVIEW**
- Branch: `fix/p1-nim-mobile-chat-ui`
- Godot baseline: **4.7.2 Stable**
- Android target: **ARM64 Editor APK**
- AI provider: NVIDIA NIM
- Model: `nvidia/nemotron-3-ultra-550b-a55b`

## Exact fixed candidate — physically verified

- Runtime fixes: `959ba1c`, `f3dce5f`, `7a4600e`
- Packaged runtime checkpoint: `24215c0ae9d1338e49848d2e19d5124c8971d21e`
- CI #260 / Run ID `37341176576`: **SUCCESS**
- APK tag: `build-24215c0ae9d1`
- APK: `godot-android-editor-arm64.apk`
- Size: **192,454,267 bytes**
- SHA-256: `10119215eb70824752ffaa2c15d53901f769c02e84a6e76bec5c0fcf809a003f`
- Direct APK: https://github.com/UniGi5/godotAI/releases/download/build-24215c0ae9d1/godot-android-editor-arm64.apk

## Physical Android verification — PASS

Exact APK tested on a real Android device:
- launch: PASS
- NIM panel: PASS
- Nemotron greeting: PASS
- ECHO-1 `NIM CHAT OK`: PASS
- ECHO-2 `Nemotron 3 Ultra`: PASS
- ECHO-3 `391`: PASS
- ECHO-4 project context: PASS
- ECHO-5 `END-OF-TEST`: PASS
- previous “Connected but silent chat” regression: **CLEARED**

## Connection reliability observation

First Test Connection attempt again returned **HTTP 503**; retry succeeded and chat then worked.

Current evidence:
- one visible POST is issued;
- historical anti-redundant-request protection is present;
- no deterministic duplicate-request path found;
- 503 is not classified as a code defect without reproducible evidence.

**HTTP 503 is open and is not marked fixed.**

## Stable transport contract

Frozen during v0.2 release review:
- `stream=false`
- `max_tokens=256`
- `chat_template_kwargs.enable_thinking=false`
- `chat_template_kwargs.force_nonempty_content=true`

## Protected areas

No casual changes to:
- Godot 4.7.2 baseline;
- provider architecture;
- HTTPS/TLS;
- API-key persistence;
- stable NIM request/response path;
- Test Connection;
- Copy Chat;
- Android packaging.

Behavior-changing modifications require a new CI build and physical regression cycle.

## Experimental tracks

MCP Bridge, Agent mode, Safe Editing and streaming replacement remain **FROZEN until v0.2 Release Lock is explicitly closed**.

## Release gate

- physical chat regression: **PASS**
- exact candidate APK: **PASS**
- first-attempt 503: **OPEN OBSERVATION**
- final reliability/release review: **IN PROGRESS**
- public non-prerelease release: **NOT YET**

Do not treat the intermittent 503 as fixed without reproducible evidence.
