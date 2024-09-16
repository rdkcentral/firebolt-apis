#include "unit.h"


class MetricsTest : public ::testing::Test {
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


// TEST_F(MetricsTest, Metricsready)
// {
//     // Parse the expected values from the JSON
//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.ready"));
   
// 	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready(&error);
    
//     // Compare the expected and actual results
//     EXPECT_EQ(error, Firebolt::Error::None);
//     EXPECT_EQ(status, expectedValues);
// }

// TEST_F(MetricsTest, TestMetricssignIn)
// {
//     // Parse the expected values from the JSON
//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.signIn"));
   
// 	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signIn(&error);
    
//     // Compare the expected and actual results
//     EXPECT_EQ(error, Firebolt::Error::None);
//     EXPECT_EQ(status, expectedValues);
// }

// TEST_F(MetricsTest, MetricssignOut)
// {
//     // Parse the expected values from the JSON
//     nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.signOut"));
   
// 	bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signOut(&error);
    
//     // Compare the expected and actual results
//     EXPECT_EQ(error, Firebolt::Error::None);
//     EXPECT_EQ(status, expectedValues);
// }



TEST_F(MetricsTest, TestMetricsStartContent)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Metrics.startContent");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent("example", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}


TEST_F(MetricsTest, TestMetricsStopContent)
{
	Firebolt::Error error = Firebolt::Error::None;
	auto actual_value = jsonEngine->get_value("Metrics.stopContent");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent("example", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}


TEST_F(MetricsTest, Metricspage)
{
    // Parse the expected values from the JSON
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.page"));
    
    std::string pageId = "xyz";
   
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().page(pageId,&error);
    
    // Compare the expected and actual results
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}

TEST_F(MetricsTest, Metricsaction)
{
    // Parse the expected values from the JSON
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.action"));
    std::cout << "Expected value for capability " << expectedValues << std::endl;
	
    

    Firebolt::Metrics::Category category = Firebolt::Metrics::Category::USER;
    auto type = "The user did foo";
	std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt; 

    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().action(category, type, parameters, &error);
    std::cout << "Status value for capability " << status << std::endl;
    
    // Compare the expected and actual results
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}

TEST_F(MetricsTest, Metricserror)
{
    // Parse the expected values from the JSON
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Metrics.error"));
    std::cout << "Expected value for capability " << expectedValues << std::endl;
	
    Firebolt::Metrics::ErrorType type = Firebolt::Metrics::ErrorType::MEDIA;
    std::string code = "MEDIA-STALLED";
    std::string description = "playback stalled";
	std::optional<Firebolt::Types::FlatMap> parameters = std::nullopt; 
    bool visible = true;


    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().error(type,code,description,visible,parameters,&error);
    std::cout << "Status value for capability " << status << std::endl;
    
    // Compare the expected and actual results
    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(status, expectedValues);
}


TEST_F(MetricsTest, TestMetricsLoadStart)
{
	auto actual_value = jsonEngine->get_value("Metrics.mediaLoadStart");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaLoadStart("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, TestMetricsMediaPlay)
{
	auto actual_value = jsonEngine->get_value("Metrics.mediaPlay");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlay("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}


TEST_F(MetricsTest, TestMetricsMediaPlaying)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaPlaying");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPlaying("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}


TEST_F(MetricsTest, TestMetricsmediaPause)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaPause");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaPause("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MetricsmediaWaiting)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaWaiting");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaWaiting("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MetricsmediaProgress)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaProgress");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaProgress("345","0.75", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, MetricsmediaSeeking)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaSeeking");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaSeeking("345","0.25", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}


TEST_F(MetricsTest, TestMetricsmediaSeeked)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaSeeked");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaSeeked("345","0.51", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, TestMetricsmediaRateChange)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaRateChange");

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRateChange("345",2, &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

TEST_F(MetricsTest, TestMetricsmediaRenditionChange)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaRenditionChange");
	std::optional<std::string> profile = std::nullopt;

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaRenditionChange("345", 1080, 950, 1020, profile,  &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

 TEST_F(MetricsTest, TestMetricsmediaEnded)
{
	std::string actual_value = jsonEngine->get_value("Metrics.mediaEnded");
	std::optional<std::string> profile = std::nullopt;

	auto value = Firebolt::IFireboltAccessor::Instance().MetricsInterface().mediaEnded("345", &error);

	EXPECT_EQ(error, Firebolt::Error::None);
	EXPECT_EQ(value, STRING_TO_BOOL(actual_value));
}

