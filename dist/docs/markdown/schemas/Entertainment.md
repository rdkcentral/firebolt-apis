---
title: Entertainment
---
# Entertainment Schema
---
Version 0.8.0


## JSON-Schema
This document was generated from a JSON-Schema, and is intended to provide a human readable overview and examples of the methods contained in the module.

For the full schema, see the link below.

| Schema |
|--------|
| [entertainment.json](https://github.com/rdkcentral/firebolt-openrpc/blob/feature/badger-parity/src/schemas/entertainment.json) |

## Table of Contents
 
 - Schemas
    - [ProgramType](#programtype)
    - [Entitlement](#entitlement)
    - [EntityInfo](#entityinfo)
    - [OfferingType](#offeringtype)
    - [WayToWatch](#waytowatch)
    - [ContentRating](#contentrating)
    - [ContentIdentifiers](#contentidentifiers)


## Schemas

### ProgramType

```typescript
type ProgramType = 'movie' | 'episode' | 'season' | 'series' | 'other' | 'preview' | 'extra' | 'concert' | 'sportingEvent' | 'advertisement' | 'musicVideo' | 'minisode'
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

In the case of a program `entityType`, specifies the program type.


---

### Entitlement

```typescript
type Entitlement = {
  entitlementId: string
  startTime?: string
  endTime?: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### EntityInfo

```typescript
type EntityInfo = {
  identifiers: ContentIdentifiers   // The ContentIdentifiers object is how the app identifies an entity or asset to
  title: string                     // Title of the entity.
  entityType: "program"
  programType: ProgramType          // In the case of a program `entityType`, specifies the program type.
  synopsis?: string                 // Short description of the entity.
  seasonNumber?: number             // For TV seasons, the season number. For TV episodes, the season that the episode belongs to.
  seasonCount?: number              // For TV series, seasons, and episodes, the total number of seasons.
  episodeNumber?: number            // For TV episodes, the episode number.
  episodeCount?: number             // For TV seasons and episodes, the total number of episodes in the current season.
  releaseDate?: string              // The date that the program or entity was released or first aired.
  contentRatings?: ContentRating[]  // A list of ContentRating objects, describing the entity's ratings in various rating schemes.
  waysToWatch?: WayToWatch[]        // An array of ways a user is might watch this entity, regardless of entitlements.
}
```

See also: 

 - [ProgramType](../../schemas/entertainment#programtype)


<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

An EntityInfo object represents an "entity" on the platform. Currently, only entities of type `program` are supported. `programType` must be supplied to identify the program type.

Additionally, EntityInfo objects must specify a properly formed
ContentIdentifiers object, `entityType`, and `title`.  The app should provide
the `synopsis` property for a good user experience if the content
metadata is not available another way.

The ContentIdentifiers must be sufficient for navigating the user to the
appropriate entity or detail screen via a `detail` intent or deep link.

EntityInfo objects must provide at least one WayToWatch object when returned as
part of an `entityInfo` method and a streamable asset is available to the user.
It is optional for the `purchasedContent` method, but recommended because the UI
may use those data.


---

### OfferingType

```typescript
type OfferingType = 'free' | 'subscribe' | 'buy' | 'rent'
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

The offering type of the WayToWatch.


---

### WayToWatch

```typescript
type WayToWatch = {
  identifiers: ContentIdentifiers       // The ContentIdentifiers object is how the app identifies an entity or asset to
  expires?: string                      // Time when the WayToWatch is no longer available.
  entitled?: boolean                    // Specify if the user is entitled to watch the entity.
  entitledExpires?: string              // Time when the entity is no longer entitled.
  offeringType?: OfferingType           // The offering type of the WayToWatch.
  hasAds?: boolean                      // True if the streamable asset contains ads.
  price?: number                        // For "buy" and "rent" WayToWatch, the price to buy or rent in the user's preferred currency.
  videoQuality?: 'SD' | 'HD' | 'UHD'[]  // List of the video qualities available via the WayToWatch.
  audioProfile: AudioProfile[]          // List of the audio types available via the WayToWatch.
  audioLanguages?: string[]             // List of audio track languages available on the WayToWatch. The first is considered the primary language. Languages are expressed as ISO 639 1/2 codes.
  closedCaptions?: string[]             // List of languages for which closed captions are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  subtitles?: string[]                  // List of languages for which subtitles are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  audioDescriptions?: string[]          // List of languages for which audio descriptions (DVD) as available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
}
```

See also: 

 - [OfferingType](../../schemas/entertainment#offeringtype)
 - [AudioProfile](../../schemas/types#audioprofile)


<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A WayToWatch describes a way to watch a video program. It may describe a single
streamable asset or a set of streamable assets. For example, an app provider may
describe HD, SD, and UHD assets as individual WayToWatch objects or rolled into
a single WayToWatch.

If the WayToWatch represents a single streamable asset, the provided
ContentIdentifiers must be sufficient to play back the specific asset when sent
via a playback intent or deep link. If the WayToWatch represents multiple
streamable assets, the provided ContentIdentifiers must be sufficient to
playback one of the assets represented with no user action. In this scenario,
the app SHOULD choose the best asset for the user based on their device and
settings. The ContentIdentifiers MUST also be sufficient for navigating the user
to the appropriate entity or detail screen via an entity intent.

The app should set the `entitled` property to indicate if the user can watch, or
not watch, the asset without making a purchase. If the entitlement is known to
expire at a certain time (e.g., a rental), the app should also provide the
`entitledExpires` property. If the entitlement is not expired, the UI will use
the `entitled` property to display watchable assets to the user, adjust how
assets are presented to the user, and how intents into the app are generated.
For example, the the Aggregated Experience could render a "Watch" button for an
entitled asset versus a "Subscribe" button for an non-entitled asset.

The app should set the `offeringType` to define how the content may be
authorized. The UI will use this to adjust how content is presented to the user.

A single WayToWatch cannot represent streamable assets available via multiple
purchase paths. If, for example, an asset has both Buy, Rent and Subscription
availability, the three different entitlement paths MUST be represented as
multiple WayToWatch objects.

`price` should be populated for WayToWatch objects with `buy` or `rent`
`offeringType`. If the WayToWatch represents a set of assets with various price
points, the `price` provided must be the lowest available price.


---

### ContentRating

```typescript
type ContentRating = {
  scheme: 'CA-Movie' | 'CA-TV' | 'CA-Movie-Fr' | 'CA-TV-Fr' | 'US-Movie' | 'US-TV'  // The rating scheme.
  rating: string                                                                    // The content rating.
  advisories?: string[]                                                             // Optional list of subratings or content advisories.
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

A ContentRating represents an age or content based of an entity. Supported rating schemes and associated types are below.

## United States

`US-Movie` (MPAA):

Ratings: `NR`, `G`, `PG`, `PG13`, `R`, `NC17`

Advisories: `AT`, `BN`, `SL`, `SS`, `N`, `V`

`US-TV` (Vchip):

Ratings: `TVY`, `TVY7`, `TVG`, `TVPG`, `TV14`, `TVMA`

Advisories: `FV`, `D`, `L`, `S`, `V`

## Canada

`CA-Movie` (OFRB):

Ratings: `G`, `PG`, `14A`, `18A`, `R`, `E`

`CA-TV` (AGVOT)

Ratings: `E`, `C`, `C8`, `G`, `PG`, `14+`, `18+`

Advisories: `C`, `C8`, `G`, `PG`, `14+`, `18+`

`CA-Movie-Fr` (Canadian French language movies):

Ratings: `G`, `8+`, `13+`, `16+`, `18+`

`CA-TV-Fr` (Canadian French language TV):

Ratings: `G`, `8+`, `13+`, `16+`, `18+`



---

### ContentIdentifiers

```typescript
type ContentIdentifiers = {
  assetId?: string           // Identifies a particular playable asset. For example, the HD version of a particular movie separate from the UHD version.
  entityId?: string          // Identifies an entity, such as a Movie, TV Series or TV Episode.
  seasonId?: string          // The TV Season for a TV Episode.
  seriesId?: string          // The TV Series for a TV Episode or TV Season.
  appContentData?: string    // App-specific content identifiers.
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

The ContentIdentifiers object is how the app identifies an entity or asset to
the Firebolt platform. These ids are used to look up metadata and deep link into
the app.

Apps do not need to provide all ids. They only need to provide the minimum
required to target a playable stream or an entity detail screen via a deep link.
If an id isn't needed to get to those pages, it doesn't need to be included.


---


