Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [developertools.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/developertools.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [find](#find)
    - [listen](#listen)
    - [once](#once)
    - [pair](#pair)
    - [unpair](#unpair)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [DeveloperTool](#developertool)

<span></span>

## Usage
To use the DeveloperTools module, you can import it into your project from the Firebolt SDK:

```javascript
import { DeveloperTools } from '@firebolt-js/manage-sdk'
```


## Methods
### find

Starts a long-running DNS-SD search for a list of developer tools that match the standard 'Firebolt Developer Tool' service type

```typescript
function find(): Promise<DeveloperTool[]>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`DeveloperTool`[]](#developertool) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { DeveloperTools } from '@firebolt-js/manage-sdk'

DeveloperTools.find()
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
[
  {
    "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9",
    "name": "A tool"
  }
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "developertools.find",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9",
      "name": "A tool"
    }
  ]
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

### pair

Configures Firebolt to accept incoming Firebolt JSON RPC messages from the developer tool identified by the given developer tool ID

```typescript
function pair(id: string): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `id` | `string` | true | The ID of the DeveloperTool to which to connect <br/>format: uuid |


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { DeveloperTools } from '@firebolt-js/manage-sdk'

DeveloperTools.pair("ff6340fb-8576-494c-97c6-e60e9a4eeba9")
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
  "method": "developertools.pair",
  "params": {
    "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9"
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

### unpair

Disconnect Firebolt as a web socket client from the web socket that corresponds to the given developer tool ID

```typescript
function unpair(id: string): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `id` | `string` | true | The ID of the DeveloperTool from which to disconnect <br/>format: uuid |


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { DeveloperTools } from '@firebolt-js/manage-sdk'

DeveloperTools.unpair("ff6340fb-8576-494c-97c6-e60e9a4eeba9")
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
  "method": "developertools.unpair",
  "params": {
    "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9"
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



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### stopFind

Starts a long-running DNS-SD search for a list of developer tools that match the standard 'Firebolt Developer Tool' service type



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `correlationId` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "developertools.stopFind",
  "params": {
    "correlationId": "xyz"
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
### onToolAvailable

Starts a long-running DNS-SD search for a list of developer tools that match the standard 'Firebolt Developer Tool' service type



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `correlationId` | `string` | true |   |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`DeveloperTool`](#developertool) |  |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "developertools.onToolAvailable",
  "params": {
    "correlationId": "xyz",
    "listen": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9",
    "name": "A tool"
  }
}
```

</details>




---

### onToolUnavailable

Starts a long-running DNS-SD search for a list of developer tools that match the standard 'Firebolt Developer Tool' service type



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `correlationId` | `string` | true |   |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`DeveloperTool`](#developertool) |  |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "developertools.onToolUnavailable",
  "params": {
    "correlationId": "xyz",
    "listen": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "id": "ff6340fb-8576-494c-97c6-e60e9a4eeba9",
    "name": "A tool"
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

### DeveloperTool


```typescript
type DeveloperTool = {
  id: string            // The ID that uniquely identifies this instance of a developer tool
  name: string          // Developer-visible 'friendly name' for the developer tool
}
```



---


