Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [closedcaptions.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/closedcaptions.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [backgroundColor](#backgroundcolor)
    - [backgroundOpacity](#backgroundopacity)
    - [enabled](#enabled)
    - [fontColor](#fontcolor)
    - [fontEdge](#fontedge)
    - [fontEdgeColor](#fontedgecolor)
    - [fontFamily](#fontfamily)
    - [fontOpacity](#fontopacity)
    - [fontSize](#fontsize)
    - [listen](#listen)
    - [once](#once)
    - [textAlign](#textalign)
    - [textAlignVertical](#textalignvertical)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [FontFamily](#fontfamily)
    - [FontSize](#fontsize)
    - [Color](#color)
    - [FontEdge](#fontedge)
    - [Opacity](#opacity)
    - [HorizontalAlignment](#horizontalalignment)
    - [VerticalAlignment](#verticalalignment)

<span></span>

## Usage
To use the ClosedCaptions module, you can import it into your project from the Firebolt SDK:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'
```


## Methods
### backgroundColor
The prefered background color for displaying closed-captions, .



To get the value of `backgroundColor` call the method like this:


```typescript
function backgroundColor(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#000000"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>





To set the value of `backgroundColor` call the method like this:


```typescript
function backgroundColor(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundColor(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function backgroundColor (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundColor((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### backgroundOpacity
The prefered opacity for displaying closed-captions backgrounds.



To get the value of `backgroundOpacity` call the method like this:


```typescript
function backgroundOpacity(): Promise<number>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `number` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundOpacity()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
100
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>





To set the value of `backgroundOpacity` call the method like this:


```typescript
function backgroundOpacity(): Promise<ListenResponse | number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundOpacity(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function backgroundOpacity (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundOpacity((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### enabled
Whether or not closed-captions are enabled.



To get the value of `enabled` call the method like this:


```typescript
function enabled(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.enabled()
    .then(enabled => {
        console.log(enabled)
    })
```
Value of `enabled`:

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
  "method": "closedcaptions.enabled",
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





To set the value of `enabled` call the method like this:


```typescript
function enabled(): Promise<ListenResponse | boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.enabled(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.enabled",
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function enabled (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.enabled((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontColor
The prefered font color for displaying closed-captions.



To get the value of `fontColor` call the method like this:


```typescript
function fontColor(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#ffffff"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#ffffff"
}
```

</details>





To set the value of `fontColor` call the method like this:


```typescript
function fontColor(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontColor(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#ffffff"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontColor (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontColor((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontEdge
The prefered font edge style for displaying closed-captions.



To get the value of `fontEdge` call the method like this:


```typescript
function fontEdge(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdge()
    .then(edge => {
        console.log(edge)
    })
```
Value of `edge`:

```javascript
"none"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdge",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "none"
}
```

</details>





To set the value of `fontEdge` call the method like this:


```typescript
function fontEdge(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdge(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdge",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "none"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontEdge (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdge((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontEdgeColor
The prefered font edge color for displaying closed-captions.



To get the value of `fontEdgeColor` call the method like this:


```typescript
function fontEdgeColor(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdgeColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#000000"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdgeColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>





To set the value of `fontEdgeColor` call the method like this:


```typescript
function fontEdgeColor(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdgeColor(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdgeColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontEdgeColor (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdgeColor((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontFamily
The prefered font family for displaying closed-captions.



To get the value of `fontFamily` call the method like this:


```typescript
function fontFamily(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontFamily()
    .then(family => {
        console.log(family)
    })
```
Value of `family`:

```javascript
"Monospace sans-serif"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontFamily",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Monospace sans-serif"
}
```

</details>





To set the value of `fontFamily` call the method like this:


```typescript
function fontFamily(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontFamily(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontFamily",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Monospace sans-serif"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontFamily (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontFamily((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontOpacity
The prefered opacity for displaying closed-captions characters.



To get the value of `fontOpacity` call the method like this:


```typescript
function fontOpacity(): Promise<number>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `number` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontOpacity()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
100
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>





To set the value of `fontOpacity` call the method like this:


```typescript
function fontOpacity(): Promise<ListenResponse | number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontOpacity(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontOpacity (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontOpacity((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### fontSize
The prefered font size for displaying closed-captions.



To get the value of `fontSize` call the method like this:


```typescript
function fontSize(): Promise<number>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `number` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontSize()
    .then(size => {
        console.log(size)
    })
```
Value of `size`:

```javascript
1
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontSize",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
}
```

</details>





To set the value of `fontSize` call the method like this:


```typescript
function fontSize(): Promise<ListenResponse | number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontSize(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontSize",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function fontSize (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontSize((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### textAlign
The prefered horizontal alignment for displaying closed-captions characters.



To get the value of `textAlign` call the method like this:


```typescript
function textAlign(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlign()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
"center"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlign",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "center"
}
```

</details>





To set the value of `textAlign` call the method like this:


```typescript
function textAlign(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlign(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlign",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "center"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function textAlign (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlign((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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

### textAlignVertical
The prefered horizontal alignment for displaying closed-captions characters.



To get the value of `textAlignVertical` call the method like this:


```typescript
function textAlignVertical(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlignVertical()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
"middle"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlignVertical",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "middle"
}
```

</details>





To set the value of `textAlignVertical` call the method like this:


```typescript
function textAlignVertical(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlignVertical(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlignVertical",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "middle"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function textAlignVertical (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlignVertical((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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
### enabled

Whether or not closed-captions are enabled.

```typescript
function enabled(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.enabled()
    .then(enabled => {
        console.log(enabled)
    })
```
Value of `enabled`:

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
  "method": "closedcaptions.enabled",
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

### fontFamily

The prefered font family for displaying closed-captions.

```typescript
function fontFamily(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontFamily()
    .then(family => {
        console.log(family)
    })
```
Value of `family`:

```javascript
"Monospace sans-serif"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontFamily",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Monospace sans-serif"
}
```

</details>




---

### fontSize

The prefered font size for displaying closed-captions.

```typescript
function fontSize(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontSize()
    .then(size => {
        console.log(size)
    })
```
Value of `size`:

```javascript
1
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontSize",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
}
```

</details>




---

### fontColor

The prefered font color for displaying closed-captions.

```typescript
function fontColor(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#ffffff"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#ffffff"
}
```

</details>




---

### fontEdge

The prefered font edge style for displaying closed-captions.

```typescript
function fontEdge(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdge()
    .then(edge => {
        console.log(edge)
    })
```
Value of `edge`:

```javascript
"none"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdge",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "none"
}
```

</details>




---

### fontEdgeColor

The prefered font edge color for displaying closed-captions.

```typescript
function fontEdgeColor(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontEdgeColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#000000"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdgeColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>




---

### fontOpacity

The prefered opacity for displaying closed-captions characters.

```typescript
function fontOpacity(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.fontOpacity()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
100
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>




---

### backgroundColor

The prefered background color for displaying closed-captions, .

```typescript
function backgroundColor(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundColor()
    .then(color => {
        console.log(color)
    })
```
Value of `color`:

```javascript
"#000000"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundColor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "#000000"
}
```

</details>




---

### backgroundOpacity

The prefered opacity for displaying closed-captions backgrounds.

```typescript
function backgroundOpacity(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.backgroundOpacity()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
100
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundOpacity",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 100
}
```

</details>




---

### textAlign

The prefered horizontal alignment for displaying closed-captions characters.

```typescript
function textAlign(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlign()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
"center"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlign",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "center"
}
```

</details>




---

### textAlignVertical

The prefered horizontal alignment for displaying closed-captions characters.

```typescript
function textAlignVertical(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/sdk'

ClosedCaptions.textAlignVertical()
    .then(opacity => {
        console.log(opacity)
    })
```
Value of `opacity`:

```javascript
"middle"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlignVertical",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "middle"
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


