#include "unit.h"

class ClosedCaptionsTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct BackgroundColorChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundColorChangedNotification
{
    void onBackgroundColorChanged(const std::string &) override;
};

void BackgroundColorChanged::onBackgroundColorChanged(const std::string &)
{
    std::cout << "onBackgroundColorChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnBackgroundColorChanged)
{
    BackgroundColorChanged backgroundColorChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(backgroundColorChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to BackgroundColorChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnBackgroundColorChanged)
{
    BackgroundColorChanged backgroundColorChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(backgroundColorChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to BackgroundColorChanged";
}

struct BackgroundOpacityChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification
{
    void onBackgroundOpacityChanged(const float) override;
};

void BackgroundOpacityChanged::onBackgroundOpacityChanged(const float)
{
    std::cout << "onBackgroundOpacityChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnBackgroundOpacityChanged)
{
    BackgroundOpacityChanged backgroundOpacityChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(backgroundOpacityChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to BackgroundOpacityChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnBackgroundOpacityChanged)
{
    BackgroundOpacityChanged backgroundOpacityChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(backgroundOpacityChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to BackgroundOpacityChanged";
}

struct ClosedCaptionEnabledChanged : public Firebolt::ClosedCaptions::IClosedCaptions::IOnEnabledChangedNotification
{
    void onEnabledChanged(const bool) override;
};

void ClosedCaptionEnabledChanged::onEnabledChanged(const bool)
{
    std::cout << "onEnabledChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnEnabledChanged)
{
    ClosedCaptionEnabledChanged ccEnabledChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(ccEnabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EnabledChanged";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnEnabledChanged)
{
    ClosedCaptionEnabledChanged ccEnabledChanged;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(ccEnabledChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EnabledChanged";
}

struct FontColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontColorChangedNotification
{
    void onFontColorChanged(const std::string &) override;
};

void FontColorSettings::onFontColorChanged(const std::string &color)
{
    std::cout << "onFontColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontColorChanged)
{
    FontColorSettings fontColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontColorChanged)
{
    FontColorSettings fontColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontColorSettings";
}

struct FontEdgeSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontEdgeChangedNotification
{
    void onFontEdgeChanged(const Firebolt::Accessibility::FontEdge &) override;
};

void FontEdgeSettings::onFontEdgeChanged(const Firebolt::Accessibility::FontEdge &edge)
{
    std::cout << "onFontEdgeChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnFontEdgeChanged)
{
    FontEdgeSettings fontEdgeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontEdgeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontEdgeSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontEdgeChanged)
{
    FontEdgeSettings fontEdgeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontEdgeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontEdgeSettings";
}

struct FontEdgeColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontEdgeColorChangedNotification
{
    void onFontEdgeColorChanged(const std::string &) override;
};

void FontEdgeColorSettings::onFontEdgeColorChanged(const std::string &color)
{
    std::cout << "onFontEdgeColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontEdgeColorChanged)
{
    FontEdgeColorSettings fontEdgeColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontEdgeColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontEdgeColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontEdgeColorChanged)
{
    FontEdgeColorSettings fontEdgeColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontEdgeColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontEdgeColorSettings";
}

struct FontFamilySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification
{
    void onFontFamilyChanged(const Firebolt::Accessibility::FontFamily &) override;
};

void FontFamilySettings::onFontFamilyChanged(const Firebolt::Accessibility::FontFamily &family)
{
    std::cout << "onFontFamilyChanged event fired";
}

TEST_F(ClosedCaptionsTest, subscribeOnFontFamilyChanged)
{
    FontFamilySettings fontFamilySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontFamilySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontFamilySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontFamilyChanged)
{
    FontFamilySettings fontFamilySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontFamilySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontFamilySettings";
}

struct FontOpacitySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontOpacityChangedNotification
{
    void onFontOpacityChanged(const float) override;
};

void FontOpacitySettings::onFontOpacityChanged(const float opacity)
{
    std::cout << "onFontOpacityChanged event fired with opacity: " << opacity;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontOpacityChanged)
{
    FontOpacitySettings fontOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontOpacitySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontOpacityChanged)
{
    FontOpacitySettings fontOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontOpacitySettings";
}

struct FontSizeSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontSizeChangedNotification
{
    void onFontSizeChanged(const float) override;
};

void FontSizeSettings::onFontSizeChanged(const float size)
{
    std::cout << "onFontSizeChanged event fired with size: " << size;
}

TEST_F(ClosedCaptionsTest, subscribeOnFontSizeChanged)
{
    FontSizeSettings fontSizeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(fontSizeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to FontSizeSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnFontSizeChanged)
{
    FontSizeSettings fontSizeSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(fontSizeSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to FontSizeSettings";
}

struct PreferredLanguagesSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnPreferredLanguagesChangedNotification
{
    void onPreferredLanguagesChanged(const std::vector<std::string> &) override;
};

void PreferredLanguagesSettings::onPreferredLanguagesChanged(const std::vector<std::string> &languages)
{
    std::cout << "onPreferredLanguagesChanged event fired with languages: ";
    for (const auto &lang : languages)
    {
        std::cout << lang << " ";
    }
    std::cout << std::endl;
}

TEST_F(ClosedCaptionsTest, subscribeOnPreferredLanguagesChanged)
{
    PreferredLanguagesSettings preferredLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(preferredLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to PreferredLanguagesSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnPreferredLanguagesChanged)
{
    PreferredLanguagesSettings preferredLanguagesSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(preferredLanguagesSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to PreferredLanguagesSettings";
}

struct TextAlignSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnTextAlignChangedNotification
{
    void onTextAlignChanged(const std::string &) override;
};

void TextAlignSettings::onTextAlignChanged(const std::string &alignment)
{
    std::cout << "onTextAlignChanged event fired with alignment: " << alignment;
}

TEST_F(ClosedCaptionsTest, subscribeOnTextAlignChanged)
{
    TextAlignSettings textAlignSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(textAlignSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TextAlignSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnTextAlignChanged)
{
    TextAlignSettings textAlignSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(textAlignSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TextAlignSettings";
}

struct TextAlignVerticalSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnTextAlignVerticalChangedNotification
{
    void onTextAlignVerticalChanged(const std::string &) override;
};

void TextAlignVerticalSettings::onTextAlignVerticalChanged(const std::string &alignment)
{
    std::cout << "onTextAlignVerticalChanged event fired with alignment: " << alignment;
}

TEST_F(ClosedCaptionsTest, subscribeOnTextAlignVerticalChanged)
{
    TextAlignVerticalSettings textAlignVerticalSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(textAlignVerticalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to TextAlignVerticalSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnTextAlignVerticalChanged)
{
    TextAlignVerticalSettings textAlignVerticalSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(textAlignVerticalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to TextAlignVerticalSettings";
}

struct WindowColorSettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnWindowColorChangedNotification
{
    void onWindowColorChanged(const std::string &) override;
};

void WindowColorSettings::onWindowColorChanged(const std::string &color)
{
    std::cout << "onWindowColorChanged event fired with color: " << color;
}

TEST_F(ClosedCaptionsTest, subscribeOnWindowColorChanged)
{
    WindowColorSettings windowColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(windowColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to WindowColorSettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnWindowColorChanged)
{
    WindowColorSettings windowColorSettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(windowColorSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to WindowColorSettings";
}

struct WindowOpacitySettings : public Firebolt::ClosedCaptions::IClosedCaptions::IOnWindowOpacityChangedNotification
{
    void onWindowOpacityChanged(const float) override;
};

void WindowOpacitySettings::onWindowOpacityChanged(const float opacity)
{
    std::cout << "onWindowOpacityChanged event fired with opacity: " << opacity;
}

TEST_F(ClosedCaptionsTest, subscribeOnWindowOpacityChanged)
{
    WindowOpacitySettings windowOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(windowOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to WindowOpacitySettings";
}

TEST_F(ClosedCaptionsTest, unsubscribeOnWindowOpacityChanged)
{
    WindowOpacitySettings windowOpacitySettings;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(windowOpacitySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to WindowOpacitySettings";
}
