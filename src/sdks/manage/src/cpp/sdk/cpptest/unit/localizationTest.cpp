#include "unit.h"

class LocalizationTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct CountryCodeSettings : public Firebolt::Localization::ILocalization::IOnCountryCodeChangedNotification {
    void onCountryCodeChanged(const std::string &) override;
};

void CountryCodeSettings::onCountryCodeChanged(const std::string &code) {
    std::cout << "onCountryCodeChanged event fired";
}

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged) {
    CountryCodeSettings countryCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(countryCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to CountryCodeSettings";
}

TEST_F(LocalizationTest, unsubscribeOnCountryCodeChanged) {
    CountryCodeSettings countryCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(countryCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to CountryCodeSettings";
}

struct LanguageSettings : public Firebolt::Localization::ILocalization::IOnLanguageChangedNotification {
    void onLanguageChanged(const std::string &) override;
};

void LanguageSettings::onLanguageChanged(const std::string &language) {
    std::cout << "onLanguageChanged event fired with language: " << language;
}

TEST_F(LocalizationTest, subscribeOnLanguageChanged) {
    LanguageSettings languageSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(languageSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LanguageSettings";
}

TEST_F(LocalizationTest, unsubscribeOnLanguageChanged) {
    LanguageSettings languageSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(languageSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LanguageSettings";
}

struct LocaleSettings : public Firebolt::Localization::ILocalization::IOnLocaleChangedNotification {
    void onLocaleChanged(const std::string &) override;
};

void LocaleSettings::onLocaleChanged(const std::string &locale) {
    std::cout << "onLocaleChanged event fired with locale: " << locale;
}

TEST_F(LocalizationTest, subscribeOnLocaleChanged) {
    LocaleSettings localeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(localeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LocaleSettings";
}

TEST_F(LocalizationTest, unsubscribeOnLocaleChanged) {
    LocaleSettings localeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(localeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LocaleSettings";
}

struct LocalitySettings : public Firebolt::Localization::ILocalization::IOnLocalityChangedNotification {
    void onLocalityChanged(const std::string &) override;
};

void LocalitySettings::onLocalityChanged(const std::string &locality) {
    std::cout << "onLocalityChanged event fired with locality: " << locality;
}

TEST_F(LocalizationTest, subscribeOnLocalityChanged) {
    LocalitySettings localitySettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(localitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LocalitySettings";
}

TEST_F(LocalizationTest, unsubscribeOnLocalityChanged) {
    LocalitySettings localitySettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(localitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LocalitySettings";
}

struct PostalCodeSettings : public Firebolt::Localization::ILocalization::IOnPostalCodeChangedNotification {
    void onPostalCodeChanged(const std::string &) override;
};

void PostalCodeSettings::onPostalCodeChanged(const std::string &postalCode) {
    std::cout << "onPostalCodeChanged event fired with postal code: " << postalCode;
}

TEST_F(LocalizationTest, subscribeOnPostalCodeChanged) {
    PostalCodeSettings postalCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(postalCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PostalCodeSettings";
}

TEST_F(LocalizationTest, unsubscribeOnPostalCodeChanged) {
    PostalCodeSettings postalCodeSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(postalCodeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PostalCodeSettings";
}

struct PreferredAudioLanguagesSettings : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    void onPreferredAudioLanguagesChanged(const std::vector<std::string>&) override;
};

void PreferredAudioLanguagesSettings::onPreferredAudioLanguagesChanged(const std::vector<std::string>& languages) {
    std::cout << "onPreferredAudioLanguagesChanged event fired with languages: ";
    for(const auto& lang : languages) {
        std::cout << lang << " ";
    }
    std::cout << std::endl;
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged) {
    PreferredAudioLanguagesSettings preferredAudioLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(preferredAudioLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PreferredAudioLanguagesSettings";
}

TEST_F(LocalizationTest, unsubscribeOnPreferredAudioLanguagesChanged) {
    PreferredAudioLanguagesSettings preferredAudioLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(preferredAudioLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PreferredAudioLanguagesSettings";
}

struct TimeZoneSettings : public Firebolt::Localization::ILocalization::IOnTimeZoneChangedNotification {
    void onTimeZoneChanged(const std::string &) override;
};

void TimeZoneSettings::onTimeZoneChanged(const std::string &timeZone) {
    std::cout << "onTimeZoneChanged event fired with time zone: " << timeZone;
}

TEST_F(LocalizationTest, subscribeOnTimeZoneChanged) {
    TimeZoneSettings timeZoneSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(timeZoneSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TimeZoneSettings";
}

TEST_F(LocalizationTest, unsubscribeOnTimeZoneChanged) {
    TimeZoneSettings timeZoneSettings;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(timeZoneSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TimeZoneSettings";
}
