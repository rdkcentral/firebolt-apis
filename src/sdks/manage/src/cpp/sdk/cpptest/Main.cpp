#include <getopt.h>
#include "ManageSDKTest.h"

void ShowMenu()
{
    printf("Options ---- >\n"
           "\tN : Get Device Name\n"
           "\tS : Set Device Name\n"
           "\tC : Subscribe/Unsubscribe for Device Name Change\n"
           "\tB : Get ClosedCaption Background Opacity\n"
           "\tO : Set ClosedCaption Background Opacity\n"
           "\tY : Subscribe/Unsubscribe for ClosedCaption Background Opacity Change\n"
           "\tF : Get ClosedCaption Font Family\n"
           "\tM : Set ClosedCaption Font Family\n"
           "\tI : Subscribe/Unsubscribe for ClosedCaption Font Family Change\n"
           "\tL : Get Localization Preferred AudioLanguages\n"
           "\tA : Set Localization Preferred AudioLanguages\n"
           "\tR : Subscribe/Unsubscribe for Localization Preferred AudioLanguages Change\n"
           "\tD : Register for Keyboard Provider and check sequence\n"
           "\tK : Register for Acknowledge Challenge Provider and check sequence\n"
           "\tP : Register for Pin Challenge Provider and check sequence\n"
           "\tQ : Quit\n\n"
          );
}

void ShowProviderMenu(std::string& module)
{
    printf("Invoke %s onRequest sequence from other entity and press\n"
         "\tR: To Send Response\n"
         "\tE: To Send Error\n"
         "\tQ : Quit\n", module.c_str());
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
            ManageSDKTest::Subscribe##Module##eventFuncName(); \
            break; \
        } \
        case 'U': { \
            ManageSDKTest::Unsubscribe##Module##eventFuncName(); \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

#define VALUE(string) #string
#define TO_STRING(string) VALUE(string)
#define HandleProviderSequence(Module) \
{ \
    int opt; \
    do { \
        getchar(); \
        std::string module = TO_STRING(Module); \
        ShowProviderMenu(module); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'R': { \
            ManageSDKTest::SendResponseMessageTo##Module##Provider(); \
            break; \
        } \
        case 'E': { \
            ManageSDKTest::SendErrorMessageTo##Module##Provider(); \
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

    printf("Firebolt Manage SDK Test\n");
    ManageSDKTest::CreateFireboltInstance(url);
    int option;

    if (ManageSDKTest::WaitOnConnectionReady() == true) {
       do {
            ShowMenu();
            printf("Enter option : ");
            option = toupper(getchar());
            switch (option) {
            case 'N': {
                ManageSDKTest::GetDeviceName();
                break;
            }
            case 'S': {
                ManageSDKTest::SetDeviceName();
                break;
            }
            case 'C': {
                HandleEventListener(Device, NameChanged)
                break;
            }
            case 'B': {
                ManageSDKTest::GetClosedCaptionBackgroundOpacity();
                break;
            }
            case 'O': {
                ManageSDKTest::SetClosedCaptionBackgroundOpacity();
                break;
            }
            case 'Y': {
                HandleEventListener(ClosedCaptions, BackgroundOpacityChanged)
                break;
            }
            case 'F': {
                ManageSDKTest::GetClosedCaptionFontFamily();
                break;
            }
            case 'M': {
                ManageSDKTest::SetClosedCaptionFontFamily();
                break;
            }
            case 'I': {
                HandleEventListener(ClosedCaptions, FontFamilyChanged)
                break;
            }
            case 'L': {
                ManageSDKTest::GetLocalizationPreferredAudioLanguages();
                break;
            }
            case 'A': {
                ManageSDKTest::SetLocalizationPreferredAudioLanguages();
                break;
            }
            case 'R': {
                HandleEventListener(Localization, PreferredAudioLanguagesChanged)
                break;
            }
#ifdef RPC_ONLY
            case 'P': {
                HandleEventListener(PinChallenge, RequestChallenge)
                break;
            }
#endif
            case 'D': {
                ManageSDKTest::RegisterKeyboardProvider();
                HandleProviderSequence(Keyboard)
                break;
            }
            case 'K': {
                ManageSDKTest::RegisterAcknowledgeChallengeProvider();
                HandleProviderSequence(AcknowledgeChallenge)
                break;
            }
            case 'P': {
                ManageSDKTest::RegisterPinChallengeProvider();
                HandleProviderSequence(PinChallenge)
                break;
            }
            default:
                break;
            }
            getchar(); // Skip white space
        } while (option != 'Q');

    } else {
        printf("Manage Test not able to connect with server.... \n");
    }

    ManageSDKTest::DestroyFireboltInstance();

    return 0;
}
