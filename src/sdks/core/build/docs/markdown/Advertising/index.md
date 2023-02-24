Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [advertising.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/advertising.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [advertisingId](#advertisingid)
    - [appBundleId](#appbundleid)
    - [config](#config)
    - [deviceAttributes](#deviceattributes)
    - [listen](#listen)
    - [once](#once)
    - [policy](#policy)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [AdPolicy](#adpolicy)
    - [AdConfigurationOptions](#adconfigurationoptions)
    - [SkipRestriction](#skiprestriction)

<span></span>

## Usage
To use the Advertising module, you can import it into your project from the Firebolt SDK:

```javascript
import { Advertising } from '@firebolt-js/sdk'
```


## Methods
### advertisingId

Get the advertising ID

```typescript
function advertisingId(): Promise<object>
```


Promise resolution:

the advertising ID

| Field | Type | Description |
| ----- | ---- | ----------- |
| `ifa` | `string` |  |
| `ifa_type` | `string` |  |
| `lmt` | `string` |  |


**Examples**

Getting the advertising ID

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.advertisingId()
    .then(advertisingId => {
        console.log(advertisingId)
    })
```
Value of `advertisingId`:

```javascript
{
  "ifa": "01234567-89AB-CDEF-GH01-23456789ABCD",
  "ifa_type": "idfa",
  "lmt": "0"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.advertisingId",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "ifa": "01234567-89AB-CDEF-GH01-23456789ABCD",
    "ifa_type": "idfa",
    "lmt": "0"
  }
}
```

</details>




---

### appBundleId

Get the App's Bundle ID

```typescript
function appBundleId(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the app bundle ID |


**Examples**

Default Example

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.appBundleId()
    .then(appBundleId => {
        console.log(appBundleId)
    })
```
Value of `appBundleId`:

```javascript
"operator.app"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.appBundleId",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "operator.app"
}
```

</details>




---

### config

Build configuration object for Ad Framework initialization

```typescript
function config(options: AdConfigurationOptions): Promise<object>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `options` | [`AdConfigurationOptions`](#adconfigurationoptions) | true | Configuration options  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | An opaque object represneting the AdConfiguration |


**Examples**

Initializing the Ad Framework

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.config({"environment":"prod","authenticationEntity":"MVPD"})
    .then(adFrameworkConfig => {
        console.log(adFrameworkConfig)
    })
```
Value of `adFrameworkConfig`:

```javascript
{
  "adServerUrl": "https://demo.v.fwmrm.net/ad/p/1",
  "adServerUrlTemplate": "https://demo.v.fwmrm.net/ad/p/1?flag=+sltp+exvt+slcb+emcr+amcb+aeti&prof=12345:caf_allinone_profile &nw=12345&mode=live&vdur=123&caid=a110523018&asnw=372464&csid=gmott_ios_tablet_watch_live_ESPNU&ssnw=372464&vip=198.205.92.1&resp=vmap1&metr=1031&pvrn=12345&vprn=12345&vcid=1X0Ce7L3xRWlTeNhc7br8Q%3D%3D",
  "adNetworkId": "519178",
  "adProfileId": "12345:caf_allinone_profile",
  "adSiteSectionId": "caf_allinone_profile_section",
  "adOptOut": true,
  "privacyData": "ew0KICAicGR0IjogImdkcDp2MSIsDQogICJ1c19wcml2YWN5IjogIjEtTi0iLA0KICAibG10IjogIjEiIA0KfQ0K",
  "ifaValue": "01234567-89AB-CDEF-GH01-23456789ABCD",
  "ifa": "ewogICJ2YWx1ZSI6ICIwMTIzNDU2Ny04OUFCLUNERUYtR0gwMS0yMzQ1Njc4OUFCQ0QiLAogICJpZmFfdHlwZSI6ICJzc3BpZCIsCiAgImxtdCI6ICIwIgp9Cg==",
  "appName": "FutureToday",
  "appBundleId": "FutureToday.comcast",
  "distributorAppId": "1001",
  "deviceAdAttributes": "ewogICJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjogIjEyMzQiCn0=",
  "coppa": 0,
  "authenticationEntity": "60f72475281cfba3852413bd53e957f6"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.config",
  "params": {
    "options": {
      "environment": "prod",
      "authenticationEntity": "MVPD"
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "adServerUrl": "https://demo.v.fwmrm.net/ad/p/1",
    "adServerUrlTemplate": "https://demo.v.fwmrm.net/ad/p/1?flag=+sltp+exvt+slcb+emcr+amcb+aeti&prof=12345:caf_allinone_profile &nw=12345&mode=live&vdur=123&caid=a110523018&asnw=372464&csid=gmott_ios_tablet_watch_live_ESPNU&ssnw=372464&vip=198.205.92.1&resp=vmap1&metr=1031&pvrn=12345&vprn=12345&vcid=1X0Ce7L3xRWlTeNhc7br8Q%3D%3D",
    "adNetworkId": "519178",
    "adProfileId": "12345:caf_allinone_profile",
    "adSiteSectionId": "caf_allinone_profile_section",
    "adOptOut": true,
    "privacyData": "ew0KICAicGR0IjogImdkcDp2MSIsDQogICJ1c19wcml2YWN5IjogIjEtTi0iLA0KICAibG10IjogIjEiIA0KfQ0K",
    "ifaValue": "01234567-89AB-CDEF-GH01-23456789ABCD",
    "ifa": "ewogICJ2YWx1ZSI6ICIwMTIzNDU2Ny04OUFCLUNERUYtR0gwMS0yMzQ1Njc4OUFCQ0QiLAogICJpZmFfdHlwZSI6ICJzc3BpZCIsCiAgImxtdCI6ICIwIgp9Cg==",
    "appName": "FutureToday",
    "appBundleId": "FutureToday.comcast",
    "distributorAppId": "1001",
    "deviceAdAttributes": "ewogICJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjogIjEyMzQiCn0=",
    "coppa": 0,
    "authenticationEntity": "60f72475281cfba3852413bd53e957f6"
  }
}
```

</details>




---

### deviceAttributes

Get the device advertising device attributes

```typescript
function deviceAttributes(): Promise<object>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | the device attributes |


**Examples**

Getting the device attributes

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.deviceAttributes()
    .then(deviceAttributes => {
        console.log(deviceAttributes)
    })
```
Value of `deviceAttributes`:

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
  "method": "advertising.deviceAttributes",
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

### policy
Get the advertising privacy and playback policy



To get the value of `policy` call the method like this:


```typescript
function policy(): Promise<AdPolicy>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AdPolicy`](#adpolicy) | Describes various ad playback enforcement rules that the app should follow. |


**Examples**

Getting the advertising policy settings

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.policy()
    .then(adPolicy => {
        console.log(adPolicy)
    })
```
Value of `adPolicy`:

```javascript
{
  "skipRestriction": "adsUnwatched",
  "limitAdTracking": false
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.policy",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "skipRestriction": "adsUnwatched",
    "limitAdTracking": false
  }
}
```

</details>





To set the value of `policy` call the method like this:


```typescript
function policy(): Promise<ListenResponse | AdPolicy>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the advertising policy settings


JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.policy(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.policy",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "skipRestriction": "adsUnwatched",
    "limitAdTracking": false
  }
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function policy (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Advertising.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.policy((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Advertising.clear(listenerId)
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
### policy

Get the advertising privacy and playback policy

```typescript
function policy(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the ad policy |


**Examples**

Getting the advertising policy settings

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/sdk'

Advertising.policy()
    .then(adPolicy => {
        console.log(adPolicy)
    })
```
Value of `adPolicy`:

```javascript
{
  "skipRestriction": "adsUnwatched",
  "limitAdTracking": false
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.policy",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "skipRestriction": "adsUnwatched",
    "limitAdTracking": false
  }
}
```

</details>




---








## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

### AdPolicy


Describes various ad playback enforcement rules that the app should follow.

```typescript
type AdPolicy = {
  skipRestriction?: SkipRestriction  // The advertisement skip restriction.
  limitAdTracking?: boolean
}
```



---

### AdConfigurationOptions


```typescript
type AdConfigurationOptions = {
  coppa?: boolean                // Whether or not the app requires US COPPA compliance.
  environment?: 'prod' | 'test'  // Whether the app is running in a production or test mode.
  authenticationEntity?: string  // The authentication provider, when it is separate entity than the app provider, e.g. an MVPD.
}
```



---

### SkipRestriction


The advertisement skip restriction.

Applies to fast-forward/rewind (e.g. trick mode), seeking over an entire opportunity (e.g. jump), seeking out of what's currently playing, and "Skip this ad..." features. Seeking over multiple ad opportunities only requires playback of the _last_ opportunity, not all opportunities, preceding the seek destination.

| Value        | Description                                                                    |
|--------------|--------------------------------------------------------------------------------|
| none         |No fast-forward, jump, or skip restrictions                                    |
| adsUnwatched | Restrict fast-forward, jump, and skip for unwatched ad opportunities only.     |
| adsAll       | Restrict fast-forward, jump, and skip for all ad opportunities                 |
| all          | Restrict fast-forward, jump, and skip for all ad opportunities and all content |

Namespace: `xrn:advertising:policy:skipRestriction:`



```typescript
type SkipRestriction = 'none' | 'adsUnwatched' | 'adsAll' | 'all'
```



---


