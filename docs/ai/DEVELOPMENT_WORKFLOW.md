# DEVELOPMENT WORKFLOW

## 1. Agent startup

Every agent starts by reading:

- `AGENTS.md`
- `docs/ai/MASTER_PROJECT_CONTEXT.md`

Then inspect the files relevant to the requested task.

Never infer repository state from memory when the current repository can be inspected directly.

## 2. Change discipline

Before editing:

1. inspect the current file;
2. understand the dependency path;
3. identify existing tests;
4. decide the smallest coherent change.

After editing:

1. validate syntax;
2. run the narrowest useful tests;
3. inspect Git diff/status;
4. commit with a descriptive message;
5. push;
6. inspect CI;
7. investigate failures before continuing.

## 3. CI contract

For the current project phase:

```
every push
  ↓
📊 Static checks
  ↓
📱 Android ARM64 Editor Release
  ↓
validate APK
  ↓
publish direct APK Release asset
```

PR builds may run validation, but releases should be published from push/manual execution, not from untrusted fork pull requests.

## 4. APK delivery contract

The user must receive a real file:

```
godot-android-editor-arm64.apk
```

Do not use:

- an AAB;
- an Actions artifact ZIP as the user-facing download;
- a ZIP containing an APK;
- unrelated platform binaries.

The preferred delivery mechanism is a GitHub Release asset attached directly as `.apk`.

## 5. APK validation

A successful build must be followed by output validation.

At minimum:

- verify the file exists;
- verify it has the APK extension;
- inspect file type/size;
- fail if the expected APK was not produced.

Where Android build tools are available, add stronger checks such as APK/package/signature validation.

## 6. Runtime crash policy

A built APK is not automatically a working app.

When a device crash is reported:

1. reproduce if possible;
2. collect `adb logcat` or equivalent crash output;
3. classify the failure;
4. create the smallest reproducible test;
5. fix the root cause;
6. add a regression test where practical.

Do not mark a startup crash as expected merely because the build completed.

## 7. Git commits

Commit messages should clearly describe the change.

Preferred examples:

- `ci: build and publish only Android ARM64 APK`
- `docs: add agent project context`
- `core: add provider abstraction`
- `nvidia: implement streaming provider`

Keep commits coherent and easy to revert.

## 8. Documentation

Architecture changes require documentation.

Important design decisions should be recorded as ADRs under `docs/ai/adr/`.

Agent-facing rules belong in Markdown, not only in chat history.

## 9. Secrets

Never commit:

- API keys;
- OAuth secrets;
- signing keystores;
- passwords;
- access tokens;
- private SSH keys.

Use environment variables, GitHub Actions Secrets, or the project's future Secret Storage subsystem.

## 10. Provider isolation

No provider-specific implementation may leak into Godot Core.

Provider-specific HTTP, authentication, payload, streaming, and error handling belong behind the provider interface.

## 11. Testing priorities

Prefer this progression:

```
pure unit test
 → integration test
 → editor test
 → CI test
 → device smoke test
```

Use deterministic tests for protocol/serialization logic whenever possible.

## 12. Current investigation

The direct APK delivery mechanism has been validated by the user. The latest observed problem is an Android startup crash.

Until crash logs establish the cause, agents should treat it as an unresolved runtime defect.

Useful future diagnostic additions include:

- manifest/package validation;
- ABI validation;
- release-vs-debug comparison;
- renderer initialization diagnostics;
- automated emulator smoke testing where runner constraints permit;
- captured logcat output on failure.

## 13. Do not overbuild

Automation should reduce repetitive work, not create a second platform to maintain.

Prefer existing GitHub Actions, Gradle, SCons, Godot test facilities, and Android tooling where they already solve the required problem.
