---
title: Firebolt APIs
---

[![semantic-release: conventional](https://img.shields.io/badge/semantic--release-conventional-e10079?logo=semantic-release)](https://github.com/semantic-release/semantic-release)

# Firebolt APIs

Firebolt APIs are defined by [OpenRPC schemas](https://spec.open-rpc.org) and used to generate SDK and documentation artifacts.

This repo contains the OpenRPC source for every Firebolt module, the three published SDK packages, and the CI/toolchain that compiles and validates them.

## Packages

| Package | Description |
|---|---|
| [`@firebolt-js/sdk`](src/sdks/core) | Core APIs for app developers |
| [`@firebolt-js/manage-sdk`](src/sdks/manage) | Device management APIs |
| [`@firebolt-js/discovery-sdk`](src/sdks/discovery) | Content discovery APIs |

## Repository layout

```
src/openrpc/        # OpenRPC JSON source — one file per module (source of truth)
src/schemas/        # Shared JSON Schema definitions
src/sdks/           # npm workspace packages (generated — do not hand-edit build/ or dist/)
requirements/       # Normative specification documents
.github/workflows/  # CI pipelines
```

## Build

Requires Node.js LTS and npm 7+.

```bash
npm ci                # install dependencies
npm run dist          # validate → compile → build all SDKs → test
npm run compile       # compile dist/firebolt-open-rpc.json only
npm run validate      # validate all OpenRPC sources
npm test              # run jest unit tests
npm run clean         # remove dist/ and workspace artifacts
```

## How compilation works

1. Each `src/openrpc/<module>.json` is validated against the OpenRPC spec.
2. All modules are merged into `dist/firebolt-open-rpc.json`.
3. The compiled OpenRPC is sliced into per-SDK subsets (core / manage / discovery).
4. TypeScript/JavaScript SDK source is code-generated from each slice.
5. Jest tests exercise the generated SDKs against mock responses.

**Never edit files under `src/sdks/*/build/` or `src/sdks/*/dist/`** — they are generated outputs.

## Authoring APIs

All API changes start in `src/openrpc/<module>.json`. Key conventions:

- Method names: `Module.method` (PascalCase module, camelCase method).
- Use the `"property"` tag for getter/setter/subscriber triples — only define the getter; the toolchain generates the rest.
- Use `"property:immutable"` for read-only properties.
- Declare capabilities via `x-uses`, `x-manages`, or `x-provides` inside a `"capabilities"` tag block.
- Every result schema needs at least one `"examples"` entry.

See [`requirements/`](requirements/) for normative specification documents and [`requirements/style-guide-and-template.md`](requirements/style-guide-and-template.md) for the spec template.

## Testing CI locally with `act`

The MFOS integration test job can be run locally using [`act`](https://github.com/nektos/act), which runs GitHub Actions workflows in Docker.

### Prerequisites

```bash
# Install act (macOS/Linux)
brew install act        # macOS
# or see https://github.com/nektos/act#installation for Linux

# Required system packages on Linux
sudo apt-get install -y xvfb x11-utils google-chrome-stable
```

### Setup

The `INTENT` Actions variable must be present. Create `.act.vars` in the repo root (it is git-ignored):

```
INTENT={"result":{"lmt":0,"us_privacy":"1-N-","discovery":{"navigateTo":{"action":"search","data":{"query":"{\"task\":\"runTest\",\"params\":{\"certification\":true,\"exceptionMethods\":[],\"methodsToBeExcluded\":[\"Lifecycle.finished\"]},\"action\":\"FIREBOLT-ALL\",\"context\":{\"communicationMode\":\"SDK\"},\"metadata\":{\"target\":\"MFOS\",\"targetVersion\":\"NIL\"},\"asynchronous\":false,\"appType\":\"firebolt\"}"},"context":{"source":"voice"}}}}}
```

### Run

```bash
act -j RunStandaloneTests --var-file .act.vars
```

### Known quirks

- **Chrome** — `act` uses a stripped Ubuntu image; the workflow installs `google-chrome-stable` automatically via the "Install Chrome" step.
- **Xvfb** — `xdpyinfo` may not connect on all runners. The readiness check is non-fatal; headless Chrome does not require a live display.
- **FCA webpack** — expect `ℹ ｢wdm｣: Compiled with warnings.` (not "successfully") on a clean install due to optional plugin stubs. This is normal and harmless.
- **Cached repos** — `act` caches the `mock-firebolt` and `firebolt-certification-app` clones between runs. Use `make mfos-clean-all` to force a fresh clone.

## Commit conventions

This repo uses [Conventional Commits](https://www.conventionalcommits.org/) enforced by commitlint.

```
<type>(<scope>): <Subject in sentence case>
```

Valid types: `feat`, `fix`, `build`, `chore`, `ci`, `docs`, `perf`, `refactor`, `revert`, `style`, `test`.

## License

Copyright 2023 Comcast Cable Communications Management, LLC — see [LICENSE](LICENSE) and [NOTICE](NOTICE).
