# Account and Device Identification Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization |
| -------------- | ------------ |
| Andrew Bennett | Sky          |
| Joe Martin     | Comcast      |

## 1. Overview

Content partners want to understand various identifiers and attributes associated with the device and/or its operator's back-office system.

This information can primarily be used to provide apps with details on the current runtime environment for telemetry purposes and rich data analysis.

This information may also be used to deploy self-configuring apps that can deliver experiences tailored to a specific subset of users.

Other back-office attributes may also be used to leverage additional platform features that are heavily reliant on such identifiers (e.g. advertising and commerce).

### 1.1. User Stories

As an app, I want to...

- Get the operator name of the device

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [4. Device Identification Attributes](#4-device-identification-attributes)
  - [4.1. Operator Name](#41-operator-name)

## 4. Device Identification Attributes

The `Device` module will provide methods allowing apps to query for various identifying attributes of the device.

### 4.1. Operator Name

The `Device` module **MUST** have an `operator` method that returns a string value describing the device's associated operator or managing entity.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:operator` capability.

```javascript
Device.operator()
//> "cableco-australia"
```
