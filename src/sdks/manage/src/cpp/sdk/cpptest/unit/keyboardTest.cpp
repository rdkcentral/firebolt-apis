#include "unit.h"

using namespace Firebolt::Keyboard;

struct KeyboardProvider : public IKeyboardProvider
{
public:
    KeyboardProvider();
    ~KeyboardProvider() override = default;
    Firebolt::Keyboard::KeyboardResult standard( const Firebolt::Keyboard::KeyboardParameters& parameters ) override;
    Firebolt::Keyboard::KeyboardResult password( const Firebolt::Keyboard::KeyboardParameters& parameters ) override;
    Firebolt::Keyboard::KeyboardResult email(const KeyboardEmailParameters& parameters) override;
};

class KeyboardTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;
    KeyboardProvider _keyboardProvider;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }
};

KeyboardProvider::KeyboardProvider()
{
}

Firebolt::Keyboard::KeyboardResult KeyboardProvider::standard(const KeyboardParameters& parameters)
{
    std::cout << "KeyboardProvider Standard is invoked" << std::endl;
    return Firebolt::Keyboard::KeyboardResult{};
}

Firebolt::Keyboard::KeyboardResult KeyboardProvider::password(const KeyboardParameters& parameters)
{
    std::cout << "KeyboardProvider Password is invoked" << std::endl;
    return Firebolt::Keyboard::KeyboardResult{};
}

Firebolt::Keyboard::KeyboardResult KeyboardProvider::email(const KeyboardEmailParameters& parameters)
{
    std::cout << "KeyboardProvider Email is invoked" << std::endl;
    return Firebolt::Keyboard::KeyboardResult{};
}

TEST_F(KeyboardTest, registerKeyboardProvider)
{
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().provide(_keyboardProvider);
}

