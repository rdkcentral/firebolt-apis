#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "firebolt.h"
#include "accessibility.h"
#include "account.h"
#include "advertising.h"
#include "device.h"
#include "discovery.h"
#include "common/entertainment.h"

void ShowMenu()
{
    printf("Enter\n"
           "\tI : Get Device ID\n"
           "\tC : Get Closed Caption Settings\n"
           "\tG : Get Voice Guidance Settings\n"
           "\tP : Get Advertising Policy\n"
           "\tU : Get Account UID\n"
           "\tE : Push EntityInfo\n"
           "\tN : Register/Unregister for Device Name change\n"
           "\tR : Register/Unregister for Screen Resolution change\n"
           "\tA : Register/Unregister for Accessibilty Voice Guidance change\n"
           "\tH : Register/Unregister for OnNavigateTo:HomeIntent\n"
           "\tS : Register/Unregister for OnNavigateTo:SearchIntent\n"
           "\tQ : Quit\n\n"
          );
}

void ShowEventMenu()
{
    printf("Enter\n"
         "\tR: Register Event\n"
         "\tU: Unregister Event\n"
         "\tQ : Quit\n");
}

#define HandleEventListener(Module, eventFuncName, Callback, eventTestStr, eventName) \
{ \
    int opt; \
    do { \
        getchar(); \
        ShowEventMenu(); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'R': { \
            uint32_t result = Module##_Register_On##eventFuncName((const void*)Callback, eventTestStr); \
            if (result != FireboltSDKErrorNone) { \
                printf("Register event %s is failed, status = %d \n", eventName, result); \
            } else { \
                printf("Event %s is registered successfully\n", eventName); \
            } \
            break; \
        } \
        case 'U': { \
            uint32_t result = Module##_Unregister_On##eventFuncName((const void*)Callback); \
            if (result != FireboltSDKErrorNone) { \
                printf("Unregister event %s is failed, status = %d \n", eventName, result); \
            } else { \
                printf("Event %s is unregistered successfully\n", eventName); \
            } \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

const char* get_skiprestriction_enum_string(Advertising_SkipRestriction skipRestriction)
{
    char* strSkipRestriction;
    switch(skipRestriction) {
    case ADVERTISING_SKIPRESTRICTION_NONE:
        strSkipRestriction = "None";
        break;
    case ADVERTISING_SKIPRESTRICTION_ADS_UNWATCHED:
        strSkipRestriction = "AdsUnwatched";
        break;
    case ADVERTISING_SKIPRESTRICTION_ADS_ALL:
        strSkipRestriction = "AdsAll";
        break;
    case ADVERTISING_SKIPRESTRICTION_ALL:
        strSkipRestriction = "All";
        break;
    default:
        strSkipRestriction = "None";
        break;
    }
    return strSkipRestriction;
}

static const char deviceNameTestStr[] = "DeviceNameTestStr";
static void NotifyDeviceNameChange(const void* userData, FireboltTypes_String_t handle)
{
    if (handle) {
        printf("Got new device.name :%s\n", FireboltTypes_String(handle));
        FireboltTypes_StringHandle_Release(handle);
    } else {
        printf("device.name event handle is not valid\n");
    }
}

static const char deviceScreenResolutionTestStr[] = "deviceScreenResolutionTestStr";
static void NotifyDeviceScreenResolutionChange(const void* userData, Device_ResolutionArray_t handle)
{
    if (Device_ResolutionArrayHandle_IsValid(handle) == true) {
        uint32_t size = Device_ResolutionArray_Size(handle);
        printf("Device ScreenResolutions changed for %d numbers\n", size);
        for (uint32_t i = 0; i < size; ++i) {
            printf("New reslution[%d] = %d\n", i, Device_ResolutionArray_Get(handle, i));
        }
        Device_ResolutionArrayHandle_Release(handle);
    } else {
        printf("device.screenresolution event handle is not valid\n");
    }
}

static const char accessibilityVoiceGuidanceTestStr[] = "AccessibilityVoiceGuidanceTestStr";
static void NotifyAccessibilityVoiceGuidanceChange(const void* userData, Accessibility_VoiceGuidanceSettings_t handle)
{
    if (Accessibility_VoiceGuidanceSettingsHandle_IsValid(handle) == true) {
        bool enabled = Accessibility_VoiceGuidanceSettings_Get_Enabled(handle);
        uint32_t speed = Accessibility_VoiceGuidanceSettings_Get_Speed(handle);
        printf("VoiceGuidanceSettings: Enabled : %d, Speed : %d\n", enabled, speed);
        Accessibility_VoiceGuidanceSettingsHandle_Release(handle);
    } else {
        printf("accessibility.voiceguidance event handle is not valid\n");
    }
}

static const char discoveryHomeIntentTestStr[] = "DiscoveryHomeIntentTestStr";
static void NotifyOnNavigateToHomeIntent(const void* userData, Intents_HomeIntent_t handle)
{
    if (Intents_HomeIntentHandle_IsValid(handle) == true) {
        char* action = Intents_HomeIntent_Get_Action(handle);
        printf("NavigateToHomeIntent: Action: %s\n", action);
        Intents_HomeIntentHandle_Release(handle);
    } else {
        printf("discovery.onNavigateToChanged HomeIntent event handle is not valid\n");
    }
}

static const char discoverySearchIntentTestStr[] = "DiscoverySearchIntentTestStr";
static void NotifyOnNavigateToSearchIntent(const void* userData, Intents_SearchIntent_t handle)
{
    if (Intents_SearchIntentHandle_IsValid(handle) == true) {
        char* action = Intents_SearchIntent_Get_Action(handle);
        printf("NavigateToSearchIntent: Action: %s\n", action);
        Intents_SearchIntentHandle_Release(handle);
    } else {
        printf("discovery.onNavigateTo LauncIntent event handle is not valid\n");
    }
}

int main (int argc, char* argv[])
{
    char* config = "{\
    \"waitTime\": 1000,\
    \"logLevel\": \"Info\",\
    \"workerPool\":{\
        \"queueSize\": 8,\
        \"threadCount\": 3\
    },\
    \"wsUrl\": \"ws://127.0.0.1:9998\"\
}";

    printf("Firebolt Core SDK Test\n");
    
    //Intitialize the SDK
    FireboltSDK_Initialize(config);
    int option;

    do {
        ShowMenu();
        printf("Enter option : ");
        option = toupper(getchar());
        switch (option) {
        case 'I': {
            //Lets get the Device ID
            FireboltTypes_String_t handle;
            uint32_t result = Device_GetId(&handle);
            if (result == FireboltSDKErrorNone) {
                printf("Device: Id:%s\n\n", FireboltTypes_String(handle));
                FireboltTypes_StringHandle_Release(handle);
                handle = NULL;
            } else {
                printf("Failed to get Device ID\n\n");
            }
            break;
        }
        case 'C': {
            Accessibility_ClosedCaptionsSettings_t handle;
            uint32_t result = Accessibility_GetClosedCaptionsSettings(&handle);

            if (result == FireboltSDKErrorNone) {
                if (Accessibility_ClosedCaptionsSettingsHandle_IsValid(handle) == true) {
                    printf("ClosedCaption Settings ------------------\n");
                    Accessibility_ClosedCaptionsStyles_t styleHandle = Accessibility_ClosedCaptionsSettings_Get_Styles(handle);
                    if (Accessibility_ClosedCaptionsStylesHandle_IsValid(styleHandle)) {
                        printf("ClosedCaptionStyles:\n");
                        char* fontFamily = Accessibility_ClosedCaptionsStyles_Get_FontFamily(styleHandle);
                        printf("\tFontFamily : %s\n", fontFamily);
                        uint32_t fontSize = Accessibility_ClosedCaptionsStyles_Get_FontSize(styleHandle);
                        printf("\tFontSize : %d\n", fontSize);
                        char* fontColor = Accessibility_ClosedCaptionsStyles_Get_FontColor(styleHandle);
                        printf("\tFontColor : %s\n", fontColor);
                        char* fontEdge = Accessibility_ClosedCaptionsStyles_Get_FontEdge(styleHandle);
                        printf("\tFontEdge : %s\n", fontEdge);
                        char* fontEdgeColor = Accessibility_ClosedCaptionsStyles_Get_FontEdgeColor(styleHandle);
                        printf("\tFontEdgeColor : %s\n", fontEdgeColor);
                        uint32_t fontOpacity = Accessibility_ClosedCaptionsStyles_Get_FontOpacity(styleHandle);
                        printf("\tFontOpacity : %d\n", fontOpacity);
                        char* bgColor = Accessibility_ClosedCaptionsStyles_Get_BackgroundColor(styleHandle);
                        printf("\tBackgroundColor : %s\n", bgColor);
                        uint32_t bgOpacity = Accessibility_ClosedCaptionsStyles_Get_BackgroundOpacity(styleHandle);
                        printf("\tBackgroundOpacity : %d\n", bgOpacity);
                        char* txAlign = Accessibility_ClosedCaptionsStyles_Get_TextAlign(styleHandle);
                        printf("\tTextAlign : %s\n", txAlign);
                        char* txAlignVertical = Accessibility_ClosedCaptionsStyles_Get_TextAlignVertical(styleHandle);
                        printf("\tTextAlignVertical : %s\n", txAlignVertical);
                        Accessibility_ClosedCaptionsStylesHandle_Release(styleHandle);
                    }
                    bool enabled = Accessibility_ClosedCaptionsSettings_Get_Enabled(handle);
                    printf("Enabled: %d\n\n", enabled);
                    Accessibility_ClosedCaptionsSettingsHandle_Release(handle);
                } else {
                    printf("Invalid ClosedCaptionsSettings_t\n\n");
                }
            } else {
                printf("Failed to get Closed Caption Settings\n\n");
            }
            break;
        }
        case 'G': {
            Accessibility_VoiceGuidanceSettings_t handle;
            uint32_t result = Accessibility_GetVoiceGuidanceSettings(&handle);

            if (result == FireboltSDKErrorNone) {
                if (Accessibility_VoiceGuidanceSettingsHandle_IsValid(handle) == true) {
                    bool enabled = Accessibility_VoiceGuidanceSettings_Get_Enabled(handle);
                    uint32_t speed = Accessibility_VoiceGuidanceSettings_Get_Speed(handle);
                    printf("VoiceGuidanceSettings: Enabled : %d, Speed : %d\n", enabled, speed);
                    Accessibility_VoiceGuidanceSettingsHandle_Release(handle);
                } else {
                    printf("Invalid VoiceGuidanceSettings_t\n\n");
                }
            } else {
                printf("Failed to get Voice Guidance Settings\n\n");
            }
            break;
        }
        case 'P': {
            Advertising_AdPolicy_t handle;
            uint32_t result = Advertising_GetPolicy(&handle);
            if (result == FireboltSDKErrorNone) {
                if (Advertising_AdPolicyHandle_IsValid(handle) == true) {
                    printf("AdPolicy: ");
                    Advertising_SkipRestriction skipRestriction = Advertising_AdPolicy_Get_SkipRestriction(handle);
                    printf("SkipRestriction = %s ", get_skiprestriction_enum_string(skipRestriction));
                    bool limitAdTracking = Advertising_AdPolicy_Get_LimitAdTracking(handle);
                    printf("LimitAdTracking = %s \n", limitAdTracking? "true" : "false");
                    Advertising_AdPolicyHandle_Release(handle);
                } else {
                    printf("Invalid Advertising_AdPolicy_t\n\n");
                }
            } else {
                printf("Failed to get Advertising Policy\n\n");
            }
            break;
        }
        case 'U': {
            FireboltTypes_String_t handle;
            uint32_t result = Account_GetUid(&handle);
            if (result == FireboltSDKErrorNone) {
                printf("Account: Uid:%s\n\n", FireboltTypes_String(handle));
                FireboltTypes_StringHandle_Release(handle);
                handle = NULL;
            } else {
                printf("Failed to get Advertising Policy\n\n");
            }
            break;
        }
        case 'E': {
            {
                Discovery_EntityInfoResult_t entityInfoResult = Discovery_EntityInfoResultHandle_Acquire();
                Entertainment_EntityInfo_t entityInfo = Entertainment_EntityInfoHandle_Acquire();

                //Populate the ContentIdentifiers Object
                Entertainment_ContentIdentifiers_t ci = Entertainment_ContentIdentifiersHandle_Acquire();
                Entertainment_ContentIdentifiers_Set_AssetId(ci, "12345678");
                Entertainment_ContentIdentifiers_Set_EntityId(ci, "ABCDEFGH");
                Entertainment_ContentIdentifiers_Set_SeasonId(ci, "1");
                Entertainment_ContentIdentifiers_Set_SeriesId(ci, "9ER34FR");
                Entertainment_ContentIdentifiers_Set_AppContentData(ci, "Sample App Content Data");

                //Populate EntityInfo Object
                //Set the ContentIdentifiers Object to EntityInfo Object
                Entertainment_EntityInfo_Set_Identifiers(entityInfo, ci);
                Entertainment_ContentIdentifiersHandle_Release(ci);
                Entertainment_EntityInfo_Set_Title(entityInfo, "Game Of Thrones");
                Entertainment_EntityInfo_Set_EntityType(entityInfo, "program");
                Entertainment_EntityInfo_Set_ProgramType(entityInfo, ENTERTAINMENT_PROGRAMTYPE_SEASON);
                Entertainment_EntityInfo_Set_Synopsis(entityInfo, "The imaginary continent of Westeros was once inhabited by a magical people, the Children of the Forest. For centuries, other people came across the Narrow Sea from the eastern continent of Essos: up North, the First Men; in the Center, the Andals; down South, the Dornish.");
                Entertainment_EntityInfo_Set_SeasonNumber(entityInfo, 1);
                Entertainment_EntityInfo_Set_EpisodeNumber(entityInfo, 1);
                Entertainment_EntityInfo_Set_ReleaseDate(entityInfo, "2012-04-23T18:25:43.511Z");

                {
                    Entertainment_EntityInfoContentRatingsContentRatingArray_t crArray = Entertainment_EntityInfoContentRatingsContentRatingArrayHandle_Acquire();
                    {
                        //Populate the ContentRatings Handle for US TV scheme
                        Entertainment_ContentRating_t cr  = Entertainment_ContentRatingHandle_Acquire();
                        Entertainment_ContentRating_Set_Scheme(cr, ENTERTAINMENT_CONTENTRATINGSCHEME_US_TV);
                        Entertainment_ContentRating_Set_Rating(cr, "TVMA");
                        Entertainment_ContentRatingAdvisoriesArray_t crAdvisories = Entertainment_ContentRatingAdvisoriesArrayHandle_Acquire();
                        Entertainment_ContentRatingAdvisoriesArray_Add(crAdvisories, "V");
                        Entertainment_ContentRatingAdvisoriesArray_Add(crAdvisories, "S");
                        Entertainment_ContentRatingAdvisoriesArray_Add(crAdvisories, "L");
                        Entertainment_ContentRating_Set_Advisories(cr, crAdvisories);
                        Entertainment_ContentRatingAdvisoriesArrayHandle_Release(crAdvisories);
                        Entertainment_EntityInfoContentRatingsContentRatingArray_Add(crArray, cr);
                    }
                    {
                        //Populate the ContentRatings Handle for US TV scheme
                        Entertainment_ContentRating_t cr = Entertainment_ContentRatingHandle_Acquire();
                        Entertainment_ContentRating_Set_Scheme(cr, ENTERTAINMENT_CONTENTRATINGSCHEME_CA_TV);
                        Entertainment_ContentRating_Set_Rating(cr, "18+");
                        Entertainment_ContentRatingAdvisoriesArray_t crAdvisories = Entertainment_ContentRatingAdvisoriesArrayHandle_Acquire();
                        Entertainment_ContentRatingAdvisoriesArray_Add(crAdvisories, "18+");
                        Entertainment_ContentRating_Set_Advisories(cr, crAdvisories);
                        Entertainment_ContentRatingAdvisoriesArrayHandle_Release(crAdvisories);
                        Entertainment_EntityInfoContentRatingsContentRatingArray_Add(crArray, cr);
                    }
                    Entertainment_EntityInfo_Set_ContentRatings(entityInfo, crArray);
                    Entertainment_EntityInfoContentRatingsContentRatingArrayHandle_Release(crArray);
                }

                //Populate WayToWatch Array in EntityInfo
                {
                    //Populate the WayToWatch Object
                    Entertainment_WayToWatch_t w2w = Entertainment_WayToWatchHandle_Acquire();
                    {
                         //Add the ContentIdentifiers Object in WayToWatch
                        Entertainment_ContentIdentifiers_t ciI = Entertainment_ContentIdentifiersHandle_Acquire();
                        Entertainment_ContentIdentifiers_Set_AssetId(ciI, "12345678");
                        Entertainment_ContentIdentifiers_Set_EntityId(ciI, "ABCDEFGH");
                        Entertainment_ContentIdentifiers_Set_SeasonId(ciI, "1");
                        Entertainment_ContentIdentifiers_Set_SeriesId(ciI, "9ER34FR");
                        Entertainment_ContentIdentifiers_Set_AppContentData(ciI, "Sample App Content Data");
                        Entertainment_WayToWatch_Set_Identifiers(w2w, ciI);
                        Entertainment_ContentIdentifiersHandle_Release(ciI);
                    }
                    Entertainment_WayToWatch_Set_Expires(w2w, "2014-04-23T18:25:43.511Z");
                    Entertainment_WayToWatch_Set_Entitled(w2w, true);
                    Entertainment_WayToWatch_Set_EntitledExpires(w2w, "2014-04-23T18:25:43.511Z");
                    Entertainment_WayToWatch_Set_OfferingType(w2w, ENTERTAINMENT_OFFERINGTYPE_FREE);
                    Entertainment_WayToWatch_Set_HasAds(w2w, true);

                    //Populate VideoQuality Array
                    Entertainment_WayToWatchVideoQualityArray_t vqArray =
                            Entertainment_WayToWatchVideoQualityArrayHandle_Acquire();
                    Entertainment_WayToWatchVideoQualityArray_Add(
                                    vqArray, ENTERTAINMENT_WAYTOWATCHVIDEOQUALITY_HD);
                    Entertainment_WayToWatchVideoQualityArray_Add(
                                    vqArray, ENTERTAINMENT_WAYTOWATCHVIDEOQUALITY_UHD);
                    Entertainment_WayToWatch_Set_VideoQuality(w2w, vqArray);
                    Entertainment_WayToWatchVideoQualityArrayHandle_Release(vqArray);

                    //Populate AudioProfile Array
                    Entertainment_WayToWatchAudioProfileAudioProfileArray_t apArray =
                            Entertainment_WayToWatchAudioProfileAudioProfileArrayHandle_Acquire();
                    Entertainment_WayToWatchAudioProfileAudioProfileArray_Add(
                                    apArray, TYPES_AUDIOPROFILE_STEREO);
                    Entertainment_WayToWatchAudioProfileAudioProfileArray_Add(
                                    apArray, TYPES_AUDIOPROFILE_DOLBY_DIGITAL_5_1);
                    Entertainment_WayToWatchAudioProfileAudioProfileArray_Add(
                                    apArray, TYPES_AUDIOPROFILE_DOLBY_DIGITAL_5_1_PLUS);
                    Entertainment_WayToWatch_Set_AudioProfile(w2w, apArray);
                    Entertainment_WayToWatchAudioProfileAudioProfileArrayHandle_Release(apArray);

                    //Populate AudioLanguages Array
                    Entertainment_WayToWatchAudioLanguagesArray_t alArray =
                            Entertainment_WayToWatchAudioLanguagesArrayHandle_Acquire();
                    Entertainment_WayToWatchAudioLanguagesArray_Add(alArray, "en");
                    Entertainment_WayToWatchAudioLanguagesArray_Add(alArray, "fr");
                    Entertainment_WayToWatch_Set_AudioLanguages(w2w, alArray);
                    Entertainment_WayToWatchAudioLanguagesArrayHandle_Release(alArray);

                    //Populate ClosedCaptions Array
                    Entertainment_WayToWatchClosedCaptionsArray_t ccArray =
                            Entertainment_WayToWatchClosedCaptionsArrayHandle_Acquire();
                    Entertainment_WayToWatchClosedCaptionsArray_Add(ccArray, "en");
                    Entertainment_WayToWatchClosedCaptionsArray_Add(ccArray, "fr");
                    Entertainment_WayToWatch_Set_ClosedCaptions(w2w, ccArray);
                    Entertainment_WayToWatchClosedCaptionsArrayHandle_Release(ccArray);

                    //Populate Subtitles Array
                    Entertainment_WayToWatchSubtitlesArray_t sbArray =
                            Entertainment_WayToWatchSubtitlesArrayHandle_Acquire();
                    Entertainment_WayToWatchSubtitlesArray_Add(sbArray, "en");
                    Entertainment_WayToWatchSubtitlesArray_Add(sbArray, "fr");
                    Entertainment_WayToWatch_Set_Subtitles(w2w, sbArray);
                    Entertainment_WayToWatchSubtitlesArrayHandle_Release(sbArray);

                    //Populate AudioDescriptions Array
                    Entertainment_WayToWatchAudioDescriptionsArray_t adArray =
                            Entertainment_WayToWatchAudioDescriptionsArrayHandle_Acquire();
                    Entertainment_WayToWatchAudioDescriptionsArray_Add(adArray, "en");
                    Entertainment_WayToWatch_Set_AudioDescriptions(w2w, adArray);
                    Entertainment_WayToWatchAudioDescriptionsArrayHandle_Release(adArray);

                    //Populate WayToWatch Array
                    Entertainment_EntityInfoWaysToWatchWayToWatchArray_t w2wArray =
                            Entertainment_EntityInfoWaysToWatchWayToWatchArrayHandle_Acquire();
                    Entertainment_EntityInfoWaysToWatchWayToWatchArray_Add(w2wArray, w2w);
                    Entertainment_EntityInfo_Set_WaysToWatch(entityInfo, w2wArray);
                    Entertainment_EntityInfoWaysToWatchWayToWatchArrayHandle_Release(w2wArray);
                    Entertainment_WayToWatchHandle_Release(w2w);
                }

                //Populate EntityInfoResult Object
                Discovery_EntityInfoResult_Set_Expires(entityInfoResult, "2012-06-23T18:25:43.511Z");
                Discovery_EntityInfoResult_Set_Entity(entityInfoResult, entityInfo);
                Entertainment_EntityInfoHandle_Release(entityInfo);

                //All Set, Call the Push
                uint32_t result = Discovery_PushEntityInfo(entityInfoResult);
                if (result == FireboltSDKErrorNone) {
                    printf("\nSuccessfully Pushed entityInfo\n");

                } else {
                    printf("\nFailed to Push entityInfo\n");
                }
                Discovery_EntityInfoResultHandle_Release(entityInfoResult);
                break;
            }
        }
        case 'R': {
            HandleEventListener(Device, ScreenResolutionChanged, (const void*)NotifyDeviceScreenResolutionChange, deviceScreenResolutionTestStr, "device.screenresolution")
            break;
        }
        case 'N': {
            HandleEventListener(Device, NameChanged, (const void*)NotifyDeviceNameChange, deviceNameTestStr, "device.name")
            break;
        }
        case 'A': {
            HandleEventListener(Accessibility, VoiceGuidanceSettingsChanged, (const void*)NotifyAccessibilityVoiceGuidanceChange, accessibilityVoiceGuidanceTestStr, "accessibility.voiceguidance")
            break;
        }
        case 'H': {
            HandleEventListener(Discovery, NavigateToHomeIntent, (const void*)NotifyOnNavigateToHomeIntent, discoveryHomeIntentTestStr, "discovery.onNavigateTo")
            break;
        }
        case 'S': {
            HandleEventListener(Discovery, NavigateToSearchIntent, (const void*)NotifyOnNavigateToSearchIntent, discoverySearchIntentTestStr, "discovery.onNavigateTo")
            break;
        }
        default:
            break;
        }
        getchar(); // Skip white space
    } while (option != 'Q');

    FireboltSDK_Deinitialize();

    return 0;
}
