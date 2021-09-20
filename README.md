---
title: Firebolt Core SDK
---
# Firebolt JS SDK
For building Firebolt compliant apps.

## Usage
Using the Firebolt SDK requires access to a private npm package.

To install the package, run:

```
npm install @firebolt-js/sdk
```

You may need to log in to npm first:

```
> npm login
npm notice Log in on https://registry.npmjs.org/
Username: _
```

Simply follow the prompts to log in and then you should be able to install the package using the `install` command above.


To use the package, import one of it's modules, e.g.:

```js
import { Lifecycle } from '@firebolt-js/sdk'
```

## Contributing
The SDK is auto-generated using OpenRPC schemas for Firebolt methods and events.

The Firebolt OpenRPC schemas, as well as the code used to generate the JavaScript Firebolt SDK, are stored in the github repository. Contact [jeremy.lacivita@comcast.com](mailto:jeremy.lacivita@comcast.com) for access.

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
npm run build:docs
```
