$version: "2"
namespace com.firebolt.localization

use com.firebolt#capability
use com.firebolt#property
use com.firebolt#propertyReadonly

service LocalizationService {
    version: "1.0"
    operations: [locality, postalCode, countryCode, language, preferredAudioLanguages, locale, latlon, additionalInfo, addAdditionalInfo, removeAdditionalInfo, timeZone, country, presentationLanguage]
}

@capability(uses: ["xrn:firebolt:capability:localization:locality"])
@property
operation locality {
    input: LocalityInput
    output: LocalityOutput
}

structure LocalityInput {
}

structure LocalityOutput {
    @required
    value: Locality
}

@capability(uses: ["xrn:firebolt:capability:localization:postal-code"])
@property
operation postalCode {
    input: PostalCodeInput
    output: PostalCodeOutput
}

structure PostalCodeInput {
}

structure PostalCodeOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:localization:country-code"])
@property
operation countryCode {
    input: CountryCodeInput
    output: CountryCodeOutput
}

structure CountryCodeInput {
}

structure CountryCodeOutput {
    @required
    value: CountryCode
}

@capability(uses: ["xrn:firebolt:capability:localization:language"])
@property
operation language {
    input: LanguageInput
    output: LanguageOutput
}

structure LanguageInput {
}

structure LanguageOutput {
    @required
    value: Language
}

@capability(uses: ["xrn:firebolt:capability:localization:language"])
@property
operation preferredAudioLanguages {
    input: PreferredAudioLanguagesInput
    output: PreferredAudioLanguagesOutput
}

structure PreferredAudioLanguagesInput {
}

structure PreferredAudioLanguagesOutput {
    @required
    value: ISO639_2LanguageList
}

@capability(uses: ["xrn:firebolt:capability:localization:locale"])
@property
operation locale {
    input: LocaleInput
    output: LocaleOutput
}

structure LocaleInput {
}

structure LocaleOutput {
    @required
    value: Locale
}

@capability(uses: ["xrn:firebolt:capability:localization:location"])
operation latlon {
    input: LatlonInput
    output: LatlonOutput
}

structure LatlonInput {
}

structure LatlonOutput {
    @required
    value: DoubleList
}

@capability(uses: ["xrn:firebolt:capability:localization:additional-info"])
operation additionalInfo {
    input: AdditionalInfoInput
    output: AdditionalInfoOutput
}

structure AdditionalInfoInput {
}

structure AdditionalInfoOutput {
    @required
    value: StringMap
}

@capability(manages: ["xrn:firebolt:capability:localization:additional-info"])
operation addAdditionalInfo {
    input: AddAdditionalInfoInput
    output: AddAdditionalInfoOutput
}

structure AddAdditionalInfoInput {
    @required
    key: String
    @required
    value: Double
}

structure AddAdditionalInfoOutput {}

@capability(manages: ["xrn:firebolt:capability:localization:additional-info"])
operation removeAdditionalInfo {
    input: RemoveAdditionalInfoInput
    output: RemoveAdditionalInfoOutput
}

structure RemoveAdditionalInfoInput {
    @required
    key: String
}

structure RemoveAdditionalInfoOutput {}

@capability(uses: ["xrn:firebolt:capability:localization:time-zone"])
@property
operation timeZone {
    input: TimeZoneInput
    output: TimeZoneOutput
}

structure TimeZoneInput {
}

structure TimeZoneOutput {
    @required
    value: TimeZone
}

@propertyReadonly
operation country {
    input: CountryInput
    output: CountryOutput
}

structure CountryInput {
}

structure CountryOutput {
    @required
    value: CountryCode
}

@propertyReadonly
operation presentationLanguage {
    input: PresentationLanguageInput
    output: PresentationLanguageOutput
}

structure PresentationLanguageInput {
}

structure PresentationLanguageOutput {
    @required
    value: Locale
}

// TODO: alias CountryCode = String (Smithy has no direct alias — use a newtype structure or inline the target)

// TODO: alias ISO639_2Language = String (Smithy has no direct alias — use a newtype structure or inline the target)

// TODO: alias Language = String (Smithy has no direct alias — use a newtype structure or inline the target)

// TODO: alias Locale = String (Smithy has no direct alias — use a newtype structure or inline the target)

// TODO: alias Locality = String (Smithy has no direct alias — use a newtype structure or inline the target)

// TODO: alias TimeZone = String (Smithy has no direct alias — use a newtype structure or inline the target)

list ISO639_2LanguageList {
    member: ISO639_2Language
}

list DoubleList {
    member: Double
}

map StringMap {
    key: String
    value: String
}
