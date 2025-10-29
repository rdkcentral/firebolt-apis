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

#include "firebolt.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <thread>

using namespace std;

bool gConnected = false;

void connectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    gConnected = connected;
}

void createFireboltInstance(const std::string &url)
{
    const std::string config = R"({
      "waitTime": 1000,
      "logLevel": "Info",
      "wsUrl": ")" + url + R"("})";

    gConnected = false;
    Firebolt::IFireboltAccessor::Instance().Connect(config, connectionChanged);
}

void destroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}

bool waitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (gConnected == false))
    {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return gConnected;
}

int main(int argc, char **argv)
{
    string url = "ws://127.0.0.1:9998";
    createFireboltInstance(url);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ::testing::InitGoogleTest(&argc, argv);
    if (!waitOnConnectionReady())
    {
        cout << "Test not able to connect with server..." << endl;
        return -1;
    }
    const auto errorCode = RUN_ALL_TESTS();

    destroyFireboltInstance();

    return errorCode;
}
