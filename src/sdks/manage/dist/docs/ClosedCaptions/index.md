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
    - [Additional Methods](#additional-methods)    
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function backgroundColor(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundColor("#000000")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundColor",
  "params": {
    "value": "#000000"
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
function backgroundColor ( subscriber: (color) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `color` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundColor( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "#000000"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function backgroundOpacity(value: number): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0
maximum: 100 |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundOpacity(100)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.backgroundOpacity",
  "params": {
    "value": 100
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
function backgroundOpacity ( subscriber: (opacity) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `opacity` | `number` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundOpacity( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": 100
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function enabled(value: boolean): Promise<null>
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function enabled ( subscriber: (enabled) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `enabled` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.enabled( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
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
  "method": "closedcaptions.enabled",
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontColor(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontColor("#ffffff")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontColor",
  "params": {
    "value": "#ffffff"
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
function fontColor ( subscriber: (color) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `color` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontColor( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "#ffffff"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontEdge(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdge("none")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdge",
  "params": {
    "value": "none"
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
function fontEdge ( subscriber: (edge) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `edge` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdge( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "none"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontEdgeColor(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdgeColor("#000000")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontEdgeColor",
  "params": {
    "value": "#000000"
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
function fontEdgeColor ( subscriber: (color) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `color` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdgeColor( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "#000000"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontFamily(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontFamily("Monospace sans-serif")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontFamily",
  "params": {
    "value": "Monospace sans-serif"
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
function fontFamily ( subscriber: (family) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `family` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontFamily( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "Monospace sans-serif"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontOpacity(value: number): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0
maximum: 100 |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontOpacity(100)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontOpacity",
  "params": {
    "value": 100
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
function fontOpacity ( subscriber: (opacity) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `opacity` | `number` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontOpacity( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": 100
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function fontSize(value: number): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0 |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontSize(1)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.fontSize",
  "params": {
    "value": 1
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
function fontSize ( subscriber: (size) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `size` | `number` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontSize( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": 1
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function textAlign(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlign("center")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlign",
  "params": {
    "value": "center"
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
function textAlign ( subscriber: (opacity) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `opacity` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlign( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "center"
}
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
function textAlignVertical(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlignVertical("middle")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "closedcaptions.textAlignVertical",
  "params": {
    "value": "middle"
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
function textAlignVertical ( subscriber: (opacity) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with ClosedCaptions.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `opacity` | `string` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlignVertical( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ ClosedCaptions.clear(listenerId)
})
```

value of `value`:

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
  "result": "middle"
}
```

</details>



---




### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### enabled

Whether or not closed-captions are enabled.

```typescript
function enabled(value: boolean): Promise<null>
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.enabled(true)
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
  "method": "closedcaptions.enabled",
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

### fontFamily

The prefered font family for displaying closed-captions.

```typescript
function fontFamily(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontFamily("Monospace sans-serif")
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
  "method": "closedcaptions.fontFamily",
  "params": {
    "value": "Monospace sans-serif"
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

### fontSize

The prefered font size for displaying closed-captions.

```typescript
function fontSize(value: number): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0 |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontSize(1)
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
  "method": "closedcaptions.fontSize",
  "params": {
    "value": 1
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

### fontColor

The prefered font color for displaying closed-captions.

```typescript
function fontColor(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontColor("#ffffff")
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
  "method": "closedcaptions.fontColor",
  "params": {
    "value": "#ffffff"
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

### fontEdge

The prefered font edge style for displaying closed-captions.

```typescript
function fontEdge(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdge("none")
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
  "method": "closedcaptions.fontEdge",
  "params": {
    "value": "none"
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

### fontEdgeColor

The prefered font edge color for displaying closed-captions.

```typescript
function fontEdgeColor(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontEdgeColor("#000000")
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
  "method": "closedcaptions.fontEdgeColor",
  "params": {
    "value": "#000000"
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

### fontOpacity

The prefered opacity for displaying closed-captions characters.

```typescript
function fontOpacity(value: number): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0
maximum: 100 |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.fontOpacity(100)
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
  "method": "closedcaptions.fontOpacity",
  "params": {
    "value": 100
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

### backgroundColor

The prefered background color for displaying closed-captions, .

```typescript
function backgroundColor(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundColor("#000000")
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
  "method": "closedcaptions.backgroundColor",
  "params": {
    "value": "#000000"
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

### backgroundOpacity

The prefered opacity for displaying closed-captions backgrounds.

```typescript
function backgroundOpacity(value: number): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `number` | true |  <br/>minumum: 0
maximum: 100 |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.backgroundOpacity(100)
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
  "method": "closedcaptions.backgroundOpacity",
  "params": {
    "value": 100
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

### textAlign

The prefered horizontal alignment for displaying closed-captions characters.

```typescript
function textAlign(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlign("center")
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
  "method": "closedcaptions.textAlign",
  "params": {
    "value": "center"
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

### textAlignVertical

The prefered horizontal alignment for displaying closed-captions characters.

```typescript
function textAlignVertical(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

ClosedCaptions.textAlignVertical("middle")
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
  "method": "closedcaptions.textAlignVertical",
  "params": {
    "value": "middle"
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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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
import { ClosedCaptions } from '@firebolt-js/manage-sdk'

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


