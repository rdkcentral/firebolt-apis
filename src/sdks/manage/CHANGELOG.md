# [0.15.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.14.0...v0.15.0) (2023-07-31)

### Bug Fixes

* Rename Advisory "Committee" to "Board" ([#135](https://github.com/rdkcentral/firebolt-apis/issues/135)) ([ef410c4](https://github.com/rdkcentral/firebolt-apis/commit/ef410c43bbb32414c3aa1d11b43093565cc90edf))
* window fix from firebolt-openrpc 2.0.3 ([8c06dd1](https://github.com/rdkcentral/firebolt-apis/commit/8c06dd1432822719f5634e2877b36efdf02a4809))

### Features

* **Nullable CC Styles** Added support to set and get null in ClosedCaptions style fields ([#150](https://github.com/rdkcentral/firebolt-apis/issues/150)) ([9c511e4](https://github.com/rdkcentral/firebolt-apis/commit/9c511e4fddebcdf5dfc04e9e8e31f98ab7eef680))
* **Window CC Styles** Added windowColor and windowOpacity to closedCaptions style ([#145](https://github.com/rdkcentral/firebolt-apis/issues/145)) ([f65b901](https://github.com/rdkcentral/firebolt-apis/commit/f65b9019bda22400df9b9634c332e720db38118d))
* **Audio Descriptions** Audio Description and Preferred Audio Languages Settings ([#45](https://github.com/rdkcentral/firebolt-apis/issues/45)) ([58f6ea1](https://github.com/rdkcentral/firebolt-apis/commit/58f6ea1dde7a819883eb3da24f879b6a9ecc9a41))

# [0.14.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.13.0...v0.14.0) (2023-06-22)

### Bug Fixes

* **Advertising:** put resetAdvertisingIdentifier back in manage sdk ([ce92ae7](https://github.com/rdkcentral/firebolt-apis/commit/ce92ae7bfff58fa1d3e4bee78c88d5edf0266473))
* * **VoiceGuidance** Change voice guidance limits to 0.5 and 2 ([#137](https://github.com/rdkcentral/firebolt-apis/issues/137)) ([b8f1944](https://github.com/rdkcentral/firebolt-apis/commit/b8f19449efd808639599b162aba61c08ec089c41))

### Features

* **Discovery** Add an event when apps call signIn or signOut ([#133](https://github.com/rdkcentral/firebolt-apis/issues/133)) ([8ba2515](https://github.com/rdkcentral/firebolt-apis/commit/8ba2515948c433ccc38662f223f5fb399cf34841))

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
