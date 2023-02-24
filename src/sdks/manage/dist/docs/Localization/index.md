Version undefined

## Overview
 

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
    - [listen](#listen)
    - [locale](#locale)
    - [locality](#locality)
    - [once](#once)
    - [postalCode](#postalcode)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [Locality](#locality)
    - [CountryCode](#countrycode)
    - [Language](#language)
    - [Locale](#locale)

<span></span>

## Usage
To use the Localization module, you can import it into your project from the Firebolt SDK:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'
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
import { Localization } from '@firebolt-js/manage-sdk'

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



To get the value of `countryCode` call the method like this:


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
import { Localization } from '@firebolt-js/manage-sdk'

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





To set the value of `countryCode` call the method like this:


```typescript
function countryCode(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device country code <br/>pattern: ^[A-Za-z]{2}$ |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.countryCode("US")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.countryCode",
  "params": {
    "value": "US"
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
function countryCode ( subscriber: (code) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `code` | `string` | Yes | the device country code |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.countryCode( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `value`:

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
  "result": "US"
}
```

</details>



---


### language
Get the ISO 639 1/2 code for the preferred language



To get the value of `language` call the method like this:


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
import { Localization } from '@firebolt-js/manage-sdk'

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





To set the value of `language` call the method like this:


```typescript
function language(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device language <br/>pattern: ^[A-Za-z]{2}$ |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.language("en")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.language",
  "params": {
    "value": "en"
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
function language ( subscriber: (lang) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `lang` | `string` | Yes | the device language |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.language( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `value`:

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

### locale
Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale



To get the value of `locale` call the method like this:


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
import { Localization } from '@firebolt-js/manage-sdk'

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





To set the value of `locale` call the method like this:


```typescript
function locale(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device locale <br/>pattern: ^[a-zA-Z]+([a-zA-Z0-9\-]*)$ |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locale("en-US")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.locale",
  "params": {
    "value": "en-US"
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
function locale ( subscriber: (locale) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `locale` | `string` | Yes | the device locale |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locale( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `value`:

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
  "result": "en-US"
}
```

</details>



---


### locality
Get the locality/city the device is located in



To get the value of `locality` call the method like this:


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
import { Localization } from '@firebolt-js/manage-sdk'

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





To set the value of `locality` call the method like this:


```typescript
function locality(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device city  |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locality("Philadelphia")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.locality",
  "params": {
    "value": "Philadelphia"
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
function locality ( subscriber: (locality) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `locality` | `string` | Yes | the device city |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locality( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `value`:

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
  "result": "Philadelphia"
}
```

</details>



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

### postalCode
Get the postal code the device is located in



To get the value of `postalCode` call the method like this:


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
import { Localization } from '@firebolt-js/manage-sdk'

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





To set the value of `postalCode` call the method like this:


```typescript
function postalCode(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device postal code  |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.postalCode("19103")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "localization.postalCode",
  "params": {
    "value": "19103"
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
function postalCode ( subscriber: (postalCode) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Localization.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `postalCode` | `string` | Yes | the device postal code |

**Examples**

Default Example


JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.postalCode( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Localization.clear(listenerId)
})
```

value of `value`:

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
  "result": "19103"
}
```

</details>



---




### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### locality

Get the locality/city the device is located in

```typescript
function locality(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device city  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locality("Philadelphia")
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
  "method": "localization.locality",
  "params": {
    "value": "Philadelphia"
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

### postalCode

Get the postal code the device is located in

```typescript
function postalCode(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device postal code  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.postalCode("19103")
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
  "method": "localization.postalCode",
  "params": {
    "value": "19103"
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

### countryCode

Get the ISO 3166 code for the counrty device is located in

```typescript
function countryCode(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device country code <br/>pattern: ^[A-Za-z]{2}$ |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.countryCode("US")
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
  "method": "localization.countryCode",
  "params": {
    "value": "US"
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

### language

Get the ISO 639 1/2 code for the preferred language

```typescript
function language(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device language <br/>pattern: ^[A-Za-z]{2}$ |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.language("en")
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
  "method": "localization.language",
  "params": {
    "value": "en"
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

### locale

Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale

```typescript
function locale(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device locale <br/>pattern: ^[a-zA-Z]+([a-zA-Z0-9\-]*)$ |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

Localization.locale("en-US")
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
  "method": "localization.locale",
  "params": {
    "value": "en-US"
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
### locality

Get the locality/city the device is located in

```typescript
function locality(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device city |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

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

### postalCode

Get the postal code the device is located in

```typescript
function postalCode(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device postal code |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

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

### countryCode

Get the ISO 3166 code for the counrty device is located in

```typescript
function countryCode(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device country code |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

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

```typescript
function language(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device language |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

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




---

### locale

Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale

```typescript
function locale(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device locale |


**Examples**

Default Example

JavaScript:

```javascript
import { Localization } from '@firebolt-js/manage-sdk'

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








## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

### Locality


```typescript
type Locality = string
```



---

### CountryCode


```typescript
type CountryCode = string
```



---

### Language


```typescript
type Language = string
```



---

### Locale


```typescript
type Locale = string
```



---


