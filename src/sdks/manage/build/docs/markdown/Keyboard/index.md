Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [keyboard.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/keyboard.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [listen](#listen)
    - [once](#once)
    - [provide](#provide)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)
 - [Provider Interfaces](#provider-interfaces)
    - [KeyboardInputProvider](#keyboardinputprovider)
 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [ProviderResponse](#providerresponse)
    - [KeyboardParameters](#keyboardparameters)
    - [KeyboardProviderRequest](#keyboardproviderrequest)
    - [KeyboardResult](#keyboardresult)

<span></span>

## Usage
To use the Keyboard module, you can import it into your project from the Firebolt SDK:

```javascript
import { Keyboard } from '@firebolt-js/manage-sdk'
```


## Methods
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

### provide

Register to provide a capability from this module.

See [Provider Interfaces](#provider-interfaces), for more info.

```typescript
function provide(provider: object | class): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `provider` | `object | class` | true | An Object or Class that implements all of the provider interface methods.  |


Promise resolution:

```javascript
void
```



---



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### standardFocus

Internal API for Standard Provider to request focus for UX purposes.




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.standardFocus",
  "params": {}
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

### passwordFocus

Internal API for Password Provider to request focus for UX purposes.




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.passwordFocus",
  "params": {}
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

### emailFocus

Internal API for Email Provider to request focus for UX purposes.




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.emailFocus",
  "params": {}
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

### standardResponse

Internal API for Standard Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.standardResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "text": "username"
      }
    }
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

### standardError

Internal API for Standard Provider to send back error.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `error` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example 1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.standardError",
  "params": {
    "error": {
      "correlationId": "123",
      "result": {
        "code": 1,
        "message": "Error"
      }
    }
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

### passwordResponse

Internal API for Password Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.passwordResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "text": "password"
      }
    }
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

### passwordError

Internal API for Password Provider to send back error.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `error` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example 1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.passwordError",
  "params": {
    "error": {
      "correlationId": "123",
      "result": {
        "code": 1,
        "message": "Error"
      }
    }
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

### emailResponse

Internal API for Email Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.emailResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "text": "email@address.com"
      }
    }
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

### emailError

Internal API for Email Provider to send back error.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `error` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example 1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.emailError",
  "params": {
    "error": {
      "correlationId": "123",
      "result": {
        "code": 1,
        "message": "Error"
      }
    }
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
### onRequestStandard

Registers as a provider for when the user should be shown a standard keyboard.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardProviderRequest`](#keyboardproviderrequest) | The request to start a keyboard session |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.onRequestStandard",
  "params": {
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
    "correlationId": "abc",
    "parameters": {
      "message": "Enter your user name."
    }
  }
}
```

</details>




---

### onRequestPassword

Registers as a provider for when the user should be shown a password keyboard, with dots for each character entered.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardProviderRequest`](#keyboardproviderrequest) | The request to start a keyboard session |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.onRequestPassword",
  "params": {
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
    "correlationId": "abc",
    "parameters": {
      "message": "Enter your user name."
    }
  }
}
```

</details>




---

### onRequestEmail

Registers as a provider for when the user should be shown a keyboard optimized for email address entry.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardProviderRequest`](#keyboardproviderrequest) | The request to start a keyboard session |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.onRequestEmail",
  "params": {
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
    "correlationId": "abc",
    "parameters": {
      "message": "Enter your user name."
    }
  }
}
```

</details>




---






## Provider Interfaces
Providers are interfaces that your app can implement in order to provide certain capabilties back to the platform.

To register a provider, use the [`provide()`](#provide) method.

Every provider interface method has the following signature:

```typescript
(parameters: object | void, session: ProviderSession) => {}
```

`ProviderSession` has the following interface:

```typescript

interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}

```

### KeyboardInputProvider
The provider interface for the `xrn:firebolt:capability:input:keyboard` capability.

```typescript
interface KeyboardInputProvider {
	standard(parameters?: KeyboardParameters, session?: FocusableProviderSession): Promise<KeyboardResult>
	password(parameters?: KeyboardParameters, session?: FocusableProviderSession): Promise<KeyboardResult>
	email(parameters?: KeyboardParameters, session?: FocusableProviderSession): Promise<KeyboardResult>
}

```

Usage:

```typescript
Keyboard.provide('xrn:firebolt:capability:input:keyboard', provider: KeyboardInputProvider | object)
```

### standard

Registers as a provider for when the user should be shown a standard keyboard.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`KeyboardParameters`](#keyboardparameters) | false |   |
| `session` | `FocusableProviderSession` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardResult`](#keyboardresult) |  |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.standard",
  "params": {
    "parameters": {
      "message": "Enter your user name."
    },
    "session": {
      "correlationId": "abc"
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
    "text": "username"
  }
}
```

</details>




---

### password

Registers as a provider for when the user should be shown a password keyboard, with dots for each character entered.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`KeyboardParameters`](#keyboardparameters) | false |   |
| `session` | `FocusableProviderSession` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardResult`](#keyboardresult) |  |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.password",
  "params": {
    "parameters": {
      "message": "Enter your user name."
    },
    "session": {
      "correlationId": "abc"
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
    "text": "password"
  }
}
```

</details>




---

### email

Registers as a provider for when the user should be shown a keyboard optimized for email address entry.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`KeyboardParameters`](#keyboardparameters) | false |   |
| `session` | `FocusableProviderSession` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`KeyboardResult`](#keyboardresult) |  |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "keyboard.email",
  "params": {
    "parameters": {
      "message": "Enter your user name."
    },
    "session": {
      "correlationId": "abc"
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
    "text": "email@address.com"
  }
}
```

</details>




---



#### Examples

**Register your app to provide the `xrn:firebolt:capability:input:keyboard` capability.**

```javascript
import { Keyboard } from '@firebolt-js/manage-sdk'

class MyKeyboardInputProvider {

    async standard(parameters, session) {
        return await Promise.resolve({
            "text": "username"
        })
    }

    async password(parameters, session) {
        return await Promise.resolve({
            "text": "password"
        })
    }

    async email(parameters, session) {
        return await Promise.resolve({
            "text": "email@address.com"
        })
    }

}

Keyboard.provide('xrn:firebolt:capability:input:keyboard', new MyKeyboardInputProvider())
```

<details>
    <summary>JSON-RPC</summary>

**Register to recieve each provider API**

Request:

```json

{
    "id": 1,
    "method": "keyboard.onRequestStandard",
    "params": {
        "listen": true
    }
}

{
    "id": 2,
    "method": "keyboard.onRequestPassword",
    "params": {
        "listen": true
    }
}

{
    "id": 3,
    "method": "keyboard.onRequestEmail",
    "params": {
        "listen": true
    }
}

```

Response:

```json

{
    "id": 1,
    "result": {
        "listening": true,
        "event": "Keyboard.onRequestStandard"
    }            
 
}

{
    "id": 2,
    "result": {
        "listening": true,
        "event": "Keyboard.onRequestPassword"
    }            
 
}

{
    "id": 3,
    "result": {
        "listening": true,
        "event": "Keyboard.onRequestEmail"
    }            
 
}

```



**Asynchronous event to initiate standard()**

Event Response:

```json
{
    "id": 1,
    "result": {
        "correlationId": "abc",
        "parameters": {
            "message": "Enter your user name."
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 4,
    "method": "keyboard.standardResponse",
    "params": {
        "correlationId": "abc",
        "result": {
            "text": "username"
        }
    }
}
```

Response:

```json
{
    "id": 4,
    "result": true
}
```



**Asynchronous event to initiate password()**

Event Response:

```json
{
    "id": 2,
    "result": {
        "correlationId": "abc",
        "parameters": {
            "message": "Enter your user name."
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 5,
    "method": "keyboard.passwordResponse",
    "params": {
        "correlationId": "abc",
        "result": {
            "text": "password"
        }
    }
}
```

Response:

```json
{
    "id": 5,
    "result": true
}
```



**Asynchronous event to initiate email()**

Event Response:

```json
{
    "id": 3,
    "result": {
        "correlationId": "abc",
        "parameters": {
            "message": "Enter your user name."
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 6,
    "method": "keyboard.emailResponse",
    "params": {
        "correlationId": "abc",
        "result": {
            "text": "email@address.com"
        }
    }
}
```

Response:

```json
{
    "id": 6,
    "result": true
}
```




</details>





## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

### ProviderResponse


```typescript
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
```



---

### KeyboardParameters


```typescript
type KeyboardParameters = {
  message: string            // The message to display to the user so the user knows what they are entering
}
```



---

### KeyboardProviderRequest


```typescript
type KeyboardProviderRequest = {
  correlationId: string           // An id to correlate the provider response with this request
  parameters: KeyboardParameters
}
```



---

### KeyboardResult


```typescript
type KeyboardResult = {
  text: string           // The text the user entered into the keyboard
  canceled?: boolean     // Whether the user canceled entering text before they were finished typing on the keyboard
}
```



---


