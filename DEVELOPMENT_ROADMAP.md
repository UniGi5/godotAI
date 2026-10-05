# DEVELOPMENT_ROADMAP.md

## Как ориентироваться в разработке

Основная рабочая ветка сейчас: `fix/p1-nim-mobile-chat-ui`.

Формат позиции:
ЭТАП.ПОДЭТАП → конкретная техническая цель.

При каждом существенном продолжении работы статус должен указывать:
- текущую позицию;
- что завершено;
- что блокирует переход;
- следующий раздел;
- требуется ли физический тест;
- готов ли продукт к v0.2/release.

---

## 0. FOUNDATION — базовая инфраструктура

### 0.1 Repository / Godot base
🟩🟩 База Godot Engine и Android Editor build pipeline.

### 0.2 Android CI
🟩🟩 Android ARM64 APK автоматически собирается после push.

### 0.3 Direct APK distribution
🟩🟩 Workflow публикует прямой APK asset.

### 0.4 AI Bridge runtime
🟩🟩 Runtime, orchestrator, provider registry и lifecycle подключены.

**Переход:** завершён.

---

## 1. NIM FIRST MILESTONE

### 1.1 Provider transport
🟩🟩 HTTPS + OpenAI-compatible chat endpoint.

### 1.2 NVIDIA configuration
🟩🟩
- provider: nvidia_nemotron
- base URL: https://integrate.api.nvidia.com/v1
- model: nvidia/nemotron-3-ultra-550b-a55b

### 1.3 NIM Editor UI
🟩🟩 Базовый mobile UI физически проверен:
- touch-friendly NIM panel;
- статус подключения;
- API key;
- Test Connection;
- Send/cancel;
- chat output;
- Copy Chat.

### 1.4 Secret storage
🟩🟩 API key persistence физически подтверждена.

### 1.5 Chat
🟩🟩 Базовый non-stream chat физически подтверждён. Пользователь также подтвердил исправления Test Connection и Copy Chat на Android.

### 1.6 Runtime/UI event bridge
🟩🟩 Базовый lifecycle и request/response path физически подтверждены.

### 1.7 Physical baseline
🟩🟩 **CONFIRMED**

Подтверждённый baseline:
- Commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- CI Run: #156
- Run ID: `37057401793`
- Result: SUCCESS
- APK: `godot-android-editor-arm64.apk`
- SHA-256: `52e385775ff38585c1e80a556a0c885ef2e9eee4dfa62bca1247fecbcba5fda5`
- Release tag: `build-0201ff8138d`

Физически подтверждено:
1. Android Editor запускается.
2. NVIDIA NIM connection работает.
3. Nemotron отвечает.
4. Test Connection после успеха не зависает.
5. Copy Chat копирует историю из conversation.
6. Android UI стабилен.

### 1.8 First milestone gate
🟩🟩 **BASELINE PASSED**

NIM first-milestone baseline больше не блокирует дальнейшую разработку. Для новых изменений, затрагивающих context/streaming/UI, физический тест требуется только после успешного CI соответствующего нового APK.

---

## 2. PROJECT CONTEXT — v0.2

### 2.1 Project identity
🟩🟩 code implemented

### 2.2 Current scene
🟩🟩 code implemented

### 2.3 Selected node
🟩🟩 code implemented

### 2.4 Current script
🟩🟩 code implemented
- selected node script path;
- selected script source;
- source limit: 12,000 characters;
- explicit truncation marker.

### 2.5 Debugger/errors context
🟩🟩 code implemented — explicit `debugger_context` scope exposes active session, paused state, error count and warning count via Godot's native debugger API.

### 2.6 Controlled context assembly
🟩🟩 code implemented — explicit scopes now include `project_identity`, `scene_context`, `selection_context`, `script_context`, `debugger_context`, and the compatibility/full `editor_context`. Existing provider contract is unchanged.

**Current blocker:** none for CI/package availability. A valid APK exists for code candidate `d4bced3`; physical Android regression has PASSED.

---

## 3. SAFE EDITING — после v0.2

### 3.1 Proposed changes
🟥🟥
### 3.2 Preview/diff
🟥🟥
### 3.3 Explicit apply
🟥🟥
### 3.4 Undo/recovery
🟥🟥

---

## 4. AGENT — после стабильного editing layer

### 4.1 Tool registry
🟥🟥
### 4.2 Permission manager
🟥🟥
### 4.3 Agent loop
🟥🟥
### 4.4 Controlled tool execution
🟥🟥

MCP, shell и автономные действия не добавляются раньше необходимости.

---

## 5. RELEASE ENGINEERING

### 5.1 Automated regression
🟥🟥
### 5.2 Physical Android smoke workflow
🟥🟥
### 5.3 Versioning
🟥🟥
### 5.4 Release APK
🟥🟥
### 5.5 Release notes / migration
🟥🟥

---

## Navigation rules

Если пользователь пишет:

«Переходим на 1.3» → продолжить с NIM Editor UI.
«Переходим на 1.4» → продолжить с API-key storage.
«Переходим на 1.7» → использовать подтверждённый baseline и не повторять уже выполненный smoke test без причины.
«Готовы к v0.2?» → проверить текущий code/CI gate и необходимость физического regression test для новых изменений.
«Готовы к релизу?» → отдельно проверить build, install, launch, functional verification, regression и release packaging.

---

## Current position

### v0.2 — Project Context

- Project identity: 🟩🟩
- Current edited scene: 🟩🟩
- Selected node: 🟩🟩
- Current script path/source: 🟩🟩
- Script source limit/truncation: 🟩🟩
- Debugger/errors context: 🟩🟩 code implemented
- Controlled context assembly: 🟩🟩

### Verification gate

- Current branch: `fix/p1-nim-mobile-chat-ui`
- Current branch HEAD: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Code candidate for physical test: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- Current HEAD CI: 🟩🟩 Run #188 / `build-c35fc592b3a2` SUCCESS.
- Physical Android test for current HEAD: 🟩🟩 PASS — user confirmed successful physical test.
- Previous NIM/mobile baseline: 🟩🟩 physically confirmed at `0201ff8`.
- v0.2: 🟩🟩 physical verification PASSED; release-lock documentation is next.
- Release: 🟥🟥 not ready.

**Next engineering action:** create/record the `DEBUG-v0.2-RELEASE-CANDIDATE` checkpoint, lock v0.2, then begin release engineering.

**Do not label the current HEAD as release-ready yet: v0.2 release lock and release engineering are still pending.**
