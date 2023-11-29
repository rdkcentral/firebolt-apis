#include <getopt.h>
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
           "\tK : Invoke keyboard methods email/password/standard\n"
           "\tM : Get Device Model\n"
           "\tE : Get Device sku\n"
           "\tQ : Quit\n\n"
          );
}

void ShowKeyboardMenu()
{
    printf("Enter\n"
         "\tE: Invoke Email method\n"
         "\tP: Invoke Password method\n"
         "\tS: Invoke Standard method\n"
         "\tQ : Quit\n");
}

void ShowEventMenu()
{
    printf("Enter\n"
         "\tS: Subscribe Event\n"
         "\tU: Unsubscribe Event\n"
         "\tQ : Quit\n");
}

void HandleKeyboardMethodsInvokation()
{
    int opt;
    do {
        getchar();
        ShowKeyboardMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'E': {
            CoreSDKTest::InvokeKeyboardEmail();
            break;
        }
        case 'P': {
            CoreSDKTest::InvokeKeyboardPassword();
            break;
        }
        case 'S': {
            CoreSDKTest::InvokeKeyboardStandard();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
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

#define options ":hu:"
int main (int argc, char* argv[])
{
    int c;
    std::string url = "ws://127.0.0.1:9998";
    while ((c = getopt (argc, argv, options)) != -1) {
        switch (c)
        {
            case 'u':
                 url = optarg;
                 break;

            case 'h':
                 printf("./TestFireboltManage -u ws://ip:port\n");
                 exit(1);
        }
    }

    printf("Firebolt Core SDK Test\n");

    CoreSDKTest::CreateFireboltInstance(url);
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
            case 'K': {
                HandleKeyboardMethodsInvokation();
                break;
            }
            case 'M': {
                CoreSDKTest::GetDeviceModel();
                break;
            }
            case 'E': {
                CoreSDKTest::GetDeviceSKU();
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
