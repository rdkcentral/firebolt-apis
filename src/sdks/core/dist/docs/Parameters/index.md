Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [parameters.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/parameters.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [initialization](#initialization)



 - [Schemas](#schemas)
    - [NavigationIntent](#navigationintent)
    - [ProgramType](#programtype)
    - [HomeIntent](#homeintent)
    - [LaunchIntent](#launchintent)
    - [EntityIntent](#entityintent)
    - [PlaybackIntent](#playbackintent)
    - [SearchIntent](#searchintent)
    - [SectionIntent](#sectionintent)
    - [TuneIntent](#tuneintent)
    - [Intent](#intent)
    - [IntentProperties](#intentproperties)
    - [MovieEntity](#movieentity)
    - [TVEpisodeEntity](#tvepisodeentity)
    - [TVSeriesEntity](#tvseriesentity)
    - [TVSeasonEntity](#tvseasonentity)
    - [AdditionalEntity](#additionalentity)
    - [UntypedEntity](#untypedentity)
    - [ChannelEntity](#channelentity)
    - [ProgramEntity](#programentity)
    - [Identifier](#identifier)
    - [SecondScreenEvent](#secondscreenevent)
    - [AppInitialization](#appinitialization)

<span></span>

## Usage
To use the Parameters module, you can import it into your project from the Firebolt SDK:

```javascript
import { Parameters } from '@firebolt-js/sdk'
```


## Methods
### initialization

Returns any initialization parameters for the app, e.g. initialial `NavigationIntent`.

```typescript
function initialization(): Promise<AppInitialization>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AppInitialization`](#appinitialization) | The initialization parameters. |


**Examples**

Default Example

JavaScript:

```javascript
import { Parameters } from '@firebolt-js/sdk'

Parameters.initialization()
    .then(init => {
        console.log(init)
    })
```
Value of `init`:

```javascript
{
  "lmt": 0,
  "us_privacy": "1-Y-",
  "discovery": {
    "navigateTo": {
      "action": "entity",
      "data": {
        "entityId": "abc",
        "entityType": "program",
        "programType": "movie"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "parameters.initialization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "lmt": 0,
    "us_privacy": "1-Y-",
    "discovery": {
      "navigateTo": {
        "action": "entity",
        "data": {
          "entityId": "abc",
          "entityType": "program",
          "programType": "movie"
        },
        "context": {
          "source": "voice"
        }
      }
    }
  }
}
```

</details>




---










## Schemas

### NavigationIntent


A Firebolt compliant representation of a user intention to navigate to a specific place in an app.

```typescript
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
```



---

### ProgramType


In the case of a program `entityType`, specifies the program type.

```typescript
type ProgramType = 'movie' | 'episode' | 'season' | 'series' | 'other' | 'preview' | 'extra' | 'concert' | 'sportingEvent' | 'advertisement' | 'musicVideo' | 'minisode'
```



---

### HomeIntent


A Firebolt compliant representation of a user intention to navigate an app to it's home screen, and bring that app to the foreground if needed.

```typescript
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### LaunchIntent


A Firebolt compliant representation of a user intention to launch an app.

```typescript
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### EntityIntent


A Firebolt compliant representation of a user intention to navigate an app to a specific entity page, and bring that app to the foreground if needed.

```typescript
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
```



---

### PlaybackIntent


A Firebolt compliant representation of a user intention to navigate an app to a the video player for a specific, playable entity, and bring that app to the foreground if needed.

```typescript
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
```



---

### SearchIntent


A Firebolt compliant representation of a user intention to navigate an app to it's search UI with a search term populated, and bring that app to the foreground if needed.

```typescript
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
```



---

### SectionIntent


A Firebolt compliant representation of a user intention to navigate an app to a section not covered by `home`, `entity`, `player`, or `search`, and bring that app to the foreground if needed.

```typescript
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
```



---

### TuneIntent


A Firebolt compliant representation of a user intention to 'tune' to a traditional over-the-air broadcast, or an OTT Stream from an OTT or vMVPD App.

```typescript
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                                           // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean                            // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                                              // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
```



---

### Intent


A Firebolt compliant representation of a user intention.

```typescript
type Intent = {
  action: string
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### IntentProperties


```typescript
type IntentProperties = {
  action: any
  data: any
  context: any
}
```



---

### MovieEntity


```typescript
type MovieEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVEpisodeEntity


```typescript
type TVEpisodeEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVSeriesEntity


```typescript
type TVSeriesEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVSeasonEntity


A Firebolt compliant representation of a TV Season entity.

```typescript
type TVSeasonEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  assetId?: string
  appContentData?: string
}
```



---

### AdditionalEntity


```typescript
type AdditionalEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### UntypedEntity


```typescript
type UntypedEntity = {
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### ChannelEntity


```typescript
type ChannelEntity = {
  entityType: "channel"
  channelType: 'streaming' | 'overTheAir'
  entityId: string                         // ID of the channel, in the target App's scope.
  appContentData?: string
}
```



---

### ProgramEntity


```typescript
type ProgramEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
}
```



---

### Identifier


```typescript
type Identifier = string
```



---

### SecondScreenEvent


An a message notification from a second screen device

```typescript
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}
```



---

### AppInitialization


```typescript
type AppInitialization = {
  us_privacy?: string                  // The IAB US Privacy string.
  lmt?: number                         // The IAB limit ad tracking opt out value.
  discovery?: {
    navigateTo?: NavigationIntent      // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
  }
  secondScreen?: {
    launchRequest?: SecondScreenEvent  // An a message notification from a second screen device
  }
}
```



---


