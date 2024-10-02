#include "unit.h"

class AccessibilityTest : public ::testing::Test
{
protected:
    JsonEngine *jsonEngine;
    Firebolt::Error error = Firebolt::Error::None;

    void SetUp() override
    {
        jsonEngine = new JsonEngine();
    }

    void TearDown() override
    {
        delete jsonEngine;
    }

    std::string fontFamilyToString(Firebolt::Accessibility::FontFamily fontFamily)
    {
        std::string str = "";
        switch (fontFamily)
        {
        case Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF:
            str = "monospaced_serif";
            break;
        case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF:
            str = "proportional_serif";
            break;
        case Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF:
            str = "monospaced_sanserif";
            break;
        case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF:
            str = "proportional_sanserif";
            break;
        case Firebolt::Accessibility::FontFamily::SMALLCAPS:
            str = "smallcaps";
            break;
        case Firebolt::Accessibility::FontFamily::CURSIVE:
            str = "cursive";
            break;
        case Firebolt::Accessibility::FontFamily::CASUAL:
            str = "casual";
            break;
        default:
            str = "unknown";
        }
        return str;
    }

    std::string fontEdgeToString(Firebolt::Accessibility::FontEdge fontEdge)
    {
        std::string str = "";
        switch (fontEdge)
        {
        case Firebolt::Accessibility::FontEdge::NONE:
            str = "none";
            break;
        case Firebolt::Accessibility::FontEdge::RAISED:
            str = "raised";
            break;
        case Firebolt::Accessibility::FontEdge::DEPRESSED:
            str = "depressed";
            break;
        case Firebolt::Accessibility::FontEdge::UNIFORM:
            str = "uniform";
            break;
        case Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT:
            str = "drop_shadow_left";
            break;
        case Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT:
            str = "drop_shadow_right";
            break;
        default:
            str = "unknown";
        }
        return str;
    }
};

TEST_F(AccessibilityTest, ClosedCaptions)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.closedCaptions"));

    Firebolt::Accessibility::ClosedCaptionsSettings closedCaptions = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptions(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve closedCaptions from Accessibility.closedCaptions() method";
    EXPECT_EQ(closedCaptions.enabled, expectedValues["enabled"]);

    if (closedCaptions.styles.has_value()) {
        const auto& styles = closedCaptions.styles.value();

        if (styles.backgroundColor.has_value())
            EXPECT_EQ(styles.backgroundColor.value(), expectedValues["styles"]["backgroundColor"]);

        if (styles.backgroundOpacity.has_value())
            EXPECT_EQ(styles.backgroundOpacity.value(), expectedValues["styles"]["backgroundOpacity"]);

        if (styles.fontColor.has_value())
            EXPECT_EQ(styles.fontColor.value(), expectedValues["styles"]["fontColor"]);

        if (styles.fontEdge.has_value())
            EXPECT_EQ(fontEdgeToString(styles.fontEdge.value()), expectedValues["styles"]["fontEdge"]);

        if (styles.fontEdgeColor.has_value())
            EXPECT_EQ(styles.fontEdgeColor.value(), expectedValues["styles"]["fontEdgeColor"]);

        if (styles.fontFamily.has_value())
            EXPECT_EQ(fontFamilyToString(styles.fontFamily.value()), expectedValues["styles"]["fontFamily"]);

        if (styles.fontOpacity.has_value())
            EXPECT_EQ(styles.fontOpacity.value(), expectedValues["styles"]["fontOpacity"]);

        if (styles.fontSize.has_value())
            EXPECT_EQ(styles.fontSize.value(), expectedValues["styles"]["fontSize"]);

        if (styles.textAlign.has_value())
            EXPECT_EQ(styles.textAlign.value(), expectedValues["styles"]["textAlign"]);

        if (styles.textAlignVertical.has_value())
            EXPECT_EQ(styles.textAlignVertical.value(), expectedValues["styles"]["textAlignVertical"]);

        if (styles.windowColor.has_value())
            EXPECT_EQ(styles.windowColor.value(), expectedValues["styles"]["windowColor"]);

        if (styles.windowOpacity.has_value())
            EXPECT_EQ(styles.windowOpacity.value(), expectedValues["styles"]["windowOpacity"]);
    }

    EXPECT_EQ(closedCaptions.preferredLanguages.value()[0], expectedValues["preferredLanguages"][0]);
    EXPECT_EQ(closedCaptions.preferredLanguages.value()[1], expectedValues["preferredLanguages"][1]);
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.closedCaptionsSettings"));

    Firebolt::Accessibility::ClosedCaptionsSettings closedCaptionSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve closedCaptionSettings from Accessibility.closedCaptionSettings() method";
    EXPECT_EQ(closedCaptionSettings.enabled, expectedValues["enabled"]);

    if (closedCaptionSettings.styles.has_value()) {
        const auto& styles = closedCaptionSettings.styles.value();

        if (styles.backgroundColor.has_value())
            EXPECT_EQ(styles.backgroundColor.value(), expectedValues["styles"]["backgroundColor"]);

        if (styles.backgroundOpacity.has_value())
            EXPECT_EQ(styles.backgroundOpacity.value(), expectedValues["styles"]["backgroundOpacity"]);

        if (styles.fontColor.has_value())
            EXPECT_EQ(styles.fontColor.value(), expectedValues["styles"]["fontColor"]);

        if (styles.fontEdge.has_value())
            EXPECT_EQ(fontEdgeToString(styles.fontEdge.value()), expectedValues["styles"]["fontEdge"]);

        if (styles.fontEdgeColor.has_value())
            EXPECT_EQ(styles.fontEdgeColor.value(), expectedValues["styles"]["fontEdgeColor"]);

        if (styles.fontFamily.has_value())
            EXPECT_EQ(fontFamilyToString(styles.fontFamily.value()), expectedValues["styles"]["fontFamily"]);

        if (styles.fontOpacity.has_value())
            EXPECT_EQ(styles.fontOpacity.value(), expectedValues["styles"]["fontOpacity"]);

        if (styles.fontSize.has_value())
            EXPECT_EQ(styles.fontSize.value(), expectedValues["styles"]["fontSize"]);

        if (styles.textAlign.has_value())
            EXPECT_EQ(styles.textAlign.value(), expectedValues["styles"]["textAlign"]);

        if (styles.textAlignVertical.has_value())
            EXPECT_EQ(styles.textAlignVertical.value(), expectedValues["styles"]["textAlignVertical"]);

        if (styles.windowColor.has_value())
            EXPECT_EQ(styles.windowColor.value(), expectedValues["styles"]["windowColor"]);

        if (styles.windowOpacity.has_value())
            EXPECT_EQ(styles.windowOpacity.value(), expectedValues["styles"]["windowOpacity"]);
    }
 
    EXPECT_EQ(closedCaptionSettings.preferredLanguages.value()[0], expectedValues["preferredLanguages"][0]);
    EXPECT_EQ(closedCaptionSettings.preferredLanguages.value()[1], expectedValues["preferredLanguages"][1]);
}

TEST_F(AccessibilityTest, VoiceGuidance)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.voiceGuidance"));

    auto voiceGuidance = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidance(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve voiceGuidance from Accessibility.voiceGuidance() method";

    EXPECT_EQ(voiceGuidance.enabled, expectedValues["enabled"]);
    EXPECT_EQ(voiceGuidance.speed, expectedValues["speed"]);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.voiceGuidanceSettings"));

    auto voiceGuidanceSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidanceSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve voiceGuidanceSettings from Accessibility.voiceGuidanceSettings() method";

    EXPECT_EQ(voiceGuidanceSettings.enabled, expectedValues["enabled"]);
    EXPECT_EQ(voiceGuidanceSettings.speed, expectedValues["speed"]);
}

TEST_F(AccessibilityTest, AudioDescriptionSettings)
{
    nlohmann::json_abi_v3_11_3::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Accessibility.audioDescriptionSettings"));

    auto audioDescriptionSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().audioDescriptionSettings(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve audioDescriptionSettings from Accessibility.audioDescriptionSettings() method";

    EXPECT_EQ(audioDescriptionSettings.enabled, expectedValues["enabled"]);
}

struct ClosedCaptionsChange : public Firebolt::Accessibility::IAccessibility::IOnClosedCaptionsSettingsChangedNotification {
    void onClosedCaptionsSettingsChanged(const Firebolt::Accessibility::ClosedCaptionsSettings&) override;
};

// Below function is for when the event trigger via setter is done
Firebolt::Accessibility::ClosedCaptionsSettings newSettings;
void ClosedCaptionsChange::onClosedCaptionsSettingsChanged(const Firebolt::Accessibility::ClosedCaptionsSettings& closedCaptionsSettings)
{
    std::cout << "ClosedCaptionsSettingsChanged event fired" << std::endl;
    newSettings = closedCaptionsSettings;
}

TEST_F(AccessibilityTest, subscribeOnClosedCaptionsSettingsChanged)
{
	Firebolt::Error error = Firebolt::Error::None;
    ClosedCaptionsChange closedCaptionsChange;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribe(closedCaptionsChange, &error);
    std::cout << " error: " << static_cast<int>(error) << std::endl;
	EXPECT_EQ(error, Firebolt::Error::None);
    /*  We could optionally return a response inside WaitForEventResponse using JSON engine's mockResponse
        pointing to #/x-schemas/Types/ListenResponse dereferenced to "{listening:true}".
        Since there is no return value for event subscription, error would be the only validation for now.
        This is until event response is returned by changing closedCaptions settings.
    */
}

TEST_F(AccessibilityTest, unsubscribeOnClosedCaptionsSettingsChanged)
{
	Firebolt::Error error = Firebolt::Error::None;
    ClosedCaptionsChange closedCaptionsChange;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(closedCaptionsChange, &error);
    std::cout << " error: " << static_cast<int>(error) << std::endl;
	EXPECT_EQ(error, Firebolt::Error::None);
}