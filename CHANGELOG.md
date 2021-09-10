# Release Notes

## 0.5.2

- Added Parameters modules
- Fixed typo in Advertising.config example result for docs/Mock
- Updated Metrics.error signature to include `type` as first parameter
- Created window.__firebolt.testHarness handshake (for Mock TL only)

## 0.5.1

- Cleaned up errors in various Mock responses
- Methods that call private Metrics APIs, e.g. Lifecycle.ready, now do so **after** promise resolution

## 0.5.0

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
