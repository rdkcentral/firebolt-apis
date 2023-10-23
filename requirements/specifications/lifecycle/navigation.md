

## 5. Activity Navigation
Typically navigation is handled either when the app is activated, via the  
`intent` parameter of the `activate` method, or by internal input within the  
app.  

There are other times when the platform needs to inform an app of a user's  
intent to navigate when the app is already `ACTIVE`, e.g. when a voice  
command is executed or a soft remote sends a message while the app is in  
focus.  

In these cases, the platform **MUST** call the `Activity.navigate` method of  
the App, and pass the `intent`.  

Within the `navigate()` method, the app **MUST** inspect the `intent` parameter 
  and prepare to fulfill a specific [Navigation  
Intent](../intents/navigation.md) for the app, which may include:  

 - Loading any metadata needed to display the user's intended content.
 - Performing any entitlement checks to decide whether to display a player or a purchase flow
 - Any other steps necesary to present content to the user quickly

### Option 1
During the `navigate()` transition, the app **MUST** inspect the `intent`  
parameter and prepare to fulfill a specific [Navigation  
Intent](../intents/navigation.md) which may include:  

 - Loading any metadata needed to display the user's intended content.
 - Performing any entitlement checks to decide whether to display a player or a purchase flow
 - Any other steps necesary to present content to the user quickly

The app **MAY** display a loading screen..  

An app **MUST NOT** receive a navigate call while it is already executing a  
navigate call.  

### Option 2
An app **MAY** receive a navigate call while it is already executing a navigate 
 call.  

> The platform **MUST** dispatch the `Lifecycle.onRequestNavigate` notification 
> to the app, and wait for `appNavigateTimeout` milliseconds for either a 
> `Lifecycle.navigateResult` or `Lifecycle.navigateError` call in response. 
> 
> Once the platform receives the `navigateResult` call, then the platform may 
> proceed with app destroying. 
> 
> If the app times out or makes an `navigateError` call, then the app **MAY** 
> be terminated. 

An app **MUST** acknowledge receipt of each navigate call.  

An app **MUST** decide how to prioritize multiple navigate calls.  

### Option 3
```typescript
Discovery.listen('navigateTo', (intent) => {
  //
})
```  