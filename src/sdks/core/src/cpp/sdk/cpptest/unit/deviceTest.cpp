#include "unit.h"


class DeviceTest : public ::testing::Test {
	protected:
		JsonEngine* jsonEngine;


	void SetUp() override
	{
		jsonEngine = new JsonEngine();
	}

	void TearDown() override
	{
		delete jsonEngine;
	}
};


TEST_F(DeviceTest, TestDeviceId)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.id");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceDistributor)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.distributor");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDevicePlatform)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.platform");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceUid)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.uid");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceType)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.type");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().type(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceModel)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.model");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceSku)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.sku");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


TEST_F(DeviceTest, TestDeviceMake)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.make");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}

// TEST_F(DeviceTest, TestDeviceversion)
// {
//     Firebolt::Error error = Firebolt::Error::None;
//     nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Device.version"));
     
//     std::string actualValueStr = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version(&error);
//     nlohmann::json actualValue = nlohmann::json::parse(actualValueStr);

//     EXPECT_EQ(error, Firebolt::Error::None);
//     EXPECT_EQ(actualValue, expectedValues);
// }

TEST_F(DeviceTest, TestDevicehdcp)
{
    Firebolt::Error error = Firebolt::Error::None;
    
    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdcp"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it) {
        expectedValues[it.key()] = it.value().get<bool>();
    }
     
    // Getting the actual value from the DeviceInterface
    Firebolt::Types::BooleanMap actualValue = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualValue, expectedValues);
}


TEST_F(DeviceTest, TestDevicehdr)
{
    Firebolt::Error error = Firebolt::Error::None;
    
    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdr"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it) {
        expectedValues[it.key()] = it.value().get<bool>();
    }
     
    // Getting the actual value from the DeviceInterface
    Firebolt::Types::BooleanMap actualValue = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualValue, expectedValues);
}


std::string AudioProfileToString(Firebolt::Types::AudioProfile profile) {
    switch (profile) {
        case Firebolt::Types::AudioProfile::STEREO:
            return "stereo";
        case Firebolt::Types::AudioProfile::DOLBY_DIGITAL_5_1:
            return "dolbyDigital5.1+";
		case Firebolt::Types::AudioProfile::DOLBY_ATMOS:
            return "dolbyAtmos";
		default:
            return "dolbyDigital5.1";
        
    }
} 

TEST_F(DeviceTest, TestDeviceaudio)
{
    Firebolt::Error error = Firebolt::Error::None;
    
    // Parse expected JSON values
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.audio"));
     
    // Getting the actual value from the DeviceInterface
    const Firebolt::Device::AudioProfiles actualValue = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&error);

    // Convert actualValue (AudioProfiles map) to JSON
    nlohmann::json actualJson;
    for (const auto& item : actualValue) {
        std::string profileKey = AudioProfileToString(item.first); // Replace this with the correct conversion function
        actualJson[profileKey] = item.second;
    }

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualJson, expectedJson);
}

TEST_F(DeviceTest, TestDevicenetwork)
{
    Firebolt::Error error = Firebolt::Error::None;
    
    // Hardcoded expected values
    Firebolt::Device::NetworkInfo expectedValues;
    expectedValues.state = Firebolt::Device::NetworkState::CONNECTED; 
    expectedValues.type = Firebolt::Device::NetworkType::WIFI;
     
    // Getting the actual value from the DeviceInterface
    Firebolt::Device::NetworkInfo actualValue = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network(&error);
  
    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualValue.state, expectedValues.state);
    EXPECT_EQ(actualValue.type, expectedValues.type);
}

TEST_F(DeviceTest, DeviceScreenResolution)
{
    Firebolt::Error error = Firebolt::Error::None;

    // Parse expected JSON values
    nlohmann::json expectedJson;
    try {
        std::string jsonString = jsonEngine->get_value("Device.screenResolution");
        expectedJson = nlohmann::json::parse(jsonString);
    } catch (const nlohmann::json::exception& e) {
        FAIL() << "Failed to parse JSON: " << e.what();
    }

    // Validate that expectedJson is an array and has the required number of elements
    if (!expectedJson.is_array()) {
        FAIL() << "Expected JSON is not an array: " << expectedJson.dump(4);
    }

    if (expectedJson.size() != 2) {
        FAIL() << "Expected JSON array does not have 2 elements: " << expectedJson.dump(4);
    }

    // Getting the actual value from the DeviceInterface
    Firebolt::Device::Resolution actualResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution(&error);

    // Convert actual value to JSON
    nlohmann::json actualJson = { actualResolution.first, actualResolution.second };

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualJson, expectedJson);
}

TEST_F(DeviceTest, DevicevideoResolution)
{
    Firebolt::Error error = Firebolt::Error::None;

    // Parse expected JSON values
    nlohmann::json expectedJson;
    try {
        std::string jsonString = jsonEngine->get_value("Device.screenResolution");
        expectedJson = nlohmann::json::parse(jsonString);
    } catch (const nlohmann::json::exception& e) {
        FAIL() << "Failed to parse JSON: " << e.what();
    }

    // Validate that expectedJson is an array and has the required number of elements
    if (!expectedJson.is_array()) {
        FAIL() << "Expected JSON is not an array: " << expectedJson.dump(4);
    }

    if (expectedJson.size() != 2) {
        FAIL() << "Expected JSON array does not have 2 elements: " << expectedJson.dump(4);
    }

    // Getting the actual value from the DeviceInterface
    Firebolt::Device::Resolution actualResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().videoResolution(&error);

    // Convert actual value to JSON
    nlohmann::json actualJson = { actualResolution.first, actualResolution.second };

    // Perform the assertions
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(actualJson, expectedJson);
}


TEST_F(DeviceTest, TestDeviceName)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Device.name");

	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, REMOVE_QUOTES(actual_value));
}


// TEST_F(DeviceTest, TestDeviceonDeviceNameChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onDeviceNameChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onDeviceNameChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonNameChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onNameChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onNameChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonHdcpChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onHdcpChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onHdcpChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonHdrChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onHdrChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onHdrChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonAudioChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onAudioChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onAudioChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonScreenResolutionChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onScreenResolutionChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onScreenResolutionChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonVideoResolutionChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onVideoResolutionChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onVideoResolutionChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(DeviceTest, TestDeviceonNetworkChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Device.onNetworkChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().DeviceInterface().onNetworkChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }