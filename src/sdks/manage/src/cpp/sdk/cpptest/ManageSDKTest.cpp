/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unistd.h>
#include "firebolt.h"
#include "ManageSDKTest.h"

using namespace std;
bool ManageSDKTest::_connected;

void ManageSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
   cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
   _connected = connected;
}

void ManageSDKTest::CreateFireboltInstance()
{
    const std::string config = "{\
            \"waitTime\": 1000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": \"ws://127.0.0.1:9998\"\
            }";

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void ManageSDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool ManageSDKTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false)) {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

void ManageSDKTest::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().Name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get DeviceName = " << name.c_str() << endl;
    } else {
        cout << "Get DeviceName status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().SetName("Hello", &error);

    if (error == Firebolt::Error::None) {
        cout << "Set DeviceName is success" << endl;
    } else {
        cout << "Set DeviceName status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetClosedCaptionBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    const float value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().BackgroundOpacity(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption BackgroundOpacity = " << value << endl;
    } else {
        cout << "Get ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetClosedCaptionBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().SetBackgroundOpacity(2.0, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption BackgroundOpacity is success" << endl;
    } else {
        cout << "Set ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetClosedCaptionFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::FontFamily value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().FontFamily(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption FontFamily = " << static_cast<int>(value) << endl;
    } else {
        cout << "Get ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetClosedCaptionFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().SetFontFamily(Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption FontFamily is success" << endl;
    } else {
        cout << "Set ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().PreferredAudioLanguages(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization PreferredAudioLanguages : " << endl;
        for (auto language: languages) {
	    cout << "----- > " <<language << endl;
	}
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = { "ara", "jpn", "hin" };
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().SetPreferredAudioLanguages(languages, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Localization PreferredAudioLanguages is success" << endl;
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
}

