# Tune Intent

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Andrew Bennett            | Sky            |
| Tim Dibben            | Sky            |
| Seth Kelly            | Comcast            |
| Jeremy LaCivita            | Comcast            |

## 1. Overview

The Firebolt Tune Intent is a notification that the platform will send
to an App, representing the user\'s intention to \"tune\" to a Channel
entity.

A Channel may be a traditional over-the-air broadcast, or an OTT Stream
from an OTT or vMVPD App.

A Tune Intent allows a user to \"tune\" i.e. set their device to watch
an already in progress broadcast or stream. Tune Intents may have
additional data to specify restarting at a program boundary, aka a
\"Listing,\" before playback begins, simulating a traditional DVR-like
experience.

For more information on Channels and Listings, see [Entities](../entities).

For more information on Intents, see [Intents](./).

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

- [1. Overview](#1-overview)
  - [1.1. Tuning](#11-tuning)
  - [1.2. Tuning to a program](#12-tuning-to-a-program)
    - [1.2.1. Tuning to the current program](#121-tuning-to-the-current-program)
    - [1.2.2. Tuning to a specific program](#122-tuning-to-a-specific-program)
    - [1.2.3. Tuning to a point in time](#123-tuning-to-a-point-in-time)
  - [1.3. Tune Intent Schema](#13-tune-intent-schema)
    - [1.3.1. ChannelEntity Schema](#131-channelentity-schema)
    - [1.3.2. TuneOptions Schema](#132-tuneoptions-schema)
  - [1.5. Examples](#15-examples)
    - [1.5.1. Launch a broadcast channel by name](#151-launch-a-broadcast-channel-by-name)
    - [1.5.2. Launch a broadcast channel by number](#152-launch-a-broadcast-channel-by-number)
    - [1.5.4. Launch an in-app channel by name](#154-launch-an-in-app-channel-by-name)
  - [1.6. Core SDK APIs](#16-core-sdk-apis)
    - [1.6.1. navigateTo Event](#161-navigateto-event)

### 1.1. Tuning

When the platform detects a user\'s intention to watch an in-progress
broadcast or stream, it will construct a Tune Intent, and pass it to an
App capable of fulfilling it. See
[Intents](./)
for more information on how the platform determines if a user has a
specific intention that justifies an Intent to be created.

A Tune Intent may be for an over-the-air broadcasted channel if the
current device has the `xrn:firebolt:capability:``tune:over-the-air`
Capability.

A Tune Intent may be for a linear streaming channel or for live
streaming event if the current device has the
`xrn:firebolt:capability:tune:``streaming` Capability.

Apps must also have access to corresponding Capability to receive Tune
Intents.

For a Tune Intent to be sent to an App all of the following **MUST** be
true:

> The platform is aware of a Tune Intent, e.g. from the RCU or a cloud
> voice integration
>
> **and**
>
> The device has the required App installed
>
> **and**
>
> The required
> [Capability](../general/capabilities/)
> (streaming or over-the-air) is `supported` by the device
>
> **and**
>
> The required Capability is `available`
>
> **and**
>
> The required Capability is `permitted` to the App (or
> public/non-negotiable)
>
> **and**
>
> The required Capability is `granted` to the App (or not gated by a
> [User
> Grant](../general/capabilities/user-grants.md))

If all of these conditions are met, then the Tune Intent MUST be
dispatched via an `onNavigateTo` notification, with a payload that
matches the Tune Intent Schema (see below).

### 1.2. Tuning to a program

When the platform detects a user\'s intention to watch a program *from
the beginning*, that is part of an in-progress broadcast or stream, it
will construct a Tune Intent and pass it to an App capable of fulfilling
it.

In this case, the Tune Intent **MUST** have an `options` property in the
`data` property, to specify additional metadata to enable the correct
user experience.

The value in the `options` property can take one of three forms.

#### 1.2.1. Tuning to the current program

A Tune with `options.restartCurrentProgram` set to `true` means that the
receiving App should start at the program boundary of the currently
playing program.

How the App determines this is not the platform\'s concern, but the user
**MUST** be presented with a video presentation that corresponds to +/-
5 seconds from the actual start of the current program.

#### 1.2.2. Tuning to a specific program

A Tune with `options.``assetId` set to some value means that the
receiving App should start playing the asset specified.

The mean of the assetId is specified on a partner-by-partner basis, and
*could* be a Listing ID, a VOD asset ID, or any other ID that, when
combined with the channel from `entityId`, enables the App to playback a
specific program,

How the App determines this is not the platform\'s concern, but the user
**MUST** be presented with a video presentation that corresponds to +/-
5 seconds from the actual start of the current program.

#### 1.2.3. Tuning to a point in time

A Tune with `options.``time` set to an ISO 8601 Date/Time means that the
receiving App should start at that point in the stream.

How the App determines this is not the platform\'s concern, but the user
**MUST** be presented with a video presentation that corresponds to +/-
5 seconds from the `time` provided.

### 1.3. Tune Intent Schema

A Tune Intent follows the same pattern as all Firebolt Intents with a
basic structure of `action`, `data`, and `context`, for example:

```json
{
  "action": "tune",
  "data": {
    "entity": {
      "entityType": "channel",
      "entityId": "urn:bbc.co.uk:channel:123"
    },
    "options": {
      "restartCurrentProgram": true
    }
  },
  "context": {
    "source": "voice"
  }
}
```


The `data` property of a Tune Entity may have the following fields:

| Property | Type            | Required | Notes     |
|----------|-----------------|----------|-----------|
| entity   | `ChannelEntity` | Yes      | See below |
| options  | `TuneOptions`   | No       | See below |

#### 1.3.1. ChannelEntity Schema

The `entity` property of the `data` property MUST be a `ChannelEntity`,
which may have the following fields:

| Property    | Type        | Required | Notes                                          |
|----------------|-------------|-----------|--------------------------------|
| entityType  | \"channel\" | Yes      | **MUST** be \"channel\"                        |
| channelType | String      | Yes      | \"streaming\" \| \"over-the-air\"              |
| entityId    | String      | Yes      | ID of the channel, in the target App\'s scope. |

#### 1.3.2. TuneOptions Schema

The `options` property of the `data` property **MUST** be a
`TuneOptions`, which **MUST** have *only one* of the following fields:

| Property              | Type    | Required | Notes                                                                                                                    |
|-------------------|------------|------------|------------------------------|
| assetId               | String  | No       | Denotes the ID of a specific listing, as scoped by the target App\'s ID-space, which the App should begin playback from. |
| restartCurrentProgram | boolean | No       | Denotes that the App should start playback at the most recent program boundary.                                          |
| time                  | string  | No       | ISO 8601 Date/Time where the App should begin playback from.                                                             |

The scope of the optional assetId is set by each App partner, and could
be one of:

-   A VOD ID for Apps that leverage encoded VOD assets for Channel
    program restart

-   A Listing ID for Apps that model program restart as Listing objects
    in the DVR window

-   Whatever sort of ID an App might want to implement a program restart

### 1.5. Examples

The following are examples of the Tune intent.

#### 1.5.1. Launch a broadcast channel by name

This is for tuning via the main experience, not \"in-app,\" e.g. \"Watch
CNN.\"

```json
{
  type: "xrn:firebolt:intent:navigation:tune",
  intent: {
    action: "tune",
    data: {
      entity: {
        entityType: "channel",
        channelType: "streaming",
        entityId: "some/merlin/id/for/cnn"
      }
    }
  }
}
```

#### 1.5.2. Launch a broadcast channel by number

This is for tuning via the main experience, not \"in-app,\" e.g. \"Watch
CNN.\"

```json
{
  type: "xrn:firebolt:intent:navigation:tune",
  intent: {
    action: "tune",
    data: {
      entity: {
        entityType: "channel",
        channelType: "streaming",
        entityId: "xrn:firebolt:channel:number:123"
      }
    }
  }
}
```

#### 1.5.4. Launch an in-app channel by name

This is for tuning to a virtual channel inside of an app, e.g. \"Watch
\'Cool Channel\' on BBC.\"

```json
{
  type: "xrn:firebolt:intent:navigation:tune",
  appId: "bbc",
  intent: {
    action: "tune",
    data: {
      entity: {
        entityType: "channel",
        channelType: "streaming",
        entityId: "urn:bbc.co.uk:channel:xyz"
      }
    }
  }
}
```

### 1.6. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`core:<module>` domain/module.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

#### 1.6.1. navigateTo Event

The Tune Intent is passed to Apps via the `navigateTo` event:

```javascript
Discovery.listen(navigateTo, (intent) => {
  if (intent.action === 'tune') {
    // handle tune logic
  }
}) 
```

See Discovery for more info.
