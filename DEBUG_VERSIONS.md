# DEBUG Versions — контроль переходов версий

## Назначение

Ветка `debug/versions` — отдельный контрольный контур проекта GodotAI для проверки состояния системы между крупными изменениями.

Она НЕ является заменой `SAFE CORE`, `UI TRACK`, `DEVELOPMENT TRACK` или `EXPERIMENTAL`.

Главная задача:

`изменение → DEBUG checkpoint → проверка → физический/CI feedback → фиксация → переход к следующему крупному изменению`

## Правила

1. Каждое крупное изменение получает отдельный DEBUG checkpoint.
2. Для checkpoint фиксируются:
   - базовый commit;
   - изменённые подсистемы;
   - ожидаемый результат;
   - CI;
   - APK;
   - физический Android test, если требуется;
   - найденные регрессии;
   - решение: PASS / HOLD / REWORK.
3. DEBUG не должен использоваться для обхода Safe Core protection.
4. Код Safe Core меняется только после отдельной проверки необходимости.
5. Experimental функции не считаются частью release-кандидата без отдельного перехода в roadmap.
6. Между крупными версиями DEBUG служит точкой возврата и сравнения.
7. APK считается проверяемым только если он однозначно связан с commit/checkpoint.
8. После физического теста результат переносится в handoff/roadmap, а DEBUG checkpoint сохраняется как историческая запись.

## Контрольные уровни

### DEBUG-BASE

Последняя физически проверенная стабильная база.

Текущая база:
- commit: `0201ff8138d89a265176c1a79c1c6e8f918f05fd`
- статус: физически проверено на Android

### DEBUG-v0.2-CANDIDATE

Текущий кандидат перед v0.2 lock:
- code candidate: `d4bced34d95b868c2d87367653ba4d2b7b5a6d75`
- branch candidate: `fix/p1-nim-mobile-chat-ui`
- documentation HEAD: `c35fc592b3a2b85139be9bb24464ea3a5f023bad`
- Android CI: Run #188 — SUCCESS
- APK tag: `build-c35fc592b3a2`
- physical Android test: PENDING

## Что проверяем на каждом крупном переходе

### 1. Repository
- branch/ref;
- commit;
- diff относительно предыдущего checkpoint;
- Safe Core затронут или нет.

### 2. Build
- Android CI;
- APK;
- checksum;
- соответствие APK commit.

### 3. Runtime
- запуск Godot Editor;
- NIM connection;
- API key persistence;
- chat;
- Test Connection;
- Copy Chat;
- UI/mobile regression.

### 4. Context
- project identity;
- project path;
- current scene;
- selected node;
- node type/path;
- selected script;
- debugger/error context;
- granular context scopes.

### 5. Release gate
- физический Android test;
- known issues;
- regression status;
- решение PASS / HOLD / REWORK.

## История checkpoint

| Checkpoint | Commit | Состояние |
|---|---|---|
| DEBUG-BASE | `0201ff8` | Android physically verified |
| DEBUG-v0.2-CANDIDATE | `d4bced3` / docs `c35fc59` | CI passed, physical test pending |

## Переход к следующей версии

Новый крупный этап создаётся только после фиксации предыдущего checkpoint.

Формат:

`DEBUG-vX.Y-<short-name>`

Примеры:
- `DEBUG-v0.2-RELEASE-CANDIDATE`
- `DEBUG-v0.3-CONTEXT`
- `DEBUG-v0.3-AGENT`

## Статусы

- 🟢 PASS — проверено
- 🟡 HOLD — ожидает проверки
- 🔴 REWORK — обнаружена проблема
- ⚪ N/A — не относится к checkpoint

## DEBUG-UI-P1-CHAT-UX-PROTOTYPE

UI checkpoint:

- branch: `ui/p1-chat-ux`
- HEAD at checkpoint start: `46cdeef1846990a96a5ec99a2fb0839c2d43076e`
- base: product branch `319e9f2be2e89c8dd9d332c25b1c6bf002471f09`
- scope: mobile NIM composer / chat viewport only
- changed runtime files:
  - `editor/ai_bridge/ui/nim_editor_panel.cpp`
  - `editor/ai_bridge/ui/nim_editor_panel.h`
- commits ahead of product branch: 5
- Safe Core transport/API contract: unchanged
- CI: 🟢 Run #203 / Run ID `37230521319` SUCCESS
- APK: 🟢 `build-293cb6606d96`
- SHA-256: `203e9951359aea46af86558235fcc31a4659f36057de7cb1fc48dfc688722c22`
- physical Android test: 🟡 READY / NOT STARTED

Expected physical result:

- multiline composer is usable;
- Send row stays visible above keyboard;
- response viewport exposes multiple lines;
- wrapping and scrolling are usable;
- no regression of connection, chat, Copy Chat, API-key persistence or context behavior.

Status: **🟡 READY FOR PHYSICAL TEST**

This checkpoint must not be used to mark v0.2 or release readiness.

## Текущий DEBUG checkpoint

**DEBUG-UI-P1-CHAT-UX-PROTOTYPE**

Parallel release gate remains:

**DEBUG-v0.2-CANDIDATE**

Main v0.2 task remains the physical Android verification of Run #188 before v0.2 lock.

