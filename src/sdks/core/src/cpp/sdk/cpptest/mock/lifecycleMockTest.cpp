#include "lifecycle_impl.h"
#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gateway/Gateway.h"
#include "mockGateway.h"

using namespace testing;

class LifecycleMockTest : public ::testing::Test
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


TEST_F(LifecycleMockTest, Close_Success) {
    Firebolt::Lifecycle::CloseReason reason = Firebolt::Lifecycle::CloseReason::USER_EXIT;
    EXPECT_CALL(*gm->mockGateway, Request("lifecycle.close", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::None));

    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(reason, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
}

TEST_F(LifecycleMockTest, Close_Failure) {
    Firebolt::Lifecycle::CloseReason reason = Firebolt::Lifecycle::CloseReason::USER_EXIT;
    EXPECT_CALL(*gm->mockGateway, Request("lifecycle.close", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(reason, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
}
