# Language Settings

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Jeremy LaCivita            | Comcast            |
| Kevin Pearson            | Comcast            |
| Tim Dibben            | Sky            |

## 1. Overview

This document describes the requirements that Firebolt platforms must
fulfill when surfacing user language preferences.

Exposing these settings, e.g. the main device language, or a list of
preferred audio languages, allows Apps to respect the device's current
setting so that the user has a seamless experience when switching from
app to app.

This document covers how Firebolt platforms manage language settings and
expose to Apps. It does not cover the use cases Apps might apply these
APIs to.

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

- [1. Overview](#1-overview)
- [2. Language](#2-language)
- [3. Locale](#3-locale)
- [4. Preferred Audio Languages](#4-preferred-audio-languages)
- [5. Core SDK APIs](#5-core-sdk-apis)
- [6. Manage SDK APIs](#6-manage-sdk-apis)

## 2. Language

Language describes the ISO 639 1/2 code for the preferred language on
this device. All Apps **SHOULD** generally render their user experience
in this language. This is a guideline, not an absolute requirement,
since different Apps may have different target audiences with differing
languages prevalent within those audiences.

This setting is represented by a mutable property which is a string
conforming to the ISO 639 1/2 standard, e.g. `'en'`.

## 3. Locale

Locale describes the *full* BCP 47 code, including script, region,
variant, etc., for the preferred language/locale on this device. Apps
**MAY** alter their user experience to match this locale to account for
local differences in the same language.

This setting is represented by a mutable property which is a string
conforming to the full BCP 47 standard, e.g. `'en-US'`.

## 4. Preferred Audio Languages

The preferred audio languages setting provides a ranked list of
languages that the user prefers to be selected on this device. All
values are from the ISO 639 1/2 standard. Apps **MAY** use this list to
influence selection of an initial audio track when playing content with
multiple languages. For example, a bilingual user living in an English
speaking country may have the `language` set to `'en`\' and the
`preferredAudioLanguages` set to `['fr', 'en']`. This
enables them to typically consume content from apps whose catalogs are
mostly filmed in English, but automatically get the French language
track when watching a French movie that has both French and English
tracks.

This setting is represented by a mutable property which is an array of
strings conforming to the ISO 639 1/2 standard, e.g. `'en'`.

## 5. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`core:localization` domain/module.

Each of these APIs a read-only property.

-   `Localization.language():Promise<string>`

-   `Localization.locale():Promise<string>`

-   `Localization.preferredAudioLanguages():Promise<string[]>`

-   `Localization.onLanguageChanged():Promise<string>`

-   `Localization.onLocaleChanged():Promise<string>`

-   `Localization.onPreferredAudioLanguagesChanged():Promise<string[]>`

## 6. Manage SDK APIs

The following APIs are exposed by the Firebolt Manage SDK as part of the
`manage` domain.

The Manage SDK APIs inclueare identical to the Core SDK, except that all
property APIs are mutable.
