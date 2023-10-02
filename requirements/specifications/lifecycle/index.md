# App Lifecycle Management

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Andrew Bennet            | Sky            |
| Cody Bonney   | Charter |
| Bart Catrysse            | Liberty           |
| Tim Dibben            | Sky            |
| Jeremy LaCivita            | Comcast            |
| Ramprasad Lakshminarayana | Sky |
| Kevin Pearson            | Comcast            |
| Peter Yu            | Comcast           |


## 1. Overview

This document describes the requirements that Firebolt platforms must
fulfill when managing App Lifecycles. *App Lifecycle* refers to the
lifecycle of an individual app from the time it is launched/loaded to
the time it is unloaded and all runtime resources are discarded.

*Loading* an app refers to fetching the initial resources, e.g. the
app-manifest and index.html, and loading them into a container capable
of running the app, e.g. a web browser.

*Launching* an app refers to the process of getting an app into a state
where it is presented as a primary part of the user experience (e.g.
visible, audible, or responding to input). This may include *loading*
the app first, if needed. For details on presentation, see [App
Presentation](./presentation.md).

*Closing* an app refers to the process of getting an app out of a state
where it is the primary user experience (e.g not visible, not audible,
and not responding to input). This **does not** involve *unloading* the
app.

*Unloading* an app refers to the process of notifying an app to do any
needed clean up, and then *terminating* it.

*Terminating* an app refers to shutting down the app's container and
reclaiming any memory, CPU, etc. that it was consuming.

*Suspending* an app refers to copying the app's memory stack out of
RAM and terminated it's CPU process so that it stops consuming
resources, but may be revived later.

*Resuming* an app refers to copying a suspended app back into the
memory space of a compatible process so that it resumes where it left
off.

- [1. Overview](#1-overview)
- [2. Lifecycle States](#2-lifecycle-states)
  - [2.1. Started](#21-started)
  - [2.2. Foreground](#22-foreground)
  - [2.3. Background](#23-background)
  - [2.4. Suspended](#24-suspended)
- [3. Lifecycle State Transitions](#3-lifecycle-state-transitions)
  - [3.1. Loading an app](#31-loading-an-app)
  - [3.2. Initializing an app](#32-initializing-an-app)
  - [3.3. Activating an app](#33-activating-an-app)
  - [3.4. Deactivating an app](#34-deactivating-an-app)
  - [3.5. Backgrounding an app](#35-backgrounding-an-app)
  - [3.6. Suspending an app](#36-suspending-an-app)
  - [3.7. Resuming an app](#37-resuming-an-app)
  - [3.8. Unloading an app](#38-unloading-an-app)
  - [3.9. Terminating an app](#39-terminating-an-app)
- [4. Core SDK APIs](#4-core-sdk-apis)
  - [4.1. LifecycleManagement Interface](#41-lifecyclemanagement-interface)
  - [4.2. Ready](#42-ready)
  - [4.4. Close](#44-close)
  - [4.5. Background](#45-background)
  - [4.6. Finished](#46-finished)
  - [4.7. State](#47-state)
  - [4.8. ResourceDeallocator Interface](#48-resourcedeallocator-interface)
- [5. Manage SDK APIs](#5-manage-sdk-apis)
  - [5.1. Terminate](#51-terminate)
  - [5.2. Suspend](#52-suspend)
  - [5.3. Unsuspend](#53-unsuspend)
- [6. Lifecycle Configuration](#6-lifecycle-configuration)


## 2. Lifecycle States
Firebolt platforms **MUST** support running one or more apps
concurrently. The platform **MUST** manage transition of apps from state
to state.

A Firebolt app, once running, **MUST** be in one of several states and
**MUST NOT** be in more than one state at a time.

As an app changes states, events are dispatched notifying the app of
it's current and previous state. These events are for reacting to each state.

For information on *influencing* state transitions, see [State Transitions](#3-lifecycle-state-transitions).

![Lifecycle States](../../images/specifications/lifecycle/lifecycle-states.png)


|            | CPU | RAM | GFX | A/V | RCU | Description                                                                    |
|------------|-----|-----|-----|-----|-----|--------------------------------------------------------------------------------|
| Started    | ✔   | ✔   |     |     |     | App is loaded, initialized, and ready for use but consuming limited resources. |
| Foreground | ✔   | ✔   | ✔   | ✔   | ✔   | App has full access to CPU, RAM, and RCU input focus. |
| Background | ✔   | ✔   | ✔   | ✔   |     | App has full access to CPU and RAM, but not RCU input focus. |
| Suspended  |     |     |     |     |     | App state is persisted to storage and removed from CPU & RAM. |

### 2.1. Started

This state allows an app to be running, but not in one of the two active
states, i.e. `FOREGROUND` and `BACKGROUND`. Started apps can execute code,
but are not [Presented](./presentation.md) to the user, do not receive
any input from RCUs, and cannot use the video decoder or graphics plan.

Apps in this state **MUST NOT** be visible.

Apps in this state **MUST NOT** receive RCU key presses.

Apps in this state **MUST NOT** have access to the audio-video decoder.

Apps in this state **MUST NOT** have access to the graphics plane.

Apps in this state **SHOULD** use a low profile footprint for memory and other resources
in this state.

Apps in this state **SHOULD** use less than XXX megabytes of RAM.

**TODO**: do we want tiers of apps? per-app config?

When an app transitions to this state, the platform **MUST** dispatch
the `Lifecycle.onStarted` notification with the current state and
previous states.

Apps in this state **MUST NOT** use the media pipeline and the platform
**MUST** tear down any Media Pipeline sessions associated with this app.

### 2.2. Foreground

This state allows an app to be presented as the primary experience to
the user.

The platform **MUST** ensure that only one or zero apps is ever in this
state at one time.

Apps in this state **MUST** be visible.

Apps in this state **MUST** receive RCU key presses that they have
permissions for.

Apps in this state **MUST** have access to the audio-video decoder.

Apps in this state **MUST** have access to the graphics plane.

Apps in this state **SHOULD NOT** have performance negatively impacted
by other processes on the device.

Apps in this state **SHOULD** use less than XXX megabytes of RAM.

**TODO**: do we want tiers of apps? per-app config?

When an app transitions to this state, the platform **MUST** dispatch
the `Lifecycle.onForeground` notification with the current state and
previous states.

### 2.3. Background

This state allows an app to be present as the secondary experience to
the user, e.g. when a system settings UI is overlayed on top of the app.

Apps in this state **MUST** either be partially visible **OR** have
access to an audio decoder, e.g. an app playing music in the background.

Apps in this state **SHOULD NOT** receive most RCU key presses, although
platforms **MAY** forward certain keys to the app, e.g. play/pause keys.

Apps in this state **MUST** have access to the audio-video decoder.

Apps in this state **MUST** have access to the graphics plane.

Apps in this state **SHOULD NOT** have performance negatively impacted
by other processes on the device.

Apps in this state **SHOULD** use less than XXX megabytes of RAM.

**TODO**: do we want tiers of apps? per-app config?

When an app transitions to this state, the platform **MUST** dispatch
the `Lifecycle.onBackground` notification with the current state and
previous states.

### 2.4. Suspended

This state allows an app to be copied from memory to local storage and
then terminated to save resources. Subsequently, the app may be copied
back into memory, and resume in the same state.

Apps **MUST** be able to subscribe to the Lifecycle.onSuspended
notification without errors regardless of whether the platform supports
suspending apps. For platforms that do not support it the notification
will just never fire.

*If* a platform does not support suspending apps, then the following
requirements **MUST NOT** be fulfilled, even partially. A platform
**MUST NOT** use the APIs documented here to implement an alternate,
non-compliant version of the app suspending feature.

*If* a platform supports suspending apps, then the following
requirements **MUST** be fulfilled.

Apps **MUST** only enter this state from the started state.

*Immediately before* an app transitions to this state, the platform
**MUST** dispatch the Lifecycle.onSuspended notification with the
current state and previous states.

The platform **MUST** save the app's memory space at this point, so that
it may be unsuspended later. If storing the app\'s memory space fails
for any reason, then the app **MUST** be treated as though it were
unloaded.

Finally, the app and its container **MUST** be removed from memory and
have other resources released as well.

Apps may optionally implement the Lifecycle.ResourceDeallocator API for
more control over app suspension.

## 3. Lifecycle State Transitions
There are several state transitions where the app and the platform need
to interact to ensure the transition goes smoothly.

By providing an implementation of the
`xrn:firebolt:capability:lifecycle:management` interface, an app can
influence how resources are managed during these state transitions. See [LifecycleManagement Interface](#41-lifecyclemanagement-interface) for more info.

![Lifecycle States](../../images/specifications/lifecycle/lifecycle-transitions.png)

### 3.1. Loading an app

Loading an app fetches the initial resources, e.g. the app-manifest and
index.html, and loads them into a container capable of running the app,
e.g. a web browser.

The platform may load apps for any number of reasons that are out of
scope for this document.

Loading an app requires the platform to know the URL to the app's
Firebolt manifest.

To load an app, platforms **MUST** use the following process.

First, fetch the app manifest and validate its signature (See 'App
Manifests' for more info).

The app **MUST** be terminated if the signature is not valid and the
manifest's releaseStatus is not developer.

Next, if the app is an HTML/JavaScript app, then load the app's initial
URL (from the app manifest) into the browser.

**TODO**: add more details here, e.g. contains, graphics, media pipeline, ram

### 3.2. Initializing an app
Once an app is loaded it **MUST** be initialized immediately.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability, then the platform **MUST** call the app's implementation of
`LifecycleManagement.initialize()`:

> The platform **MUST** dispatch the `Lifecycle.onRequestInitialize`
> notification to the app, and wait for `appReadyTimeout` milliseconds
> for either a `Lifecycle.ready` or `Lifecycle.initializeError` call in
> response.
>
> **NOTE**: this requires a minor change to our code-generate to customize
> a provider result method name.
>
> Once the platform receives the `initializeResult` call, then the app
> is considered "ready" to be activated and presented to the user.
>
> If the app times out or makes an `initializeError` call, then the app
> **MUST** be terminated.

If an app does not provide the capability, then the app is doing a
synchronous initialization and needs to let the platform know when it
is complete:

> The platform **MUST** wait `appReadyTimeout` milliseconds for the app
> to call `Lifecycle.ready()`, at which point the app is considered
> "ready" to be activated and presented to the user.
>
> If the app times out, then the app **MUST** be terminated.

Apps **SHOULD** set up any Firebolt event listeners during
initialization, since the platform will wait until the app is ready
before dispatching many critical events such as Lifecycle and
Presentation events.

Apps **SHOULD** acquire any important authentication needed for the
app to function during initialization.

Apps **MAY** load a limited set of global display resources, e.g. a
global style sheet or a logo used throughout the experience, during
initialization.

**TODO**: discuss this ^^

Once an app is "ready" it **MUST** be transitioned to the `STARTED`
state within 500 milliseconds.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability and calls `Lifecycle.ready` when the platform is not waiting
for the app to finish initializing, then the platform **MUST** return 
and error, and terminate the app.

### 3.3. Activating an app

Launching an app transitions it to one of the *active* states
(foreground or background) so that it becomes part of the user's
experience.

The platform may launch apps for any number of reasons that are out of
scope for this document.

To launch an app, platforms **MUST** use the following process.

If the app is already in the `FOREGROUND` state, then it is already
launched and there is no need to do anything else. The platform **MUST
NOT** dispatch any *additional* lifecycle notifications when attempting
to launch an app that is already in the foreground state and the
remainder of this section does not apply.

If the app is not loaded, then the platform **MUST** [load](#31-loading-an-app) it first.

If the app is not initialized, the platform **MUST** [initialize](#32-initializing-an-app) it first.

If the app is suspended, then it **MUST** be [resumed](#37-resuming-an-app) first.

At this point, the app **MUST** be in either the `STARTED` or `BACKGROUND`
state.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability, then the platform **MUST** call the app's implementation of
`LifecycleManagement.activate()`:

> The platform **MUST** dispatch the `Lifecycle.onRequestActivate`
> notification to the app, and wait for `appActivateTimeout` milliseconds
> for either a `Lifecycle.activateResult` or `Lifecycle.activateError`
> call in response.
>
> The `onRequestActivate` call **MUST** include a `NavigationIntent`.
>
> Once the platform receives the `activateResult` call, then the app
> may be moved to the target state, `FOREGROUND` or `BACKGROUND`
> and presented to the user.
>
> If the app times out or makes an `activateError` call, then the app
> **MUST** be terminated.

If an app does not provide the capability, then:

> The platform **MUST** move the app to the target state, `FOREGROUND`
> or `BACKGROUND` and presented to the user.
>
> Then, the platform **MUST** dispatch a `Discovery.onNavigateTo`
> notification to the platform with a `NavigationIntent`.

### 3.4. Deactivating an app

Closing an app transitions it to the `STARTED` state, so that it is no
longer part of the user's experience.

The platform may close apps for any number of reasons that are out of
scope for this document.

Apps **MAY** request to be closed, via the `Lifecycle.close()` API method.

To close an app, platforms **MUST** use the following process.

If an app is already in the `STARTED` state, then it is already closed
and there is no need to do anything else. The platform **MUST NOT**
dispatch any *additional* lifecycle notifications when attempting to
close an app that is already in the `STARTED` state and the remainder of
this section does not apply.

If an app is already performing a `deactivate()` transition, the platform
**MUST** ignore the new attempt to close the app, allow the pending
closure to complete, and the remainder of this section does not apply.

If an app is already performing an `activate()` transition, the platform
**MUST** wait for the activate call to succeed or fail and then skip the
remaining [activation steps](#33-activating-an-app).

If an app is currently [initializing](#32-initializing-an-app), the
platform **MUST** wait for initialization to succeed or fail.

If an app is currently in the `SUSPENDED` state, is [unloading](#38-unloading-an-app),
or is performing a `suspend()` or `resume()` transition, then the app 
cannot be closed and the platform **MUST NOT** close it, and the
remainder of this section does not apply.

At this point, the app **MUST** be in one of the active states.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability, then the platform **MUST** call the app's implementation of
`LifecycleManagement.deactivate()`:

> The platform **MUST** dispatch the `Lifecycle.onRequestDeactivate`
> notification to the app, and wait for `appDeactivateTimeout` milliseconds
> for either a `Lifecycle.deactivateResult` or `Lifecycle.deactivateError`
> call in response.
>
> Once the platform receives the `deactivateResult` call, then the app
> may be moved to the `STARTED` state.
>
> If the app times out or makes a `deactivateError` call, then the app
> **MUST** be terminated.

If an app does not provide the capability, then it will not provide any
resource management:

> The platform **MUST** move the app to the `STARTED` state.
>
> The platform **SHOULD** prioritize this app for unloading if it is not
> reactivated within `appLegacyUnloadTimeout` milliseconds.

### 3.5. Backgrounding an app

Backgrounding an app transitions it to the `BACKGROUND` state, so that it
is no longer the primary user experience.

The platform may background apps for any number of reasons that are out
of scope for this document.

Apps that are in the `FOREGROUND` state **MAY** request to be
backgrounded, via the `Lifecycle.background()` API method. See the
Background API below.

To background an app, platforms **MUST** use the following process.

If an app is already in the `BACKGROUND` state, then it is already
backgrounded and there is no need to do anything else. The platform
**MUST NOT** dispatch any *additional* lifecycle notifications when
attempting to background an app that is already in the `BACKGROUND` state
and the remainder of this section does not apply.

If an app is already performing a `activate()` transition, the platform
**MUST** ignore the new attempt to activate the app, allow the pending
activation to complete, and the remainder of this section does not apply.

If an app is currently [initializing](#32-initializing-an-app), the
platform **MUST** wait for initialization to succeed or fail.

If an app is currently in the `SUSPENDED` state, is [unloading](#38-unloading-an-app),
or is performing a `suspend()` or `resume()` transition, then the app 
cannot be backgrounded and the platform **MUST NOT** try to, and the
remainder of this section does not apply.

At this point, the app **MUST** be in either the `FOREGROUND` or `STARTED`
state.

Finally, the platform **MUST** transition the app to the background
state (see '[Background](#24-background)' above).

### 3.6. Suspending an app

Suspending an app transitions it to the `SUSPENDED` state, so that it is
no longer using resources on the device.

The platform may suspend apps for any number of reasons that are out of
scope for this document. However, it is the platform's decision to
suspend an app, not the app itself.

To suspend an app, platforms **MUST** use the following process.

If an app is already in the `SUSPENDED` state, then it is already
suspended and there is no need to do anything else. The platform **MUST
NOT** dispatch any *additional* lifecycle notifications when attempting
to suspend an app that is already in the suspended state and the
remainder of this section does not apply.

If the app is not loaded, or is not in the `STARTED` state, then it
cannot be suspended, and the remainder of this section does not need to
happen.

At this point, the app **MUST** be in the `STARTED` state.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability, then the platform **MUST** call the app's implementation of
`LifecycleManagement.suspend()`:

> The platform **MUST** dispatch the `Lifecycle.onRequestSuspend`
> notification to the app, and wait for `appSuspendTimeout` milliseconds
> for either a `Lifecycle.suspendResult` or `Lifecycle.suspendError`
> call in response.
>
> Once the platform receives the `suspendResult` call, then the app
> may be moved to the `SUSPENDED` state.
>
> If the app times out or makes a `suspendError` call, then the app
> **MUST** be [unloaded](#38-unloading-an-app).

If an app does not provide the capability, then it cannot be suspended
and the platform **MUST NOT** attempt to.

### 3.7. Resuming an app

Unsuspending an app loads it's previous state back into memory and
transitions it to the started state, so that it may be launched back
into its original state.

The platform may unsuspend apps for any number of reasons that are out
of scope for this document.

To unsuspend an app, platforms **MUST** use the following process.

If an app is not in the `SUSPENDED` state, then it cannot be unsuspended
and there is no need to do anything else. The platform **MUST NOT**
dispatch any *additional* lifecycle notifications when attempting to
unsuspend an app that is not in the `SUSPENDED` state and the remainder of
this section does not apply.

At this point, the app **MUST** be in the `SUSPENDED` state.

Next, the platform **MUST** load the app's saved memory state back into
an appropriate container. If this fails for any reason then the unsuspend
operation failed and should error out and the app **MUST** be considered
unloaded. Additionally, the app **MUST** be removed from the list of
suspended apps, so that an unsuspend operation is not attempted again.

Suspended apps **MUST** provide the  `xrn:firebolt:capability:lifecycle:management`
capability, so the platform **MUST** call the app's implementation of
`LifecycleManagement.resume()`:

The platform **MUST** dispatch the `Lifecycle.onRequestResume`
notification to the app, and wait for `appResumeTimeout` milliseconds
for either a `Lifecycle.resumeResult` or `Lifecycle.resumeError`
call in response.

Once the platform receives the `resumeResult` call, then the app
may be moved to the `STARTED` state.

If the app times out or makes a `resumeError` call, then the app
**MUST** be terminated.

### 3.8. Unloading an app

Unloading an app transitions it out of memory, so that it is no longer
using resources on the device.

The platform may unload apps for any number of reasons that are out of
scope for this document.

To unload an app, platforms **MUST** use the following process.

If an app is not in the `STARTED` state, then it cannot be unloaded and
there is no need to do anything else. The platform **MUST NOT** dispatch
any *additional* lifecycle notifications when attempting to unload an
app that is not in the `STARTED` state and the remainder of this section
does not need to happen.

At this point, the app **MUST** be in the `STARTED` state.

If an app provides the `xrn:firebolt:capability:lifecycle:management`
capability, then the platform **MUST** call the app's implementation of
`LifecycleManagement.unload()`:

> The platform **MUST** dispatch the `Lifecycle.onRequestUnload`
> notification to the app, and wait for `appUnloadTimeout` milliseconds
> for either a `Lifecycle.finished` or `Lifecycle.unloadError`
> call in response.
>
> Once the platform receives the `finished` call, then the platform
> may proceed with app unloading.
>
> If the app times out or makes an `activateError` call, then the app
> **MUST** be terminated.

If an app does not provide the capability, then:

> The platform **MUST** dispatch the `onUnloading` notification and
> wait `appUnloadTimeout` milliseconds for the app to call `Lifecycle.finished`
>
> When the `finished` call occurs, or the timeout is reached, the platform
> **MUST** unload and terminate the app.

### 3.9. Terminating an app

Terminating an app removes it from memory without dispatching any state
changes.

The platform **SHOULD** terminate apps when one of the transitions outlined
here fails for some reason, or if an app becomes non-responsesive.

Terminating an app results in removing it from memory and all resources
held by the app and it's container being freed up.

Platforms **MAY** terminate an app when needed but **SHOULD NOT** do
this in place of graceful [unloading](#38-unloading-an-app).

## 4. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK.

### 4.1. LifecycleManagement Interface
The `LifeCycleManagement` interface is implemented by Apps to provide resource management.

```typescript
interface LifecycleManagement {
  function create(params: LaunchParameters): Promise<void>;
  function activate(intent: NavigationIntent): Promise<void>;
  function deactivate(): Promise<void>;
  function suspend(): Promise<void>;
  function resume(): Promise<void>;
}
```

Example:

```typescript
import { Lifecycle } from '@firebolt-js/sdk'

class ExampleLifecycleManager implements Lifecycle.LifecycleManagement {
  function create(params: LaunchParameters): Promise<void> {
    const limitTracking:boolean = params.limitAdTracking
  }

  function activate(intent: NavigationIntent): Promise<void> {
    if (intent.action === "playback") {
      console.log("Deep link to playback of " + intent.data.entityId)
    }
  }

  function deactivate(): Promise<void> {
    // free up MSE
    video.src = ""
    video.load()
  }

  function suspend(): Promise<void> {
    // unload all images
    document.querySelectorAll("img").forEach((img:HTMLElement) => {
      img.parentElement.removeChild(img)
    })
  }

  function resume(): Promise<void> {
    // reload images
  }
}
```

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, etc.

### 4.2. Ready

The Lifecycle.ready() API allows an app to notify the platform that it
is initialized and ready to be displayed to the end user. This method
**MUST NOT** be called more than once.

### 4.4. Close

The Lifecycle.close() API allows an app to request that it be closed by
the platform.

This method requires a reason parameter, which tells the platform why
the app is requesting to be closed:

| Reason                    | Description                                                                                                                                                              |
|------------------------------------|------------------------------------|
| CloseReason.REMOTE_BUTTON | The user pressed the back or last button on the RCU and the App has determined it is at the top of it's navigation stack and should go back to the platform home screen. |
| CloseReason.USER_EXIT     | The user selected an exit control exposed by the app's UI.                                                                                                               |
| CloseReason.ERROR         | The app is experiencing unrecoverable issues and needs to be closed and unloaded.                                                                                        |

Platforms generally **SHOULD** respect this call and move the app to the
started state, but there may be edge cases where this is not possible,
e.g. the app is considered to be the default experience for the device,
and closing it would leave no other UX present.

When the request to close is not respected, the Lifecycle.close() method
**MUST** return an error.

Platforms **MAY** prioritize apps to be unloaded based on the reason
provided. For example, apps closed due to the RCU are less likely to be
unloaded since it may be an accidental RCU press, whereas an explicit
user exit is more likely to be intentional.

### 4.5. Background

The Lifecycle.background() API allow an app to request that it be moved
to the background state.

An app **MUST** have the
xrn:firebolt:capability:lifecycle:request-background capability to call
this API, otherwise an error **MUST** be returned.

This method requires a target parameter, which tells the platform which
app should be brought to the foreground:

| Target                       | Description                                                                                                                                              |
|------------------------------------|------------------------------------|
| ForegroundTarget.LAST_APP    | The next app on the stack, i.e. the most recently used app before this one, will be promoted to the foreground when this app is moved to the background. |
| ForegroundTarget.DEFAULT_APP | The platform's default app for this operation will be moved to the foreground when this app is moved to the background.                                  |

The default app **SHOULD** be the main experience that users expect when
they start up their device. Platforms **MAY** use a different default
app within reason.

Platforms generally **SHOULD** respect this call and move the app to the
background state, but there may be edge cases where this is not
possible, e.g. the app is considered to be the default experience for
the device, and hiding it would leave no other UX present.

When the request to background an app is not respected, the
Lifecycle.background() method **MUST** return an error.

### 4.6. Finished

The Lifecycle.finished() API allows an app to notify the platform that
it is done preparing to be unloaded.

This allows the platform to unload the app *before* appFinishedTimeout
milliseconds have passed, so that apps can be unloaded faster.

The platform **MUST** unload an app after appFinishedTimeout
milliseconds even if this method is never called.

This method results in an error if it is called while the app is in any
other state than unloading, or called more than once while in that
state.

### 4.7. State

The Lifecycle.state() method provides convenient access to the current
state, and is implemented by the Core SDK listening to all state
notifications. This method **MUST NOT** be asynchronous.

### 4.8. ResourceDeallocator Interface

An app may provide a ResourceDeallocator implementation in order to
support more efficient resource usage in the various lifecycle states.

| Method     | Return | Description                                                                                                                                                                              |
|----------|--------|------------------------------------------------------|
| started() | void   | Called when the platform wants to transition the app to the started state. The transition will not occur until the method returns, errors, or times out (see appStartedTimeout, below) |
| supend()   | void   | Called when the platform wants to transition the app to the suspended state. The transition will not occur until the method returns, errors, or times out (see appSuspendTimeout, below) |

Note that these methods are implemented by the App, not the platform.
The platform requests them via onRequest\<method\> events.

## 5. Manage SDK APIs

The following APIs are exposed by the Firebolt Manage SDK.

See the Firebolt Manage SDK documentation for details around syntax,
etc.

### 5.1. Terminate

The terminate() API requests that the platform terminate a specific app.

This method requires an appId parameter, which tells the platform which
app to terminate.

### 5.2. Suspend

The suspend() API requests that the platform suspends a specific app.

This method requires an appId parameter, which tells the platform which
app to suspend.

### 5.3. Unsuspend

The unsuspend() API requests that the platform unsuspends a specific
app.

This method requires an appId parameter, which tells the platform which
app to unsuspend.

## 6. Lifecycle Configuration

TODO: do we want these to be per spec, per distributor, or per app?

In order to enable Firebolt Certification of a device's Lifecycle
Management features, the device **MUST** support the following
configuration options, so that the Firebolt Certification Test Suite
knows which optional conditions to test for, and for how long to wait
for state transitions.

The LifecyclePolicy fields are:

| Field              | Type   | Required | Description                                                                                                                                                                                      |
|-------------------|-------|----------|-------------------------------------|
| appReadyTimeout    | bigint | Yes      | Number of milliseconds the platform should wait before terminating a loaded app that did not call ready().                                                                                       |
| appFinishedTimeout | bigint | Yes      | Number of milliseconds the platform should wait after dispatching the onUnloading notification before finally unloading an app that did not call finished().                                     |
| appSuspendTimeout  | bigint | Yes      | Number of milliseconds the platform should wait after dispatching the onRequestSuspend notification before finally suspending (or terminating) an app that did not call onSuspendResponse().     |
| appStartedTimeout | bigint | Yes      | Number of milliseconds the platform should wait after dispatching the onRequestStarted notification before finally inactivating (or terminating) an app that did not call onStartedResponse(). |
