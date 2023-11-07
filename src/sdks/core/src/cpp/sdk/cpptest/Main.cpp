
#include "CoreSDKTest.h"

void ShowMenu()
{
    printf("Enter\n"
           "\tD : Get Device Name\n"
           "\tN : Subscribe/Unsubscribe for Device Name Change\n"
           "\tA : Get Device Audio Profiles\n"
           "\tS : Subscribe/Unsubscribe for Device Audio Profiles Change\n"
           "\tR : Get Device Screen Resolution\n"
           "\tU : Subscribe/Unsubscribe for Device Screen Resolution\n"
           "\tL : Get Localization Preferred AudioLanguages\n"
           "\tP : Subscribe/Unsubscribe for Localization Preferred AudioLanguages Change\n"
           "\tC : Get Closed Caption Settings\n"
           "\tB : Subscribe/Unsubscribe for Closed Caption Settings\n"
           "\tQ : Quit\n\n"
          );
}

void ShowEventMenu()
{
    printf("Enter\n"
         "\tS: Subscribe Event\n"
         "\tU: Unsubscribe Event\n"
         "\tQ : Quit\n");
}

#define HandleEventListener(Module, eventFuncName) \
{ \
    int opt; \
    do { \
        getchar(); \
        ShowEventMenu(); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'S': { \
            CoreSDKTest::Subscribe##Module##eventFuncName(); \
            break; \
        } \
        case 'U': { \
            CoreSDKTest::Unsubscribe##Module##eventFuncName(); \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
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
    
    CoreSDKTest::CreateFireboltInstance();
    int option;
    if (CoreSDKTest::WaitOnConnectionReady() == true) {
       do {
            ShowMenu();
            printf("Enter option : ");
            option = toupper(getchar());
            switch (option) {
            case 'D': {
                CoreSDKTest::GetDeviceName();
                break;
            }
            case 'N': {
                HandleEventListener(Device, NameChanged)
                break;
            }
            case 'A': {
                CoreSDKTest::GetDeviceAudio();
                break;
            }
            case 'S': {
                HandleEventListener(Device, AudioChanged)
                break;
            }
            case 'R': {
                CoreSDKTest::GetDeviceScreenResolution();
                break;
            }
            case 'U': {
                HandleEventListener(Device, ScreenResolutionChanged)
                break;
            }
            case 'L': {
                CoreSDKTest::GetLocalizationPreferredAudioLanguages();
                break;
            }
            case 'P': {
                HandleEventListener(Localization, PreferredAudioLanguagesChanged)
                break;
            }
            case 'C': {
                CoreSDKTest::GetAccessibilityClosedCaptionsSettings();
                break;
            }
            case 'B': {
                HandleEventListener(Accessibility, ClosedCaptionsSettingsChanged)
                break;
            }
            default:
                break;
            }
            getchar(); // Skip white space
        } while (option != 'Q');

    } else {
        printf("Core Test not able to connect with server.... \n");
    }

    CoreSDKTest::DestroyFireboltInstance();

    return 0;
}
