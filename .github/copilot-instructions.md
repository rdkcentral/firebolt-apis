# Firebolt APIs — GitHub Copilot Instructions

## What this repo is

This is the **Firebolt API specification and SDK source** for the [Firebolt](https://github.com/rdkcentral/firebolt-apis) platform — a JSON-RPC over WebSocket API for TV app development. It contains:

- **`src/openrpc/`** — one OpenRPC JSON file per module (e.g. `device.json`, `lifecycle.json`). These are the *source of truth* for every API.
- **`src/schemas/`** — shared JSON Schema definitions referenced by the OpenRPC files.
- **`src/sdks/core|manage|discovery`** — npm workspace packages. Source is *generated* from OpenRPC; do not hand-edit generated files under `build/` or `dist/`.
- **`dist/firebolt-open-rpc.json`** — compiled artifact produced by `npm run compile`. Checked in only for release; regenerate it locally with `make compile`.
- **`requirements/`** — normative specification documents (Markdown). These describe the *intent* behind the APIs.
- **`.github/workflows/`** — CI pipelines including the MFOS integration test (`run-standalone-mfos-tests.yml`).
- **`.github/fca/`** — patches applied to the firebolt-certification-app before running MFOS tests.

## Build and test commands

```bash
npm run dist        # full pipeline: validate → compile → sdks → test
npm run compile     # compile dist/firebolt-open-rpc.json only
npm run validate    # validate all OpenRPC sources
npm test            # run jest unit tests
npm run clean       # remove dist/ and workspace artifacts
```

Run `act -j RunStandaloneTests --var-file .act.vars` to reproduce the CI integration test locally with `act`.

## How the API compilation pipeline works

1. `npm run validate:each` — validates each `src/openrpc/*.json` file against the JSON Schema + OpenRPC spec.
2. `npm run compile` — runs `firebolt-openrpc openrpc` to merge all module files into `dist/firebolt-open-rpc.json`.
3. `npm run slice --workspaces` — slices the compiled OpenRPC into per-SDK subsets (core / manage / discovery).
4. `npm run sdk --workspaces` — code-generates TypeScript/JavaScript SDK source from the sliced OpenRPC JSON.
5. `npm run test` — runs jest tests that exercise the generated SDK against mock responses.

**Never directly edit files under `src/sdks/*/build/` or `src/sdks/*/dist/`** — they are generated outputs.

## OpenRPC authoring rules

All API changes start in `src/openrpc/<module>.json`. Key conventions:

- Method names follow `Module.method` (PascalCase module, camelCase method) — e.g. `Device.id`, `Lifecycle.ready`.
- Use `"property"` tag for getter/setter/subscriber triples; the toolchain auto-generates the setter and subscriber — only define the getter.
- Use `"property:immutable"` for read-only properties (no setter generated).
- Use `"event"` tag for event methods.
- Capabilities are declared via `x-uses`, `x-manages`, or `x-provides` tags inside a `"capabilities"` tag block.
- All `$ref` schema references should point into `src/schemas/` or the local `#/components/schemas/` section.
- Result schemas must include at least one `"examples"` entry. The first example is used in generated docs.
- `"version"` in each module file is `"0.0.0"` — the actual version is injected at compile time from the root `package.json`.

## Commit conventions

This repo uses [Conventional Commits](https://www.conventionalcommits.org/) enforced by commitlint:

```
<type>(<scope>): <Subject in sentence case>
```

Valid types: `feat`, `fix`, `build`, `chore`, `ci`, `docs`, `perf`, `refactor`, `revert`, `style`, `test`.

Subject must be **sentence case** (first word capitalised, rest lowercase).

Examples:
```
feat(device): Add hdmiInput module
fix(lifecycle): Correct ready event schema
ci: Install Chrome via apt for act compatibility
```

## MFOS integration test setup

The CI job `RunStandaloneTests` (`.github/workflows/run-standalone-mfos-tests.yml`) clones and runs:
- **mock-firebolt** (MFOS) — a mock JSON-RPC server that simulates the Firebolt platform
- **firebolt-certification-app** (FCA) — a test runner app built on webpack 4 + LightningJS

Repos are cloned as siblings to this one in the parent directory. Patches in `.github/fca/` and `.github/mock-firebolt/` are applied after checkout.

The `INTENT` GitHub Actions variable must be set on the repository and controls what test suite FCA runs. Its value is a JSON object POSTed to MFOS at `/api/v1/state/method/parameters.initialization/result`:

```json
{
  "result": {
    "lmt": 0,
    "us_privacy": "1-Y-",
    "discovery": {
      "navigateTo": {
        "action": "search",
        "context": {"source": "voice"},
        "data": {
          "query": "{\"task\":\"runTest\",\"params\":{\"certification\":false},\"context\":{\"communicationMode\":\"Transport\"},\"metadata\":{\"target\":\"MFOS\",\"fireboltVersion\":\"1.5.0\",\"targetVersion\":\"1.0\"},\"standalone\":true}"
        }
      }
    }
  }
}
```

For local `act` runs store this in `.act.vars` (git-ignored):
```
INTENT={"result":{"lmt":0,...}}
```

## Known CI/local quirks

- **`act` uses a stripped Ubuntu image** — `google-chrome-stable` is installed by the "Install Chrome" step before tests run. On real GitHub runners it is already present (no-op).
- **FCA uses webpack 4** — `@lightningjs/core` ≥ 2.12 uses ES2022 class-field syntax that webpack 4 (acorn 6) cannot parse. The `webpack.patch` in `.github/fca/` adds a `babel-loader` rule scoped to `node_modules/@lightningjs/`.
- **`setExternalApiResponse`, `FireboltExtensionInvoker`, `AdditionalFireboltTestCases.json`** — these are optional FCA plugin extension points. Missing-module webpack warnings for them are expected and harmless; they are caught by try/catch in FCA source.
- **`MISSING-RESULT` from MFOS** — means `INTENT` is empty or malformed. Check the `INTENT` variable.

## SDK package names

| Workspace | npm package | Purpose |
|---|---|---|
| `src/sdks/core` | `@firebolt-js/sdk` | Core Firebolt APIs for app developers |
| `src/sdks/manage` | `@firebolt-js/manage-sdk` | Device management APIs |
| `src/sdks/discovery` | `@firebolt-js/discovery-sdk` | Content discovery APIs |

## Requirements documents

Normative specs live in `requirements/specifications/`. They use RFC 2119 keywords (MUST, SHALL, SHOULD, MAY). When adding or changing an API, update the corresponding spec document. New specs should follow the template in `requirements/style-guide-and-template.md`.

---

## API authoring with OpenSpec

This repo uses **OpenSpec** to manage API changes — new modules, new methods, type changes. All
in-flight changes live under `openspec/changes/`. The full governance context (type conventions,
method tags, naming rules, tooling commands) is in `openspec/config.yaml`.

### Workflow commands

| Command | What it does |
|---------|--------------|
| `/opsx:new-fb-api` | **Add a new Firebolt API end-to-end** — interviews you in plain English, resolves all Smithy decisions, creates the change, and implements it. No Smithy knowledge required. |
| `/opsx:modify-fb-api` | **Modify an existing Firebolt API end-to-end** — interviews you to identify the operation and what is changing, detects breaking changes, creates the change, and implements it. No Smithy knowledge required. |
| `/opsc:propose` | Propose a new API change — generates `proposal.md`, `design.md`, `specs/`, `tasks.md` |
| `/opsc:apply` | Work through the tasks in an active change (drafts `.smithy`, runs validation) |
| `/opsc:explore` | Thinking-partner mode — explore a design question before committing to a proposal |
| `/opsc:archive` | Archive a completed change after all tasks are done |

### What the AI does during `/opsc:apply`

When applying a spec change task, the AI will:
1. Read existing `src/smithy/` files to infer type and naming conventions
2. Draft or modify the target `src/smithy/<module>.json` Smithy AST
3. Call `fb-gen --lint` to validate the spec
4. Call `fb-gen --diff` to confirm no unintended upstream drift
5. Mark the task complete and proceed to the next

### MCP tooling (`fb-mcp`)

`fb-mcp` is an MCP server that exposes the SDK generator as structured tools for AI agents.
Configure it in your VS Code `mcp.json`:

```json
{
  "firebolt": {
    "command": "fb-mcp",
    "env": {
      "FB_SPEC_DIR": "${workspaceFolder}/src/smithy"
    }
  }
}
```

Tools available to the AI:
- `list_modules` — list all modules in `src/smithy/`
- `get_module` — full IR summary of a module (method names, types, kinds)
- `validate_module` — parse and lint a spec file, returns errors with no side effects
- `generate` — generate C++/Rust/TS bindings and return file contents (does not write to disk)
- `diff_vs_upstream` — compare Smithy specs against OpenRPC upstream for drift

