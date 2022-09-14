---
title: Accessibility
---

# Accessibility Module
---
Version 0.8.0

## Overview
 The `Accessibility` module provides access to the user/device settings for closed captioning and voice guidance.

Apps **SHOULD** attempt o respect these settings, rather than manage and persist seprate settings, which would be different per-app.

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [accessibility.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/accessibility.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [closedCaptions](#closedcaptions)
    - [closedCaptionsSettings](#closedcaptionssettings)
    - [listen](#listen)
    - [once](#once)
    - [voiceGuidance](#voiceguidance)
    - [voiceGuidanceSettings](#voiceguidancesettings)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ClosedCaptionsStyles](#closedcaptionsstyles)
    - [ClosedCaptionsSettings](#closedcaptionssettings)
    - [VoiceGuidanceSettings](#voiceguidancesettings)

<span></span>

## Usage
To use the Accessibility module, you can import it into your project from the Firebolt SDK:

```javascript
import { Accessibility } from '@firebolt-js/sdk'
```


## Methods
### closedCaptions

This API is **deprecated** since version 0.6.0. Use `Accessibility.closedCaptionsSettings()` instead.

Get the user's preferred closed-captions settings

```typescript
function closedCaptions(): Promise<ClosedCaptionsSettings>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ClosedCaptionsSettings`](#closedcaptionssettings) | the closed captions settings |


**Examples**

Getting the closed captions settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.closedCaptions()
    .then(closedCaptionsSettings => {
        console.log(closedCaptionsSettings)
    })
```
Value of `closedCaptionsSettings`:

```javascript
{
  "enabled": true,
  "styles": {
    "fontFamily": "Monospace sans-serif",
    "fontSize": 1,
    "fontColor": "#ffffff",
    "fontEdge": "none",
    "fontEdgeColor": "#7F7F7F",
    "fontOpacity": 100,
    "backgroundColor": "#000000",
    "backgroundOpacity": 100,
    "textAlign": "center",
    "textAlignVertical": "middle"
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
  "method": "accessibility.closedCaptions",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "styles": {
      "fontFamily": "Monospace sans-serif",
      "fontSize": 1,
      "fontColor": "#ffffff",
      "fontEdge": "none",
      "fontEdgeColor": "#7F7F7F",
      "fontOpacity": 100,
      "backgroundColor": "#000000",
      "backgroundOpacity": 100,
      "textAlign": "center",
      "textAlignVertical": "middle"
    }
  }
}
```

</details>




---

### closedCaptionsSettings
Get the user's preferred closed-captions settings



To get the value, call the method with no parameters:


```typescript
function closedCaptionsSettings(): Promise<ClosedCaptionsSettings>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ClosedCaptionsSettings`](#closedcaptionssettings) | the closed captions settings |


**Examples**

Getting the closed captions settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.closedCaptionsSettings()
    .then(closedCaptionsSettings => {
        console.log(closedCaptionsSettings)
    })
```
Value of `closedCaptionsSettings`:

```javascript
{
  "enabled": true,
  "styles": {
    "fontFamily": "Monospace sans-serif",
    "fontSize": 1,
    "fontColor": "#ffffff",
    "fontEdge": "none",
    "fontEdgeColor": "#7F7F7F",
    "fontOpacity": 100,
    "backgroundColor": "#000000",
    "backgroundOpacity": 100,
    "textAlign": "center",
    "textAlignVertical": "middle"
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
  "method": "accessibility.closedCaptionsSettings",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "styles": {
      "fontFamily": "Monospace sans-serif",
      "fontSize": 1,
      "fontColor": "#ffffff",
      "fontEdge": "none",
      "fontEdgeColor": "#7F7F7F",
      "fontOpacity": 100,
      "backgroundColor": "#000000",
      "backgroundOpacity": 100,
      "textAlign": "center",
      "textAlignVertical": "middle"
    }
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function closedCaptionsSettings(subscriber: (closedCaptionsSettings: ClosedCaptionsSettings) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for closedCaptionsSettings changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Accessibility.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `closedCaptionsSettings` | [`ClosedCaptionsSettings`](#closedcaptionssettings) | Yes | the closed captions settings  |

**Examples**

Getting the closed captions settings


JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.closedCaptionsSettings(closedCaptionsSettings => {
  // property value was changed
  console.log(closedCaptionsSettings)
}).then(listenerId => {
  // you can clear this listener w/ Accessibility.clear(listenerId)
})
```

value of `closedCaptionsSettings`:

```javascript
{
  "enabled": true,
  "styles": {
    "fontFamily": "Monospace sans-serif",
    "fontSize": 1,
    "fontColor": "#ffffff",
    "fontEdge": "none",
    "fontEdgeColor": "#7F7F7F",
    "fontOpacity": 100,
    "backgroundColor": "#000000",
    "backgroundOpacity": 100,
    "textAlign": "center",
    "textAlignVertical": "middle"
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
  "method": "accessibility.onClosedCaptionsSettingsChanged",
  "params": {
    "listen": true
  }
}
```

Response:
```json
{
  "jsonrpc": "2.0",
  "id": "1",
  "result": {
    "listening": "true"
  }
}
```

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "styles": {
      "fontFamily": "Monospace sans-serif",
      "fontSize": 1,
      "fontColor": "#ffffff",
      "fontEdge": "none",
      "fontEdgeColor": "#7F7F7F",
      "fontOpacity": 100,
      "backgroundColor": "#000000",
      "backgroundOpacity": 100,
      "textAlign": "center",
      "textAlignVertical": "middle"
    }
  }
}
```

</details>



---


### listen
Listen for events from this module.

To listen to a specific event pass the event name as the first parameter:


```typescript
Accessibility.listen(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Accessibility.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Accessibility.listen((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Accessibility.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### once
Listen for only one occurance of an event from this module. The callback will be cleared after one event.

To listen to a specific event pass the event name as the first parameter:


```typescript
Accessibility.once(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Accessibility.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Accessibility.once((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Accessibility.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### voiceGuidance

This API is **deprecated** since version 0.6.0. Use `Accessibility.voiceGuidanceSettings()` instead.

Get the user's preferred voice guidance settings

```typescript
function voiceGuidance(): Promise<VoiceGuidanceSettings>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`VoiceGuidanceSettings`](#voiceguidancesettings) | the voice guidance settings |


**Examples**

Getting the voice guidance settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.voiceGuidance()
    .then(settings => {
        console.log(settings)
    })
```
Value of `settings`:

```javascript
{
  "enabled": true,
  "speed": 5
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessibility.voiceGuidance",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "speed": 5
  }
}
```

</details>




---

### voiceGuidanceSettings
Get the user's preferred voice guidance settings



To get the value, call the method with no parameters:


```typescript
function voiceGuidanceSettings(): Promise<VoiceGuidanceSettings>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`VoiceGuidanceSettings`](#voiceguidancesettings) | the voice guidance settings |


**Examples**

Getting the voice guidance settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.voiceGuidanceSettings()
    .then(settings => {
        console.log(settings)
    })
```
Value of `settings`:

```javascript
{
  "enabled": true,
  "speed": 5
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessibility.voiceGuidanceSettings",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "speed": 5
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function voiceGuidanceSettings(subscriber: (settings: VoiceGuidanceSettings) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for voiceGuidanceSettings changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Accessibility.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `settings` | [`VoiceGuidanceSettings`](#voiceguidancesettings) | Yes | the voice guidance settings  |

**Examples**

Getting the voice guidance settings


JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/sdk'

Accessibility.voiceGuidanceSettings(settings => {
  // property value was changed
  console.log(settings)
}).then(listenerId => {
  // you can clear this listener w/ Accessibility.clear(listenerId)
})
```

value of `settings`:

```javascript
{
  "enabled": true,
  "speed": 5
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessibility.onVoiceGuidanceSettingsChanged",
  "params": {
    "listen": true
  }
}
```

Response:
```json
{
  "jsonrpc": "2.0",
  "id": "1",
  "result": {
    "listening": "true"
  }
}
```

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enabled": true,
    "speed": 5
  }
}
```

</details>



---







## Events



### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
| closedCaptionsSettingsChanged | onClosedCaptionsSettingsChanged | [ClosedCaptionsSettings](#closedcaptionssettings) | [closedCaptionsSettings](#closedcaptionssettings) |
| voiceGuidanceSettingsChanged | onVoiceGuidanceSettingsChanged | [VoiceGuidanceSettings](#voiceguidancesettings) | [voiceGuidanceSettings](#voiceguidancesettings) |







## Schemas

### ClosedCaptionsStyles


The default styles to use when displaying closed-captions

```typescript
type ClosedCaptionsStyles = {
  fontFamily?: string
  fontSize?: number
  fontColor?: string
  fontEdge?: string
  fontEdgeColor?: string
  fontOpacity?: number
  backgroundColor?: string
  backgroundOpacity?: number
  textAlign?: string
  textAlignVertical?: string
}
```



---

### ClosedCaptionsSettings


```typescript
type ClosedCaptionsSettings = {
  enabled: boolean               // Whether or not closed-captions should be enabled by default
  styles: ClosedCaptionsStyles   // The default styles to use when displaying closed-captions
}
```



---

### VoiceGuidanceSettings


```typescript
type VoiceGuidanceSettings = {
  enabled: boolean              // Whether or not voice guidance should be enabled by default
  speed: number                 // The speed at which voice guidance speech will be read back to the user
}
```



---


