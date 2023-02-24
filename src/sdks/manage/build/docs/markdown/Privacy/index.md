Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [privacy.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/privacy.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [allowACRCollection](#allowacrcollection)
    - [allowAppContentAdTargeting](#allowappcontentadtargeting)
    - [allowCameraAnalytics](#allowcameraanalytics)
    - [allowPersonalization](#allowpersonalization)
    - [allowPrimaryBrowseAdTargeting](#allowprimarybrowseadtargeting)
    - [allowPrimaryContentAdTargeting](#allowprimarycontentadtargeting)
    - [allowProductAnalytics](#allowproductanalytics)
    - [allowRemoteDiagnostics](#allowremotediagnostics)
    - [allowResumePoints](#allowresumepoints)
    - [allowUnentitledPersonalization](#allowunentitledpersonalization)
    - [allowUnentitledResumePoints](#allowunentitledresumepoints)
    - [allowWatchHistory](#allowwatchhistory)
    - [listen](#listen)
    - [once](#once)
    - [settings](#settings)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [PrivacySettings](#privacysettings)

<span></span>

## Usage
To use the Privacy module, you can import it into your project from the Firebolt SDK:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'
```


## Methods
### allowACRCollection
Whether the user allows their automatic content recognition data to be collected



To get the value of `allowACRCollection` call the method like this:


```typescript
function allowACRCollection(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowACRCollection()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowACRCollection",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowACRCollection` call the method like this:


```typescript
function allowACRCollection(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowACRCollection(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowACRCollection",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowACRCollection ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowACRCollection( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowACRCollection",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowAppContentAdTargeting
Whether the user allows ads to be targeted to the user while watching content in apps



To get the value of `allowAppContentAdTargeting` call the method like this:


```typescript
function allowAppContentAdTargeting(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowAppContentAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowAppContentAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowAppContentAdTargeting` call the method like this:


```typescript
function allowAppContentAdTargeting(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowAppContentAdTargeting(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowAppContentAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowAppContentAdTargeting ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowAppContentAdTargeting( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowAppContentAdTargeting",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowCameraAnalytics
Whether the user allows data from their camera to be used for Product Analytics



To get the value of `allowCameraAnalytics` call the method like this:


```typescript
function allowCameraAnalytics(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowCameraAnalytics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowCameraAnalytics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowCameraAnalytics` call the method like this:


```typescript
function allowCameraAnalytics(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowCameraAnalytics(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowCameraAnalytics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowCameraAnalytics ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowCameraAnalytics( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowCameraAnalytics",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowPersonalization
Whether the user allows their usage data to be used for personalization and recommendations



To get the value of `allowPersonalization` call the method like this:


```typescript
function allowPersonalization(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPersonalization()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPersonalization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowPersonalization` call the method like this:


```typescript
function allowPersonalization(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPersonalization(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPersonalization",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowPersonalization ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPersonalization( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPersonalization",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowPrimaryBrowseAdTargeting
Whether the user allows ads to be targeted to the user while browsing in the primary experience



To get the value of `allowPrimaryBrowseAdTargeting` call the method like this:


```typescript
function allowPrimaryBrowseAdTargeting(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryBrowseAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryBrowseAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowPrimaryBrowseAdTargeting` call the method like this:


```typescript
function allowPrimaryBrowseAdTargeting(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryBrowseAdTargeting(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryBrowseAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowPrimaryBrowseAdTargeting ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryBrowseAdTargeting( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryBrowseAdTargeting",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowPrimaryContentAdTargeting
Whether the user allows ads to be targeted to the user while watching content in the primary experience



To get the value of `allowPrimaryContentAdTargeting` call the method like this:


```typescript
function allowPrimaryContentAdTargeting(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryContentAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryContentAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowPrimaryContentAdTargeting` call the method like this:


```typescript
function allowPrimaryContentAdTargeting(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryContentAdTargeting(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryContentAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowPrimaryContentAdTargeting ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryContentAdTargeting( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryContentAdTargeting",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowProductAnalytics
Whether the user allows their usage data can be used for analytics about the product



To get the value of `allowProductAnalytics` call the method like this:


```typescript
function allowProductAnalytics(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowProductAnalytics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowProductAnalytics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowProductAnalytics` call the method like this:


```typescript
function allowProductAnalytics(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowProductAnalytics(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowProductAnalytics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowProductAnalytics ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowProductAnalytics( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowProductAnalytics",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowRemoteDiagnostics
Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device



To get the value of `allowRemoteDiagnostics` call the method like this:


```typescript
function allowRemoteDiagnostics(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowRemoteDiagnostics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowRemoteDiagnostics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowRemoteDiagnostics` call the method like this:


```typescript
function allowRemoteDiagnostics(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowRemoteDiagnostics(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowRemoteDiagnostics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowRemoteDiagnostics ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowRemoteDiagnostics( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowRemoteDiagnostics",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowResumePoints
Whether the user allows resume points for content to show in the main experience



To get the value of `allowResumePoints` call the method like this:


```typescript
function allowResumePoints(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowResumePoints()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowResumePoints",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowResumePoints` call the method like this:


```typescript
function allowResumePoints(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowResumePoints(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowResumePoints",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowResumePoints ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowResumePoints( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowResumePoints",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowUnentitledPersonalization
Whether the user allows their usage data to be used for personalization and recommendations for unentitled content



To get the value of `allowUnentitledPersonalization` call the method like this:


```typescript
function allowUnentitledPersonalization(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledPersonalization()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledPersonalization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowUnentitledPersonalization` call the method like this:


```typescript
function allowUnentitledPersonalization(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledPersonalization(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledPersonalization",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowUnentitledPersonalization ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledPersonalization( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledPersonalization",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowUnentitledResumePoints
Whether the user allows resume points for content from unentitled providers to show in the main experience



To get the value of `allowUnentitledResumePoints` call the method like this:


```typescript
function allowUnentitledResumePoints(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledResumePoints()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledResumePoints",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowUnentitledResumePoints` call the method like this:


```typescript
function allowUnentitledResumePoints(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledResumePoints(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledResumePoints",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowUnentitledResumePoints ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledResumePoints( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledResumePoints",
  "params": {}
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
  "result": true
}
```

</details>



---


### allowWatchHistory
Whether the user allows their watch history from all sources to show in the main experience



To get the value of `allowWatchHistory` call the method like this:


```typescript
function allowWatchHistory(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowWatchHistory()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowWatchHistory",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `allowWatchHistory` call the method like this:


```typescript
function allowWatchHistory(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowWatchHistory(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowWatchHistory",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>





To subscribe to notifications when the value changes, call the method like this:


```typescript
function allowWatchHistory ( subscriber: (allow) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Privacy.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `allow` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowWatchHistory( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Privacy.clear(listenerId)
})
```

value of `value`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowWatchHistory",
  "params": {}
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
  "result": true
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

### settings

Gets the allowed value for all privacy settings

```typescript
function settings(): Promise<PrivacySettings>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`PrivacySettings`](#privacysettings) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.settings()
    .then(settings => {
        console.log(settings)
    })
```
Value of `settings`:

```javascript
{
  "allowACRCollection": true,
  "allowResumePoints": false,
  "allowAppContentAdTargeting": false,
  "allowCameraAnalytics": true,
  "allowPersonalization": true,
  "allowPrimaryBrowseAdTargeting": false,
  "allowPrimaryContentAdTargeting": false,
  "allowProductAnalytics": true,
  "allowRemoteDiagnostics": true,
  "allowUnentitledPersonalization": true,
  "allowUnentitledResumePoints": false,
  "allowWatchHistory": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.settings",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "allowACRCollection": true,
    "allowResumePoints": false,
    "allowAppContentAdTargeting": false,
    "allowCameraAnalytics": true,
    "allowPersonalization": true,
    "allowPrimaryBrowseAdTargeting": false,
    "allowPrimaryContentAdTargeting": false,
    "allowProductAnalytics": true,
    "allowRemoteDiagnostics": true,
    "allowUnentitledPersonalization": true,
    "allowUnentitledResumePoints": false,
    "allowWatchHistory": true
  }
}
```

</details>




---



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### allowResumePoints

Whether the user allows resume points for content to show in the main experience

```typescript
function allowResumePoints(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowResumePoints(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowResumePoints",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowUnentitledResumePoints

Whether the user allows resume points for content from unentitled providers to show in the main experience

```typescript
function allowUnentitledResumePoints(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledResumePoints(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledResumePoints",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowWatchHistory

Whether the user allows their watch history from all sources to show in the main experience

```typescript
function allowWatchHistory(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowWatchHistory(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowWatchHistory",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowProductAnalytics

Whether the user allows their usage data can be used for analytics about the product

```typescript
function allowProductAnalytics(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowProductAnalytics(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowProductAnalytics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowPersonalization

Whether the user allows their usage data to be used for personalization and recommendations

```typescript
function allowPersonalization(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPersonalization(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPersonalization",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowUnentitledPersonalization

Whether the user allows their usage data to be used for personalization and recommendations for unentitled content

```typescript
function allowUnentitledPersonalization(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledPersonalization(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledPersonalization",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowRemoteDiagnostics

Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device

```typescript
function allowRemoteDiagnostics(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowRemoteDiagnostics(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowRemoteDiagnostics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowPrimaryContentAdTargeting

Whether the user allows ads to be targeted to the user while watching content in the primary experience

```typescript
function allowPrimaryContentAdTargeting(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryContentAdTargeting(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryContentAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowPrimaryBrowseAdTargeting

Whether the user allows ads to be targeted to the user while browsing in the primary experience

```typescript
function allowPrimaryBrowseAdTargeting(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryBrowseAdTargeting(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryBrowseAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowAppContentAdTargeting

Whether the user allows ads to be targeted to the user while watching content in apps

```typescript
function allowAppContentAdTargeting(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowAppContentAdTargeting(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowAppContentAdTargeting",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowACRCollection

Whether the user allows their automatic content recognition data to be collected

```typescript
function allowACRCollection(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowACRCollection(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowACRCollection",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---

### allowCameraAnalytics

Whether the user allows data from their camera to be used for Product Analytics

```typescript
function allowCameraAnalytics(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowCameraAnalytics(true)
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowCameraAnalytics",
  "params": {
    "value": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
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
### allowResumePoints

Whether the user allows resume points for content to show in the main experience

```typescript
function allowResumePoints(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowResumePoints()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowResumePoints",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowUnentitledResumePoints

Whether the user allows resume points for content from unentitled providers to show in the main experience

```typescript
function allowUnentitledResumePoints(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledResumePoints()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledResumePoints",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowWatchHistory

Whether the user allows their watch history from all sources to show in the main experience

```typescript
function allowWatchHistory(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowWatchHistory()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowWatchHistory",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowProductAnalytics

Whether the user allows their usage data can be used for analytics about the product

```typescript
function allowProductAnalytics(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowProductAnalytics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowProductAnalytics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowPersonalization

Whether the user allows their usage data to be used for personalization and recommendations

```typescript
function allowPersonalization(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPersonalization()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPersonalization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowUnentitledPersonalization

Whether the user allows their usage data to be used for personalization and recommendations for unentitled content

```typescript
function allowUnentitledPersonalization(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowUnentitledPersonalization()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowUnentitledPersonalization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowRemoteDiagnostics

Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device

```typescript
function allowRemoteDiagnostics(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowRemoteDiagnostics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowRemoteDiagnostics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowPrimaryContentAdTargeting

Whether the user allows ads to be targeted to the user while watching content in the primary experience

```typescript
function allowPrimaryContentAdTargeting(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryContentAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryContentAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowPrimaryBrowseAdTargeting

Whether the user allows ads to be targeted to the user while browsing in the primary experience

```typescript
function allowPrimaryBrowseAdTargeting(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowPrimaryBrowseAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowPrimaryBrowseAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowAppContentAdTargeting

Whether the user allows ads to be targeted to the user while watching content in apps

```typescript
function allowAppContentAdTargeting(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowAppContentAdTargeting()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowAppContentAdTargeting",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowACRCollection

Whether the user allows their automatic content recognition data to be collected

```typescript
function allowACRCollection(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowACRCollection()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowACRCollection",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### allowCameraAnalytics

Whether the user allows data from their camera to be used for Product Analytics

```typescript
function allowCameraAnalytics(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Privacy } from '@firebolt-js/manage-sdk'

Privacy.allowCameraAnalytics()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "privacy.allowCameraAnalytics",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
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

### PrivacySettings


```typescript
type PrivacySettings = {
  allowACRCollection: boolean
  allowResumePoints: boolean
  allowAppContentAdTargeting: boolean
  allowCameraAnalytics: boolean
  allowPersonalization: boolean
  allowPrimaryBrowseAdTargeting: boolean
  allowPrimaryContentAdTargeting: boolean
  allowProductAnalytics: boolean
  allowRemoteDiagnostics: boolean
  allowUnentitledPersonalization: boolean
  allowUnentitledResumePoints: boolean
  allowWatchHistory: boolean
}
```



---


