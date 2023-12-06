# Firebolt RPC Requirements

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Bart Catrysse   | Liberty        |
| Piotr Kobzda    | Liberty        |
| Jeremy LaCivita | Comcast        |

## 1. Overview
This document outlines the requirements for remote proceedure call (RPC) APIs surfaced by a Firebolt implementation to Firebolt Apps.

This document does not cover the scope of the Firebolt SDK vs the App itself, and the term "Firebolt App" is meant to denote a fully built App, including the Firebolt SDK.

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Protocol](#3-protocol)
  - [3.1. JSON-RPC](#31-json-rpc)
    - [3.1.1. Asynchronous Events](#311-asynchronous-events)
    - [3.1.2. Provider Interfaces](#312-provider-interfaces)
  - [3.2. Other Protocols](#32-other-protocols)
- [4. Transport](#4-transport)
  - [4.1. API Version](#41-api-version)

## 3. Protocol
Firebolt implmentations **MUST** support RPC using the [JSON-RPC 2.0](https://www.jsonrpc.org/specification) protocol.

The RPC interface of every Firebolt method **MUST** be defined via an [OpenRPC schema](https://spec.open-rpc.org).

RPC method schemas **SHOULD** use the Firebolt OpenRPC Extensions to enable language-specific design patterns to be applied to similar APIs.

Firebolt implementations **MAY** support other RPC protocols in addition to JSON-RPC 2.0, as long as a compatible transport layer is provided so that apps do not have to be rewritten.

### 3.1. JSON-RPC

Firebolt implementations **MUST** support all aspects of the JSON-RPC specification.

Firebolt implementations **MUST** send only one response for each request.

#### 3.1.1. Asynchronous Events
Asynchronous events, aka "notifications," **MUST** be handled by leveraging the common "duplex" pattern where both the Firebolt App & the Firebolt Implementation act as a JSON-RPC Server *and* a JSON-RPC client.

To register for an event, e.g "Sunrise", the Firebolt App would call an RPC method on the Firebolt Implementation called `Sky.onSunrise` with the `listen` parameter set to `true`:

```json
{
    "id": 1,
    "method": "Sky.onSunrise",
    "params": [
        {
            "listen": true
        }
    ]
}
```

This `onSunrise` call **MUST** only have one response: either an empty success result, or an error describing why the event registration was not successful.

If a Firebolt App has registered for an event, e.g. "Sunrise," then the Firebolt Implementation **SHOULD** send any occurences of the "Sunrise" event to the app via a JSON-RPC notification request:

```json
{
    "id": 1,
    "method": "Sky.sunrise",
    "params": []
}
```

#### 3.1.2. Provider Interfaces
Provider Interfaces allow a Firebolt App to "provide" a Firebolt Capability back to the Firebolt Implementation, in the form of an interface dictated by Firebolt and implemented by the app.

Provider Interfaces **MUST** be handled by leveraging the common "duplex" pattern where both the Firebolt App & the Firebolt Implementation act as a JSON-RPC Server *and* a JSON-RPC client.

To register as a provider for a capability, e.g. "xrn:firebolt:capability:sky:sun", the Firebolt App would call an RPC method on the Firebolt Implementation for each interface method in the "xrn:firebolt:capability:sky:sun" interface.

For this example, the "xrn:firebolt:capability:sky:sun" interface consists of:

```typescript
interface Sun {
    function rise(): Promise<void>;
    function set(): Promise<void>;
}
```

To register for this Provider Interface, the Firebolt App would call an RPC method on the Firebolt Implementation called `provide`, with the `methods` parameter set to `['rise', 'set']`, e.g.:

```json
{
    "id": 1,
    "method": "Sky.provide",
    "params": [
        {
            "methods": [
                "Sun.rise",
                "Sun.set"
            ]
        }
    ]
}
```

If the App does not include a method required by the Sun interface, then the Firebolt Implementation **MUST** return an error.

For backwards compatibility, the Firebolt App **MAY** register each method separately, e.g.:

```json
{
    "id": 1,
    "method": "Sky.provide",
    "params": [
        {
            "method": "Sun.rise"
        }
    ]
}
```

and then separately:

```json
{
    "id": 1,
    "method": "provide",
    "params": [
        {
            "method": "Sun.set"
        }
    ]
}
```

In this case, the Firebolt Implementation **MUST NOT** throw errors for an incomplete method list, but rather terminate the App when it's `Application.create()` method is completed if not all required methods are registered.

If a Firebolt App has registered as a capability provider, e.g. "SkySun," then the Firebolt Implementation **SHOULD** call the appropriate methods via the app's JSON-RPC server as neeeded, e.g.:

```json
{
    "id": 1,
    "method": "Sun.rise",
    "params": []
}
```

The app **MUST** respond either either a result or an error.

### 3.2. Other Protocols
Other protocols are outside the scope of this document.

## 4. Transport
The RPC Protocol **MUST** be handled over a WebSocket.

### 4.1. API Version
The Firebolt API Version *and* protocol **MUST** be passsed as part of the Accept header:

```http
Accept: application/firebolt.v{version}+{protocol}
```

e.g.

```http
Accept: application/firebolt.v2.0.0+json-rpc
```
