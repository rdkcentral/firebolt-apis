#include "localization_impl.h"
#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

using namespace testing;

class LocalizationMockTest : public ::testing::Test
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

TEST_F(LocalizationMockTest, AdditionalInfo_Success)
{
    Firebolt::Localization::JsonData_Info mockResponse;
    mockResponse.FromString(R"({"timezone": "PST", "currency": "USD"})");

    EXPECT_CALL(*gm->mockGateway, Request("localization.additionalInfo", _, testing::Matcher<Firebolt::Localization::JsonData_Info &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    auto info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(info["timezone"], "PST");
    EXPECT_EQ(info["currency"], "USD");
}

TEST_F(LocalizationMockTest, AdditionalInfo_Failure)
{
    EXPECT_CALL(*gm->mockGateway, Request("localization.additionalInfo", _, testing::Matcher<Firebolt::Localization::JsonData_Info &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    auto info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(info.empty());
}

TEST_F(LocalizationMockTest, CountryCode_Success)
{
    FireboltSDK::JSON::String mockResponse = "US";

    EXPECT_CALL(*pm->mockProperties, Get("localization.countryCode", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "US");
}

TEST_F(LocalizationMockTest, CountryCode_Failure)
{
    EXPECT_CALL(*pm->mockProperties, Get("localization.countryCode", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(LocalizationMockTest, Language_Success)
{
    FireboltSDK::JSON::String mockResponse = "en";

    EXPECT_CALL(*pm->mockProperties, Get("localization.language", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().language(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "en");
}

TEST_F(LocalizationMockTest, Language_Failure)
{
    EXPECT_CALL(*pm->mockProperties, Get("localization.language", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().language(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(LocalizationMockTest, PostalCode_Success)
{
    FireboltSDK::JSON::String mockResponse = "12345";

    EXPECT_CALL(*pm->mockProperties, Get("localization.postalCode", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Error error;
    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().postalCode(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(result, "12345");
}

TEST_F(LocalizationMockTest, PostalCode_Failure)
{
    EXPECT_CALL(*pm->mockProperties, Get("localization.postalCode", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Error error;
    std::string result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().postalCode(&error);

    EXPECT_EQ(error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}