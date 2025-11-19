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

#include "FireboltDemoService.h"
#include <config.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace
{
std::ostream& operator<<(std::ostream& out, Firebolt::Error& error)
{
    switch (error)
    {
    case Firebolt::Error::None:
    {
        out << "None";
        break;
    }
    case Firebolt::Error::General:
    {
        out << "General";
        break;
    }
    case Firebolt::Error::Timedout:
    {
        out << "Timedout";
        break;
    }
    case Firebolt::Error::NotConnected:
    {
        out << "NotConnected";
        break;
    }
    case Firebolt::Error::AlreadyConnected:
    {
        out << "AlreadyConnected";
        break;
    }
    case Firebolt::Error::InvalidRequest:
    {
        out << "InvalidRequest";
        break;
    }
    case Firebolt::Error::MethodNotFound:
    {
        out << "MethodNotFound";
        break;
    }
    case Firebolt::Error::InvalidParams:
    {
        out << "InvalidParams";
        break;
    }
    case Firebolt::Error::CapabilityNotAvaialbale:
    {
        out << "CapabilityNotAvaialbale";
        break;
    }
    case Firebolt::Error::CapabilityNotSupported:
    {
        out << "CapabilityNotSupported";
        break;
    }
    case Firebolt::Error::CapabilityGet:
    {
        out << "CapabilityGet";
        break;
    }
    case Firebolt::Error::CapabilityNotPermitted:
    {
        out << "CapabilityNotPermitted";
        break;
    }
    }
    return out;
}
} // namespace

FireboltDemoService::FireboltDemoService()
{
    std::string url = "ws://127.0.0.1:9998";
    const char* fireboltEndpoint = std::getenv("FIREBOLT_ENDPOINT");
    if (fireboltEndpoint)
    {
        url = fireboltEndpoint;
    }
    std::cout << "Using firebolt URL: " << url << std::endl;

    Firebolt::Config config;
    config.wsUrl = url;
    config.waitTime_ms = 3000;
    config.log.level = Firebolt::LogLevel::Debug;

    auto error =
        Firebolt::IFireboltAccessor::Instance().Connect(config, [this](const bool connected, const Firebolt::Error error)
                                                        { this->onConnectionChanged(connected, error); });
    if (Firebolt::Error::None != error)
    {
        throw std::runtime_error("Failed to connect");
    }
    std::unique_lock<std::mutex> lock{mutex_};
    if (!cv_.wait_for(lock, std::chrono::seconds{1}, [this]() { return connected_; }))
    {
        deinitialize();
        throw std::runtime_error("Cannot connect to Firebolt");
    }
    std::cout << "We are connected!\n";
}

FireboltDemoService::~FireboltDemoService()
{
    deinitialize();
}

std::string bool2str(const bool value)
{
    return value ? "true" : "false";
}

void FireboltDemoService::lifecycle()
{
    auto state = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().getCurrentState();
    if (state)
    {
      std::cout << "Current state: " << static_cast<int>(*state) << std::endl;
    }
    else
    {
        std::cout << "Cannot get current state, err:" << static_cast<int32_t>(state.error()) << std::endl;
    }

    auto id = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnStateChanged(
        [&](const std::vector<Firebolt::Lifecycle::StateChange> &changes)
        {
            std::cout << "[Subscription] Lifecycle state changed: " << static_cast<int>(changes[0].newState)
                      << ", old state: " << static_cast<int>(changes[0].oldState) << ", focused: " << changes[0].focused
                      << std::endl;
        });
    if (!id)
    {
        std::cout << "Failed to subscribe, error: " << id.error() << std::endl;
        return;
    }
    lifecycleSubscriptionIds_.insert(*id);
}

void FireboltDemoService::unsubscribeAll()
{
    std::cout << "Unsubscribing..." << std::endl;
    for (const auto &id : lifecycleSubscriptionIds_)
    {
        auto result{Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(id)};
        if (!result)
        {
            std::cout << "Unsubscribe with id: " << id << " failed, error: " << result.error() << std::endl;
        }
    }
}

void FireboltDemoService::onConnectionChanged(const bool connected, const Firebolt::Error error)
{
    (void)error; //unused
    std::unique_lock<std::mutex> lock{mutex_};
    connected_ = connected;
    cv_.notify_one();
}

void FireboltDemoService::deinitialize()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}
