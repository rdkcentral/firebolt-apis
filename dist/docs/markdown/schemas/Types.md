---
title: Types
---
# Types Schema
---
Version 0.8.0


## JSON-Schema
This document was generated from a JSON-Schema, and is intended to provide a human readable overview and examples of the methods contained in the module.

For the full schema, see the link below.

| Schema |
|--------|
| [types.json](https://github.com/rdkcentral/firebolt-openrpc/blob/feature/badger-parity/src/schemas/types.json) |

## Table of Contents
 
 - Schemas
    - [SemanticVersion](#semanticversion)
    - [AudioProfile](#audioprofile)
    - [BooleanMap](#booleanmap)
    - [FlatMap](#flatmap)
    - [LocalizedString](#localizedstring)
    - [ListenResponse](#listenresponse)
    - [ProviderRequest](#providerrequest)
    - [ProviderResponse](#providerresponse)
    - [Timeout](#timeout)


## Schemas

### SemanticVersion

```typescript
type SemanticVersion = {
  major: number
  minor: number
  patch: number
  readable: string
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### AudioProfile

```typescript
type AudioProfile = 'stereo' | 'dolbyDigital5.1' | 'dolbyDigital7.1' | 'dolbyDigital5.1+' | 'dolbyDigital7.1+' | 'dolbyAtmos'
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### BooleanMap

```typescript
type BooleanMap = {
  [property: string]: boolean
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### FlatMap

```typescript
type FlatMap = {
  [property: string]: string | number | boolean
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### LocalizedString

```typescript
type LocalizedString = string | object
```




<details>
  <summary><b>Examples</b></summary>

```json
"A simple string, with no language code"

{
  "en": "This is english",
  "es": "esto es español"
}
```

</details>


#### Details

Localized string supports either a simple `string` or a Map<string, string> of language codes to strings. When using a simple `string`, the current preferred langauge from `Localization.langauge()` is assumed.


---

### ListenResponse

```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### ProviderRequest

```typescript
type ProviderRequest = {
  correlationId: string   // The id that was passed in to the event that triggered a provider method to be called
  parameters?: object     // The result of the provider response.
}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### ProviderResponse

```typescript
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>




---

### Timeout

```typescript
type Timeout = number
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

Defines the timeout in seconds. If the threshold for timeout is passed for any operation without a result it will throw an error.


---


