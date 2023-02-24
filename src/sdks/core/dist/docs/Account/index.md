Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [account.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/account.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [id](#id)
    - [uid](#uid)



 - [Schemas](#schemas)

<span></span>

## Usage
To use the Account module, you can import it into your project from the Firebolt SDK:

```javascript
import { Account } from '@firebolt-js/sdk'
```


## Methods
### id
Get the platform back-office account identifier



To get the value of `id` call the method like this:


```typescript
function id(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the id |


**Examples**

Default Example

JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.id()
    .then(id => {
        console.log(id)
    })
```
Value of `id`:

```javascript
"123"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.id",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "123"
}
```

</details>




To set the value of `id` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.id()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function id (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Account.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.id((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Account.clear(listenerId)
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

### uid
Gets a unique id for the current app & account



To get the value of `uid` call the method like this:


```typescript
function uid(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | a unique ID |


**Examples**

Getting the unique ID

JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.uid()
    .then(uniqueId => {
        console.log(uniqueId)
    })
```
Value of `uniqueId`:

```javascript
"ee6723b8-7ab3-462c-8d93-dbf61227998e"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.uid",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "ee6723b8-7ab3-462c-8d93-dbf61227998e"
}
```

</details>




To set the value of `uid` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.uid()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function uid (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Account.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.uid((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Account.clear(listenerId)
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









