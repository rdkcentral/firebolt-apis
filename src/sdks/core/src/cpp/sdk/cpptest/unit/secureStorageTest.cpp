#include "unit.h"


// class SecureStorageTest : public ::testing::Test {
// 	protected:
// 		JsonEngine* jsonEngine;
//         Firebolt::Error error = Firebolt::Error::None;

// 	void SetUp() override
// 	{
// 		jsonEngine = new JsonEngine();
// 	}

// 	void TearDown() override
// 	{
// 		delete jsonEngine;
// 	}
// };


// TEST_F(SecureStorageTest, Get)
// {
// 	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("SecureStorage.get"));

// 	auto value = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(SecureStorageTest, TestSecureStorageset)
// {
	
// 	auto actual_value = jsonEngine->get_value("SecureStorage.set");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().set(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(SecureStorageTest, TestSecureStorageremove)
// {
	
// 	auto actual_value = jsonEngine->get_value("SecureStorage.remove");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(SecureStorageTest, TestSecureStorageclear)
// {
	
// 	auto actual_value = jsonEngine->get_value("SecureStorage.clear");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }
