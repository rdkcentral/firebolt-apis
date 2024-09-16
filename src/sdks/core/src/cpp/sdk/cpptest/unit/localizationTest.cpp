#include "unit.h"


// class LocalizationTest : public ::testing::Test {
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


// TEST_F(LocalizationTest, TestLocalizationlocality)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.locality");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locality(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationpostalCode)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.postalCode");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().postalCode(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationcountryCode)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.countryCode");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationlanguage)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.language");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().language(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationpreferredAudioLanguages)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.preferredAudioLanguages");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationlocale)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.locale");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().locale(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationlatlon)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.latlon");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().latlon(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationadditionalInfo)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.additionalInfo");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonLocalityChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onLocalityChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onLocalityChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonPostalCodeChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onPostalCodeChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onPostalCodeChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonCountryCodeChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onCountryCodeChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onCountryCodeChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonLanguageChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onLanguageChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onLanguageChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonPreferredAudioLanguagesChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onPreferredAudioLanguagesChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onPreferredAudioLanguagesChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }


// TEST_F(LocalizationTest, TestLocalizationonLocaleChanged)
// {
// 	Firebolt::Error error = Firebolt::Error::None;
// 	auto actual_value = jsonEngine->get_value("Localization.onLocaleChanged");
// 	actual_value = actual_value.substr(1, actual_value.length() - 2);
// 	auto value = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().onLocaleChanged(&error);
// 	EXPECT_EQ(error, Firebolt::Error::None);
// 	EXPECT_EQ(value, actual_value);
// }