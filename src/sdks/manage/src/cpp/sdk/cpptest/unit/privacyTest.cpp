#include "unit.h"

class PrivacyTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct AllowACRCollectionSettings : public Firebolt::Privacy::IPrivacy::IOnAllowACRCollectionChangedNotification {
    void onAllowACRCollectionChanged(const bool) override;
};

void AllowACRCollectionSettings::onAllowACRCollectionChanged(const bool isAllowed) {
    std::cout << "onAllowACRCollectionChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowACRCollectionChanged) {
    AllowACRCollectionSettings allowACRCollectionSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowACRCollectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowACRCollectionSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowACRCollectionChanged) {
    AllowACRCollectionSettings allowACRCollectionSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowACRCollectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowACRCollectionSettings";
}

struct AllowAppContentAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowAppContentAdTargetingChangedNotification {
    void onAllowAppContentAdTargetingChanged(const bool) override;
};

void AllowAppContentAdTargetingSettings::onAllowAppContentAdTargetingChanged(const bool isAllowed) {
    std::cout << "onAllowAppContentAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowAppContentAdTargetingChanged) {
    AllowAppContentAdTargetingSettings allowAppContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowAppContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowAppContentAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowAppContentAdTargetingChanged) {
    AllowAppContentAdTargetingSettings allowAppContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowAppContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowAppContentAdTargetingSettings";
}

struct AllowCameraAnalyticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowCameraAnalyticsChangedNotification {
    void onAllowCameraAnalyticsChanged(const bool) override;
};

void AllowCameraAnalyticsSettings::onAllowCameraAnalyticsChanged(const bool isAllowed) {
    std::cout << "onAllowCameraAnalyticsChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowCameraAnalyticsChanged) {
    AllowCameraAnalyticsSettings allowCameraAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowCameraAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowCameraAnalyticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowCameraAnalyticsChanged) {
    AllowCameraAnalyticsSettings allowCameraAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowCameraAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowCameraAnalyticsSettings";
}

struct AllowPersonalizationSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPersonalizationChangedNotification {
    void onAllowPersonalizationChanged(const bool) override;
};

void AllowPersonalizationSettings::onAllowPersonalizationChanged(const bool isAllowed) {
    std::cout << "onAllowPersonalizationChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPersonalizationChanged) {
    AllowPersonalizationSettings allowPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPersonalizationSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPersonalizationChanged) {
    AllowPersonalizationSettings allowPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPersonalizationSettings";
}

struct AllowPrimaryBrowseAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPrimaryBrowseAdTargetingChangedNotification {
    void onAllowPrimaryBrowseAdTargetingChanged(const bool) override;
};

void AllowPrimaryBrowseAdTargetingSettings::onAllowPrimaryBrowseAdTargetingChanged(const bool isAllowed) {
    std::cout << "onAllowPrimaryBrowseAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPrimaryBrowseAdTargetingChanged) {
    AllowPrimaryBrowseAdTargetingSettings allowPrimaryBrowseAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPrimaryBrowseAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPrimaryBrowseAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPrimaryBrowseAdTargetingChanged) {
    AllowPrimaryBrowseAdTargetingSettings allowPrimaryBrowseAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPrimaryBrowseAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPrimaryBrowseAdTargetingSettings";
}

struct AllowPrimaryContentAdTargetingSettings : public Firebolt::Privacy::IPrivacy::IOnAllowPrimaryContentAdTargetingChangedNotification {
    void onAllowPrimaryContentAdTargetingChanged(const bool) override;
};

void AllowPrimaryContentAdTargetingSettings::onAllowPrimaryContentAdTargetingChanged(const bool isAllowed) {
    std::cout << "onAllowPrimaryContentAdTargetingChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowPrimaryContentAdTargetingChanged) {
    AllowPrimaryContentAdTargetingSettings allowPrimaryContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowPrimaryContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowPrimaryContentAdTargetingSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowPrimaryContentAdTargetingChanged) {
    AllowPrimaryContentAdTargetingSettings allowPrimaryContentAdTargetingSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowPrimaryContentAdTargetingSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowPrimaryContentAdTargetingSettings";
}

struct AllowProductAnalyticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowProductAnalyticsChangedNotification {
    void onAllowProductAnalyticsChanged(const bool) override;
};

void AllowProductAnalyticsSettings::onAllowProductAnalyticsChanged(const bool isAllowed) {
    std::cout << "onAllowProductAnalyticsChanged event fired";
}

TEST_F(PrivacyTest, subscribeOnAllowProductAnalyticsChanged) {
    AllowProductAnalyticsSettings allowProductAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowProductAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowProductAnalyticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowProductAnalyticsChanged) {
    AllowProductAnalyticsSettings allowProductAnalyticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowProductAnalyticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowProductAnalyticsSettings";
}

struct AllowRemoteDiagnosticsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowRemoteDiagnosticsChangedNotification {
    void onAllowRemoteDiagnosticsChanged(const bool) override;
};

void AllowRemoteDiagnosticsSettings::onAllowRemoteDiagnosticsChanged(const bool isAllowed) {
    std::cout << "onAllowRemoteDiagnosticsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowRemoteDiagnosticsChanged) {
    AllowRemoteDiagnosticsSettings allowRemoteDiagnosticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowRemoteDiagnosticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowRemoteDiagnosticsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowRemoteDiagnosticsChanged) {
    AllowRemoteDiagnosticsSettings allowRemoteDiagnosticsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowRemoteDiagnosticsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowRemoteDiagnosticsSettings";
}

struct AllowResumePointsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowResumePointsChangedNotification {
    void onAllowResumePointsChanged(const bool) override;
};

void AllowResumePointsSettings::onAllowResumePointsChanged(const bool isAllowed) {
    std::cout << "onAllowResumePointsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowResumePointsChanged) {
    AllowResumePointsSettings allowResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowResumePointsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowResumePointsChanged) {
    AllowResumePointsSettings allowResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowResumePointsSettings";
}

struct AllowUnentitledPersonalizationSettings : public Firebolt::Privacy::IPrivacy::IOnAllowUnentitledPersonalizationChangedNotification {
    void onAllowUnentitledPersonalizationChanged(const bool) override;
};

void AllowUnentitledPersonalizationSettings::onAllowUnentitledPersonalizationChanged(const bool isAllowed) {
    std::cout << "onAllowUnentitledPersonalizationChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowUnentitledPersonalizationChanged) {
    AllowUnentitledPersonalizationSettings allowUnentitledPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowUnentitledPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowUnentitledPersonalizationSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowUnentitledPersonalizationChanged) {
    AllowUnentitledPersonalizationSettings allowUnentitledPersonalizationSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowUnentitledPersonalizationSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowUnentitledPersonalizationSettings";
}

struct AllowUnentitledResumePointsSettings : public Firebolt::Privacy::IPrivacy::IOnAllowUnentitledResumePointsChangedNotification {
    void onAllowUnentitledResumePointsChanged(const bool) override;
};

void AllowUnentitledResumePointsSettings::onAllowUnentitledResumePointsChanged(const bool isAllowed) {
    std::cout << "onAllowUnentitledResumePointsChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowUnentitledResumePointsChanged) {
    AllowUnentitledResumePointsSettings allowUnentitledResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowUnentitledResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowUnentitledResumePointsSettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowUnentitledResumePointsChanged) {
    AllowUnentitledResumePointsSettings allowUnentitledResumePointsSettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowUnentitledResumePointsSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowUnentitledResumePointsSettings";
}

struct AllowWatchHistorySettings : public Firebolt::Privacy::IPrivacy::IOnAllowWatchHistoryChangedNotification {
    void onAllowWatchHistoryChanged(const bool) override;
};

void AllowWatchHistorySettings::onAllowWatchHistoryChanged(const bool isAllowed) {
    std::cout << "onAllowWatchHistoryChanged event fired with isAllowed: " << isAllowed;
}

TEST_F(PrivacyTest, subscribeOnAllowWatchHistoryChanged) {
    AllowWatchHistorySettings allowWatchHistorySettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(allowWatchHistorySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AllowWatchHistorySettings";
}

TEST_F(PrivacyTest, unsubscribeOnAllowWatchHistoryChanged) {
    AllowWatchHistorySettings allowWatchHistorySettings;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(allowWatchHistorySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AllowWatchHistorySettings";
}
