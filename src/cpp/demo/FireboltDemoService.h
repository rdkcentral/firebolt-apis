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

#pragma once

#include "firebolt.h"
#include <condition_variable>
#include <mutex>
#include <set>
#include <string>

class FireboltDemoService
{
public:
    struct DeviceInfo
    {
        std::string id;
        std::string manufacturer;
        std::string model;
        std::string name;
        std::string platform;
        std::string type;
        std::string uid;
    };

    FireboltDemoService();
    ~FireboltDemoService();
    FireboltDemoService(const FireboltDemoService&) = delete;
    FireboltDemoService(FireboltDemoService&&) = delete;
    FireboltDemoService& operator=(const FireboltDemoService&) = delete;
    FireboltDemoService& operator=(FireboltDemoService&&) = delete;

    DeviceInfo getAndPrintDeviceValues();

    void setupDeviceSubscriptions();
    void unsubscribeAll();

private:
    void onConnectionChanged(const bool connected, const Firebolt::Error error);
    void deinitialize();

private:
    std::mutex mutex_{};
    std::condition_variable cv_;
    bool connected_{false};
    std::set<Firebolt::SubscriptionId> deviceSubscriptionIds_;
    std::string currentDeviceName_;
};
