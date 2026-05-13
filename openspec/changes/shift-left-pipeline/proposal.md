## Change: Shift-Left Validation Pipeline

## What it does

Extends the OpenSpec session into a full end-to-end validation loop: spec authoring
→ generated unit tests → client build gate → sideload to device. A new API added
via `/opsx:new-fb-api` can be proved working on-device without leaving the AI session
or manually operating any of the five repos involved.

The change also fixes foundational workspace debt that would otherwise make the
pipeline silently fragile for new contributors: a missing profile file and undeclared
cross-repo path assumptions.

---

## Problem Statement

Today, the first real signal that a new Firebolt C++ API is correct arrives at
Gate 4 — manual inspection on a physical device. The cheaper gates (lint, unit
tests, client build) either do not exist in the workflow or are not wired together.

Specific breakage identified during exploration:

1. **Missing profile file** — `fb-conformance/run.py` expects
   `firebolt-cpp-client/firebolt-cpp-client.profile.yaml`, which does not exist.
   The full conformance profile is silently broken.

2. **Undeclared workspace dependencies** — `rdke.profile.yaml` references
   `../../firebolt-js-client/src/openrpc` (a separate GitHub repo). No manifest,
   README, or setup script declares this requirement. New contributors get silent
   `fb-gen` failures.

3. **Event and Provider gaps at Gate 2** — generated unit tests (`fb-testgen`)
   skip `MethodKind::Event` and `MethodKind::Provider` entirely. These are the
   method kinds most likely to fail silently on device.

4. **Provider is unimplemented in the generator** — `emit.rs` emits a
   `// TODO: wire up provider` stub for every Provider method. Providers do not
   work at all in the generated client; this is undetected by any current gate.

5. **No build+deploy orchestration** — going from a passing lint to a running
   binary on the SoC requires manually operating `fb-gen`, `build-stack.sh`,
   `build-native.sh`/`build-cross.sh`, and `iterate.sh` across four directories.
   No single entry point exists.

---

## Scope

### Repo: `firebolt-apis`
- `openspec/changes/shift-left-pipeline/` — this change
- `openspec/rdke.profile.yaml` — no change needed (correct as-is)

### Repo: `firebolt-cpp-client`
- Add `firebolt-cpp-client.profile.yaml` (symlink or copy of
  `../firebolt-apis/openspec/rdke.profile.yaml`)

### Repo: `firebolt-sdk-gen`
- `crates/fb-testgen/src/lib.rs` — add Event (Phase A: registration smoke; Phase B:
  dispatch via `fireEvent()` injector)
- `crates/fb-backend-cpp/src/emit.rs` — implement Provider stub (replace TODO with
  actual transport wiring for `registerFooProvider`)
- `crates/fb-backend-cpp/src/emit_tests.rs` — emit compile smoke test for Provider
  methods

### Repo: `firebolt-cpp` (workspace root)
- Add `check-workspace.sh` — validates required sibling repos exist, emits clear
  errors with clone instructions if not
- Add `workspace.manifest.yaml` — machine-readable list of required repos, relative
  paths, and purpose
- Update `fb-conformance/run.py` — fix full profile `profile_yaml` path (points at
  non-existent file today); monarch profile left untouched
- Update `build-stack.sh` — add `--change <name>` flag triggering `fb-gen` regen for
  the named change's modules before cmake rebuild

### Repo: `firebolt-dobby-testapp`
- Add `generated/` subdir — `build-native.sh` uses `generated/main.cpp` when present,
  falls back to `app/main.cpp`
- `fb-gen --emit gateway-probe` populates `generated/main.cpp` with a call to every
  getter and event registration in the spec

### Skill: `openspec-apply-change`
- After Gate 1 (lint) passes: automatically run Gate 2 (compile + run generated tests)
- After Gate 2 passes: offer Gate 3 (`build-stack.sh --change <name>`)
- After Gate 3 passes: offer Gate 4 (gateway probe → iterate.sh)

---

## Gate Chain

```
Gate 0  Interview        /opsx:new-fb-api — describe in English
Gate 1  Lint             fb-gen --lint                     (seconds, auto)
Gate 2  Unit tests       emit tests → compile → run        (seconds, auto)
Gate 3  Client build     build-stack.sh --change <name>    (minutes, offered)
Gate 4  Device           gateway-probe → iterate.sh        (minutes, explicit)
```

Gates 1–2 run automatically in the AI session on every iteration. Gates 3–4 are
offered only after the prior gate passes and require explicit user confirmation.

---

## What is explicitly out of scope

- Provider Gate 2 dispatch testing (blocked until Provider impl is complete; deferred
  to a follow-on change)
- entos Gate 4 / sideload path: `firebolt-dobby-testapp` has no entos equivalent.
  Tracked as task **4.6** for a follow-on change; does not block this pipeline.
- Monarch client: untouched. This pipeline targets `firebolt-cpp-client` (full
  profile) and `firebolt-entos-runtime-apis` (entos profile) only.
