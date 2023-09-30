# App Presentation
need to write this up...

## 1. States

- fullscreen
- obscured
- offscreen
- scaled
- thumbnail
- loading

## 2. Off-screen Video
If an app has the `xrn:firebolt:capability:presentation:offscreen-audio` or `-video` capability, then it can keep playing video/audio.

Need a transition interface, e.g. `PresentationManager.hide()` to allow app to tear down video.

## 3. Platform-provided Loading Screen
Most apps will leverage a platform-provided loading screen.

If an app provides the `xrn:firebolt:capability:presentation:loading-screen`
capability, then the platform **MAY** use the app-provided loading screen, in
which case, the rest of the section does not apply.

The loading screen **SHOULD** include a loading image referenced in the app's
manifest and cached on the device.

The loading screen **MUST** be displayed when the user attempts to launch the
app.

The loading screen **MUST** stay displayed until the app becomes active, or
launching is cancelled.

The presentation state of the app **MUST** be `LOADING` for the entire time
the loading screen is displayed.

See [Lifecycle](./index.md) for more info on launching.

## 4. App-provided Loading Screen
If an app provides the `xrn:firebolt:capability:presentation:loading-screen`
capability, then the platform **MAY** invoke this capability in some situations.

In order for an app and use an app-provided loading screen, the app **MUST**
provide the `xrn:firebolt:capability:lifecycle:management` capability. If the app
does not provide this capability, then app-provided loading screens **MUST NOT**
but invoked for the app. 

When cold launching apps with this capability:

> The platform **MUST** display the platform-provided loading screen when
> the app starts loading.
> 
> Then the app's loading screen **MUST** be requested immediately after the app
> is loaded. See [Displaying the app-provided loading screen](#41-displaying-the-app-provided-loading-screen),
> below.

When hot launching apps with this capability:

> The platform **MUST** display the platform-provided loading screen when
> the app launch is requested.
> 
> Then the app's loading screen **MUST** be requested immediately. See 
> [Displaying the app-provided loading screen](#41-displaying-the-app-provided-loading-screen),
> below.

See [Lifecycle](./index.md) for more info on loading and activating apps.

### 4.1. Displaying the app provided loading screen.
To display the loading screen:

The platform **MUST** dispatch the `Presentation.onRequestLoadingScreen`
notification to the app, and wait for `loadingScreenTimeout` milliseconds
for either a `Presentation.loadingScreenResult` or
`Lifecycle.loadingScreenError` call in response.

**NOTE**: this requires a minor change to our code-generate to customize
a provider method name, e.g. x-method-name: "display".

Once the platform receives the `loadingScreenResult` call, then the app
**MUST** be made visible in whatever presentation mode the app would
have been launched into (typically `FULLSCREEN`).
 
If the app times out or makes an `loadingScreenError` call, then the app
will not be made visible until activation is complete.
