---
title: Intents
---
# Intents Schema
---
Version 0.8.0


## JSON-Schema
This document was generated from a JSON-Schema, and is intended to provide a human readable overview and examples of the methods contained in the module.

For the full schema, see the link below.

| Schema |
|--------|
| [intents.json](https://github.com/rdkcentral/firebolt-openrpc/blob/feature/badger-parity/src/schemas/intents.json) |

## Table of Contents
 
 - Schemas
    - [AppIntentMessage](#appintentmessage)
    - [PlatformIntentMessage](#platformintentmessage)
    - [Intent](#intent)
    - [IntentProperties](#intentproperties)
    - [NavigationIntent](#navigationintent)
    - [DiscoveryIntent](#discoveryintent)
    - [DeviceIntent](#deviceintent)
    - [PlaybackControlIntent](#playbackcontrolintent)
    - [DialogIntent](#dialogintent)
    - [LaunchIntent](#launchintent)
    - [HomeIntent](#homeintent)
    - [EntityIntent](#entityintent)
    - [ChannelEntity](#channelentity)
    - [ProgramEntity](#programentity)
    - [MovieEntity](#movieentity)
    - [TVEpisodeEntity](#tvepisodeentity)
    - [TVSeasonEntity](#tvseasonentity)
    - [TVSeriesEntity](#tvseriesentity)
    - [AdditionalEntity](#additionalentity)
    - [UntypedEntity](#untypedentity)
    - [TuneIntent](#tuneintent)
    - [PlaybackIntent](#playbackintent)
    - [SearchIntent](#searchintent)
    - [SectionIntent](#sectionintent)
    - [ContentDiscoveryIntent](#contentdiscoveryintent)
    - [EntityAppSelectionIntent](#entityappselectionintent)
    - [ButtonIntent](#buttonintent)
    - [VolumeIntent](#volumeintent)
    - [PowerIntent](#powerintent)
    - [MicrophoneIntent](#microphoneintent)
    - [InputIntent](#inputintent)
    - [PauseIntent](#pauseintent)
    - [PlaybackSpeedIntent](#playbackspeedintent)
    - [TrickPlayIntent](#trickplayintent)
    - [SeekIntent](#seekintent)
    - [SkipIntent](#skipintent)
    - [ClosedCaptionsIntent](#closedcaptionsintent)
    - [AudioDescriptionIntent](#audiodescriptionintent)
    - [MessageIntent](#messageintent)
    - [Identifier](#identifier)
    - [Filter](#filter)
    - [Keyword](#keyword)
    - [DirectionalOperation](#directionaloperation)
    - [BooleanToggle](#booleantoggle)
    - [IntentMessage](#intentmessage)


## Schemas

### AppIntentMessage

```typescript
type AppIntentMessage = {
  type: string
  appId: string
  intent: NavigationIntent  // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
  metadata?: {
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "type": "xrn:firebolt:intent:app:launch",
  "appId": "Netflix",
  "intent": {
    "action": "launch",
    "context": {
      "source": "voice"
    }
  },
  "metadata": {
    "foo": "bar"
  }
}

{
  "type": "xrn:firebolt:intent:app:entity",
  "appId": "Netflix",
  "intent": {
    "action": "entity",
    "data": {
      "entityType": "program",
      "programType": "movie",
      "entityId": "jerry-mcguire"
    },
    "context": {
      "source": "voice"
    }
  },
  "metadata": {
    "foo": "bar"
  }
}
```

</details>


#### Details

A message sent to a Firebolt app.


---

### PlatformIntentMessage

```typescript
type PlatformIntentMessage = {
  type: string
  intent: ContentDiscoveryIntent | EntityAppSelectionIntent | PauseIntent | SeekIntent | SkipIntent | TrickPlayIntent | ClosedCaptionsIntent | AudioDescriptionIntent | ButtonIntent | PowerIntent | VolumeIntent | MicrophoneIntent | InputIntent | TuneIntent | MessageIntent
  metadata?: {
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "type": "xrn:firebolt:intent:platform:power",
  "intent": {
    "action": "power",
    "data": {
      "toggle": true
    },
    "context": {
      "source": "voice"
    }
  },
  "metadata": {
    "foo": "bar"
  }
}

{
  "type": "xrn:firebolt:intent:platform:discovery",
  "intent": {
    "action": "discovery",
    "data": {
      "query": "christmas",
      "menus": [
        "christmas-menu"
      ],
      "federation": [
        {
          "appId": "netflix",
          "exclude": true
        }
      ]
    },
    "context": {
      "source": "voice"
    }
  }
}
```

</details>


#### Details

A message sent to the Firebolt platform.


---

### Intent

```typescript
type Intent = {
  action: string
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a user intention.


---

### IntentProperties

```typescript
type IntentProperties = {
  action: any
  data: any
  context: any
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### NavigationIntent

```typescript
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate to a specific place in an app.


---

### DiscoveryIntent

```typescript
type DiscoveryIntent = ContentDiscoveryIntent | EntityAppSelectionIntent
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a user intention to discover something at the aggregate experience level, e.g. content, apps, etc.


---

### DeviceIntent

```typescript
type DeviceIntent = ButtonIntent | PowerIntent | VolumeIntent | MicrophoneIntent | InputIntent | TuneIntent
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a user intention to control some aspect of their device.


---

### PlaybackControlIntent

```typescript
type PlaybackControlIntent = PauseIntent | SeekIntent | SkipIntent | TrickPlayIntent | ClosedCaptionsIntent | AudioDescriptionIntent
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a user intention to control some aspect of in-progress playback.


---

### DialogIntent

```typescript
type DialogIntent = MessageIntent
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A Firebolt compliant representation of a platform or user intention to converse in a dialog.


---

### LaunchIntent

```typescript
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "launch",
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to launch an app.


---

### HomeIntent

```typescript
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "home",
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate an app to it's home screen, and bring that app to the foreground if needed.


---

### EntityIntent

```typescript
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "entity",
  "context": {
    "source": "voice"
  },
  "data": {
    "entityType": "program",
    "programType": "movie",
    "entityId": "el-camino"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate an app to a specific entity page, and bring that app to the foreground if needed.


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




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### ProgramEntity

```typescript
type ProgramEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
}
```

See also: 

 - [ProgramType](../../schemas/entertainment#programtype)


<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




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




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityType": "program",
  "programType": "movie",
  "entityId": "el-camino"
}
```

</details>




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




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityType": "program",
  "programType": "episode",
  "entityId": "breaking-bad-pilot",
  "seriesId": "breaking-bad",
  "seasonId": "breaking-bad-season-1"
}
```

</details>




---

### TVSeasonEntity

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




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityType": "program",
  "programType": "season",
  "entityId": "breaking-bad-season-1",
  "seriesId": "breaking-bad"
}
```

</details>


#### Details

A Firebolt compliant representation of a TV Season entity.


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




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityType": "program",
  "programType": "series",
  "entityId": "breaking-bad"
}
```

</details>




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




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityType": "program",
  "programType": "concert",
  "entityId": "live-aid"
}
```

</details>




---

### UntypedEntity

```typescript
type UntypedEntity = {
  entityId: string
  assetId?: string
  appContentData?: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "entityId": "an-entity"
}
```

</details>




---

### TuneIntent

```typescript
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                        // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean         // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                           // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "tune",
  "data": {
    "entity": {
      "entityType": "channel",
      "channelType": "streaming",
      "entityId": "an-ott-channel"
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

</details>


#### Details

A Firebolt compliant representation of a user intention to 'tune' to a traditional over-the-air broadcast, or an OTT Stream from an OTT or vMVPD App.


---

### PlaybackIntent

```typescript
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "playback",
  "data": {
    "entityType": "program",
    "programType": "episode",
    "entityId": "breaking-bad-pilot",
    "seriesId": "breaking-bad",
    "seasonId": "breaking-bad-season-1"
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate an app to a the video player for a specific, playable entity, and bring that app to the foreground if needed.


---

### SearchIntent

```typescript
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "search",
  "data": {
    "query": "walter white"
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate an app to it's search UI with a search term populated, and bring that app to the foreground if needed.


---

### SectionIntent

```typescript
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "section",
  "data": {
    "sectionName": "settings"
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate an app to a section not covered by `home`, `entity`, `player`, or `search`, and bring that app to the foreground if needed.


---

### ContentDiscoveryIntent

```typescript
type ContentDiscoveryIntent = {
  action: "discovery"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: {
    query: string
    filters?: object[]
    keywords?: object[]
    menus?: string[]
    federation?: object[]
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "discovery",
  "context": {
    "source": "voice"
  },
  "data": {
    "query": "Bill Murray Comedies in 4K",
    "filters": [
      {
        "key": "videoResolution",
        "value": "UHD"
      }
    ],
    "keywords": [
      {
        "keyword": "Bill Murray",
        "type": "Person",
        "appId": "FooApp"
      },
      {
        "keyword": "Comedies",
        "type": "Genre",
        "appId": "FooApp"
      }
    ],
    "menus": [
      "abcdef",
      "ghijkl"
    ],
    "federation": [
      {
        "appId": "BarApp",
        "exclude": false
      }
    ]
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to discover content with out a clear specific entity match.


---

### EntityAppSelectionIntent

```typescript
type EntityAppSelectionIntent = {
  action: "entityAppSelection"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: {
    query: string
    entity: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity
    apps: object[]
    menus?: string[]
    federation?: object[]
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "entityAppSelection",
  "context": {
    "source": "voice"
  },
  "data": {
    "query": "the departed",
    "entity": {
      "entityType": "program",
      "programType": "movie",
      "entityId": "departed-merlin-id"
    },
    "apps": [
      {
        "appId": "hbo",
        "entity": {
          "entityType": "program",
          "programType": "movie",
          "entityId": "departed-hbo-id"
        }
      },
      {
        "appId": "netflix",
        "entity": {
          "entityType": "program",
          "programType": "movie",
          "entityId": "departed-netflix-id"
        }
      }
    ],
    "federation": [
      {
        "appId": "netflix",
        "exclude": true
      }
    ],
    "menusIds": [
      "123"
    ]
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to navigate to a specific entity that could be served by more than one app.


---

### ButtonIntent

```typescript
type ButtonIntent = {
  action: "button"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    operation: 'down' | 'up' | 'prev' | 'next' | 'enter' | 'exit' | 'info' | 'menu' | 'back' | 'cancel' | 'record'
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "button",
  "data": {
    "operation": "menu"
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to interact with their device in a way analogous to pressing one of the remote buttons.


---

### VolumeIntent

```typescript
type VolumeIntent = {
  action: "volume"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: object | object
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "volume",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "volume",
  "data": {
    "value": 0.7
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "volume",
  "data": {
    "value": 0.1,
    "relative": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to change the device volume.


---

### PowerIntent

```typescript
type PowerIntent = {
  action: "power"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: boolean
    toggle?: true
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "power",
  "data": {
    "value": false
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "power",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to turn their device on or off.


---

### MicrophoneIntent

```typescript
type MicrophoneIntent = {
  action: "microphone"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: boolean
    toggle?: true
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "microphone",
  "data": {
    "value": false
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "microphone",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to turn their microphone on or off.


---

### InputIntent

```typescript
type InputIntent = {
  action: "input"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    interface: 'hdmi' | 'rca' | 'vga' | 'etc...'
    number?: number
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "input",
  "data": {
    "interface": "hdmi"
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "input",
  "data": {
    "interface": "hdmi",
    "number": 1
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to change which video input is active.


---

### PauseIntent

```typescript
type PauseIntent = {
  action: "pause"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: boolean
    toggle?: true
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "pause",
  "data": {
    "value": false
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "pause",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to pause/unpause in-progress playback.


---

### PlaybackSpeedIntent

```typescript
type PlaybackSpeedIntent = {
  action: "speed"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: number
    toggle?: boolean
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "speed",
  "data": {
    "value": 2
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "speed",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to change the speed of in-progress playback.


---

### TrickPlayIntent

```typescript
type TrickPlayIntent = {
  action: "trickplay"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: true
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "trickplay",
  "data": {
    "direction": "forward",
    "speed": 2
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "trickplay",
  "data": {
    "direction": "backward",
    "speed": 2
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to fast-forward or rewind in-progress playback.


---

### SeekIntent

```typescript
type SeekIntent = {
  action: "seek"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: true
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "seek",
  "data": {
    "seconds": 300
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "seek",
  "data": {
    "direction": "forward",
    "seconds": 30
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "seek",
  "data": {
    "direction": "backward",
    "seconds": 30
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to seek to a different time for in-progress playback.


---

### SkipIntent

```typescript
type SkipIntent = {
  action: "skip"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: true
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "skip",
  "data": {
    "direction": "forward",
    "count": 1
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "skip",
  "data": {
    "direction": "backward",
    "count": 1
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to skip a scene/chapter/ad during in-progress playback.


---

### ClosedCaptionsIntent

```typescript
type ClosedCaptionsIntent = {
  action: "closedcaptions"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: boolean
    toggle?: true
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "closedcaptions",
  "data": {
    "value": false
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "closedcaptions",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to enable/disable closed captions.


---

### AudioDescriptionIntent

```typescript
type AudioDescriptionIntent = {
  action: "audiodescriptions"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: boolean
    toggle?: true
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "audiodescriptions",
  "data": {
    "value": false
  },
  "context": {
    "source": "voice"
  }
}

{
  "action": "audiodescriptions",
  "data": {
    "toggle": true
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a user intention to enable/disable audio descriptions.


---

### MessageIntent

```typescript
type MessageIntent = {
  action: "message"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    value?: string
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "action": "message",
  "data": {
    "value": "Here's a message"
  },
  "context": {
    "source": "voice"
  }
}
```

</details>


#### Details

A Firebolt compliant representation of a platform intention to display a message on the device.


---

### Identifier

```typescript
type Identifier = string
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### Filter

```typescript
type Filter = {
  key?: string
  value?: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### Keyword

```typescript
type Keyword = {
  keyword?: string
  type?: string
  appId?: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### DirectionalOperation

```typescript
type DirectionalOperation = {
  direction?: 'forward' | 'backward'
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### BooleanToggle

```typescript
type BooleanToggle = {
  value?: boolean
  toggle?: true
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### IntentMessage

```typescript
type IntentMessage = {
  type: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---


