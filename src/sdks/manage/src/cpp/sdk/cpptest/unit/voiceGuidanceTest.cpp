#include "unit.h"

class VoiceGuidanceTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct EnabledSettings : public Firebolt::VoiceGuidance::IVoiceGuidance::IOnEnabledChangedNotification {
    void onEnabledChanged(const bool) override;
};

void EnabledSettings::onEnabledChanged(const bool isEnabled) {
    std::cout << "onEnabledChanged event fired with isEnabled: " << isEnabled;
}

TEST_F(VoiceGuidanceTest, subscribeOnEnabledChanged) {
    EnabledSettings enabledSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().subscribe(enabledSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledSettings";
}

TEST_F(VoiceGuidanceTest, unsubscribeOnEnabledChanged) {
    EnabledSettings enabledSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().unsubscribe(enabledSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledSettings";
}

struct SpeedSettings : public Firebolt::VoiceGuidance::IVoiceGuidance::IOnSpeedChangedNotification {
    void onSpeedChanged(const float) override;
};

void SpeedSettings::onSpeedChanged(const float speed) {
    std::cout << "onSpeedChanged event fired with speed: " << speed;
}

TEST_F(VoiceGuidanceTest, subscribeOnSpeedChanged) {
    SpeedSettings speedSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().subscribe(speedSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SpeedSettings";
}

TEST_F(VoiceGuidanceTest, unsubscribeOnSpeedChanged) {
    SpeedSettings speedSettings;
    Firebolt::IFireboltAccessor::Instance().VoiceGuidanceInterface().unsubscribe(speedSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SpeedSettings";
}
