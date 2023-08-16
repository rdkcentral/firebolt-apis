# User Interest Intents

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Eugene Chung            | Comcast            |
| Tim Dibben            | Sky            |
| Mike Horwitz            | Comcast            |
| Jeremy LaCivita            | Comcast            |

## 1. Overview

In additional to traditional discovery APIs such as Watch History and
Watch Next, Firebolt provides a more abstract API that facilitates
impromptu content discovery connections between first-party Aggregated
Experiences and third-party Apps.

The User Interest Capability enables Apps to provide meta-data on
content that the user has expressed an interest in to Aggregated
Experience Apps that have been given access to use this Capability.

This allows for open ended design of Aggregated Experience App features
that present App-specific content to re-engage the user with the content
inside the originating App.

While the functionality and UX is left to the Aggregated Experience App,
typically designed by each Firebolt Distributor, the Firebolt API
enables events to register user interest and pass entity meta-data:

![Diagram Description automatically
generated](../../../requirements/images/specifications/intents/user-interest/media/image1.png)

Which generally enables Aggregated Experiences to present that entity
meta-data in some way that leads to re-launching the original App at a
later point, using a `navigateTo` notification:

![Diagram Description automatically
generated](../../../requirements/images/specifications/intents/user-interest/media/image2.png)

This is just one example of what an Aggregated Experience App might do
with the User Interest API.

Note that this API **should not** be used to implement Watch History or
Watch Next features. These concepts are much more fundamental to
Firebolt and have explicit APIs so that Firebolt Distributors can keep
track of which apps are using them separately.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. User Interest from an in-app UX](#3-user-interest-from-an-in-app-ux)
- [4. User Interest from a platform UX](#4-user-interest-from-a-platform-ux)
- [5. User Interest Bulk Updates](#5-user-interest-bulk-updates)
- [6. Core SDK APIs](#6-core-sdk-apis)
- [7. Discovery.interested](#7-discoveryinterested)
- [8. InterestIntent](#8-interestintent)
- [9. Manage SDK APIs](#9-manage-sdk-apis)
- [10. Content.onInterestedIn](#10-contentoninterestedin)
- [11. InterestedInIntent](#11-interestedinintent)


## 3. User Interest from an in-app UX

Some Apps will have a built-in user interface for users to express
interest in content from the App. This could be a \"Favorite\" button,
an in-app \"My List\" button, etc.

If the App wants to leverage any additional exposure from the device\'s
Aggregated Experience, it can wire up this UI to the Firebolt User
Interest API, in addition to any in-app features that it\'s already
invoking.

By calling the `Discovery.interested` method with the relevant entity
meta-data, the device\'s Aggregated Experience will be notified of the
user\'s interest in that entity:

```typescript
Discovery.interested(type:InterestType, entity:EntityInfo)
```

The type parameter denotes what sort of interest:

-   `interest`
-   `disinterest`

When this method is called with a valid `EntityInfo`, the platform
**MUST** dispatch a `Content.onInterestedIn` notification to all Apps
that have registered for it (typically Aggregated Experience Apps) with
information about the app, interest type, and the entity.

If the result is `null` or is not a valid entity, i.e. does not match
the [EntityInfo](../entities/) schema, then no `Content.onInterestedIn`
notification will be dispatched.

The `Discovery.interested` method **MUST NOT** be used in place of more
specific Discovery methods, e.g. `Discovery.watchNext` or
`Discovery.watched`. These methods facilitate specific UX flows that may
have separate legal opt-outs for each user.

The `Discovery.interested` method **MUST NOT** be called unless the user
is activating a UI element in the app, or in a second screen experience
that is communicating with the app, that implies interest of some kind.

**TODO**: This seems like a contractual obligation, as testing this is
non-trivial / impossible. Are we keeping track of contractual
requirements anywhere?

## 4. User Interest from a platform UX

Firebolt platforms may provide a platform UX, e.g. voice or and RCU, to
express user interest in content from an active App. To facilitate this
Apps will need to be told about the user\'s expressed interest in their
content.

In this case, two different intents are required to complete the
interaction. The `InterestIntent` is leveraged by an Aggregated
Experience to let the current foreground app know that the user is
interested in something currently on the screen or selected. Once the
foreground app receives this intent, the flow is much like the previous
use case.

First, the Aggregated Experience (or some app with the correct
capability) detects that the user is interested in something. In this
picture the interest is triggered by an RCU button, but how this occurs
is outside the scope of this document. When this happens, an
`InterestIntent` is generated and sent to the foreground app.

![](../../../requirements/images/specifications/intents/user-interest/media/image3.png)

Next, the foreground app receives and responds to the `InterestIntent`
by providing the EntityInfo, which triggers an `InterestedInIntent`:

![Diagram Description automatically
generated](../../../requirements/images/specifications/intents/user-interest/media/image4.png)

A user\'s intention to express interest in something is handled by the
`InterestIntent`. This intent happens *before* the platform knows which
content is displayed and/or selected by the foreground or background
apps. The `InterestIntent` may originate from a cloud system, e.g.
Voice, or from the RCU, or elsewhere. Origination of this intent is out
of scope for this document. This intent includes the type of interest,
e.g. interest or disinterest.

To fire an `InterestIntent` to the current App, another app, typically
the Aggregated Experience, will call the `Content.interest()` method
of the Discovery SDK. This generates a new intent.

When this intent occurs, any App in the foreground or background
Lifecycle state, that has registered a callback via the
`Discovery.interested` API **MUST** have that callback invoked with the
`InterestIntent` as the only parameter.

Once an App\'s callback is invoked, that app will have `interestTimeout`
milliseconds to return a value or throw an error. Values returned after
that time **MUST** be ignored. The timeout value is stored in the
device\'s configuration manifest.

To be notified when a user expresses interest in the currently displayed
content, an App **MUST** call `Discovery.interested` with a callback
method, to register as a provider of this capability:

```typescript
Discovery.interested((intent:InterestIntent) => EntityInfo)
```

This API uses Firebolt\'s `polymorphic-pull` OpenRPC tag, to specify
that it is a push/pull API.

If there is a valid entity to return, then the method registered by the
App **MUST** return the currently displayed entity meta-data.

If there is no valid entity to return, then the method **MUST** throw an
exception.

If more than one App returns a valid `EntityInfo`, the value from the
App in the foreground **MUST** be used, and the others will be ignored.
If only one is returned, then it may come from the foreground or
background app. See
[Lifecycle](../lifecycle/) for more info on Lifecycle states.

Once a single `EntityInfo` is selected the platform **MUST** dispatch a
`Content.onInterestedIn` notification to all Apps that have registered
for it (typically Aggregated Experience Apps) with metadata about the
app and entity as its data.

The `Content.onInterestedIn` event has the `InterestedInIntent` as its
data.

The platform **MUST NOT** dispatch more than one `onInterestedIn`
notification, even if more than one App responded to the pull request.

An Aggregated Experience can register for the `Content.onInterestedIn`
notification, and it will receive notifications when an `EntityInfo` is
returned from the active App after a `Discovery.interested` call is
fulfilled.

## 5. User Interest Bulk Updates

Sending bulk interest updates, e.g. Entities the user expressed interest
in on a different platform, is not supported.

## 6. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`core:discovery` domain/module.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

## 7. Discovery.interested

This is a push/pull API that allows Apps to either push entities that
the user has expressed interest in to the platform, or respond to pull
request from the platform for the same.

To push an entity that the user is interested in pass an `EntityInfo`
object to the method:

```typescript
Discovery.interested(type: InterestType, entity: EntityInfo): Promise<void>
```

To respond to pull requests for the current entity, because the user has
expressed interest in some way that the platform manages, register a
callback as the parameter:

```typescript
Discovery.interested((intent:InterestIntent) => EntityInfo): Promise<void>
```

The callback takes an `InterestIntent` that provides any context about
the user\'s intention.

## 8. InterestIntent

An `InterestIntent` denotes that the user has expressed interest in the
currently displayed and/or selected content:

```typescript
type InterestIntent {
  action: "interest"
  data: {
    type: "interest"
  },
  context: {
    source: "rcu" | "voice"
  }
}
```


## 9. Manage SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`manage:content `domain/module.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

## 10. Content.onInterestedIn

This notification allows Aggregated Experience Apps to be informed when
a user expresses interest in some Content, and the content resolves to a
valid Entity from some App.

`Content.listen('interestedIn', InterestedInIntent => void): Promise<void>`

The callback will be passed an `InterestedEventData` object with
information about the entity that the user expressed interest in.

## 11. InterestedInIntent

`InterestedInIntent` provides information about what the user has
expressed interest in:

```typescript
type InterestedInIntent {
  action: "interestedIn",
  data: {
    appId: string,
    type: InterestType,
    entity: EntityInfo
  }
}
```
