#include "unit.h"

using namespace Firebolt::AcknowledgeChallenge;

struct AcknowledgeChallengeProvider : public IAcknowledgeChallengeProvider
{
    AcknowledgeChallengeProvider();
    ~AcknowledgeChallengeProvider() override = default;
    GrantResult challenge(const AcknowledgeChallengeParameters &parameters) override;
};

class AcknowledgeChallengeTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    AcknowledgeChallengeProvider _acknowledgeChallengeProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

AcknowledgeChallengeProvider::AcknowledgeChallengeProvider()
{
}

GrantResult AcknowledgeChallengeProvider::challenge(const AcknowledgeChallengeParameters &parameters)
{
    std::cout << "AcknowledgeChallengeProvider challenge is invoked" << std::endl;
    return { true };
}

TEST_F(AcknowledgeChallengeTest, registerAcknowledgeChallengeProvider)
{
    Firebolt::IFireboltAccessor::Instance().AcknowledgeChallengeInterface().provide(_acknowledgeChallengeProvider);
}
