---
title: Localization
---

# Localization Module
---
Version 0.8.0

## Overview
 Methods for accessessing location and language preferences

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [localization.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/localization.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [additionalInfo](#additionalinfo)
    - [countryCode](#countrycode)
    - [language](#language)
    - [latlon](#latlon)
    - [listen](#listen)
    - [locale](#locale)
    - [locality](#locality)
    - [once](#once)
    - [postalCode](#postalcode)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [LatLon](#latlon)

<span></span>

## Usage
To use the Localization module, you can import it into your project from the Firebolt SDK:

```javascript
import { Localization } from '@firebolt-js/sdk'
```


## Methods
### additionalInfo

Get any platform-specific localization information, in an Map<string, string>

```typescript
function additionalInfo(): Promise<object>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | the additional info |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.additionalInfo()
    .then(info => {
        console.log(info)
    })
```
Value of `info`:

```javascript
{}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.additionalInfo",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {}
}
```

</details>




---

### countryCode

Get the ISO 3166 code for the counrty device is located in

```typescript
function countryCode(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device country code |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.countryCode()
    .then(code => {
        console.log(code)
    })
```
Value of `code`:

```javascript
"US"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.countryCode",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "US"
}
```

</details>




---

### language
Get the ISO 639 1/2 code for the preferred language



To get the value, call the method with no parameters:


```typescript
function language(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device language |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.language()
    .then(lang => {
        console.log(lang)
    })
```
Value of `lang`:

```javascript
"en"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.language",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "en"
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function language(subscriber: (lang: string) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for language changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `lang` | `string` | Yes | the device language  |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.language(lang => {
  // property value was changed
  console.log(lang)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `lang`:

```javascript
"en"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.onLanguageChanged",
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
  "result": "en"
}
```

</details>



---


### latlon

Get the approximate latitude and longitude coordinates of the device location

```typescript
function latlon(): Promise<[number, number]>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `[number, number]` | lat/long tuple |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.latlon()
    .then(latlong => {
        console.log(latlong)
    })
```
Value of `latlong`:

```javascript
[
  39.9549,
  75.1699
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.latlon",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    39.9549,
    75.1699
  ]
}
```

</details>




---

### listen
Listen for events from this module.

To listen to a specific event pass the event name as the first parameter:


```typescript
Localization.listen(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Localization.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Localization.listen((event: string, data: any) => void): Promise<number>
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
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Localization.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### locale

Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale

```typescript
function locale(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device locale |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.locale()
    .then(locale => {
        console.log(locale)
    })
```
Value of `locale`:

```javascript
"en-US"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.locale",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "en-US"
}
```

</details>




---

### locality

Get the locality/city the device is located in

```typescript
function locality(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device city |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.locality()
    .then(locality => {
        console.log(locality)
    })
```
Value of `locality`:

```javascript
"Philadelphia"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.locality",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Philadelphia"
}
```

</details>




---

### once
Listen for only one occurance of an event from this module. The callback will be cleared after one event.

To listen to a specific event pass the event name as the first parameter:


```typescript
Localization.once(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Localization.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Localization.once((event: string, data: any) => void): Promise<number>
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
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Localization.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### postalCode

Get the postal code the device is located in

```typescript
function postalCode(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device postal code |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/sdk'

Localization.postalCode()
    .then(postalCode => {
        console.log(postalCode)
    })
```
Value of `postalCode`:

```javascript
"19103"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.postalCode",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "19103"
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
| languageChanged | onLanguageChanged | string | [language](#language) |







## Schemas

### LatLon


```typescript
type LatLon = [number, number]
```



---


