# DEVELOPMENT_ROADMAP.md

## Как ориентироваться в разработке

Основная рабочая ветка сейчас: `master`.

Формат позиции:
`ЭТАП.ПОДЭТАП` → конкретная техническая цель.

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

## 1. NIM FIRST MILESTONE — текущий этап

Цель: получить реально работающий NVIDIA NIM внутри Android Godot Editor.

### 1.1 Provider transport
🟩🟩 HTTPS + OpenAI-compatible chat endpoint.

### 1.2 NVIDIA configuration
🟩🟩
- provider: `nvidia_nemotron`
- base URL: `https://integrate.api.nvidia.com/v1`
- model: `nvidia/nemotron-3-ultra-550b-a55b`

### 1.3 NIM Editor UI
🟥🟥 **ТЕКУЩАЯ ПОЗИЦИЯ**
- найти правильную точку интеграции в Android Editor;
- создать touch-friendly NIM panel;
- статус подключения;
- поле API key;
- Test Connection.

### 1.4 Secret storage
🟥🟥
- Android-compatible local storage;
- API key не попадает в Git/project/logs;
- storage abstraction оставить пригодной для последующего secure backend.

### 1.5 Chat
🟥🟥
- message input;
- send/cancel;
- streamed response;
- ошибки;
- empty/long response handling.

### 1.6 Runtime/UI event bridge
🟩🟥 Частично готов.
Нужно окончательно связать worker/provider events с UI без блокировки Editor.

### 1.7 First physical smoke test
🟥🟥 **ТРЕБУЕТСЯ ФИЗИЧЕСКИЙ ТЕСТ**
Только после готовности 1.3–1.5.

Проверка:
1. Install APK.
2. Launch Editor.
3. Open NIM.
4. Enter/save API key.
5. Test Connection.
6. `Hello. Reply with exactly: NIM_OK`
7. Проверить `NIM_OK`.
8. Второй coding request.
9. Streaming.
10. Invalid key/network error.

### 1.8 First milestone gate
🟥🟥

Условие перехода:
**BUILD + INSTALL + LAUNCH + NIM REQUEST + RESPONSE verified on physical Android device.**

---

## 2. PROJECT CONTEXT — v0.2

### 2.1 Project identity
🟥🟥

### 2.2 Current scene
🟥🟥

### 2.3 Selected node
🟥🟥

### 2.4 Current script
🟥🟥

### 2.5 Debugger/errors context
🟥🟥

### 2.6 Controlled context assembly
🟥🟥

**Переход:** только после завершения этапа 1.

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

**«Переходим на 1.3»**
→ продолжить с NIM Editor UI.

**«Переходим на 1.4»**
→ продолжить с API-key storage.

**«Переходим на 1.7»**
→ подготовить физический smoke test; не считать его выполненным без реального устройства.

**«Готовы к v0.2?»**
→ проверить gate 1.8, а не просто наличие успешного CI.

**«Готовы к релизу?»**
→ отдельно проверить build, install, launch, functional verification, regression и release packaging.

---

## Current position

**1.3 — NIM Editor UI**

Следующий переход:
**1.3 → 1.4 → 1.5 → 1.6 → 1.7 → 1.8 → v0.2**

Текущий physical-test requirement: 🟥🟥 NOT YET.
Current v0.2 gate: 🟥🟥 NOT READY.
