# DEVELOPMENT_ROADMAP.md

## Как ориентироваться в разработке

Основная рабочая ветка сейчас: master.

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

## 1. NIM FIRST MILESTONE — текущий этап

Цель: получить реально работающий NVIDIA NIM внутри Android Godot Editor.

### 1.1 Provider transport
🟩🟩 HTTPS + OpenAI-compatible chat endpoint.

### 1.2 NVIDIA configuration
🟩🟩
- provider: nvidia_nemotron
- base URL: https://integrate.api.nvidia.com/v1
- model: nvidia/nemotron-3-ultra-550b-a55b

### 1.3 NIM Editor UI
🟩🟥 Частично готов.
- touch-friendly NIM panel;
- статус подключения;
- поле API key;
- Test Connection;
- Send/cancel;
- streaming output.

### 1.4 Secret storage
🟩🟥 Частично готов.
- Android-compatible local storage;
- API key не попадает в Git/project/logs;
- storage abstraction оставлена пригодной для последующего secure backend.

### 1.5 Chat
🟩🟥 Частично готов.
- message input;
- send/cancel;
- streamed response;
- ошибки;
- response buffer reset per turn.

### 1.6 Runtime/UI event bridge
🟩🟥 Частично готов.
Worker/provider events доставляются в UI через deferred main-thread обработку; request-id guard защищает от stale events; lifecycle Panel → Runtime исправлен.
Остаётся подтверждение поведения на реальном Android Editor.

### 1.7 First physical smoke test / corrected APK
🟩🟩 VERIFIED on corrected Android build

Тестовый пакет до диагностики:
- Commit: 4f5028ef9f87447ab71f75bbef6f925f9e63d220
- CI run: #58 🟩
- APK: godot-android-editor-arm64.apk
- SHA-256: 33332749c987ad64707022008bb898bc641b71d0c92e6629597a7fca2353dbe4
- Direct APK:
  https://github.com/UniGi5/godotAI/releases/download/build-4f5028ef9f87/godot-android-editor-arm64.apk

Проверка:
1. Install APK.
2. Launch Editor.
3. Confirm no startup crash.
4. Open NIM.
5. Enter/save API key.
6. Test Connection.
7. Verify NIM_OK.
8. Send a second coding request.
9. Verify streaming.
10. Test invalid-key handling.
11. Test network-error handling.
12. Reopen editor and verify current key persistence.

Фактический результат предыдущего физического теста: APK устанавливался, но при запуске практически сразу закрывался без видимой ошибки. Причина установлена: release APK не содержал основной native `libgodot_android.so`.

Исправление подтверждено CI #64: корректный APK 192,421,503 bytes содержит `lib/arm64-v8a/libgodot_android.so` размером 168,766,080 bytes; zipalign и apksigner проходят.

Новый физический тестовый APK: https://github.com/UniGi5/godotAI/releases/download/build-11e68e28cfc8/godot-android-editor-arm64.apk

Диагностический commit: `025846eaa556f187035f2f0f56df6171464c0ffc`.
Исправление packaging: `11e68e28cfc80d7d705e0cccb0a29b96cb8d9cb6`.

Переход 1.7 → 1.8: только после исправления/подтверждения launch path на реальном устройстве.

### 1.8 First milestone gate
🟩🟥 PARTIAL — launch + NIM chat + project/editor context verified; streaming/error regression remains

Условие:
BUILD + INSTALL + LAUNCH + NIM REQUEST + RESPONSE verified on physical Android device, плюс базовая проверка streaming/error paths.

---

## 2. PROJECT CONTEXT — v0.2

### 2.1 Project identity
🟩🟩 Physically verified — Nemotron identified the project name.

### 2.2 Current scene
🟩🟥 Implemented and included in editor context; physical field-level verification pending.

### 2.3 Selected node
🟩🟥 Implemented; latest API/lifecycle fixes are in master; physical verification pending.

### 2.4 Current script
🟥🟥 NEXT implementation block

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

«Переходим на 1.3» → продолжить с NIM Editor UI.
«Переходим на 1.4» → продолжить с API-key storage.
«Переходим на 1.7» → подготовить/проводить физический smoke test; не считать его выполненным без реального устройства.
«Готовы к v0.2?» → проверить gate 1.8, а не просто наличие успешного CI.
«Готовы к релизу?» → отдельно проверить build, install, launch, functional verification, regression и release packaging.

---

## Current position

2.3 — Selected node context implementation ready; physical verification pending

Последний CI: #64 🟩.
Корректный APK опубликован как prerelease asset.
Следующий переход:
2.3 → 2.4 → 2.5 → 2.6 → v0.2.

Текущий physical-test requirement: 🟥🟥 REQUIRED только после новой APK-сборки с изменением поведения — проверить selected-node context и regression текущего NIM baseline.
Current v0.2 gate: 🟩🟥 PARTIAL — не готов к упаковке v0.2 до завершения context + streaming/error regression.
