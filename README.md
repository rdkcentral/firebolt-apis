# firebolt-core-sdk
Firebolt Core SDK modules

## Dependencies
This project depends on the `refactor/split-utils-and-modules` branch of the `ottx/firebolt-openrpc` project.

Note that it's currently configured to link to that branch via local filesystem:

```
"devDependencies": {
    "@firebolt-js/openrpc": "../firebolt-openrpc/",
}
```

Also note that this project has "stolen" the package name of the original `ottx/firebolt-openrpc` package, as that's what is used to publish the SDK to NPM, and the SDK now lives here.

The `ottx/firebolt-openrpc` project has been renamed `@firebolt-js/openrpc` to keep the same NPM organization, but name it after the tools that it leverages.

All of the Core SDK modules, schemas, and templates have been moved here, and the /utils/ to generate code, docs, etc, remain in `firebolt-openrpc`.

The JS templates, `src/template/js/sdk` live in **both** repositories and are merged (`firebolt-core-sdk` overrides any duplicates).

This allows for sharing of:

- Transport Layer
- Event module (e.g. listen, etc.)
- Logging
- etc.

This is very much a work-in-progress, please reach out to @jlaciv000 for more info.