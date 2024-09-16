#include "unit.h"


// class InternalTest : public ::testing::Test {
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


// TEST_F(InternalTest, TestInternalinitialize)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Internal.initialize");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().InternalInterface().initialize(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }