#include "unit.h"

class AudioDescriptionsTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};


struct EnabledChanged : public Firebolt::AudioDescriptions::IAudioDescriptions::IOnEnabledChangedNotification
{
    void onEnabledChanged( const bool ) override; 
};


void EnabledChanged::onEnabledChanged(const bool)
{
    std::cout << "onAudioDescriptionEnabledChanged event fired";
}


TEST_F(AudioDescriptionsTest, subscribeonEnabledChanged)
{
    EnabledChanged enabledChanged;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().subscribe(enabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledChanged";
}

TEST_F(AudioDescriptionsTest, unsubscribeonEnabledChanged)
{
    EnabledChanged enabledChanged;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().unsubscribe(enabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledChanged";
}