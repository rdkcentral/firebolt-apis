# [0.11.0](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.10.0...v0.11.0) (2023-05-01)


### Bug Fixes

* **api:** Removing future APIs ([bac48f5](https://github.com/rdkcentral/firebolt-core-sdk/commit/bac48f5bd0223b765d896d11766b049450c3f37d))
* Build SDK before npm publish ([#64](https://github.com/rdkcentral/firebolt-core-sdk/issues/64)) ([1994587](https://github.com/rdkcentral/firebolt-core-sdk/commit/199458742f13d46c8d55b60e75112f8de393a8c4))
* Change doc examples to https ([#79](https://github.com/rdkcentral/firebolt-core-sdk/issues/79)) ([0da43e6](https://github.com/rdkcentral/firebolt-core-sdk/commit/0da43e666842bb75d20f9585c0d1f3f0236388ee))
* Don't ignore source files when pulbishing to npm [skip ci] ([19d695b](https://github.com/rdkcentral/firebolt-core-sdk/commit/19d695bcee81a1c7e89749b04d427ec50581c5a1))
* FIRESDK-31 returned response from Lifecycle.ready method ([#81](https://github.com/rdkcentral/firebolt-core-sdk/issues/81)) ([7d13347](https://github.com/rdkcentral/firebolt-core-sdk/commit/7d133473829c30227246b53d32b92c609398344f))
* Initiate semantic-release ([f2fe209](https://github.com/rdkcentral/firebolt-core-sdk/commit/f2fe209ef08a3ce0cb470666da29720e7ab24946))
* **Lifecycle:** Remove private LifecycleManagement API ([a3208ea](https://github.com/rdkcentral/firebolt-core-sdk/commit/a3208ea8cc9cc9d818fb2bc7e70453f2d368c4dd))
* **READMEs:** Add various READMEs, remove Discovery SDK ([80365af](https://github.com/rdkcentral/firebolt-core-sdk/commit/80365afad63faf3a67a8f679047c3fc618aaa413))
* **README:** Update Readme ([0b8c20a](https://github.com/rdkcentral/firebolt-core-sdk/commit/0b8c20a1f25824b6647a553a1c05a6a8cfac47e8))
* **release:** Bring back npm plugin, turn of publish ([2fc9196](https://github.com/rdkcentral/firebolt-core-sdk/commit/2fc91962d85e050350415dd628d6144e8569299d))
* **release:** Copy broilerplate docs into each workspace ([2e6bd34](https://github.com/rdkcentral/firebolt-core-sdk/commit/2e6bd34b4317e9663aeafc173f6c6f9a6f249e83))
* **release:** Drop redundant copy of each SDK's /dist/ ([97dd3da](https://github.com/rdkcentral/firebolt-core-sdk/commit/97dd3dadfa278c76a4a99357c9eb3ede6dfc59f7))
* **release:** Fix bug where CHANGELOG.md only updated in [@latest](https://github.com/latest) channel ([9d96665](https://github.com/rdkcentral/firebolt-core-sdk/commit/9d96665616dd6d644f9c47411b8a41f8c33d8e30))
* **release:** Fixed untested mv/cp ([a329280](https://github.com/rdkcentral/firebolt-core-sdk/commit/a329280cf099ada6d42e9b3d451a10c35bb60c67))
* **release:** Initiating semantic-release test ([17063e8](https://github.com/rdkcentral/firebolt-core-sdk/commit/17063e885215701dbab982ab058d916ec54badba))
* **release:** Only scrub pre-release notes on prod release cycle ([4cf4de3](https://github.com/rdkcentral/firebolt-core-sdk/commit/4cf4de3bc2df1669191f595190a8fb5d8f955394))
* **release:** Pointing to next branch for `firebolt-openrpc` ([e25b57a](https://github.com/rdkcentral/firebolt-core-sdk/commit/e25b57ac6986187752e39d78881c0ad529b39226))
* **release:** Remove redundant build, fix broilerplate copy ([836b246](https://github.com/rdkcentral/firebolt-core-sdk/commit/836b246040d6b92131156b24cc69c401de5d7424))
* **release:** Stop pushing mono-artifact to npm ([a7c772e](https://github.com/rdkcentral/firebolt-core-sdk/commit/a7c772e143662f8b7650280eea12262e70bc3f2a))
* **rpc:** Better rpc.discover capability ([91bc54b](https://github.com/rdkcentral/firebolt-core-sdk/commit/91bc54b470dffe14464d95f318d6fb49474ed3ff))
* **specification:** Removing unused capabilities ([befcba4](https://github.com/rdkcentral/firebolt-core-sdk/commit/befcba40cd70f95de59c3d7ceb5d25c82c7b7926))
* Support arrays of EventObjects ([67f561d](https://github.com/rdkcentral/firebolt-core-sdk/commit/67f561d52a4d8aa0ef8cdabe6fadb91c6af00d65))
* **tests:** Update tests per previous commit ([8010c5b](https://github.com/rdkcentral/firebolt-core-sdk/commit/8010c5b4c52d4b02e0ac33a3eabd0a460f1ce39a))
* **typo:** Fixed misspelled "primitives" ([c3403c9](https://github.com/rdkcentral/firebolt-core-sdk/commit/c3403c9fba7ee037acb1aa53d3b866898689ed04))
* Updated secure storage spec to allow null as result value ([#84](https://github.com/rdkcentral/firebolt-core-sdk/issues/84)) ([7ed1fed](https://github.com/rdkcentral/firebolt-core-sdk/commit/7ed1fed9ab9f5d84927c4e31c2816e15da0d6f44))
* Word publish scripts ([#78](https://github.com/rdkcentral/firebolt-core-sdk/issues/78)) ([df66ebf](https://github.com/rdkcentral/firebolt-core-sdk/commit/df66ebf642de26dced139998b2834fc8f801e88b))
* Word publish scripts ([#78](https://github.com/rdkcentral/firebolt-core-sdk/issues/78)) ([3ee86bf](https://github.com/rdkcentral/firebolt-core-sdk/commit/3ee86bf587e94d51d662c24d4eb0fe63a799f213))


### Features

* Add Secure Storage module ([#77](https://github.com/rdkcentral/firebolt-core-sdk/issues/77)) ([e633428](https://github.com/rdkcentral/firebolt-core-sdk/commit/e633428843d802b330d5fc6d93a4a5e3e5370521))
* Added new methods for additionaInfo ([fe3c488](https://github.com/rdkcentral/firebolt-core-sdk/commit/fe3c48878f4c18550174c8de416335c2a7f8316f))
* Make capabilities:info and capabilities:request non-negotiable ([e79ff5a](https://github.com/rdkcentral/firebolt-core-sdk/commit/e79ff5a88aa41eaaa37c7ad2a717b234500df1b5))
* **Metrics:** Add distributor Metrics.event API ([e5b87bd](https://github.com/rdkcentral/firebolt-core-sdk/commit/e5b87bd2fa8f0f3be8d17b5fadd657a88491a974))
* **specification:** Add script to generate Firebolt Version Specification JSON ([d417ac4](https://github.com/rdkcentral/firebolt-core-sdk/commit/d417ac4b7f96b314476401d20bf2e2b71bce5de5))
* Trigger ([9792bee](https://github.com/rdkcentral/firebolt-core-sdk/commit/9792beee52a1937a0e90bebcd5a80265e5f7eaac))
* Trigger ([01156ca](https://github.com/rdkcentral/firebolt-core-sdk/commit/01156ca1ae023d944984637dad3bb9e5151941c1))
* Trigger ([35cb430](https://github.com/rdkcentral/firebolt-core-sdk/commit/35cb430f7ffb5ece384b8799707aeb945e72aa9e))
* Trigger ([eba005f](https://github.com/rdkcentral/firebolt-core-sdk/commit/eba005f3565475fb01a0d73f907839c621b74e43))
* Trigger ([52bf827](https://github.com/rdkcentral/firebolt-core-sdk/commit/52bf827508bcec2995ccbbae6b614a8b839132bc))
* Trigger ([2a2b739](https://github.com/rdkcentral/firebolt-core-sdk/commit/2a2b73910b96017afa4ee6e3c3d3420591ca61ac))
* Trigger ([ccfc364](https://github.com/rdkcentral/firebolt-core-sdk/commit/ccfc364b342947ab2e1ffadbe5e3825a207c4d83))
* Trigger ([b3e6f83](https://github.com/rdkcentral/firebolt-core-sdk/commit/b3e6f83fd6326b1ddd341ef30baa3c5b63382f62))
* Turn on dryRun ([228e7d9](https://github.com/rdkcentral/firebolt-core-sdk/commit/228e7d97af909933ed2b3a5984d76e957cc98f7f))
* Turn on dryRun ([f90d475](https://github.com/rdkcentral/firebolt-core-sdk/commit/f90d47595def476cd09f4e646f1f99a22180791f))

# [0.11.0-next.8](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.7...v0.11.0-next.8) (2023-05-01)


### Bug Fixes

* **specification:** Removing unused capabilities ([befcba4](https://github.com/rdkcentral/firebolt-core-sdk/commit/befcba40cd70f95de59c3d7ceb5d25c82c7b7926))

# [0.11.0-next.7](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.6...v0.11.0-next.7) (2023-05-01)


### Bug Fixes

* Support arrays of EventObjects ([67f561d](https://github.com/rdkcentral/firebolt-core-sdk/commit/67f561d52a4d8aa0ef8cdabe6fadb91c6af00d65))
* **typo:** Fixed misspelled "primitives" ([c3403c9](https://github.com/rdkcentral/firebolt-core-sdk/commit/c3403c9fba7ee037acb1aa53d3b866898689ed04))


### Features

* **Metrics:** Add distributor Metrics.event API ([e5b87bd](https://github.com/rdkcentral/firebolt-core-sdk/commit/e5b87bd2fa8f0f3be8d17b5fadd657a88491a974))

# [0.11.0-next.6](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.5...v0.11.0-next.6) (2023-05-01)


### Features

* Added new methods for additionaInfo ([fe3c488](https://github.com/rdkcentral/firebolt-core-sdk/commit/fe3c48878f4c18550174c8de416335c2a7f8316f))

# [0.11.0-next.5](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.4...v0.11.0-next.5) (2023-04-28)


### Features

* Make capabilities:info and capabilities:request non-negotiable ([e79ff5a](https://github.com/rdkcentral/firebolt-core-sdk/commit/e79ff5a88aa41eaaa37c7ad2a717b234500df1b5))

# [0.11.0-next.4](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.3...v0.11.0-next.4) (2023-04-25)


### Bug Fixes

* **Lifecycle:** Remove private LifecycleManagement API ([a3208ea](https://github.com/rdkcentral/firebolt-core-sdk/commit/a3208ea8cc9cc9d818fb2bc7e70453f2d368c4dd))

# [0.11.0-next.3](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.2...v0.11.0-next.3) (2023-04-25)


### Bug Fixes

* **api:** Removing future APIs ([bac48f5](https://github.com/rdkcentral/firebolt-core-sdk/commit/bac48f5bd0223b765d896d11766b049450c3f37d))
* **tests:** Update tests per previous commit ([8010c5b](https://github.com/rdkcentral/firebolt-core-sdk/commit/8010c5b4c52d4b02e0ac33a3eabd0a460f1ce39a))

# [0.11.0-next.2](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-next.1...v0.11.0-next.2) (2023-04-18)


### Bug Fixes

* **release:** Fix bug where CHANGELOG.md only updated in [@latest](https://github.com/latest) channel ([9d96665](https://github.com/rdkcentral/firebolt-core-sdk/commit/9d96665616dd6d644f9c47411b8a41f8c33d8e30))

# [0.11.0-one-repository.5](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.11.0-one-repository.4...v0.11.0-one-repository.5) (2023-04-17)


### Bug Fixes

* **release:** Bring back npm plugin, turn of publish ([2fc9196](https://github.com/rdkcentral/firebolt-core-sdk/commit/2fc91962d85e050350415dd628d6144e8569299d))


# [0.10.0](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.9.0...v0.10.0) (2023-02-06)


### Bug Fixes

* Capability module needs capability tags ([#71](https://github.com/rdkcentral/firebolt-core-sdk/issues/71)) ([6f0af1b](https://github.com/rdkcentral/firebolt-core-sdk/commit/6f0af1b9712faab137b1652ea337d5f284196ad4))
* Change doc examples to https ([#79](https://github.com/rdkcentral/firebolt-core-sdk/issues/79)) ([c7047af](https://github.com/rdkcentral/firebolt-core-sdk/commit/c7047af9f3fa47e8cd7d252c3bbd321fa8f3d125))
* FIRESDK-31 returned response from Lifecycle.ready method ([#81](https://github.com/rdkcentral/firebolt-core-sdk/issues/81)) ([efc740f](https://github.com/rdkcentral/firebolt-core-sdk/commit/efc740f7899897981cc840f12efe30f3e9543be4))
* Updated openrpc version to 1.8.0-next.2 ([#85](https://github.com/rdkcentral/firebolt-core-sdk/issues/85)) ([b988c41](https://github.com/rdkcentral/firebolt-core-sdk/commit/b988c4159b154f8c041b766f794618250448bce0))
* Updated secure storage spec to allow null as result value ([#84](https://github.com/rdkcentral/firebolt-core-sdk/issues/84)) ([4117ad7](https://github.com/rdkcentral/firebolt-core-sdk/commit/4117ad79322c8a3decd59f5ad52d5dfe6cf2f2a4))
* Use new openrpc template code with bug fixes ([#69](https://github.com/rdkcentral/firebolt-core-sdk/issues/69)) ([9fed6fc](https://github.com/rdkcentral/firebolt-core-sdk/commit/9fed6fcb71b9914e91674f5e80f7d61673cc66fe))
* Word publish scripts ([#78](https://github.com/rdkcentral/firebolt-core-sdk/issues/78)) ([a3846e0](https://github.com/rdkcentral/firebolt-core-sdk/commit/a3846e0db22e1221547ad97a019aba3850c51f6a))


### Features

* Add content-access api, deprecate entitlements, remove availabi… ([#83](https://github.com/rdkcentral/firebolt-core-sdk/issues/83)) ([f3c8017](https://github.com/rdkcentral/firebolt-core-sdk/commit/f3c8017eb391119e47d810426fdae4b11d8e0c38))
* Add Secure Storage module ([#77](https://github.com/rdkcentral/firebolt-core-sdk/issues/77)) ([f62e4ae](https://github.com/rdkcentral/firebolt-core-sdk/commit/f62e4aeb9325df00c6a2484cf3aaa0b756bd8113))
* New Capabilities API ([#63](https://github.com/rdkcentral/firebolt-core-sdk/issues/63)) ([0ba5ef5](https://github.com/rdkcentral/firebolt-core-sdk/commit/0ba5ef5e030ce740e40fd5ad30ca5cfd100cf32e))
* Trigger ([607825b](https://github.com/rdkcentral/firebolt-core-sdk/commit/607825bd5547c74a8a7707f751446ab0e069d9f9))
* Turn on dryRun ([dcddc60](https://github.com/rdkcentral/firebolt-core-sdk/commit/dcddc6068f91505d97457ed04eb8e2996dab9278))




# 0.9.0

### Features

* Adding Availabilities API ([#65](https://github.com/rdkcentral/firebolt-core-sdk/issues/65)) ([ec940dd](https://github.com/rdkcentral/firebolt-core-sdk/commit/ec940dd1a7a6865f18d64ada69793c87556a172e))
* Tagging Capabilities ([e3b6ee2](https://github.com/rdkcentral/firebolt-core-sdk/commit/e3b6ee2475fbd9157a40bc92490c06df135ebc34))

### Bug Fixes

* Don't ignore source files when publishing to npm [skip ci] ([cb26ff2](https://github.com/rdkcentral/firebolt-core-sdk/commit/cb26ff2e09416613c5557e76966eccbe0ec66d54))
* Build SDK before npm publish ([#64](https://github.com/rdkcentral/firebolt-core-sdk/issues/64)) ([f221fa3](https://github.com/rdkcentral/firebolt-core-sdk/commit/f221fa34e24e29e86487b1ec98468b64f495d134))
* **Lifecycle:** lifecycle state api returns correct state in all circumstances ([31e405c](https://github.com/rdkcentral/firebolt-core-sdk/commit/31e405c124d29a3e87294dc4b356ff8df9972af8))

# 0.8.1

- Added Device.version().firmware to surface the underlying hardware firmware version
- Added Device.version().api to surface the latest Firebolt API supported by this device
- Deprecated Device.version().os which does not have a formal specification. Use `firmware` instead.

# 0.8.0

- Tune Intents are now supported in `navigateTo` events
- Added TypeScript declarations for Settings and Events
- Fixed/Removed test-enabling code from SDK
- Fixed bug where the SDK would initialize itself even when not being used

# 0.7.0

- Removed all `bigint` types from TypeScript declarations, in favor of `number`, since bigint is not widely supported across browsers. This changes impacts:
    - Device.screenResolution
    - Device.videoResolution
    - Discovery.purchasedContent
    - Metrics.mediaProgress
    - Metrics.mediaSeeking
    - Metrics.mediaSeeked
    - Parameters.initialization

To upgrade to 0.7.0 simply change the type of any Firebolt Promise resolutions from `bigint` to `number`, e.g.:

```typescript
const res:[bigint, bigint] = await Device.screenResolution()
```

Should become:

```typescript
const res:[number, number] = await Device.screenResolution()
```

# 0.6.2

- Fixed incompatibility with Jest 26 due to [jest/issues/10565](https://github.com/facebook/jest/issues/10565)


# 0.6.1

- Changed Firebolt build to use `.mjs` extension
- Firebolt builds are now pure ES6 modules, not bundled with Webpack
- Added `types` path to package.json
- Fixed TypeScript declarations for `FlatMap` and `BooleanMap`
- Added TypeScript return type declarations for `listen` and `once` (all modules)
- Added TypeScript declaration for `clear` method (all modules)
- Changed `{}` return type to `void` for listener callbacks

# 0.6.0

- Added support for [rdkcentral/mock-firebolt](https://github.com/rdkcentral/mock-firebolt/) via a WebSocket transport layer
- Deprecated Accessibility.closedCaptions and voiceGuidance, created properties for Accessibility.closedCaptionsSettings and voiceGuidanceSettings, which support subscribers
- Deprecated Device.listen('deviceNameChanged'), added support for subscribing to Device.name()
- Added support for subscribing to property changes: Device.audio, hdcp, hdr, name, network, screenResolution, videoResolution, Advertising.policy, Discovery.policy, Localization.language
- Added proper TypeScript declarations for Discovery.entityInfo and Discovery.purchasedContent
- Fixed race condition w/ Transport Layer initialization

# 0.5.2

- Added Parameters modules
- Fixed typo in Advertising.config example result for docs/Mock
- Updated Metrics.error signature to include `type` as first parameter
- Created window.__firebolt.testHarness handshake (for Mock TL only)
- Added `LocalizedString` type for localized string dictionaries
- Updated `Discovery.watchNext` to use `LocalizedString` for `title` and each property of `images`
- Added `OfferingType` and `ProgramType` parameters to `Discovery.purchasedContent`

# 0.5.1

- Cleaned up errors in various Mock responses
- Methods that call private Metrics APIs, e.g. Lifecycle.ready, now do so **after** promise resolution

# 0.5.0

- Updated TS declarations (.d.ts) to detect which event is being passed to `.listen()` methods
- Updated all `listen()` and `once()` methods to return a `Promise`
- Renamed `verifyContentRating` and `verifyPurchase` to `approveContentRating` and `approvePurchase` respectively
- Added `Profile.flags()` for distributor-specific profile flags
- Added optional `source` field to all `LifecycleEvents`
- Complete rewrite of `Metrics` APIs (see docs)
- Added `policyChanged` events to `Discovery` and `Advertising`
- Fixed duplicate RPC `listen` calls when listening to an event in slightly different ways, e.g. `once()` vs `listen()`
- Added Account, Authentication, Keyboard, Profile, SecondScreen modules
- Added Federated Search APIs to Discovery
- Added TypeScript/Intellisense declarations file
- Fixed spelling error on Accessibility module name
- Moved the `coppa` parameter for `Advertising.confg()` into the `options` object, and made it optional
- Final version of `Advertising.policy().skipRestriction` semantics
