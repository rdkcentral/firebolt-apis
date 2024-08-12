#include "unit.h"


// class KeyboardTest : public ::testing::Test {
// 	protected:
// 		JsonEngine* jsonEngine;

// 	void SetUp() override
// 	{
// 		jsonEngine = new JsonEngine();
// 	}

// 	void TearDown() override
// 	{
// 		delete jsonEngine;
// 	}
// };


// TEST_F(KeyboardTest, TestKeyboardemail)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Keyboard.email");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().email(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(KeyboardTest, TestKeyboardpassword)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Keyboard.password");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().password(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(KeyboardTest, TestKeyboardstandard)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Keyboard.standard");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().standard(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }