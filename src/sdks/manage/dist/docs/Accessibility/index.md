Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [accessibility.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/accessibility.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [closedCaptionsSettings](#closedcaptionssettings)
    - [listen](#listen)
    - [once](#once)
    - [voiceGuidance](#voiceguidance)
    - [voiceGuidanceSettings](#voiceguidancesettings)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [VoiceGuidanceSettings](#voiceguidancesettings)
    - [ClosedCaptionsSettings](#closedcaptionssettings)
    - [ListenResponse](#listenresponse)
    - [ClosedCaptionsStyles](#closedcaptionsstyles)
    - [FontFamily](#fontfamily)
    - [FontSize](#fontsize)
    - [Color](#color)
    - [FontEdge](#fontedge)
    - [Opacity](#opacity)
    - [HorizontalAlignment](#horizontalalignment)
    - [VerticalAlignment](#verticalalignment)

<span></span>

## Usage
To use the Accessibility module, you can import it into your project from the Firebolt SDK:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'
```


## Methods
### closedCaptionsSettings
Get the user's preferred closed-captions settings



To get the value of `closedCaptionsSettings` call the method like this:


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
import { Accessibility } from '@firebolt-js/manage-sdk'

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





To set the value of `closedCaptionsSettings` call the method like this:


```typescript
function closedCaptionsSettings(): Promise<ListenResponse | ClosedCaptionsSettings>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the closed captions settings


JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

Accessibility.closedCaptionsSettings(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function closedCaptionsSettings (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Accessibility.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

Accessibility.closedCaptionsSettings((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Accessibility.clear(listenerId)
})
```

value of `value`:

```javascript
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
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
```

</details>


---

### listen

Listen for events from this module.

```typescript
function listen(event?: string): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |




---

### once

Listen for only one occurance of an event from this module. The callback will be cleared after one event.

```typescript
function once(event?: string): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |




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
import { Accessibility } from '@firebolt-js/manage-sdk'

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



To get the value of `voiceGuidanceSettings` call the method like this:


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
import { Accessibility } from '@firebolt-js/manage-sdk'

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





To set the value of `voiceGuidanceSettings` call the method like this:


```typescript
function voiceGuidanceSettings(): Promise<ListenResponse | VoiceGuidanceSettings>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the voice guidance settings


JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

Accessibility.voiceGuidanceSettings(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function voiceGuidanceSettings (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Accessibility.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

Accessibility.voiceGuidanceSettings((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Accessibility.clear(listenerId)
})
```

value of `value`:

```javascript
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
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
```

</details>


---






## Events



### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
### closedCaptionsSettings

Get the user's preferred closed-captions settings

```typescript
function closedCaptionsSettings(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the closed captions settings |


**Examples**

Getting the closed captions settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

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




---

### voiceGuidanceSettings

Get the user's preferred voice guidance settings

```typescript
function voiceGuidanceSettings(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the voice guidance settings |


**Examples**

Getting the voice guidance settings

JavaScript:

```javascript
import { Accessibility } from '@firebolt-js/manage-sdk'

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




---








## Schemas

### VoiceGuidanceSettings


```typescript
type VoiceGuidanceSettings = {
  enabled: boolean              // Whether or not voice guidance should be enabled by default
  speed: number                 // The speed at which voice guidance speech will be read back to the user
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

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

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

### FontFamily


```typescript
type FontFamily = string
```



---

### FontSize


```typescript
type FontSize = number
```



---

### Color


```typescript
type Color = string
```



---

### FontEdge


```typescript
type FontEdge = string
```



---

### Opacity


```typescript
type Opacity = number
```



---

### HorizontalAlignment


```typescript
type HorizontalAlignment = string
```



---

### VerticalAlignment


```typescript
type VerticalAlignment = string
```



---


