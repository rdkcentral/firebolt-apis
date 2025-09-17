/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CoreSDKTest.h"
#include <iomanip>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace std;
bool CoreSDKTest::_connected;
std::map<CoreSDKTest::Subscriptions, uint64_t> CoreSDKTest::_subscriptionIds{};

template <typename T> inline std::string toError(const Firebolt::Result<T>& result)
{
  if (result) {
      return "";
  }
  return "Error: " + std::to_string(static_cast<int>(result.error()));
}

void CoreSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void CoreSDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = R"({
      "waitTime": 1000,
      "logLevel": "Info",
      "wsUrl": ")" + url + R"("})";

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void CoreSDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}

bool CoreSDKTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false))
    {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

template <typename T> using EnumMap = std::unordered_map<T, string>;
template <typename T> inline const string& ConvertFromEnum(EnumMap<T> enumMap, T type)
{
    return enumMap[type];
}
template <typename T> inline const T ConvertToEnum(EnumMap<T> enumMap, const string& str)
{
    T value;
    for (auto element : enumMap)
    {
        if (element.second == str)
        {
            value = element.first;
            break;
        }
    }
    return value;
}

void CoreSDKTest::GetClosedCaptionsBackgroundOpacity()
{
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundOpacity();

    if (result)
    {
        cout << "Get ClosedCaption BackgroundOpacity = " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetClosedCaptionsBackgroundOpacity failed. " + toError(result));
    }
}

void CoreSDKTest::SetClosedCaptionsBackgroundOpacity()
{
    unsigned bgOpacity = 1;

    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundOpacity(bgOpacity);

    if (result.error() == Firebolt::Error::None)
    {
        cout << "Set ClosedCaption BackgroundOpacity to " << bgOpacity << " is success" << endl;
    }
    else
    {
        throw std::runtime_error("SetClosedCaptionsBackgroundOpacity failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged()
{
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribeOnBackgroundOpacityChanged(
        [](auto bo) { std::cout << "Background opacity changed to: " << bo << std::endl; });
    if (result)
    {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
        _subscriptionIds[Subscriptions::ClosedCaptionsOpacity] = result.value();
    }
    else
    {
        throw std::runtime_error("SubscribeClosedCaptionsBackgroundOpacityChanged failed. " + toError(result));
    }
}

void CoreSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged()
{
    auto subscriptionIter{_subscriptionIds.find(Subscriptions::ClosedCaptionsOpacity)};
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for closed captions opacity change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe closed captions opacity is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe closed captions opacity failed. " + toError(result));
    }
}

EnumMap<Firebolt::Accessibility::FontFamily> fontFamilyMap =
    {{Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF, "MonospacedSerif"},
     {Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF, "ProportionalSerif"},
     {Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF, "MonospacedSanserif"},
     {Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, "ProportionalSanserif"},
     {Firebolt::Accessibility::FontFamily::SMALLCAPS, "SmallCaps"},
     {Firebolt::Accessibility::FontFamily::CURSIVE, "Cursive"},
     {Firebolt::Accessibility::FontFamily::CASUAL, "Casual"}};

void CoreSDKTest::GetClosedCaptionsFontFamily()
{
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontFamily();

    if (result)
    {
        cout << "Get ClosedCaption FontFamily value = "
             << ConvertFromEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, *result) << endl;
    }
    else
    {
        throw std::runtime_error("GetClosedCaptionsFontFamily failed. " + toError(result));
    }
}

void CoreSDKTest::SetClosedCaptionsFontFamily()
{
    Firebolt::Accessibility::FontFamily fontFamily = Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF;

    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontFamily(fontFamily);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Set ClosedCaption FontFamily to MonospacedSerif is success" << endl;
    }
    else
    {
        throw std::runtime_error("SetClosedCaptionsFontFamily failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeClosedCaptionsFontFamilyChanged()
{
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribeOnFontFamilyChanged(
        [](const auto& ff)
        {
            std::cout << "Background font family changed to: "
                      << ConvertFromEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, ff) << std::endl;
        });
    if (result)
    {
        cout << "Subscribe ClosedCaptions FontFamilyChange is success" << endl;
        _subscriptionIds[Subscriptions::ClosedCaptionsFontFamily] = result.value();
    }
    else
    {
        throw std::runtime_error("SubscribeClosedCaptionsFontFamilyChanged failed. " + toError(result));
    }
}

void CoreSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged()
{
    auto subscriptionIter{_subscriptionIds.find(Subscriptions::ClosedCaptionsFontFamily)};
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for closed captions font family change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe closed captions font family is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe closed captions font family failed. " + toError(result));
    }
}

void CoreSDKTest::GetDeviceName()
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name();

    if (result)
    {
        cout << "Get Device Name = " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetDeviceName failed. " + toError(result));
    }
}

void CoreSDKTest::GetDeviceVersion()
{
    auto version = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version();

    if (version)
    {
        cout << "Get Device Version (SDK) = " << version->sdk.major << "." << version->sdk.minor << "."
             << version->sdk.patch << " " << version->sdk.readable << endl;
    }
    else
    {
        cout << "Get Device Version status = " << static_cast<int>(version.error()) << endl;
    }
}

void CoreSDKTest::SubscribeDeviceNameChanged()
{
    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnDeviceNameChanged(
        [](const std::string& value) { cout << "Device Name Changed to " << value << endl; });
    if (id)
    {
        cout << "Subscribe Device NameChange is success" << endl;
        _subscriptionIds[Subscriptions::DeviceName] = id.value();
    }
    else
    {
        throw std::runtime_error("SubscribeDeviceNameChanged failed. " + toError(id));
    }
}

void CoreSDKTest::UnsubscribeDeviceNameChanged()
{
    auto subscriptionIter{_subscriptionIds.find(Subscriptions::DeviceName)};
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for device name change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe Device NameChange is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("UnsubscribeDeviceNameChanged failed. " + toError(result));
    }
}

void CoreSDKTest::GetDeviceModel()
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model();

    if (result)
    {
        cout << "Get Device Model = " << result->c_str() << endl;
    }
    else
    {
        throw std::runtime_error("GetDeviceModel failed. " + toError(result));
    }
}

void CoreSDKTest::GetDeviceSku()
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku();

    if (result)
    {
        cout << "Get Device Sku = " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetDeviceSku failed. " + toError(result));
    }
}

void PrintDeviceAudioProfiles(const Firebolt::Device::AudioProfiles& audioProfiles)
{
    cout << "Get Device AudioProfiles :-> " << endl;

    cout << "Profile: Stereo, Status: " << audioProfiles.stereo << endl;
    cout << "Profile: Dolby Digital 5.1, Status: " << audioProfiles.dolbyDigital5_1 << endl;
    cout << "Profile: Dolby Digital 5.1 Plus, Status: " << audioProfiles.dolbyDigital5_1_plus << endl;
    cout << "Profile: Dolby Atmos, Status: " << audioProfiles.dolbyAtmos << endl;
}

void CoreSDKTest::GetDeviceAudio()
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio();
    if (result)
    {
        PrintDeviceAudioProfiles(*result);
    }
    else
    {
        throw std::runtime_error("GetDeviceAudio failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeDeviceAudioChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnAudioChanged(
        [](const auto&) { std::cout << "Audio profiles changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe Device Audio Change is success" << endl;
        _subscriptionIds[Subscriptions::DeviceAudio] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("SubscribeDeviceAudioChanged failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeDeviceAudioChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::DeviceAudio);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for device audio change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe Device Audio Change is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("UnsubscribeDeviceAudioChanged failed. " + toError(result));
    }
}

void PrintDeviceScreenResolution(const Firebolt::Device::Resolution& screenResolution)
{
    cout << "Get Device ScreenResolution :-> " << endl;
    cout << "[" << screenResolution[0] << ", " << screenResolution[1] << "]" << endl;
}

void CoreSDKTest::GetDeviceScreenResolution()
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution();
    if (result)
    {
        PrintDeviceScreenResolution(*result);
    }
    else
    {
        throw std::runtime_error("GetDeviceScreenResolution failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeDeviceScreenResolutionChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnScreenResolutionChanged(
        [](const std::string& value) { cout << "Device ScreenResolution Changed to " << value << endl; });
    if (subscriptionId)
    {
        cout << "Subscribe Device ScreenResolution Change is success" << endl;
        _subscriptionIds[Subscriptions::DeviceScreenResolution] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("SubscribeDeviceScreenResolutionChanged failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeDeviceScreenResolutionChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::DeviceScreenResolution);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for device screen resolution change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe Device ScreenResolution Change is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("UnsubscribeDeviceScreenResolutionChanged failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeHdmiAutoLowLatencyModeCapableChanged()
{
    auto subscriptionId =
        Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnAutoLowLatencyModeCapableChanged(
            [](const auto& value) { cout << "Hdmi Input AutoLowLatencyModeCapable changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe Hdmi Input AutoLowLatencyModeCapable Change is success" << endl;
        _subscriptionIds[Subscriptions::HdmiInputAutoLowLatencyModeCapable] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe HdmiInputAutoLowLatencyModeCapableChange failed." + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeHdmiAutoLowLatencyModeCapableChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::HdmiInputAutoLowLatencyModeCapable);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for Hdmi Input AutoLowLatencyModeCapable Change" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe Hdmi Input AutoLowLatencyModeCapable Change is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe Hdmi Input AutoLowLatencyModeCapable Change failed. " + toError(result));
    }
}

void CoreSDKTest::GetAutoLowLatencyModeCapable()
{
    std::string port = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port);

    if (result)
    {
        cout << "GetAutoLowLatencyModeCapable is a success." << endl;
    }
    else
    {
        throw std::runtime_error("GetAutoLowLatencyModeCapable failed. " + toError(result));
    }
}

void CoreSDKTest::SetAutoLowLatencyModeCapable()
{
    std::string port = "HDMI1";
    bool value = false;
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setAutoLowLatencyModeCapable(port, value);

    if (result.error() == Firebolt::Error::None)
    {
        cout << "SetAutoLowLatencyModeCapable is a success." << endl;
    }
    else
    {
        throw std::runtime_error("SetAutoLowLatencyModeCapable failed. " + toError(result));
    }
}

void CoreSDKTest::GetEdidVersion()
{
    std::string port = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port);

    if (result)
    {
        cout << "GetEdidVersion is a success." << endl;
    }
    else
    {
        throw std::runtime_error("GetEdidVersion failed. " + toError(result));
    }
}

void CoreSDKTest::SetEdidVersion()
{
    std::string port = "HDMI1";
    Firebolt::HDMIInput::EDIDVersion value = Firebolt::HDMIInput::EDIDVersion::V1_4;
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setEdidVersion(port, value);

    if (result.error() == Firebolt::Error::None)
    {
        cout << "SetEdidVersion is a success." << endl;
    }
    else
    {
        throw std::runtime_error("SetEdidVersion failed. " + toError(result));
    }
}

void CoreSDKTest::OpenHdmiPort()
{
    std::string portId = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().open(portId);

    if (result)
    {
        cout << "OpenHdmiPort is a success." << endl;
    }
    else
    {
        throw std::runtime_error("OpenHdmiPort failed. " + toError(result));
    }
}

void CoreSDKTest::CloseHdmiPort()
{
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().close();

    if (result)
    {
        cout << "CloseHdmiPort is a success." << endl;
    }
    else
    {
        throw std::runtime_error("CloseHdmiPort failed. " + toError(result));
    }
}

void CoreSDKTest::GetHdmiPortInfo()
{
    std::string portId = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().port(portId);

    if (result)
    {
        cout << "GetHdmiPortInfo is a success." << endl;
    }
    else
    {
        throw std::runtime_error("GetHdmiPortInfo failed. " + toError(result));
    }
}

void CoreSDKTest::LifecycleReady()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().ready();

    if (result.error() == Firebolt::Error::None)
    {
        cout << "LifecycleReady is a success." << endl;
    }
    else
    {
        throw std::runtime_error("LifecycleReady failed. " + toError(result));
    }
}

void CoreSDKTest::LifecycleClose()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(
        Firebolt::Lifecycle::CloseReason::REMOTE_BUTTON);

    if (result.error() == Firebolt::Error::None)
    {
        cout << "LifecycleClose is a success." << endl;
    }
    else
    {
        throw std::runtime_error("LifecycleClose failed. " + toError(result));
    }
}

void CoreSDKTest::LifecycleFinished()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().finished();

    if (result.error() == Firebolt::Error::None)
    {
        cout << "LifecycleFinished is a success." << endl;
    }
    else
    {
        throw std::runtime_error("LifecycleFinished failed. " + toError(result));
    }
}

void CoreSDKTest::LifecycleState()
{
    auto state = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state();

    if (state)
    {
        cout << "LifecycleState is a success: " << *state << endl;
    }
    else
    {
        throw std::runtime_error("LifecycleState failed. " + toError(state));
    }
}

void CoreSDKTest::SubscribeOnLifecycleBackgroundChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnBackgroundChanged(
        [](const auto&) { std::cout << "LifecycleBackground changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LifecycleBackground change is success" << endl;
        _subscriptionIds[Subscriptions::LifecycleBackgroundChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LifecycleBackground failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLifecycleBackgroundChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LifecycleBackgroundChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LifecycleBackground" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LifecycleBackground is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LifecycleBackground failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLifecycleForegroundChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnForegroundChanged(
        [](const auto&) { std::cout << "LifecycleForeground changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LifecycleForeground change is success" << endl;
        _subscriptionIds[Subscriptions::LifecycleForegroundChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LifecycleForeground failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLifecycleForegroundChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LifecycleForegroundChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LifecycleForeground" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LifecycleForeground is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LifecycleForeground failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLifecycleInactiveChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnInactiveChanged(
        [](const auto&) { std::cout << "LifecycleInactive changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LifecycleInactive change is success" << endl;
        _subscriptionIds[Subscriptions::LifecycleInactiveChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LifecycleInactive failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLifecycleInactiveChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LifecycleInactiveChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LifecycleInactive" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LifecycleInactive is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LifecycleInactive failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLifecycleSuspendedChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnSuspendedChanged(
        [](const auto&) { std::cout << "LifecycleSuspended changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LifecycleSuspended change is success" << endl;
        _subscriptionIds[Subscriptions::LifecycleSuspendedChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LifecycleSuspended failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLifecycleSuspendedChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LifecycleSuspendedChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LifecycleSuspended" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LifecycleSuspended is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LifecycleSuspended failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLifecycleUnloadingChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnUnloadingChanged(
        [](const auto&) { std::cout << "LifecycleUnloading changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LifecycleUnloading change is success" << endl;
        _subscriptionIds[Subscriptions::LifecycleUnloadingChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LifecycleUnloading failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLifecycleUnloadingChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LifecycleUnloadingChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LifecycleUnloading" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LifecycleUnloading is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LifecycleUnloading failed. " + toError(result));
    }
}

void CoreSDKTest::GetLocalizationCountryCode()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode();

    if (result)
    {
        cout << "Get LocalizationCountryCode = " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetLocalizationCountryCode failed. " + toError(result));
    }
}

void CoreSDKTest::GetLocalizationPreferredAudioLanguages()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages();

    if (result)
    {
        cout << "Get LocalizationPregetPreferredAudioLanguages = [\n";
        for (const auto& localization : *result)
        {
            std::cout << localization << endl;
        }
        std::cout << "]\n";
    }
    else
    {
        throw std::runtime_error("GetLocalizationPregetPreferredAudioLanguages failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLocalizationCountryCodeChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnCountryCodeChanged(
        [](const auto&) { std::cout << "LocalizationCountryCode changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LocalizationCountryCode change is success" << endl;
        _subscriptionIds[Subscriptions::LocalizationCountryCodeChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LocalizationCountryCode failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLocalizationCountryCodeChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LocalizationCountryCodeChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LocalizationCountryCode" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LocalizationCountryCode is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LocalizationCountryCode failed. " + toError(result));
    }
}

void CoreSDKTest::SubscribeOnLocalizationPreferredAudioLanguagesChanged()
{
    auto subscriptionId =
        Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPreferredAudioLanguagesChanged(
            [](const auto&) { std::cout << "LocalizationPreferredAudioLanguages changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LocalizationPreferredAudioLanguages change is success" << endl;
        _subscriptionIds[Subscriptions::LocalizationPreferredAudioLanguagesChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LocalizationPreferredAudioLanguages failed. " + toError(subscriptionId));
    }
}

void CoreSDKTest::UnsubscribeOnLocalizationPreferredAudioLanguagesChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LocalizationPreferredAudioLanguagesChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LocalizationPreferredAudioLanguages" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LocalizationPreferredAudioLanguages is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LocalizationPreferredAudioLanguages failed. " + toError(result));
    }
}

void CoreSDKTest::MetricsReady()
{
    auto result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready();
    if (result)
    {
        cout << "MetricsReady is a success: " << *result << endl;
    }
    else
    {
        throw std::runtime_error("MetricsReady failed. " + toError(result));
    }
}

void CoreSDKTest::ClearSecureStorage()
{
    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(
        Firebolt::SecureStorage::StorageScope::ACCOUNT);

    if (Firebolt::Error::None == result.error())
    {
        cout << "ClearSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("ClearSecureStorage failed. " + toError(result));
    }
}

void CoreSDKTest::GetSecureStorage()
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                             "authRefreshToken");

    if (result)
    {
        cout << "GetSecureStorage is a success: " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetSecureStorage failed. " + toError(result));
    }
}

void CoreSDKTest::RemoveSecureStorage()
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                                "authRefreshToken");

    if (Firebolt::Error::None == result.error())
    {
        cout << "RemoveSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("RemoveSecureStorage failed. " + toError(result));
    }
}

void CoreSDKTest::SetSecureStorage()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .set(Firebolt::SecureStorage::StorageScope::DEVICE, "authRefreshToken",
                           "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});

    if (Firebolt::Error::None == result.error())
    {
        cout << "SetSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("SetSecureStorage failed. " + toError(result));
    }
}

void CoreSDKTest::SetSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .setForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken",
                                 "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});

    if (Firebolt::Error::None == result.error())
    {
        cout << "SetSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("SetSecureStorageForApp failed. " + toError(result));
    }
}

void CoreSDKTest::RemoveSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .removeForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken");

    if (Firebolt::Error::None == result.error())
    {
        cout << "RemoveSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("RemoveSecureStorageForApp failed. " + toError(result));
    }
}

void CoreSDKTest::ClearSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .clearForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT);

    if (Firebolt::Error::None == result.error())
    {
        cout << "ClearSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("ClearSecureStorageForApp failed. " + toError(result));
    }
}
