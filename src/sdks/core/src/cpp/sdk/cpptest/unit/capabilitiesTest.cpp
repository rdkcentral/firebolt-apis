#include "unit.h"


class CapabilitiesTest : public ::testing::Test {
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


TEST_F(CapabilitiesTest, Supported)
{
	nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.supported"));


	bool supported = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().supported("xrn:firebolt:capability:wifi:scan", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(supported, expectedValues);
}


TEST_F(CapabilitiesTest, CapabilitiesSupported)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.supported"));
    
    std::string capability = "xrn:firebolt:capability:wifi:scan";
    
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().supported(capability, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}

TEST_F(CapabilitiesTest, Available)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.available"));
    
    std::string capability = "xrn:firebolt:capability:token:device";
   
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().available(capability, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}



TEST_F(CapabilitiesTest, Permitted)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.permitted"));
    
    std::string capability = "xrn:firebolt:capability:input:keyboard";

    // Initialize options with a role
    std::optional<Firebolt::Capabilities::CapabilityOption> options;
    options.emplace();  // Initialize the optional
    options->role = Firebolt::Capabilities::Role::MANAGE;

    // Call the permitted function
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().permitted(capability, options, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}

TEST_F(CapabilitiesTest, Granted)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.granted"));
    std::string capability = "xrn:firebolt:capability:localization:postal-code";

    std::optional<Firebolt::Capabilities::CapabilityOption> options;
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().granted(capability, options, &error);
   
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}


TEST_F(CapabilitiesTest, TestCapabilitiesinfo) {
    // Parse the expected values from the JSON
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Capabilities.info"));

    // Extract the expected result for the specific capability
    nlohmann::json expectedValue;
    for (const auto& item : expectedValues) {
        if (item["capability"] == "xrn:firebolt:capability:device:model") {
            expectedValue = item;
            break;
        }
    }
    // Define the capabilities to query
    std::vector<std::string> capabilities = {
        "xrn:firebolt:capability:device:model"
    };

    // Call the method to get actual results
    Firebolt::Error error;
    std::vector<Firebolt::Capabilities::CapabilityInfo> actualValues = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().info(capabilities, &error);

    // Ensure there's at least one result
    ASSERT_FALSE(actualValues.empty());

    // Compare the first actual value with the expected value
    Firebolt::Capabilities::CapabilityInfo actualValue = actualValues[0];

    // Compare each field
    EXPECT_EQ(actualValue.capability, expectedValue["capability"].get<std::string>());
    EXPECT_EQ(actualValue.supported, expectedValue["supported"].get<bool>());
    EXPECT_EQ(actualValue.available, expectedValue["available"].get<bool>());

    if (expectedValue.contains("use")) {
        if (expectedValue["use"].contains("permitted")) {
            auto expectedPermitted = expectedValue["use"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["use"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.use.permitted, expectedPermitted);
        }
        if (expectedValue["use"].contains("granted")) {
            auto expectedGranted = expectedValue["use"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["use"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.use.granted, expectedGranted);
        }
    }

    if (expectedValue.contains("manage")) {
        if (expectedValue["manage"].contains("permitted")) {
            auto expectedPermitted = expectedValue["manage"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["manage"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.manage.permitted, expectedPermitted);
        }
        if (expectedValue["manage"].contains("granted")) {
            auto expectedGranted = expectedValue["manage"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["manage"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.manage.granted, expectedGranted);
        }
    }

    if (expectedValue.contains("provide")) {
        if (expectedValue["provide"].contains("permitted")) {
            auto expectedPermitted = expectedValue["provide"]["permitted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["provide"]["permitted"].get<bool>());
            EXPECT_EQ(actualValue.provide.permitted, expectedPermitted);
        }
        if (expectedValue["provide"].contains("granted")) {
            auto expectedGranted = expectedValue["provide"]["granted"].is_null() ? std::optional<bool>{} : std::make_optional(expectedValue["provide"]["granted"].get<bool>());
            EXPECT_EQ(actualValue.provide.granted, expectedGranted);
        }
    }

    EXPECT_EQ(error, Firebolt::Error::None);
}


// TEST_F(CapabilitiesTest, TestCapabilitiesrequest)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Capabilities.request");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().request(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(CapabilitiesTest, TestCapabilitiesonAvailable)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Capabilities.onAvailable");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().onAvailable(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(CapabilitiesTest, TestCapabilitiesonUnavailable)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Capabilities.onUnavailable");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().onUnavailable(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(CapabilitiesTest, TestCapabilitiesonGranted)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Capabilities.onGranted");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().onGranted(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(CapabilitiesTest, TestCapabilitiesonRevoked)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Capabilities.onRevoked");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().onRevoked(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }