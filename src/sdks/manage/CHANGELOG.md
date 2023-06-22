# [0.13.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.12.0...v0.13.0) (2023-06-09)

### Bug Fixes

* Grant providers should allow null responses for deferred challenges ([#128](https://github.com/rdkcentral/firebolt-apis/issues/128)) ([0ddd11a](https://github.com/rdkcentral/firebolt-apis/commit/0ddd11af282aed85112fb739993ae58cfc1c4910))
* Point to `firebolt-openrpc` 2.0.1 ([c57cb21](https://github.com/rdkcentral/firebolt-apis/commit/c57cb218343fd058e2e6e676d52d9d0c904ad9a8))
* Added Changelog note about accessory removal ([02e81c0](https://github.com/rdkcentral/firebolt-apis/commit/02e81c0f0233862e2d2386989943a840eddc5b6a))

### Features

* Add SecureStorage.setForApp, removeForApp, .clearForApp methods. ([#127](https://github.com/rdkcentral/firebolt-apis/issues/127)) ([4422c79](https://github.com/rdkcentral/firebolt-apis/commit/4422c79122fc35e7b35180254be52bf33c64ab5b))

# [0.12.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.11.0...v0.12.0) (2023-05-18)

### Bug Fixes

* Updated `Advertising.resetIdentifier` capability ([47e730c](https://github.com/rdkcentral/firebolt-core-sdk/commit/47e730c4572ca2b8b9fdc3b2062121ef802914aa))
* Removed `Accessory` module, which was not finished or ready for release ([6bcbb3f](https://github.com/rdkcentral/firebolt-apis/commit/6bcbb3fa347cb412e0d973beb6ecff7fe966607a))

### Features

* Add the `Advertising.skipRestriction` API and included in Manage SDK ([#122](https://github.com/rdkcentral/firebolt-core-sdk/issues/122)) ([da9d75f](https://github.com/rdkcentral/firebolt-core-sdk/commit/da9d75f8c29bf04674e3de692874888796665a9a))


# [0.11.0](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.10.0...v0.11.0) (2023-05-01)

This is the first release of the Firebolt Manage SDK, which is used by first party, or trusted, apps to manage a Firebolt device.

### Features

* Accessory module
* Account module
* AcknowledgeChallenge module
* Advertising module
* ClosedCaptions module
* Device module
* Keyboard module
* Localization module
* Metrics module
* PinChallenge module
* Privacy module
* UserGrants module
* VoiceGuidance module
* Wifi module
