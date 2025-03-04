#include "unit.h"

using namespace Firebolt::PinChallenge;

struct PinChallengeProvider : public IPinChallengeProvider
{
public:
    PinChallengeProvider();
    ~PinChallengeProvider() override = default;
    virtual PinChallengeResult challenge( const PinChallengeParameters& parameters) override;
};

class PinChallengeTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    PinChallengeProvider _pinChallengeProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

PinChallengeProvider::PinChallengeProvider()
{
}

PinChallengeResult PinChallengeProvider::challenge(const PinChallengeParameters &parameters)
{
    std::cout << "PinChallengeProvider challenge is invoked" << std::endl;
    Firebolt::PinChallenge::PinChallengeResult r{true, ResultReason::NO_PIN_REQUIRED};
    return r;
}

TEST_F(PinChallengeTest, registerPinChallengeProvider)
{
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().provide(_pinChallengeProvider);
}
