#include "unit.h"
#include "common/types.h"


class SecondScreenTest : public ::testing::Test {
	protected:
		JsonEngine* jsonEngine;
        Firebolt::Error error = Firebolt::Error::None;

	void SetUp() override
	{
		jsonEngine = new JsonEngine();
	}

	void TearDown() override
	{
		delete jsonEngine;
	}
};


// TEST_F(SecondScreenTest, Protocols)
// {
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.protocols"));

// 	Firebolt::Types::BooleanMap protocols = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().protocols(&error);

// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(protocols["dial1.7"], expectedValues["dial1.7"]);
// }


// TEST_F(SecondScreenTest, Device)
// {
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.device"));

// 	std::string value = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().device("dial", &error);

// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, expectedValues);
// }


// TEST_F(SecondScreenTest, FriendlyName)
// {
	
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.friendlyName"));

// 	std::string friendlyName = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().friendlyName(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);

// 	EXPECT_EQ(friendlyName, expectedValues);
// }


// TEST_F(SecondScreenTest, TestSecondScreenonLaunchRequest)
// {
// 	
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.onLaunchRequest");
// 	expectedValues = expectedValues.substr(1, expectedValues.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().onLaunchRequest(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, expectedValues);
// }


// TEST_F(SecondScreenTest, TestSecondScreenonCloseRequest)
// {
// 	
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.onCloseRequest");
// 	expectedValues = expectedValues.substr(1, expectedValues.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().onCloseRequest(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, expectedValues);
// }


// TEST_F(SecondScreenTest, TestSecondScreenonFriendlyNameChanged)
// {
// 	
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecondScreen.onFriendlyNameChanged");
// 	expectedValues = expectedValues.substr(1, expectedValues.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().onFriendlyNameChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, expectedValues);
// }