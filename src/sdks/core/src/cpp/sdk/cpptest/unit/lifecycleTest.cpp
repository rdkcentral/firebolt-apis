#include "unit.h"


class LifecycleTest : public ::testing::Test {
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
 
// TEST_F(LifecycleTest, TestLifecycleready) {

//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Lifecycle.ready"));

//     Firebolt::IFireboltAccessor::Instance().LifecycleInterface().ready(&error);
//     nlohmann::json_abi_v3_11_3::json actualValues;
//     if (error == Firebolt::Error::None) {
//         // If successful, set actualValues to null
//        actualValues = nlohmann::json::value_t::null;
//     }

//     EXPECT_EQ(error, Firebolt::Error::None);

//     EXPECT_EQ(actualValues, expectedValues);
// }

// TEST_F(LifecycleTest, Lifecyclefinished) {

//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Lifecycle.finished"));

//     Firebolt::IFireboltAccessor::Instance().LifecycleInterface().finished(&error);
//     nlohmann::json_abi_v3_11_3::json actualValues;
//     if (error == Firebolt::Error::None) {
//         // If successful, set actualValues to null
//        actualValues = nlohmann::json::value_t::null;
//     }

//     EXPECT_EQ(error, Firebolt::Error::None);
    
//     EXPECT_EQ(actualValues, expectedValues);
// }

// TEST_F(LifecycleTest, Lifecyclestate) {

//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Lifecycle.state"));

//     std::string actualValues = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state(&error);

//     EXPECT_EQ(error, Firebolt::Error::None);
    
//     EXPECT_NE(actualValues, expectedValues);
// }

 TEST_F(LifecycleTest, Lifecycleclose)
{
	Firebolt::Error error = Firebolt::Error::None;
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Lifecycle.close"));
    
    
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(Firebolt::Lifecycle::CloseReason::USER_EXIT, &error);
	nlohmann::json_abi_v3_11_3::json actualValues;
    if (error == Firebolt::Error::None) {
        // If successful, set actualValues to null
       actualValues = nlohmann::json::value_t::null;
    }

    EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(expectedValues, actualValues);
}

// TEST_F(LifecycleTest, TestLifecycleclose)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.close");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }

// TEST_F(LifecycleTest, TestLifecycleonInactive)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.onInactive");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().onInactive(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LifecycleTest, TestLifecycleonForeground)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.onForeground");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().onForeground(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LifecycleTest, TestLifecycleonBackground)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.onBackground");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().onBackground(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LifecycleTest, TestLifecycleonSuspended)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.onSuspended");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().onSuspended(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LifecycleTest, TestLifecycleonUnloading)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Lifecycle.onUnloading");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().onUnloading(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }