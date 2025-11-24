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

#include <condition_variable>
#include <firebolt/firebolt.h>
#include <mutex>
#include <set>

class FireboltDemoService
{
public:
    FireboltDemoService();
    ~FireboltDemoService();
    FireboltDemoService(const FireboltDemoService&) = delete;
    FireboltDemoService(FireboltDemoService&&) = delete;
    FireboltDemoService& operator=(const FireboltDemoService&) = delete;
    FireboltDemoService& operator=(FireboltDemoService&&) = delete;

    void lifecycle();

    void unsubscribeAll();

private:
    void onConnectionChanged(const bool connected, const Firebolt::Error error);
    void deinitialize();

private:
    std::mutex mutex_{};
    std::condition_variable cv_;
    bool connected_{false};
    std::set<Firebolt::SubscriptionId> lifecycleSubscriptionIds_;
};
