# ADR-0004: Runtime Validation Is Separate From Build Success

## Status

Accepted

## Decision

A successful APK build does not imply a successful Android runtime.

Runtime validation is tracked separately from:

1. compilation;
2. APK packaging;
3. APK validation;
4. installation;
5. application launch;
6. smoke tests.

## Rationale

The current project has produced a valid downloadable APK while the user observed a startup crash. Treating build success as runtime success would hide the defect.

## Consequence

Agents must collect runtime evidence such as logcat/crash output and must not classify a startup crash as expected without evidence.
