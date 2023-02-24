Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [lifecycle.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/lifecycle.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [listen](#listen)
    - [once](#once)
    - [provide](#provide)
    - [session](#session)
    - [setState](#setstate)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)
 - [Provider Interfaces](#provider-interfaces)
    - [LaunchProvider](#launchprovider)
    - [StateLifecycleProvider](#statelifecycleprovider)
 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [ProviderResponse](#providerresponse)
    - [NavigationIntent](#navigationintent)
    - [ProgramType](#programtype)
    - [HomeIntent](#homeintent)
    - [LaunchIntent](#launchintent)
    - [EntityIntent](#entityintent)
    - [PlaybackIntent](#playbackintent)
    - [SearchIntent](#searchintent)
    - [SectionIntent](#sectionintent)
    - [TuneIntent](#tuneintent)
    - [Intent](#intent)
    - [IntentProperties](#intentproperties)
    - [MovieEntity](#movieentity)
    - [TVEpisodeEntity](#tvepisodeentity)
    - [TVSeriesEntity](#tvseriesentity)
    - [TVSeasonEntity](#tvseasonentity)
    - [AdditionalEntity](#additionalentity)
    - [UntypedEntity](#untypedentity)
    - [ChannelEntity](#channelentity)
    - [ProgramEntity](#programentity)
    - [Identifier](#identifier)
    - [LifecycleReadyParameters](#lifecyclereadyparameters)
    - [LifecycleLaunchParameters](#lifecyclelaunchparameters)
    - [LifecycleLaunchResponse](#lifecyclelaunchresponse)
    - [LifecycleCloseParameters](#lifecyclecloseparameters)
    - [LifecycleFinishedParameters](#lifecyclefinishedparameters)
    - [LifecycleReadyRequest](#lifecyclereadyrequest)
    - [LifecycleLaunchRequest](#lifecyclelaunchrequest)
    - [LifecycleCloseRequest](#lifecyclecloserequest)
    - [LifecycleFinishedRequest](#lifecyclefinishedrequest)
    - [AppSession](#appsession)
    - [CloseReason](#closereason)
    - [LifecycleState](#lifecyclestate)
    - [SecondScreenEvent](#secondscreenevent)

<span></span>

## Usage
To use the Lifecycle module, you can import it into your project from the Firebolt SDK:

```javascript
import { Lifecycle } from '@firebolt-js/manage-sdk'
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

### session

Used by a Lifecycle provider to tell Firebolt that an app session has been started or updated. Firebolt can use this information to have context about the app when it makes API requests

```typescript
function session(session: AppSession): Promise<object>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `session` | [`AppSession`](#appsession) | true |   |


Promise resolution:

| Field | Type | Description |
| ----- | ---- | ----------- |
| `sessionId` | `string` |  |


**Examples**

Starts or updates an app session

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/manage-sdk'

Lifecycle.session({
                    "app": {
                      "id": "SomeApp",
                      "url": "https://some-app.firebolt.rdkcentral.com"
                    },
                    "runtime": {
                      "id": "WebBrowser-1"
                    },
                    "launch": {
                      "intent": {
                        "action": "search",
                        "data": {
                          "query": "Dog videos"
                        },
                        "context": {
                          "source": "voice"
                        }
                      }
                    }
                  })
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
{
  "sessionId": "c0d012b4-0854-4bbc-82d5-ab52ac29dd94"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.session",
  "params": {
    "session": {
      "app": {
        "id": "SomeApp",
        "url": "https://some-app.firebolt.rdkcentral.com"
      },
      "runtime": {
        "id": "WebBrowser-1"
      },
      "launch": {
        "intent": {
          "action": "search",
          "data": {
            "query": "Dog videos"
          },
          "context": {
            "source": "voice"
          }
        }
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
  "result": {
    "sessionId": "c0d012b4-0854-4bbc-82d5-ab52ac29dd94"
  }
}
```

</details>




---

### setState

Used by provider to update the state of an application so that the state can be emitted to apps.

```typescript
function setState(appId: string, state: LifecycleState): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `appId` | `string` | true |   |
| `state` | [`LifecycleState`](#lifecyclestate) | true |   |


Promise resolution:

```javascript
void
```

**Examples**

Set application lifecycle state to inactive

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/manage-sdk'

Lifecycle.setState("SomeAppId", "inactive")
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
  "method": "lifecycle.setState",
  "params": {
    "appId": "SomeAppId",
    "state": "inactive"
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
### launchResponse

Internal API for Launch Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example #1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.launchResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "success": true
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

<details>
    <summary>More examples...</summary>
Example #2



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.launchResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "success": false
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

</details>



---

### launchError

Internal API for Launch Provider to send back error.



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
  "method": "lifecycle.launchError",
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

### readyResponse

Internal API for Ready Provider to send back response.



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
  "method": "lifecycle.readyResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": null
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

### readyError

Internal API for Ready Provider to send back error.



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
  "method": "lifecycle.readyError",
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

### closeResponse

Internal API for Close Provider to send back response.



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
  "method": "lifecycle.closeResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": null
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

### closeError

Internal API for Close Provider to send back error.



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
  "method": "lifecycle.closeError",
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

### finishedResponse

Internal API for Finished Provider to send back response.



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
  "method": "lifecycle.finishedResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": null
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

### finishedError

Internal API for Finished Provider to send back error.



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
  "method": "lifecycle.finishedError",
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
### onRequestLaunch

Tells the provider that an app should be launched



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleLaunchRequest`](#lifecyclelaunchrequest) | The app was requested to be launched |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onRequestLaunch",
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
    "correlationId": "123",
    "parameters": {
      "appId": "SomeAppId",
      "intent": {
        "action": "home",
        "context": {
          "source": "voice"
        }
      }
    }
  }
}
```

</details>




---

### onRequestReady

Tells the provider that an app has said they are ready



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleReadyRequest`](#lifecyclereadyrequest) | The app has said they are ready |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onRequestReady",
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
    "correlationId": "123",
    "parameters": {
      "appId": "SomeAppId"
    }
  }
}
```

</details>




---

### onRequestClose

Tells the provider that an app has requested closing itself



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleCloseRequest`](#lifecyclecloserequest) | The app has requested to be closed |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onRequestClose",
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
    "correlationId": "123",
    "parameters": {
      "appId": "SomeAppId",
      "reason": "userExit"
    }
  }
}
```

</details>




---

### onRequestFinished

Tells the provider that an app has said they are finished cleaning up while unloading



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleFinishedRequest`](#lifecyclefinishedrequest) | The app has said they are finished |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onRequestFinished",
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
    "correlationId": "123",
    "parameters": {
      "appId": "SomeAppId"
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


```

### LaunchProvider
The provider interface for the `xrn:firebolt:capability:lifecycle:launch` capability.

```typescript
interface LaunchProvider {
	launch(parameters?: LifecycleLaunchParameters, session?: ProviderSession): Promise<LifecycleLaunchResponse>
}

```

Usage:

```typescript
Lifecycle.provide('xrn:firebolt:capability:lifecycle:launch', provider: LaunchProvider | object)
```

### launch

Tells the provider that an app should be launched



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`LifecycleLaunchParameters`](#lifecyclelaunchparameters) | false |   |
| `session` | `ProviderSession` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleLaunchResponse`](#lifecyclelaunchresponse) |  |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.launch",
  "params": {
    "parameters": {
      "appId": "SomeAppId",
      "intent": {
        "action": "home",
        "context": {
          "source": "voice"
        }
      }
    },
    "session": {
      "correlationId": "123"
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
    "success": true
  }
}
```

</details>




---



#### Examples

**Register your app to provide the `xrn:firebolt:capability:lifecycle:launch` capability.**

```javascript
import { Lifecycle } from '@firebolt-js/manage-sdk'

class MyLaunchProvider {

    async launch(parameters, session) {
        return await Promise.resolve({
            "success": true
        })
    }

}

Lifecycle.provide('xrn:firebolt:capability:lifecycle:launch', new MyLaunchProvider())
```

<details>
    <summary>JSON-RPC</summary>

**Register to recieve each provider API**

Request:

```json

{
    "id": 1,
    "method": "lifecycle.onRequestLaunch",
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
        "event": "Lifecycle.onRequestLaunch"
    }            
 
}

```



**Asynchronous event to initiate launch()**

Event Response:

```json
{
    "id": 1,
    "result": {
        "correlationId": "123",
        "parameters": {
            "appId": "SomeAppId",
            "intent": {
                "action": "home",
                "context": {
                    "source": "voice"
                }
            }
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 2,
    "method": "lifecycle.launchResponse",
    "params": {
        "correlationId": "123",
        "result": {
            "success": true
        }
    }
}
```

Response:

```json
{
    "id": 2,
    "result": true
}
```




</details>

### StateLifecycleProvider
The provider interface for the `xrn:firebolt:capability:lifecycle:state` capability.

```typescript
interface StateLifecycleProvider {
	ready(parameters?: LifecycleReadyParameters, session?: ProviderSession): Promise<void>
	close(parameters?: LifecycleCloseParameters, session?: ProviderSession): Promise<void>
	finished(parameters?: LifecycleFinishedParameters, session?: ProviderSession): Promise<void>
}

```

Usage:

```typescript
Lifecycle.provide('xrn:firebolt:capability:lifecycle:state', provider: StateLifecycleProvider | object)
```

### ready

Tells the provider that an app has said they are ready



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`LifecycleReadyParameters`](#lifecyclereadyparameters) | false |   |
| `session` | `ProviderSession` | false |   |


Promise resolution:

```javascript
void
```

**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.ready",
  "params": {
    "parameters": {
      "appId": "SomeAppId"
    },
    "session": {
      "correlationId": "123"
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

### close

Tells the provider that an app has requested closing itself



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`LifecycleCloseParameters`](#lifecyclecloseparameters) | false |   |
| `session` | `ProviderSession` | false |   |


Promise resolution:

```javascript
void
```

**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.close",
  "params": {
    "parameters": {
      "appId": "SomeAppId",
      "reason": "userExit"
    },
    "session": {
      "correlationId": "123"
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

### finished

Tells the provider that an app has said they are finished cleaning up while unloading



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`LifecycleFinishedParameters`](#lifecyclefinishedparameters) | false |   |
| `session` | `ProviderSession` | false |   |


Promise resolution:

```javascript
void
```

**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.finished",
  "params": {
    "parameters": {
      "appId": "SomeAppId"
    },
    "session": {
      "correlationId": "123"
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



#### Examples

**Register your app to provide the `xrn:firebolt:capability:lifecycle:state` capability.**

```javascript
import { Lifecycle } from '@firebolt-js/manage-sdk'

class MyStateLifecycleProvider {

    async ready(parameters, session) {
        return await Promise.resolve(null)
    }

    async close(parameters, session) {
        return await Promise.resolve(null)
    }

    async finished(parameters, session) {
        return await Promise.resolve(null)
    }

}

Lifecycle.provide('xrn:firebolt:capability:lifecycle:state', new MyStateLifecycleProvider())
```

<details>
    <summary>JSON-RPC</summary>

**Register to recieve each provider API**

Request:

```json

{
    "id": 1,
    "method": "lifecycle.onRequestReady",
    "params": {
        "listen": true
    }
}

{
    "id": 2,
    "method": "lifecycle.onRequestClose",
    "params": {
        "listen": true
    }
}

{
    "id": 3,
    "method": "lifecycle.onRequestFinished",
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
        "event": "Lifecycle.onRequestReady"
    }            
 
}

{
    "id": 2,
    "result": {
        "listening": true,
        "event": "Lifecycle.onRequestClose"
    }            
 
}

{
    "id": 3,
    "result": {
        "listening": true,
        "event": "Lifecycle.onRequestFinished"
    }            
 
}

```



**Asynchronous event to initiate ready()**

Event Response:

```json
{
    "id": 1,
    "result": {
        "correlationId": "123",
        "parameters": {
            "appId": "SomeAppId"
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 4,
    "method": "lifecycle.readyResponse",
    "params": {
        "correlationId": "123",
        "result": null
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



**Asynchronous event to initiate close()**

Event Response:

```json
{
    "id": 2,
    "result": {
        "correlationId": "123",
        "parameters": {
            "appId": "SomeAppId",
            "reason": "userExit"
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 5,
    "method": "lifecycle.closeResponse",
    "params": {
        "correlationId": "123",
        "result": null
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



**Asynchronous event to initiate finished()**

Event Response:

```json
{
    "id": 3,
    "result": {
        "correlationId": "123",
        "parameters": {
            "appId": "SomeAppId"
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 6,
    "method": "lifecycle.finishedResponse",
    "params": {
        "correlationId": "123",
        "result": null
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

### NavigationIntent


A Firebolt compliant representation of a user intention to navigate to a specific place in an app.

```typescript
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
```



---

### ProgramType


In the case of a program `entityType`, specifies the program type.

```typescript
type ProgramType = 'movie' | 'episode' | 'season' | 'series' | 'other' | 'preview' | 'extra' | 'concert' | 'sportingEvent' | 'advertisement' | 'musicVideo' | 'minisode'
```



---

### HomeIntent


A Firebolt compliant representation of a user intention to navigate an app to it's home screen, and bring that app to the foreground if needed.

```typescript
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### LaunchIntent


A Firebolt compliant representation of a user intention to launch an app.

```typescript
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### EntityIntent


A Firebolt compliant representation of a user intention to navigate an app to a specific entity page, and bring that app to the foreground if needed.

```typescript
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
```



---

### PlaybackIntent


A Firebolt compliant representation of a user intention to navigate an app to a the video player for a specific, playable entity, and bring that app to the foreground if needed.

```typescript
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
```



---

### SearchIntent


A Firebolt compliant representation of a user intention to navigate an app to it's search UI with a search term populated, and bring that app to the foreground if needed.

```typescript
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
```



---

### SectionIntent


A Firebolt compliant representation of a user intention to navigate an app to a section not covered by `home`, `entity`, `player`, or `search`, and bring that app to the foreground if needed.

```typescript
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
```



---

### TuneIntent


A Firebolt compliant representation of a user intention to 'tune' to a traditional over-the-air broadcast, or an OTT Stream from an OTT or vMVPD App.

```typescript
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                                           // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean                            // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                                              // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
```



---

### Intent


A Firebolt compliant representation of a user intention.

```typescript
type Intent = {
  action: string
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
```



---

### IntentProperties


```typescript
type IntentProperties = {
  action: any
  data: any
  context: any
}
```



---

### MovieEntity


```typescript
type MovieEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVEpisodeEntity


```typescript
type TVEpisodeEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVSeriesEntity


```typescript
type TVSeriesEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### TVSeasonEntity


A Firebolt compliant representation of a TV Season entity.

```typescript
type TVSeasonEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  assetId?: string
  appContentData?: string
}
```



---

### AdditionalEntity


```typescript
type AdditionalEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### UntypedEntity


```typescript
type UntypedEntity = {
  entityId: string
  assetId?: string
  appContentData?: string
}
```



---

### ChannelEntity


```typescript
type ChannelEntity = {
  entityType: "channel"
  channelType: 'streaming' | 'overTheAir'
  entityId: string                         // ID of the channel, in the target App's scope.
  appContentData?: string
}
```



---

### ProgramEntity


```typescript
type ProgramEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
}
```



---

### Identifier


```typescript
type Identifier = string
```



---

### LifecycleReadyParameters


```typescript
type LifecycleReadyParameters = {
  appId: string                    // The application ID
}
```



---

### LifecycleLaunchParameters


```typescript
type LifecycleLaunchParameters = {
  appId: string                     // The application ID
  intent?: NavigationIntent         // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
}
```



---

### LifecycleLaunchResponse


```typescript
type LifecycleLaunchResponse = {
  success: boolean                // Whether the launch succeeded
}
```



---

### LifecycleCloseParameters


```typescript
type LifecycleCloseParameters = {
  appId: string                    // The application ID
  reason: CloseReason              // The application close reason
}
```



---

### LifecycleFinishedParameters


```typescript
type LifecycleFinishedParameters = {
  appId: string                       // The application ID
}
```



---

### LifecycleReadyRequest


```typescript
type LifecycleReadyRequest = {
  parameters: LifecycleReadyParameters
}
```



---

### LifecycleLaunchRequest


```typescript
type LifecycleLaunchRequest = {
  parameters: LifecycleLaunchParameters
}
```



---

### LifecycleCloseRequest


```typescript
type LifecycleCloseRequest = {
  parameters: LifecycleCloseParameters
}
```



---

### LifecycleFinishedRequest


```typescript
type LifecycleFinishedRequest = {
  parameters: LifecycleFinishedParameters
}
```



---

### AppSession


```typescript
type AppSession = {
  app: {
    id: string                          // The identifier for the app
    url?: string                        // The url that the app will be launched with
    title?: string                      // The display title of the app
    catalog?: string                    // The catalog id that this app's content metadata comes from
  }
  runtime?: {
    id?: string                         // The identifier for the runtime
    transport?: 'bridge' | 'websocket'  // The type of transport the application container will use to communicate to Firebolt
  }
  launch?: {
    intent?: NavigationIntent           // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
    secondScreen?: SecondScreenEvent    // An a message notification from a second screen device
  }
}
```



---

### CloseReason


The application close reason

```typescript
type CloseReason = 'remoteButton' | 'userExit' | 'done' | 'error'
```



---

### LifecycleState


The application lifecycle state

```typescript
type LifecycleState = 'initializing' | 'inactive' | 'foreground' | 'background' | 'unloading' | 'suspended'
```



---

### SecondScreenEvent


An a message notification from a second screen device

```typescript
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}
```



---


