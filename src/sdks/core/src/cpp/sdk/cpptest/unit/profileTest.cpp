#include "unit.h"
#include "common/types.h"


class ProfileTest : public ::testing::Test {
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


TEST_F(ProfileTest, ApproveContentRating)
{
	
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Profile.approveContentRating"));

	bool value = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approveContentRating(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(value, expectedValues);
}


TEST_F(ProfileTest, ApprovePurchase)
{
	
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Profile.approvePurchase"));

	bool value = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approvePurchase(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, expectedValues);
}


TEST_F(ProfileTest, Flags)
{
	
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Profile.flags"));

	Firebolt::Types::FlatMap flag = Firebolt::IFireboltAccessor::Instance().ProfileInterface().flags(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(flag["userExperience"], expectedValues["userExperience"]);
}