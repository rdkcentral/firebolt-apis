#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "device_impl.h"
#include "../unit/unit.h"
#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

using namespace testing;

class DeviceMockTest : public ::testing::Test
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

TEST_F(DeviceMockTest, Version_Success) {
    Firebolt::Device::JsonData_DeviceVersion mockResponse;
    mockResponse.Sdk.Readable = "Firebolt Core SDK 1.2.3";
    EXPECT_CALL(*gm->mockGateway, Request("device.version", _, testing::Matcher<Firebolt::Device::JsonData_DeviceVersion &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version(&gm->error);
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "Firebolt Core SDK 1.2.3");
}

TEST_F(DeviceMockTest, Version_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("device.version", _, testing::Matcher<Firebolt::Device::JsonData_DeviceVersion &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version(&gm->error);
    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(result.empty());
}

TEST_F(DeviceMockTest, Audio_Success) {
    Firebolt::Device::JsonData_AudioProfiles mockResponse;
    mockResponse.Stereo = true;
    mockResponse.DolbyDigital5_1 = false;
    mockResponse.DolbyDigital5_1_plus = true;
    mockResponse.DolbyAtmos = false;
    EXPECT_CALL(*pm->mockProperties, Get("device.audio", testing::Matcher<Firebolt::Device::JsonData_AudioProfiles &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&pm->error);
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(result.stereo);
    EXPECT_FALSE(result.dolbyDigital5_1);
    EXPECT_TRUE(result.dolbyDigital5_1_plus);
    EXPECT_FALSE(result.dolbyAtmos);
}

TEST_F(DeviceMockTest, Audio_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.audio", testing::Matcher<Firebolt::Device::JsonData_AudioProfiles &>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));
    
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&pm->error);
    EXPECT_EQ(pm->error, Firebolt::Error::Timedout);
}

TEST_F(DeviceMockTest, Distributor_Success) {
    FireboltSDK::JSON::String mockResponse = "ValidDistributor";
    EXPECT_CALL(*pm->mockProperties, Get("device.distributor", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor(&pm->error);
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "ValidDistributor");
}

TEST_F(DeviceMockTest, Distributor_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.distributor", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor(&pm->error);
    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_TRUE(result.empty());
}

TEST_F(DeviceMockTest, Hdcp_Success) {
    Firebolt::Device::JsonData_HDCPVersionMap mockResponse;
    mockResponse.Hdcp1_4 = true;
    mockResponse.Hdcp2_2 = true;
    
    EXPECT_CALL(*pm->mockProperties, Get("device.hdcp", testing::Matcher<Firebolt::Device::JsonData_HDCPVersionMap &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    Firebolt::Device::HDCPVersionMap result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(result.hdcp1_4);
    EXPECT_TRUE(result.hdcp2_2);
}

TEST_F(DeviceMockTest, Hdcp_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.hdcp", testing::Matcher<Firebolt::Device::JsonData_HDCPVersionMap &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    
    Firebolt::Device::HDCPVersionMap result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_FALSE(result.hdcp1_4);
    EXPECT_FALSE(result.hdcp2_2);
}

TEST_F(DeviceMockTest, Hdr_Success) {
    Firebolt::Device::JsonData_HDRFormatMap mockResponse;
    mockResponse.Hdr10 = true;
    mockResponse.Hdr10Plus = false;
    mockResponse.DolbyVision = true;
    mockResponse.Hlg = false;
    
    EXPECT_CALL(*pm->mockProperties, Get("device.hdr", testing::Matcher<Firebolt::Device::JsonData_HDRFormatMap &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    Firebolt::Device::HDRFormatMap result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_TRUE(result.hdr10);
    EXPECT_FALSE(result.hdr10Plus);
    EXPECT_TRUE(result.dolbyVision);
    EXPECT_FALSE(result.hlg);
}

TEST_F(DeviceMockTest, Hdr_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.hdr", testing::Matcher<Firebolt::Device::JsonData_HDRFormatMap &>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));
    
    Firebolt::Device::HDRFormatMap result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::Timedout);
    EXPECT_FALSE(result.hdr10);
    EXPECT_FALSE(result.hdr10Plus);
    EXPECT_FALSE(result.dolbyVision);
    EXPECT_FALSE(result.hlg);
}

TEST_F(DeviceMockTest, Id_Success) {
    FireboltSDK::JSON::String mockResponse = "valid_device_id";
    EXPECT_CALL(*pm->mockProperties, Get("device.id", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "valid_device_id");
}

TEST_F(DeviceMockTest, Id_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.id", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(DeviceMockTest, Name_Success) {
    FireboltSDK::JSON::String mockResponse = "FireboltDevice";
    EXPECT_CALL(*pm->mockProperties, Get("device.name", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "FireboltDevice");
}

TEST_F(DeviceMockTest, Name_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.name", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::MethodNotFound));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::MethodNotFound);
    EXPECT_EQ(result, "");
}

TEST_F(DeviceMockTest, Model_Success) {
    FireboltSDK::JSON::String mockResponse = "FireboltModelX";
    EXPECT_CALL(*pm->mockProperties, Get("device.model", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "FireboltModelX");
}

TEST_F(DeviceMockTest, Model_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.model", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(DeviceMockTest, Make_Success) {
    FireboltSDK::JSON::String mockResponse = "ValidDeviceMake";
    EXPECT_CALL(*pm->mockProperties, Get("device.make", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "ValidDeviceMake");
}

TEST_F(DeviceMockTest, Make_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.make", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(DeviceMockTest, Network_Success) {
    Firebolt::Device::JsonData_NetworkInfoResult mockResponse;
    mockResponse.State = Firebolt::Device::NetworkState::CONNECTED;
    mockResponse.Type = Firebolt::Device::NetworkType::WIFI;
    
    EXPECT_CALL(*pm->mockProperties, Get("device.network", testing::Matcher<Firebolt::Device::JsonData_NetworkInfoResult &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Device::NetworkInfoResult result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result.state, Firebolt::Device::NetworkState::CONNECTED);
    EXPECT_EQ(result.type, Firebolt::Device::NetworkType::WIFI);
}

TEST_F(DeviceMockTest, Network_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.network", testing::Matcher<Firebolt::Device::JsonData_NetworkInfoResult &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    Firebolt::Device::NetworkInfoResult result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::NotConnected);
}

TEST_F(DeviceMockTest, Platform_Success) {
    FireboltSDK::JSON::String mockResponse = "ValidPlatformID";
    EXPECT_CALL(*pm->mockProperties, Get("device.platform", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "ValidPlatformID");
}

TEST_F(DeviceMockTest, Platform_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("device.platform", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));

    std::string result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::Timedout);
    EXPECT_EQ(result, "");
}
