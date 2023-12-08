# Firebolt RPC Requirements

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Andrew Bennett  | Sky            |
| Bart Catrysse   | Liberty        |
| Piotr Kobzda    | Liberty        |
| Jeremy LaCivita | Comcast        |
| Kevin Pearson   | Comcast        |

## 1. Overview
This document outlines the requirements for remote proceedure call (RPC) APIs surfaced by a Firebolt implementation to Firebolt Apps.

This document does not cover the scope of the Firebolt SDK vs the App itself, and the term "Firebolt App" is meant to denote a fully built App, including the Firebolt SDK.

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Protocol](#3-protocol)
  - [3.1. OpenRPC Documents](#31-openrpc-documents)
    - [3.1.1. OpenRPC Ids](#311-openrpc-ids)
    - [3.1.2. Duplex Linking](#312-duplex-linking)
  - [3.2. Asynchronous Events](#32-asynchronous-events)
  - [3.3. Provider Interfaces](#33-provider-interfaces)
- [4. Transport](#4-transport)
  - [4.1. API Version](#41-api-version)

## 3. Protocol
Firebolt implmentations **MUST** support RPC using the [JSON-RPC 2.0](https://www.jsonrpc.org/specification) protocol.

The RPC interface of every Firebolt method **MUST** be defined via an [OpenRPC document](https://spec.open-rpc.org).

RPC method definitions **SHOULD** use the [Firebolt OpenRPC](https://github.com/rdkcentral/firebolt-openrpc/) Extensions to enable language-specific design patterns to be applied to similar APIs.

Firebolt implementations **MAY** support other RPC protocols in addition to JSON-RPC 2.0, as long as a compatible transport layer is provided so that apps do not have to be rewritten.

Firebolt implementations **MUST** support all aspects of the JSON-RPC specification.

Firebolt implementations **MUST** send only one response for each request.

**TODO**: Add note about case sensitivity

### 3.1. OpenRPC Documents
Since both the App and the Firebolt Implementation expose APIs, there **MUST** be a separate OpenRPC definition for each.

The Firebolt Implementation OpenRPC Document:
```
firebolt-open-rpc.json
```

The Firebolt App OpenRpc Document:

```
firebolt-application-open-rpc.json
```

#### 3.1.1. OpenRPC Ids
The Firebolt Implementation OpenRPC Document **MUST** have the `$id` set to:

```
"$schema": "https://meta.open-rpc.org/",
"$id": "https://rdkcentral.github.io/firebolt/openrpc/platform"
```

An HTTP `GET` on `https://rdkcentral.github.io/firebolt/openrpc/platform` **MUST** return the latest product version of the Firebolt Implementation Open RPC Definition.

The Firebolt App OpenRpc Document **MUST** have the `$id` set to:

```
"$schema": "https://meta.open-rpc.org/",
"$id": "https://rdkcentral.github.io/firebolt/openrpc/application"
```

An HTTP `GET` on `https://rdkcentral.github.io/firebolt/openrpc/application` **MUST** return the latest product version of the Firebolt Application Open RPC Definition.

#### 3.1.2. Duplex Linking
Since a platform OpenRPC definition has a corresponding application defintion, it **MUST** be denoted by an OpenRPC `x-client-api` extension property in the `info` section.

Similarly, the application OpenRPC definition **MUST** reference the platform definition in the `x-client-api` property.

Firebolt Platform OpenRPC:

```json
{
    "$id": "https://rdkcentral.github.io/firebolt/openrpc/platform",
    "info": {
        "title": "Firebolt",
        "x-client-api": "https://rdkcentral.github.io/firebolt/openrpc/application"
    }
}
```

Firebolt Application OpenRPC:

```json
{
    "$id": "https://rdkcentral.github.io/firebolt/openrpc/application",
    "info": {
        "title": "Firebolt",
        "x-client-api": "https://rdkcentral.github.io/firebolt/openrpc/platform"
    }
}
```

### 3.2. Asynchronous Events
Asynchronous events, aka "notifications," **MUST** be handled by leveraging the common "duplex" pattern where both the Firebolt App & the Firebolt Implementation act as a JSON-RPC Server *and* a JSON-RPC client.

To register for an event, e.g "sunrise", the Firebolt App would call an RPC method on the Firebolt Implementation called `Sky.onSunrise` with the `listen` parameter set to `true`:

App -> Firebolt

```json
{
    "id": 1,
    "method": "Sky.onSunrise",
    "params": {
        "listen": true
    }
}
```

This `onSunrise` call **MUST** only have one response: either an empty success result, or an error describing why the event registration was not successful.

2.0 success

```json
{
    "id": 1,
    "result": null
}
```

2.0 failure

```json
{
    "id": 1,
    "error": {
        "code": 111,
        "message": "failed"
    }
}
```

If a Firebolt App has registered for an event, e.g. "sunrise," then the Firebolt Implementation **SHOULD** send any occurences of the "sunrise" event to the app via a JSON-RPC notification request:

Firebolt -> App

```json
{
    "method": "Sky.sunrise",
    "params": {}
}
```

If a Firebolt App registers (or unregisters) for an event, e.g. "sunrise," more than once, then the Firebolt Implementation **SHOULD** treat the request as a success if the initial request was successful. The Firebolt Implementation **MUST** send only one notification to the app per occurences of the "sunrise" event regardless of how many times it registered.

A single unregistration for an event **MUST** result in the notifications for that event being turned off for that app, regardless of how many times the app had registered.

The Platform event registration API **MUST** have an `x-notifier` extension property on the `event` tag with a `$ref` style value to a method in the platform RPC:

```json
{
    "methods": [
        {
            "name": "Sky.onSunrise",
            "tags": [
                {
                    "name": "event",
                    "x-notifier": "Sky.sunrise"
                }
            ]
        }
    ]
}
```

### 3.3. Provider Interfaces
Provider Interfaces allow a Firebolt App to "provide" a Firebolt Capability back to the Firebolt Implementation, in the form of an interface dictated by Firebolt and implemented by the app.

Provider Interfaces **MUST** be handled by leveraging the common "duplex" pattern where both the Firebolt App & the Firebolt Implementation act as a JSON-RPC Server *and* a JSON-RPC client.

For this example, the `"xrn:firebolt:capability:sky:sun"` interface consists of (Written in TypeScript for brevity):

```typescript
interface Sun {
    function rise(): Promise<void>;
    function set(): Promise<void>;
}
```

To register as a provider for a capability, e.g. `"xrn:firebolt:capability:sky:sun"`, the Firebolt App would call an RPC method on the Firebolt Implementation to enable the interface to be called on the application by the platform.

The Platform provider registration API **MUST** have a `provider` tag and an `x-interface` string parameter denoting the name of the interface from the Application OpenRPC that this registration API is enabling.

```json
{
    "methods": [
        {
            "name": "Sky.provideSun",
            "tags": [
				{
					"name": "provider",
                    "x-interface": "Sun"
				}
            ],
            "params": [
                {
                    "name": "enbled",
                    "required": true,
                    "schema": {
                        "type": "boolean"
                    }
                }
            ]
        }
    ]
}
```

To register for this Provider Interface, the Firebolt App would call the RPC method, e.g.:

```json
{
    "id": 1,
    "method": "Sky.provideSun",
    "params": {
        "enabled": true
    }
}
```

If a Firebolt App has registered as a capability provider, e.g. "xrn:firebolt:capability:sky:sun", then the Firebolt Implementation **SHOULD** call the appropriate methods via the app's JSON-RPC server as neeeded, e.g.:

```json
{
    "id": 1,
    "method": "Sun.rise",
    "params": []
}
```

The app **MUST** respond either either a result or an error.

## 4. Transport
The RPC Protocol **MUST** be handled over a WebSocket.

### 4.1. API Version
The Firebolt API Version *and* protocol **MUST** be passsed as part of the Sec-WebSocket-Protocol header:

```http
Sec-WebSocket-Protocol: firebolt.v2.0.0, json-rpc
```
