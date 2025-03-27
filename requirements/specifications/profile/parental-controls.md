# Parental Controls Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization |
| -------------- | ------------ |
| Andrew Bennett | Sky          |
| Joe Martin     | Comcast      |

## 1. Overview

Content partners need access to the user's parental control preferences in order to tailor the user experience in accordance to those preferences.

To support this, Firebolt shall provide content partners with access to the user's parental control preferences, allowing them to provide a safe and controlled user experience.  Content partners are expected to honor the parental control preferences as set by the user, gating or outright preventing access to unwanted or sensitive content.

### 1.1. User Stories

As an app, I want to...

- Get whether the user has enabled viewing restrictions
- Get a list of content ratings (and sub-ratings, if applicable) the user has chosen to restrict from viewing
- Get whether the user should be able to view unrated content
- Be notified when the user's viewing restriction preferences have changed

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. Viewing Restriction](#31-viewing-restriction)
  - [3.2. Content Rating](#32-content-rating)
- [4. Restrictions](#4-restrictions)
  - [4.1. Viewing Restrictions](#41-viewing-restrictions)

## 3. Constants, Types, and Schemas

### 3.1. Viewing Restriction

The Firebolt `Profile` module **MUST** have a `ViewingRestriction` object of the following schema:

| Property  | Type       | Required | Description                                                                          |
| --------- | ---------- | -------- | ------------------------------------------------------------------------------------ |
| `scheme`  | `string`   | Yes      | A rating scheme (e.g. MPAA for US movies). This may be operator or region dependant. |
| `ratings` | `[]Rating` | Yes      | A list of ratings the user wishes to restrict.                                       |

### 3.2. Content Rating

The Firebolt `Profile` module **MUST** have a `ContentRating` object of the following schema:

| Property     | Type       | Required | Description                                                                                                                                           |
| ------------ | ---------- | -------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `rating`     | `string`   | Yes      | A content rating (e.g. PG-13 for an MPAA rated movie). This may be operator or region dependant.                                                      |
| `subRatings` | `[]string` | Yes      | A list of sub-ratings/content descriptors (e.g. ['V'] for violent content for a US TV based rating scheme). This may be operator or region dependant. |

## 4. Restrictions

Apps need to know which parental control restrictions are in place for the current profile so they can curate the user experience in accordance to those restrictions.

To facilitate this, the `Profile` module will provide convenience methods that allow access to the user's preferred restrictions.

### 4.1. Viewing Restrictions

The `Profile` module **MUST** include a `viewingRestrictions` method that returns an object describing the user's preferred viewing restrictions.

This method's response **MUST** support the following properties:

| Property                 | Type                   | Required | Description                                               |
| ------------------------ | ---------------------- | -------- | --------------------------------------------------------- |
| `enabled`                | `boolean`              | Yes      | Whether or not viewing restrictions are currently enabled |
| `restrictions`           | `[]ViewingRestriction` | Yes      |                                                           |
| `restrictUnratedContent` | `boolean`              | Yes      | Whether or not unrated content should be viewable         |

This method **MUST** have a corresponding `onViewingRestrictionsChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:profile:viewingrestrictions` capability.

```javascript
Profile.viewingRestrictions()
//> {
//>     enabled: true,
//>     restrictions: [
//>         {
//>             scheme: 'MPAA',
//>             ratings: [
//>                 {rating: 'R'},
//>                 {rating: 'NC-17'}
//>             ]
//>         },
//>         {
//>             scheme: 'US_TV',
//>             ratings: [
//>                 {rating: 'TV-14', subRatings: ['V']},
//>                 {rating: 'TV-MA'},
//>             ]
//>         }
//>     ],
//>     restrictUnratedContent: true
//> }
```
