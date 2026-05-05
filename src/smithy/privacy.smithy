$version: "2"
namespace com.firebolt.privacy

use com.firebolt#property

service PrivacyService {
    version: "1.0"
    operations: [allowResumePoints, allowUnentitledResumePoints, allowWatchHistory, allowProductAnalytics, allowPersonalization, allowUnentitledPersonalization, allowRemoteDiagnostics, allowPrimaryContentAdTargeting, allowPrimaryBrowseAdTargeting, allowAppContentAdTargeting, allowACRCollection, allowCameraAnalytics, settings]
}

@property
operation allowResumePoints {
    input: AllowResumePointsInput
    output: AllowResumePointsOutput
}

structure AllowResumePointsInput {
}

structure AllowResumePointsOutput {
    @required
    value: Boolean
}

@property
operation allowUnentitledResumePoints {
    input: AllowUnentitledResumePointsInput
    output: AllowUnentitledResumePointsOutput
}

structure AllowUnentitledResumePointsInput {
}

structure AllowUnentitledResumePointsOutput {
    @required
    value: Boolean
}

@property
operation allowWatchHistory {
    input: AllowWatchHistoryInput
    output: AllowWatchHistoryOutput
}

structure AllowWatchHistoryInput {
}

structure AllowWatchHistoryOutput {
    @required
    value: Boolean
}

@property
operation allowProductAnalytics {
    input: AllowProductAnalyticsInput
    output: AllowProductAnalyticsOutput
}

structure AllowProductAnalyticsInput {
}

structure AllowProductAnalyticsOutput {
    @required
    value: Boolean
}

@property
operation allowPersonalization {
    input: AllowPersonalizationInput
    output: AllowPersonalizationOutput
}

structure AllowPersonalizationInput {
}

structure AllowPersonalizationOutput {
    @required
    value: Boolean
}

@property
operation allowUnentitledPersonalization {
    input: AllowUnentitledPersonalizationInput
    output: AllowUnentitledPersonalizationOutput
}

structure AllowUnentitledPersonalizationInput {
}

structure AllowUnentitledPersonalizationOutput {
    @required
    value: Boolean
}

@property
operation allowRemoteDiagnostics {
    input: AllowRemoteDiagnosticsInput
    output: AllowRemoteDiagnosticsOutput
}

structure AllowRemoteDiagnosticsInput {
}

structure AllowRemoteDiagnosticsOutput {
    @required
    value: Boolean
}

@property
operation allowPrimaryContentAdTargeting {
    input: AllowPrimaryContentAdTargetingInput
    output: AllowPrimaryContentAdTargetingOutput
}

structure AllowPrimaryContentAdTargetingInput {
}

structure AllowPrimaryContentAdTargetingOutput {
    @required
    value: Boolean
}

@property
operation allowPrimaryBrowseAdTargeting {
    input: AllowPrimaryBrowseAdTargetingInput
    output: AllowPrimaryBrowseAdTargetingOutput
}

structure AllowPrimaryBrowseAdTargetingInput {
}

structure AllowPrimaryBrowseAdTargetingOutput {
    @required
    value: Boolean
}

@property
operation allowAppContentAdTargeting {
    input: AllowAppContentAdTargetingInput
    output: AllowAppContentAdTargetingOutput
}

structure AllowAppContentAdTargetingInput {
}

structure AllowAppContentAdTargetingOutput {
    @required
    value: Boolean
}

@property
operation allowACRCollection {
    input: AllowACRCollectionInput
    output: AllowACRCollectionOutput
}

structure AllowACRCollectionInput {
}

structure AllowACRCollectionOutput {
    @required
    value: Boolean
}

@property
operation allowCameraAnalytics {
    input: AllowCameraAnalyticsInput
    output: AllowCameraAnalyticsOutput
}

structure AllowCameraAnalyticsInput {
}

structure AllowCameraAnalyticsOutput {
    @required
    value: Boolean
}

operation settings {
    input: SettingsInput
    output: SettingsOutput
}

structure SettingsInput {
}

structure SettingsOutput {
    @required
    value: PrivacySettings
}

structure PrivacySettings {
    @required
    allowACRCollection: Boolean
    @required
    allowAppContentAdTargeting: Boolean
    @required
    allowCameraAnalytics: Boolean
    @required
    allowPersonalization: Boolean
    @required
    allowPrimaryBrowseAdTargeting: Boolean
    @required
    allowPrimaryContentAdTargeting: Boolean
    @required
    allowProductAnalytics: Boolean
    @required
    allowRemoteDiagnostics: Boolean
    @required
    allowResumePoints: Boolean
    @required
    allowUnentitledPersonalization: Boolean
    @required
    allowUnentitledResumePoints: Boolean
    @required
    allowWatchHistory: Boolean
}
