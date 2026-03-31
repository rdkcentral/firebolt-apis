# Network Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor | Organization |
| ----------- | ------------ |
| Joe Martin  | Comcast      |

## 1. Overview

Applications want to query for the device's network connectivity state and capabilities, which will allow them to monitor for network connection changes and provide an appropriate experience (such as gracefully stop playback when the network connection is reported as down).

To support this, Firebolt shall provide applications with access to various networking APIs that allow them to query for various properties of the device's local network connection.

### 1.1. User Stories

As an app, I want to...

- Get a simple report of the device's network connection state
- Be notified when the device's connection to the local network has changed

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Network](#3-network)
  - [3.1. Connected State](#31-connected-state)

## 3. Network

The `Network` module will provide methods to various network properties, such as the network connection state.

### 3.1. Connected State

The `Activation` module **MUST** include a `connected` method that returns whether or not the device has an enabled and usable connection to the local network.

This method **MUST** have a corresponding `onConnectedChanged` event to notify listeners when a change to the network connection has occured.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:network:connected` capability.

```javascript
Network.connected()
//> true
```
