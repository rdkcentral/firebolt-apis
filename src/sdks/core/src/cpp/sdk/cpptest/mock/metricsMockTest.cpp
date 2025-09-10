#include "metrics_impl.h"
#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gateway/Gateway.h"
#include "mockGateway.h"

using namespace testing;

class MetricsMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<GatewayMockTest> gm;

    void SetUp() override
    {
        gm = std::make_unique<GatewayMockTest>();
        gm->SetUp();
    }

    void TearDown() override
    {
        gm->TearDown();
        gm.reset(); // Cleanup
    }
};

TEST_F(MetricsMockTest, Ready_Success) {
    Firebolt::Error error;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.ready", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, Ready_Failure) {
    Firebolt::Error error;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.ready", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}

TEST_F(MetricsMockTest, SignIn_Success) {
    Firebolt::Error error;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.signIn", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signIn(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, SignIn_Failure) {
    Firebolt::Error error;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.signIn", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signIn(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::Timedout);
    EXPECT_FALSE(result);
}


TEST_F(MetricsMockTest, SignOut_Success) {
    Firebolt::Error error;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.signOut", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signOut(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, SignOut_Failure) {
    Firebolt::Error error;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.signOut", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signOut(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::Timedout);
    EXPECT_FALSE(result);
}

TEST_F(MetricsMockTest, Action_Success) {
    Firebolt::Error error;
    Firebolt::Metrics::Category category = Firebolt::Metrics::Category::USER;
    std::string type = "someType";
    std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.action", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().action(category, type, parameters, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, Error_Success) {
    Firebolt::Error error;
    Firebolt::Metrics::ErrorType type = Firebolt::Metrics::ErrorType::MEDIA;
    std::string code = "ERROR_CODE";
    std::string description = "Error description";
    bool visible = true;
    std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.error", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().error(type, code, description, visible, parameters, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, MediaEnded_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity123";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaEnded", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaEnded(entityId, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, MediaLoadStart_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity123";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaLoadStart", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaLoadStart(entityId, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, MediaPause_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity456";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaPause", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPause(entityId, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, MediaPlay_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity123";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaPlay", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlay(entityId, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, MediaPlaying_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity456";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaPlaying", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlaying(entityId, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, MediaProgress_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity123";
    std::string progress = "50%";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaProgress", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaProgress(entityId, progress, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, MediaRateChange_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity456";
    float rate = 1.5f;

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaRateChange", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRateChange(entityId, rate, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, MediaRenditionChange_Success) {
    Firebolt::Error error;
    std::string entityId = "mediaEntity789";
    float bitrate = 5000.0f;
    float width = 1920.0f;
    float height = 1080.0f;
    std::optional<std::string> profile = "HD";

    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.mediaRenditionChange", _, testing::Matcher<WPEFramework::Core::JSON::Boolean&>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRenditionChange(entityId, bitrate, width, height, profile, &error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}


TEST_F(MetricsMockTest, StartContent_Success) {
    std::optional<std::string> entityId = "testEntity";
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.startContent", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent(entityId, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, StartContent_Failure) {
    std::optional<std::string> entityId = "testEntity";

    EXPECT_CALL(*gm->mockGateway, Request("metrics.startContent", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent(entityId, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_FALSE(result);
}

TEST_F(MetricsMockTest, StopContent_Success) {
    std::optional<std::string> entityId = "testEntity";
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("metrics.stopContent", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent(entityId, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(MetricsMockTest, StopContent_Failure) {
    std::optional<std::string> entityId = "testEntity";

    EXPECT_CALL(*gm->mockGateway, Request("metrics.stopContent", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    bool result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent(entityId, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_FALSE(result);
}
