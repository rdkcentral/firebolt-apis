# Release Notes

## 0.6.0

- Added support for [rdkcentral/mock-firebolt](https://github.com/rdkcentral/mock-firebolt/) via a WebSocket transport layer
- Deprecated Accessibility.closedCaptions and voiceGuidance, created properties for Accessibility.closedCaptionsSettings and voiceGuidanceSettings, which support subscribers
- Deprecated Device.listen('deviceNameChanged'), added support for subscribing to Device.name()
- Added support for subscribing to property changes: Device.audio, hdcp, hdr, name, network, screenResolution, videoResolution, Advertising.policy, Discovery.policy, Localization.language
- Added proper TypeScript declarations for Discovery.entityInfo and Discovery.purchasedContent
- Fixed race condition w/ Transport Layer initialization

## 0.5.2

- Added Parameters modules
- Fixed typo in Advertising.config example result for docs/Mock
- Updated Metrics.error signature to include `type` as first parameter
- Created window.__firebolt.testHarness handshake (for Mock TL only)
- Added `LocalizedString` type for localized string dictionaries
- Updated `Discovery.watchNext` to use `LocalizedString` for `title` and each property of `images`
- Added `OfferingType` and `ProgramType` parameters to `Discovery.purchasedContent`

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
