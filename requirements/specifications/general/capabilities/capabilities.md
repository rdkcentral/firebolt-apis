# Capabilities

Document Status: Candidate Specification

See [Firebolt Requirements Governance](./governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Andrew Bennett            | Sky            |
| Tim Dibben | Sky |
| Jeremy LaCivita | Comcast |
| Kevin Pearson | Comcast | 
| Peter Yu | Comcast |

## 1. Overview

This document introduces Firebolt Capabilities, which enable discovery
of supported features, negotiation of App permissions, and end-user
grants for Apps to access sensitive features.

Apps can detect if Capabilities are supported and available. If so, Apps
can **Use**, **Provide**, or **Manage** capabilities that they are given
access to.

The most common case is for an App to `use` a Capability, the platform
to `provide` it, and the Distributor\'s Settings App to `manage` it:

![Diagram Description automatically
generated](../../../images/specifications/general/capabilities/image1.png)

However, Apps may also provide Capabilities back to the platform:

![Diagram Description automatically
generated](../../../images/specifications/general/capabilities/image2.png)

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Introduction to Capabilities](#3-introduction-to-capabilities)
  - [3.1. Capabilities](#31-capabilities)
  - [3.2. Availability](#32-availability)
  - [3.3. Permissions](#33-permissions)
  - [3.4. Roles](#34-roles)
  - [3.5. User Grants](#35-user-grants)
  - [3.6. Capability Identifiers](#36-capability-identifiers)
- [4. How Capabilities Work](#4-how-capabilities-work)
  - [4.1. Supported Capabilities](#41-supported-capabilities)
  - [4.2. Available Capabilities](#42-available-capabilities)
  - [4.3. Permitted Capabilities](#43-permitted-capabilities)
  - [4.4. User Granted Capabilities](#44-user-granted-capabilities)
  - [4.5. Invoking Capabilities](#45-invoking-capabilities)
- [5. Configuring Device Capabilities](#5-configuring-device-capabilities)
  - [5.1. Device Supported Capabilities](#51-device-supported-capabilities)
  - [5.2. Device Grant Policy Overrides](#52-device-grant-policy-overrides)
- [6. Capability Schemas](#6-capability-schemas)
  - [6.1. Firebolt Specification Schema](#61-firebolt-specification-schema)
  - [6.2. Firebolt Device Schema](#62-firebolt-device-schema)
  - [6.3. CapabilitiesManifest](#63-capabilitiesmanifest)
  - [6.4. CapabilityPolicy](#64-capabilitypolicy)
  - [6.5. JavaScript](#65-javascript)
  - [6.6. CapabilityKey](#66-capabilitykey)
  - [6.7. CapabilityLevel](#67-capabilitylevel)
  - [6.8. PermissionPolicy](#68-permissionpolicy)
  - [6.9. CapabilityConfig](#69-capabilityconfig)
- [7. Capability to Feature Mapping](#7-capability-to-feature-mapping)
  - [7.1. App installation](#71-app-installation)
  - [7.2. Firebolt APIs](#72-firebolt-apis)
  - [7.3. Extension APIs](#73-extension-apis)
  - [7.4. W3C APIs](#74-w3c-apis)
  - [7.5. Hidden Permissions](#75-hidden-permissions)
- [8. Firebolt Capability Catalog](#8-firebolt-capability-catalog)
- [9. APIs](#9-apis)
  - [9.1. Core SDK APIs](#91-core-sdk-apis)
    - [9.1.1. Supported](#911-supported)
    - [9.1.2. Available](#912-available)
    - [9.1.3. Permitted](#913-permitted)
    - [9.1.4. Granted](#914-granted)
    - [9.1.5. CapabilityInfo](#915-capabilityinfo)
    - [9.1.6. CapabilityDenyReason](#916-capabilitydenyreason)
    - [9.1.7. Info](#917-info)
    - [9.1.8. PermissionInfo](#918-permissioninfo)
    - [9.1.9. Request](#919-request)
    - [9.1.10. onAvailable](#9110-onavailable)
    - [9.1.11. onUnavailable](#9111-onunavailable)
    - [9.1.12. onGranted](#9112-ongranted)
    - [9.1.13. onRevoked](#9113-onrevoked)
  - [9.2. Manage SDK APIs](#92-manage-sdk-apis)
    - [9.2.1. Granted Method](#921-granted-method)

## 3. Introduction to Capabilities

This section defines the key concepts behind the Firebolt Capabilities
system. Each portion of this section provides a background and
conversational definitions of the terms used in the rest of this
document, and through all Firebolt Requirements Specifications.

### 3.1. Capabilities

A Capability is a discrete unit of functionality that a Firebolt device
might be able to perform. It is granular enough to enable appropriate
access controls across all Firebolt Apps, but useful enough to be a
meaningful functional unit that an App might care about. Bluetooth is a
good example of a Capability.

The Firebolt Specification determines the range of possible
Capabilities.

Firebolt platforms advertise which Capabilities are supported. The set
of capabilities supported by a device is an immutable set and will never
change at runtime. Supporting Wi-Fi and having an active Wi-Fi
connection are two different things.

Firebolt platforms determine if an App is allowed to invoke the
different aspects of a Capability (see [Roles](#roles), below).

Firebolt Apps list which Capabilities are required and optional for the
App to be installed.

Firebolt Apps inspect which Capabilities are supported and active.

Firebolt Distributors sign off on some, or all, of the App's listed
required and optional Capabilities.

### 3.2. Availability

A Capability may rely on intermittently available resources, for example
a network capability requires an Ethernet or Wi-Fi network connection.

A supported capability is only considered available if those resources
could be used by the App right now (pending any needed [User
Grants](#user-grants)). For example, the needed resources are not
disabled, not tied up by other apps, and not experiencing any
intermittent network, hardware, or signal issues.

A supported capability is always supported, but it may not always be
*available*.

If a Capability requires Permissions, then it will never be available to
Apps without at least one Role assigned for that Capability (see
[Permissions](#permissions), below).

Capabilities may be available to one App while not available to another
based on non-Permissions criteria. For example, the Video Pipeline may
be available to Apps in the Foreground or Background Lifecycle state,
but not Apps in the Inactive state.

Firebolt platforms determine if a supported capability is available or
not.

### 3.3. Permissions

A Permission is what allows an App to attempt to invoke an aspect of a
Capability. Permissions to a Capability are granted to an App with a
[Role](#roles), by a Firebolt Distributor.

Firebolt documents and APIs will use the term "Permission"
interchangeably with phrases like:

-   An App's Assigned Role for a Capability

-   App + Capability + Role

-   Etc.

The Firebolt Specification determines which Capabilities require
Permissions.

The Firebolt Specification determines which Permission requirements may
be overridden by Distributors.

An App is considered to have Permission to a Capability if it is:

-   Listed with a Role in the App's manifest and signed by the App
    provider

-   Listed and signed again by the Distributor on the App's behalf

-   Listed and signed by the App Publisher when running in self-signed developer
    mode

An App can invoke a Capability if:

-   It has permission, which includes a Role, for that capability

-   The capability is supported by the current device

-   The App is invoking aspects of the capability that it has the
    appropriate Role for

-   The capability is [Available](#availability) at time of invocation

See [Permitted Capabilities](#permitted-capabilities) for more info.

### 3.4. Roles

Every Firebolt Capability has exactly three roles:

-   Use

-   Manage

-   Provide

While these roles will be defined on a case-by-case basis for each
capability, they should generally follow the guidelines set here.

The `Use` role is for providing basic access so that an App can leverage
the standard use cases of the Capability. The `Use` role will not enable
an App to perform management tasks such as turning the Capability on and
off for the entire device. The `Use` role will not enable an App to
perform administrative tasks such as renaming HDMI inputs, etc.

The `Manage` role is for providing access to a Capability's management
and administrative features. This role may be used to allow an App to
build a Settings UI for the Capability, for example. The `Manage` role
is not for creating tiers of permissions within a Capability, but for
separating out administrative APIs, for example turning a feature on and
off.

Most Capabilities are provided by the platform, denoted by making the
`Provide` role `private` for that Capability. However, there are use
cases where Apps may provide Capabilities. The `Provide` role allows for
declaring that an App *implements* the Capability and can be registered
with the platform for fulfilling the Capability's features. This could
be used for functionality that needs to be customized from Distributor
to Distributor. The `Provide` role may also be used to allow Apps to
contribute to aggregated functionality, for example a federated search
feature. By providing a capability, an App is signing up to implement
any `Use` or `Manage` APIs required by that capability.

Each role must be explicitly assigned. An App *never* inherits the
operations from one role by virtue of being granted another. Roles may
have overlapping functionality.

A [Permission](#permissions) is the combination of a Capability w/ a
Role determines which specific operations are permitted.

### 3.5. User Grants

A User Grant allows some Permissions to depend on the User of the
Firebolt Device to explicitly grant access for one or all Apps to use a
specific Capability. This an additional layer of access control on top
of Permissions.

The Firebolt Specification determines which Permissions require User
Grants by default.

It is not possible to require a User Grant for a Capability that is open
to all Apps.

Distributors may override any User Grant details that are defined by the
Firebolt Specification if that User Grant Policy is set to
`overridable: true`.

**Proposal:** Consumers want to know that their Smart TV platform treats
security as a first-class design principal. As such, table-stakes User
Grant policies, e.g. App access to Bluetooth, may be denoted as
overridable: false in the Firebolt Specification, to remove any
possibility of a security flaw.

An App is considered to have a User Grant to a Capability if it is:

-   Has Permission to the Capability

-   The User Grant is for the same Role as the Permission above

-   The Capability is **securely** approved by the device user

If an App invokes a Capability but does not have an active User Grant,
then the platform will block invocation, prompt the user for a grant,
and then continue with the original invocation, e.g. the App does not
have to call the originating API again (assuming the user did give their
approval).

See [User Granted Capabilities](#user-granted-capabilities) for more
info.

### 3.6. Capability Identifiers

Capabilities **MUST** be identified by an XRN. The structure of a Firebolt Capability URN is as follows:

`xrn:firebolt:capability:<category>:<name>`

For example:

`xrn:firebolt:capability:protocol:bluetooth`

The `<category>` is used to group capabilities together to
facilitate bulk permissions and **MUST** match the following regular
expression:

`^[a-zA-Z0-9\-]{1,32}$`

Note that categories are not related to individual SDK modules, which
group things to facilitate App development simplicity, not permissions
management across multiple SDKs.

The `<name>` identifies the specific capability when combined with the
`<category>` and **MUST** match the following regular expression:

`^[a-zA-Z0-9\-]{1,32}$`

## 4. How Capabilities Work

A given Capability may or may not be supported or available.
Additionally, a given Role may or may not be permitted or granted for a
given Capability.

While support for a Capability is static and global, the other status
may differ from App to App.

Determining the status of a Role and/or Capability is fundamental to
both the Platform and the Apps that run on it.

### 4.1. Supported Capabilities

Once an App has been launched, it may need to check if a certain
capability is supported, to present the appropriate user experience. For
example, an App may want to put Dolby Atmos badges next to its content,
but only if the platform supports Dolby Atmos.

The Firebolt Specification determines which capabilities **MUST** be
supported by all Firebolt Devices, by listing those Capabilities in the
Firebolt Specification Schema as `level: "must"` in the Capabilities
array.

For a capability to be supported, it **MUST** have *one* or *both* of
the following:

> A supported capability **MUST** have the necessary hardware and
> software to invoke all required aspects of all Roles of the
> capability.
>
> **OR**
>
> A supported capability **MUST** have the necessary hardware and
> software to support a *certified*, after-market peripheral that
> provides the capability. Note that this includes peripherals that have
> not yet been connected to or installed on the device.

However, a Firebolt device **MUST NOT** be considered to support a
capability if the capability is disabled by the static distributor
configuration.

The platform **MUST** return accurate responses based on these
requirements to all [APIs](#apis) outlined below.

### 4.2. Available Capabilities

Once an App has been launched, it may need to check if a certain
capability is available, to start the appropriate user experience. For
example, an App that uses an external camera may need to check if the
user has set up their camera before proceeding to the main user
experience.

A Capability is available to an App if **all** the following are true:

> An available Capability **MUST** be supported.
>
> An available Capability **MUST** have a provider, either an App, an
> Extension SDK, or the OS itself.
>
> The provider of the Capability **MUST** consider it to be available
>
> An available Capability **MUST NOT** be currently disabled by any
> user, account, or device setting.
>
> An available Capability **MUST** either be approved for all Apps by
> the Firebolt Specification, **OR** have a Permission assigned to the
> App in question by the distributor or the providing App, for at least
> one Role.
>
> An available Capability **MUST** be considered available by at least
> one provider of the capability. This is specified by the requirements
> for each feature.

An available Capability **MAY** be tied to a User Grant, regardless of
whether the user has granted it yet. Secure user grants gate permission,
not availability.

The platform **MUST** return accurate responses based on these
requirements to all [APIs](#apis) outlined below.

### 4.3. Permitted Capabilities

Capabilities may be permitted to *all* Apps by the Firebolt
Specification Schema, or to individual Apps by the Distributor-signed
App Manifest.

An App may need to know if a Capability is permitted to it once it has
been launched. For example, it may need to check if a certain capability
is permitted, to enable the correct features for the current
distributor. For example, an App that has just been installed might not
show a Returns true for capability/role combinations that do not r
Sign-up option when running on a distributor that has not allowed it to
`use` the `commerce:subscribe` capability, and only allow existing users
to sign in.

Determining if a Capability is permitted requires knowing which **Role**
is being leveraged.

Permitted capabilities **MUST** be denoted as `public` in the [Firebolt
Specification Schema](#_Firebolt_Specification_Schema).

Additionally, **one** of the following **MUST** be true as well:

> The Role **MUST** have `negotiable` set to `false`
>
> **OR**
>
> The Role **MUST** be approved for the capability by the distributor in
> the App Manifest

A permitted Capability **MAY** be tied to a User Grant, regardless of
whether the user has granted it yet.

The platform **MUST** return accurate responses based on these
requirements to all [APIs](#apis) outlined below.

### 4.4. User Granted Capabilities

Some Capabilities may require a User Grant. It is the App's choice
whether it requests these grants at launch or allows the platform to
interrupt the App's experience when User Grant-gated Capabilities are
invoked.

Determining if a Capability has been granted by the user requires
knowing which Role is being used.

For a Capability to be considered granted, it **MUST** be supported.

Additionally, a Capability + Role is granted to an App if **one** of the
following is true:

> A granted capability **MUST** have the Role securely granted to the
> App by the user and that grant must not be expired.
>
> **OR**
>
> A granted capability **MUST** have the Role permanently granted to the
> App by the App Manifest, e.g., if the user implicitly granted these by
> virtue of an end user license agreement.

Firebolt platforms **MUST** support acquiring a user grant *at the
moment the Capability is invoked*, without requiring any reinvocation of
the Capability.

See [User Grants](./user-grants.md), for more info.

The platform **MUST** return accurate responses based on these
requirements to all [APIs](#apis) outlined below.

### 4.5. Invoking Capabilities

When invoking a Capability, there are several factors that determine
whether the calling App will be allowed. The primary factor is which
Role is being leveraged by the invocation.

A given Capability & Role can be public or not, and it can be negotiable
or not.

If a Role for a Capability is public and non-negotiable, then all Apps
are allowed to invoke it, without any explicit permission from the
platform distributor. This is subject to support, availability, and any
required User Grants.

If a Role for a Capability is public and negotiable, then Apps **MUST**
be permitted by each distributor to use it on that distributor\'s
devices.

If a Role for a Capability is private, then it **MUST NOT** be permitted
or granted to any Apps.

A Role for a Capability **MUST NOT** be flagged as negotiable if it is
private.

If a Capability is gated by a User Grant requirement, then any
invocation **MUST** check the grant status for the Role in question, and
potentially re-acquire a User Grant for the App to invoke it.

The following flow diagrams show the order of operations for determining
if a Firebolt API, that depends on one or more capabilities, may be
invoked. The checks in this diagram **MUST** be executed in this order
to ensure that error codes are consistent and User Grant prompts are not
displayed to end users in situations where the API call will still not
be allowed for other reasons.

![](../../../images/specifications/general/capabilities/image4.png)

Note that determining user grants may involve presenting a UX to the end
user. During this time, a necessary capability may become unavailable.
Due to this, necessary Capabilities MUST be reevaluated for availability
after determining user grant status. For a more detailed flow diagram
for evaluating User Grants, see [User Grants](./user-grants.md).

## 5. Configuring Device Capabilities

The Firebolt Specification describes all the possible, non-Extension
capabilities that a particular version of Firebolt allows. Individual
Firebolt devices, however, may not support every Capability and may want
to override certain aspects of those Capabilities.

Every Firebolt-compliant device **MUST** include an official, versioned
Firebolt JSON configuration that conforms to the [Firebolt Specification
Schema](#_Firebolt_Specification_Schema), so that the implementation
knows how to configure each capability, and which aspects are
overridable.

Additionally, every Firebolt-compliant device **MUST** have a versioned

Firebolt Device JSON configuration that conforms to the Firebolt Device
Schema, so that the implementation knows how each capability has been
overridden by the Distributor for this device.

See [Firebolt Device Schema](#firebolt-device-schema) for more info.

### 5.1. Device Supported Capabilities

Firebolt-compliant devices **MUST** list all the Capabilities they
support in the Device Capabilities configuration file\'s `supported`
array.

The `supported` array **MUST** contain a `CapabilityConfig` for every
Firebolt Capability supported by this device.

The `supported` array **MUST** contain an entry for every Capability
from the Firebolt Specification Schema that has a level of `must`.

The `supported` array **MAY** contain entries for any `should` or
`could` Capabilities.

The supported array **MUST NOT** contain any entries for Capabilities
not found in the Firebolt Specification Schema.

### 5.2. Device Grant Policy Overrides

Firebolt-compliant devices **MAY** override any `GrantPolicies` that
have `overridable` set to `true`.

This can be used to permanently disable a User Grant

Firebolt-compliant devices **MUST NOT** override any `GrantPolicies`
that have `overridable` set to `false`.

`GrantOverrides` are included in the `grantOverrides` array of the
`CapabilityConfig` for the Capability in question.

If both the Firebolt Specification Schema and the Device Schema have
different, valid overrides for the same capability + appId, then the
device config **MUST** be used by that device.

## 6. Capability Schemas

This section describes how Capabilities are represented in the static
Firebolt configuration for a device.

### 6.1. Firebolt Specification Schema

Each version of Firebolt **MUST** have a single Firebolt Specification
Schema that is the source-of-truth for and contains all possible
capabilities provided by Apps or Firebolt platforms.\
\
See the [Firebolt Specification
Schema](https://github.com/rdkcentral/firebolt-schemas) on GitHub for
more info on exact semantics.

**NOTE**: This is still in development, and shouldn\'t hold up the
Capabilities Spec

This schema **MUST** have the following fields for specifying the
Capabilities of that version of the Firebolt Specification. Every field
of this object, and every sub-object it contains is **required** unless
noted by \'optional.\'

| Property       | Type                       | Description                                                                 |
|---------------------|----------------|-----------------------------------|
| `version`      | `string`                   | The Firebolt version that this Capability Manifest describes.               |
| `capabilities` | `CapabilityPolicy[]` | All possible Firebolt capabilities for this version of Firebolt.            |
| `javascript`   | `JavaScript[]`           | Mapping of W3C JavaScript APIs to Capabilities.                             |
| `signature`    | `string`                   | Signature from the Firebolt Platform Owner over digest of all other fields. |

Firebolt \"Bumblebee\" Firebolt Specification JSON can be seen here:

**NOTE**: This is still in development, and shouldn\'t hold up the
Capabilities Spec

### 6.2. Firebolt Device Schema

Each Firebolt device will have a static configuration for overriding
which capabilities are supported, as well as any negotiable Capability
overrides. Every field of this object, and every sub-object it contains
is **required** unless noted by \'optional.\'

| Property       | Type                   | Description                                                   |
|--------------------|--------------------|---------------------------------|
| `version`      | `string`               | The Firebolt version that this Capability Manifest describes. |
| `capabilities` | `CapabilitiesManifest` | An object describing the Capabilities of this device          |

The `version` **MUST** match the `version` in the [Firebolt
Specification Schema](#_Firebolt_Specification_Schema).

### 6.3. CapabilitiesManifest

| Property        | Type                          | Description                                                           |
|--------------------|--------------------|---------------------------------|
| `supported`     | `string[]`                  | List of supported capabilities for this device.                       |
| `grantPolicies` | `Map<Role,GrantPolicy>` | An optional GrantPolicy override for each role: use, manage, provide. |

See [GrantPolicy](./user-grants.md) in the User Grant requirements document, for more info.

### 6.4. CapabilityPolicy

A Firebolt Capability that must, should, or could be implemented by
Firebolt platforms.

| Property  | Type                 | Description                           |
|-----------|----------------------|---------------------------------------|
| `id`      | `CapabilityKey`      | The XRN of the Capability.            |
| `level`   | `CapabilityLevel`    | Requirement level of this Capability. |
| `use`     | `PermissionPolicy` | The policy for `use` permissions.     |
| `manage`  | `PermissionPolicy` | The policy for `manage` permissions.  |
| `provide` | `PermissionPolicy` | The policy for `provide` permissions. |

### 6.5. JavaScript

A representation of how a specific set of JavaScript APIs is mapped to
capabilities.

| Property      | Type         | Description                                                                                                                                                                             |
|-----------|----------|----------------------------------------------------|
| `class`       | `string`     | The name of the JavaScript class.                                                                                                                                                       |
| `methods`     | `string[]` | An array of method names from the class.                                                                                                                                                |
| `uses`      | `string[]` | An array of capabilities that these methods `use`, which will apply support, availability, permissions, and user grants as defined herein.                                              |
| `manages`   | `string[]` | An array of capabilities that these methods `manage`, which will apply support, availability, permissions, and user grants as defined herein.                                           |
| `synchronous` | `boolean`    | Does this API need to support a synchronous return value? If so, then User Grants must be acquired before calling it, or it will simply error out w/out prompting the user for a grant. |

**Done**: how do User Grants impact synchronous methods?
Capabilities.request() (see above)

### 6.6. CapabilityKey

A `string` matching the pattern:

`/`\^xrn:firebolt:capability:\[a-zA-Z0-9\\-\]{1,32}:\[a-zA-Z0-9\\-\]{1,32}\$/

### 6.7. CapabilityLevel

A `string` enumeration.

| Value    | Description                                                                                                                       |
|----------------|--------------------------------------------------------|
| `must`   | The capability **MUST** be implemented by all Firebolt platforms.                                                                 |
| `should` | The capability **SHOULD** be implemented by all Firebolt platforms. Platforms without this capability will be reviewed regularly. |
| `could`  | The capability is optional and **MAY** be implemented by Firebolt platforms.                                                      |

### 6.8. PermissionPolicy

An access policy for a particular role of a capability.

| Property     | Type          | Description                                                            |
|------------------|--------------|-----------------------------------------|
| `public`     | `boolean`     | Is this role & capability potentially accessible by Apps.              |
| `negotiable` | `boolean`     | Is this role & capability negotiable between distributors and Apps.    |
| `userGrant`  | `GrantPolicy` | *Optional*. Does this capability/role require a user grant to be used. |

If a Policy has `public` set to `false`, then it is a private
Role/Capability that cannot be given to an App. This could be used to
ensure that an important capability is always provided by the platform.
The value of `negotiable` does not matter in this case.

If a Policy has `public` set to `true` and `negotiable` set to `false`,
then it a Role/Capability that *all* Apps may leverage without needing
to be permitted by the platform distributor.

If a Policy has `public` set to `true` and `negotiable` set to `true`,
then it is a Role/Capability that can only be leveraged by Apps when
running on a distributor that has permitted access the App.

### 6.9. CapabilityConfig

A Firebolt Capability id, along with any user grant overrides.

| Property                | Type                  | Description                                                              |
|------------------|---------------|---------------------------------------|
| `id`                    | `CapabilityKey`       | The XRN of the Capability.                                               |
| `useGrantOverrides` | `GrantPolicy[]` | *Optional*. Does this capability & role require a user grant to be used. |
| `manageGrantOverrides`  | `GrantPolicy[]`   | *Optional*. Does this capability & role require a user grant to be used. |
| `provideGrantOverrides` | `GrantPolicy[]`   | *Optional*. Does this capability & role require a user grant to be used. |

## 7. Capability to Feature Mapping

Capabilities denote functionality, and functionality can manifest in
several ways.

### 7.1. App installation

Some Apps may not be useful, and may even prove counter to their goals,
if installed on a device without certain capabilities. For example, a
Dolby Vision demonstration App that requires it only be installed on
devices that support Dolby Vision, to avoid playing back lower quality
content that users might mistake for Dolby Vision content.

If an App includes a capability in one of its App Manifest's `required`
Capability lists:

-   `app.capabilities.used.required`

-   `app.capabilities.managed.required`

-   `app.capabilities.provided.required`

Then that App **MUST NOT** be installable on Firebolt devices that do
not support that capability.

Apps that have an unsupported capability inside one of its `optional`
lists **SHOULD NOT** be prevented from installation, unless there is
some other reason outside the scope of this document.

### 7.2. Firebolt APIs

Some Firebolt APIs may require the use of one or more Capabilities.
These methods MUST have all required Capabilities listed in the method's
OpenRPC schema.

Capabilities are listed in one of three OpenRPC extensions attached to
the `'capabilities' `tag on the method: `x-uses`, `x-manages`,
`x-provides`. 

If a method lists more than one Capability for a role, then it may
specify that those capabilities are either all required, any combination
of them is required, or one and only one is required. This is done by
setting the `x-uses-operator` value to either `allOf`, `anyOf`, or
`oneOf`. This value defaults to `allOf` if not specified. An example of
this is an API to find and pair remotes, regardless of which connection
protocol is needed. This API requires `anyOf bluetooth:scan`,
`rf4ce:scan`, `wifi:scan`. If one or more of these capabilities is
available (and permitted) then the API will execute using the available
and permitted protocols.

If a method *requires* a capability, and that capability requires a user
grant that the App does not have, then the platform **MUST** block and
initiate a User Grant flow. Once granted, the platform **MUST** return
the expected value without the App having to reinvoke the API. If not
granted after the User Grant flow, the platform **MUST** return an
error.

Capabilities that enhance an API, but are not fundamentally required,
for example a `play` API optionally uses the `'hdr:dolbyvision'`
capability, **MUST NOT** be listed in the OpenRPC schema.

If a method leverages an *optional* Capability that is unavailable or
unpermitted, it **MUST** leave out or defer the optional functionality.

If a method leverages an *optional* Capability that requires a user
grant the App does not have, it **MUST** leave out the optional
functionality, and it **MUST NOT** request a user grant.

### 7.3. Extension APIs

Extension SDKs implement their methods in the cloud but rely on
Firebolt's Permissions and Capabilities model.

Requirements for Extension SDKS is outside of the scope of this document.

### 7.4. W3C APIs
Firebolt platforms may need to control access to certain W3C APIs. For
example, a platform may want to allow some Apps to use the
MediaDevices.getUserMedia API, but not all Apps.

For each W3C JavaScript API that needs to be gated by a Permission, an
entry in the Firebolt Version Manifest's JavaScript capabilities configuration **MUST** exist, for example:

```json
{
  JavaScript: [
    {
      class: "MediaDevices",
      methods: [
        "getUserMedia"
      ],
      uses: [
        "xrn:firebolt:capability:media:avinput"
      ],
      manages: [
        "xrn:firebolt:capability:media:avinput"
      ]
    }
  ]
}
```

If a W3C API, e.g. MediaDevices, exists in the schema, then it requires
permissions to use.

The requirements for invoking W3C APIs are the same as [Firebolt
APIs](#firebolt-apis).

**Proposal**: W3C APIs that need to return synchronously **MUST NOT**
prompt the user to acquire any User Grants. Apps that use these APIs
**MUST** request the grant before invoking the APIs.

### 7.5. Hidden Permissions

A hidden permission arises when an API requires permission to one
Capability which in turn requires another Capability gated by a
different permission. This is not supported by Firebolt, and all
permission dependencies should be validated to avoid this.

Firebolt Capabilities **MUST NOT** have hidden permissions.

For example:

-   API `Module.methodOne()` requires permission to `use` the
    `'contrived:capability1'` Capability

-   API `Module.methodTwo()` requires permission to `use` the
    `'contrived:capability2'` Capability

-   `methodOne`'s implementation calls `methodTwo`

There is now a hidden permission: `methodOne` requires both
`capability1` and `capabilty2`.

Note that it's fine for a method to leverage an ungated, but also
unavailable Capability, such as a DIAL API failing because the network
capability is unavailable.

## 8. Firebolt Capability Catalog

**This isn't done**, but it's intended to be a real, proposed snapshot
(not examples) of the capabilities needed by Firebolt 0.6.0. I still
need to add [Extension Features](#extension-apis) and [W3C
Features](#w3c-apis).

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 19%" />
<col style="width: 15%" />
<col style="width: 16%" />
<col style="width: 16%" />
<col style="width: 16%" />
</colgroup>
<thead>
<tr class="header">
<th>Category</th>
<th>Name</th>
<th>Has</th>
<th>Use Role</th>
<th>Manage Role</th>
<th>Provide Role</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>account</td>
<td>uid</td>
<td><em>NA</em></td>
<td>Read the app-specific account UID</td>
<td>Reset one or all app specific account UIDs</td>
<td><em>NA</em></td>
</tr>
<tr class="even">
<td>advertising</td>
<td>framework</td>
<td>Ability to use the Ad Framework</td>
<td>Read the Ad Framework configuration</td>
<td>Write/Delete the Ad Framework configuration</td>
<td>Provide cloud services for the Ad Framework Extension APIs</td>
</tr>
<tr class="odd">
<td>advertising</td>
<td>policy</td>
<td>Ability to surface ad policy to apps</td>
<td>Read Ad Policy settings</td>
<td>Write/Delete Ad Policy Settings</td>
<td>Provide services for persisting Ad Policy Settings</td>
</tr>
<tr class="even">
<td>device</td>
<td>uid</td>
<td><em>NA</em></td>
<td>Read the app-specific device UID</td>
<td>Reset one or all app Specific device UIDs</td>
<td><em>NA</em></td>
</tr>
<tr class="odd">
<td>content</td>
<td>entitlements</td>
<td>Ability to surface app content entitlements in aggregated
experience</td>
<td>Query entitlements across aggregated providers</td>
<td><em>NA</em></td>
<td>Provide entitlements upon request or as needed</td>
</tr>
<tr class="even">
<td>content</td>
<td>entityInfo</td>
<td>Ability to surface app content metadata in aggregated
experience</td>
<td>Query entity info metadata across aggregated providers</td>
<td><em>NA</em></td>
<td>Provide entity info metadata upon request or as needed</td>
</tr>
<tr class="odd">
<td>content</td>
<td>purchasedContent</td>
<td>Ability to surface app user’s purchased content in aggregated
experience</td>
<td>Query purchased content lists across aggregated providers</td>
<td><em>NA</em></td>
<td>Provide a purchased content list upon request or as needed</td>
</tr>
<tr class="even">
<td>content</td>
<td>watched</td>
<td>Ability to surface app user’s watched content in aggregated
experience</td>
<td>Query watched content across aggregated providers</td>
<td><em>NA</em></td>
<td>Provide watched content upon request or as needed</td>
</tr>
<tr class="odd">
<td>content</td>
<td>watchNext</td>
<td>Ability to surface app suggested watch next content in aggregated
experience</td>
<td>Query suggestions for what to watch next content across aggregated
providers</td>
<td><em>NA</em></td>
<td>Provide suggestions for what to watch next upon request or as
needed</td>
</tr>
<tr class="even">
<td>keyboard</td>
<td>email</td>
<td><em>NA</em></td>
<td>Request an email keyboard to be presented and an email returned</td>
<td>Manage which apps can provide email keyboards</td>
<td>Provide an email keyboard upon request</td>
</tr>
<tr class="odd">
<td>lifecycle</td>
<td>background</td>
<td>Ability for apps to run in the background</td>
<td>Permission for a specific App to run in the background</td>
<td>Permission to push <em>any</em> app to the background</td>
<td><em>NA</em></td>
</tr>
<tr class="even">
<td>lifecycle</td>
<td>launch</td>
<td><em>NA</em></td>
<td>Ability to launch apps within an apps own family</td>
<td>Ability to launch <em>any</em> app</td>
<td><em>NA</em></td>
</tr>
<tr class="odd">
<td>lifecycle</td>
<td>suspend</td>
<td>Ability for apps to be suspended</td>
<td><em>NA</em></td>
<td>Permission to suspend <em>any</em> app</td>
<td><em>NA</em></td>
</tr>
<tr class="even">
<td>input</td>
<td>hdmi</td>
<td>Ability to switch HDMI inputs</td>
<td>Permission to change the inputs</td>
<td>Permission to give friendly names the inputs</td>
<td><em>NA</em></td>
</tr>
<tr class="odd">
<td>protocol</td>
<td>bluetooth</td>
<td>Bluetooth</td>
<td>Permission to scan for devices and pair.</td>
<td>Permission to enable/disable.</td>
<td><em>NA</em></td>
</tr>
<tr class="even">
<td>protocol</td>
<td>wifi</td>
<td>Wi-Fi and WPS</td>
<td><p>Permission to</p>
<ul>
<li><p>scan for networks</p></li>
<li><p>pair to network</p></li>
<li><p>pair via WPS</p></li>
</ul></td>
<td>Permission to enable/disable Wi-Fi</td>
<td></td>
</tr>
<tr class="odd">
<td>protocol</td>
<td>tuner</td>
<td>Has a tuner</td>
<td>Permission to scan for and tune channels</td>
<td>Permission to name channels</td>
<td></td>
</tr>
<tr class="even">
<td>intent</td>
<td>tune</td>
<td>Has a tuner</td>
<td>Permission to request the user be tuned to a channel</td>
<td><em>NA</em></td>
<td>Permission to provide mapping from Tune intents to actual antennae
stations value</td>
</tr>
</tbody>
</table>

## 9. APIs

### 9.1. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`core:capabilities` domain/module. This module is intended for App
developers to have one place to check for all aspects of "can I do
this." Including supported, available, permitted, and granted
Capabilities. It also provides bulk operations for figuring out which
needed Capabilities are unavailable, in order to wait for them, and
which ones are ungranted, in order to request them.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

#### 9.1.1. Supported

Returns whether the platform supports the passed capability.

`function Capabilities.supported(capability string): boolean`

#### 9.1.2. Available

Returns whether a capability is available now.

`function Capabilities.available(capability string): boolean`

#### 9.1.3. Permitted

Returns whether the current App has permission to the passed capability
and role. Role defaults to `'use'`. Returns `true` for capability/role
combinations that do not require permission.

`function Capabilities.permitted(capability: string, role?: string): boolean`

#### 9.1.4. Granted

Returns whether the current App has a user grant for passed capability
and role. Role defaults to `'use'`. Returns `true` for capabilities that
do not require a user grant.

`function Capabilities.granted(capability: string, role?: string): boolean`

#### 9.1.5. CapabilityInfo 

Object describing all aspects a given Role and Capability for the App in
question:

`type CapabilityInfo {`\
`  capability: string,`

`  role: "use" | "provide" | "manage",`

`  supported: boolean,`

`  available: boolean,`

`  permitted: boolean,`

`  granted: boolean,`

`  details?: DenyReason[]`

`}`

The details array contains an ordered list of reasons why leveraging the
Role might be denied at the current time.

#### 9.1.6. CapabilityDenyReason 

An string enumeration of reasons why a Capability might not be
invokable. Values in the CapabilityInfo.details array **MUST** be sorted
in the order of this table.

| Value            | Description                                                                           |
|-----------------|-------------------------------------------------------|
| `unpermitted`    | The App is not permitted to leverage the role in question by the current Distributor. |
| `unsupported`    | The capability is not supported on this device.                                       |
| `disabled`       | The capability is disabled by a user setting.                                         |
| `unavailable`    | The capability is unavailable for some reason other than a user setting.              |
| `grant-denied` | The User denied the App from using the role in question.                              |
| `ungranted`      | The role in question has not been granted to the App by the User.                     |

Some of these values are subsets of others:

If the details array contains `grant-denied` then it **MUST** also
contain `ungranted`.

If the details array contains `disabled` then it **MUST** also contain
`unavailable`.

#### 9.1.7. Info

Returns an array of `CapabilityInfo` objects for the passed in
capabilities. Typically used to determine which capabilities are
unsupported or unavailable, in bulk.

`function Capabilities.info(role: string, capabilities: string[]): CapabilityInfo[]`

#### 9.1.8. PermissionInfo 

Object describing a Capability / Role pair.

`type PermissionInfo {`\
`  capability: string,`

`  role: "use" | "provide" | "manage"`

`}`

#### 9.1.9. Request

Requests grants for all capability/role combinations in the `roles`
array. Method resolves when all requested capability/roles are granted.
Rejects otherwise. This method may block for extended periods pending
user interaction.

`function Capabilities.request(grants:PermissionInfo[]): CapabilityInfo[]`

#### 9.1.10. onAvailable

Listens for all App permitted capabilities to become available.

`function Capability.available(capability: string, CapabilityInfo => void): integer`

#### 9.1.11. onUnavailable

Listens for all App permitted capabilities to become unavailable.

`function Capability.unavailable(capability: string, CapabilityInfo => void): integer`

#### 9.1.12. onGranted

Listens for all App permitted capabilities to become granted.

`function Capability.granted(role: string, capability: string, CapabilityInfo => void): integer`

#### 9.1.13. onRevoked

Listens for all App permitted capabilities to become revoked.

`function Capability.revoked(role: string, capability: string, CapabilityInfo => void): integer`

### 9.2. Manage SDK APIs

The following APIs are exposed by the Firebolt Manage SDK as part of the
`manage:usergrants` domain/module. This module is intended for
Management UIs that show a list of grants per App or Capability, and
allow users to revoke them.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

#### 9.2.1. Granted Method

Returns whether the user has granted this capability to an App

`UserGrants.granted(appId: string, role: string, capability: string): boolean`