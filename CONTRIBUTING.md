# Contributing
If you would like to contribute code to this project you can do so through GitHub by forking the repository
and sending a pull request.
Before RDK accepts your code into the project you must sign the RDK Contributor License Agreement (CLA).

## Project Structure
The SDK is auto-generated using OpenRPC schemas for Firebolt methods and events.

This ensures consistent docs, api, and tests.

Code and doc-generation is handled by `@firebolt-js/openrpc`, which is a package of tools for generating SDKs from OpenRPC schemas. It is open source and hosted on GitHub:
[Firebolt OpenRPC](https://www.github.com/rdkcentral/firebolt-openrpc/).


The Firebolt Core SDK schemas are open source and available on GitHub:
[Firebolt Core SDK](https://www.github.com/rdkcentral/firebolt-core-sdk/).

For manageability, each module has it's own [OpenRPC](https://spec.open-rpc.org) schema file, and they are merged into single schema when building.

Top-level repository contents include:

| Path | Description |
|------|-------------|
| build | Target for various sdk & doc builds |
| build/docs/markdown | Target for markdown documentation of the SDK |
| dist | Target for production distributions, to be hosted on npm, etc |
| src | Contains all schemas and code & doc generate src, including scripts and templates
| src/modules| Contains top-level OpenRPC schemas for each module |
| src/schemas| Contains reusable JSON-Schemas |
| src/template| Contains templates for docs & various sdk builds |


All of the JSON files in `modules` are merged together using `src/template.json` as the container. When merging, every module's methods have the module's `title` (from `info.title`) inserted before the method name and joined with a `.`. The `components`, e.g. `schemas`, etc., from each module are also merged. Here is a detailed diagram of how the merge script works.
![Merge Script Control Flow Diagram](./merge-script-control-flow.svg)

To see the merged OpenRPC output, run:

```
npm run build:openrpc
```

and look at the output in `dist/firebolt-open-rpc.json`.

Reusable Firebolt schemas are stored in `src/schemas` and injected into the generated schema.

Reusable non-Firebolt schemas are stored in `src/external` and injected into the generated schema when referenced.

Absolute `$ref` links are left as is.

To generate the SDK, run:

```
npm run build:sdk
```

and look at the generated JS in `build/sdk/javascript`.

To test the SDK, run:

```
npm run dist:sdk
```

This builds the production version of the SDK and runs all tests.

To re-run the tests (w/out building the SDK) you can, run:

```
npm run test
```

Note that this is mainly useful for test-writing when the SDK is not changing.

To generate the docs, run:

```
npm run dist:docs
```
