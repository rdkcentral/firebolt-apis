#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "accessibility_impl.h"
#include "../unit/unit.h"
#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

using namespace testing;

class AccessibilityMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<GatewayMockTest> gm;
    std::unique_ptr<PropertiesMockTest> pm;

    void SetUp() override
    {
        gm = std::make_unique<GatewayMockTest>();
        gm->SetUp();

        pm = std::make_unique<PropertiesMockTest>();
        pm->SetUp();
    }

    void TearDown() override
    {
        gm->TearDown();
        gm.reset(); // Cleanup

        pm->TearDown();
        pm.reset(); // Cleanup
    }
};

TEST_F(AccessibilityMockTest, AudioDescriptionSettings_Success) {
    Firebolt::Accessibility::JsonData_AudioDescriptionSettings mockResponse;
    mockResponse.Enabled = true;
    
    EXPECT_CALL(*pm->mockProperties, Get("accessibility.audioDescriptionSettings", testing::Matcher<Firebolt::Accessibility::JsonData_AudioDescriptionSettings &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    Firebolt::Accessibility::AudioDescriptionSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().audioDescriptionSettings(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(settings.enabled);
}

TEST_F(AccessibilityMockTest, AudioDescriptionSettings_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("accessibility.audioDescriptionSettings", testing::Matcher<Firebolt::Accessibility::JsonData_AudioDescriptionSettings &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    Firebolt::Accessibility::AudioDescriptionSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().audioDescriptionSettings(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(settings.enabled);
}

TEST_F(AccessibilityMockTest, ClosedCaptions_Success) {
    Firebolt::Accessibility::JsonData_ClosedCaptionsSettings mockResponse;
    mockResponse.Enabled = true;
    mockResponse.Styles.FontSize = 1.0f;
    
    EXPECT_CALL(*gm->mockGateway, Request("accessibility.closedCaptions", _, testing::Matcher<Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));
    
    Firebolt::Accessibility::ClosedCaptionsSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptions(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(settings.enabled);
    EXPECT_EQ(settings.styles->fontSize, 1.0f);
}

TEST_F(AccessibilityMockTest, ClosedCaptions_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("accessibility.closedCaptions", _, testing::Matcher<Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));
    
    Firebolt::Accessibility::ClosedCaptionsSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptions(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::Timedout);
    EXPECT_FALSE(settings.enabled);
}

TEST_F(AccessibilityMockTest, ClosedCaptionsSettings_Success) {
    Firebolt::Accessibility::JsonData_ClosedCaptionsSettings mockResponse;
    mockResponse.Enabled = true;
    mockResponse.Styles.FontFamily = Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF;
    mockResponse.Styles.FontSize = 1.5f;
    mockResponse.Styles.FontColor = "#FFFFFF";

    EXPECT_CALL(*pm->mockProperties, Get("accessibility.closedCaptionsSettings", testing::Matcher<Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Accessibility::ClosedCaptionsSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(settings.enabled);
    ASSERT_TRUE(settings.styles.has_value());
    EXPECT_EQ(settings.styles->fontFamily, Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF);
    EXPECT_EQ(settings.styles->fontSize, 1.5f);
    EXPECT_EQ(settings.styles->fontColor, "#FFFFFF");
}

TEST_F(AccessibilityMockTest, ClosedCaptionsSettings_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("accessibility.closedCaptionsSettings", testing::Matcher<Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Accessibility::ClosedCaptionsSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_FALSE(settings.enabled);
    EXPECT_FALSE(settings.styles.has_value());
}

TEST_F(AccessibilityMockTest, VoiceGuidance_Success) {
    Firebolt::Accessibility::JsonData_VoiceGuidanceSettings mockResponse;
    mockResponse.Enabled = true;
    mockResponse.Speed = 2.0f;

    EXPECT_CALL(*gm->mockGateway, Request("accessibility.voiceGuidance", _, testing::Matcher<Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Accessibility::VoiceGuidanceSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidance(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(settings.enabled);
    EXPECT_EQ(settings.speed, 2.0f);
}

// TEST_F(AccessibilityMockTest, VoiceGuidance_Failure) {
//     EXPECT_CALL(*gm->mockGateway, Request("accessibility.voiceGuidance", _, testing::Matcher<Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &>(_)))
//         .WillOnce(Return(Firebolt::Error::NotConnected));

//     Firebolt::Accessibility::VoiceGuidanceSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidance(&gm->error);

//     EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
//     EXPECT_FALSE(settings.enabled);
//     EXPECT_EQ(settings.speed, 0);
// }

TEST_F(AccessibilityMockTest, VoiceGuidanceSettings_Success) {
    Firebolt::Accessibility::JsonData_VoiceGuidanceSettings mockResponse;
    mockResponse.Enabled = true;
    mockResponse.Speed = 1.5f;

    EXPECT_CALL(*pm->mockProperties, Get("accessibility.voiceGuidanceSettings", testing::Matcher<Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Accessibility::VoiceGuidanceSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidanceSettings(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(settings.enabled);
    EXPECT_EQ(settings.speed, 1.5f);
}

// TEST_F(AccessibilityMockTest, VoiceGuidanceSettings_Failure) {
//     EXPECT_CALL(*pm->mockProperties, Get("accessibility.voiceGuidanceSettings", testing::Matcher<Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &>(_)))
//         .WillOnce(Return(Firebolt::Error::General));

//     Firebolt::Accessibility::VoiceGuidanceSettings settings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidanceSettings(&pm->error);

//     EXPECT_EQ(pm->error, Firebolt::Error::General);
//     EXPECT_FALSE(settings.enabled);
//     EXPECT_FALSE(settings.speed.has_vlaue());
// }
