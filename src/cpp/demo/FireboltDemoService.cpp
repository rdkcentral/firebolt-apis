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

    const std::string config = "{\
    \"waitTime\": 3000,\
    \"logLevel\": \"Info\",\
    \"workerPool\":{\
    \"queueSize\": 8,\
    \"threadCount\": 3\
    },\
    \"wsUrl\": " + url + "}";

    auto error = Firebolt::IFireboltAccessor::Instance().Initialize(config);
    if (Firebolt::Error::None != error)
    {
        throw std::runtime_error("Failed to initialize");
    }
    error = Firebolt::IFireboltAccessor::Instance().Connect([this](const bool connected, const Firebolt::Error error)
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

void FireboltDemoService::setupDeviceSubscriptions()
{
    std::cout << "Setup Device subscriptions..." << std::endl;
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnDeviceNameChanged(
        [](const auto& deviceName)
        { std::cout << "[Subscription] Device name changed to: " << deviceName << std::endl; });
    if (subscriptionId)
    {
        deviceSubscriptionIds_.insert(*subscriptionId);
    }
    else
    {
        std::cout << "Failed to subscribe on DeviceNameChanged, error: " << subscriptionId.error() << std::endl;
    }
    subscriptionId = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnNameChanged(
        [](const auto& name) { std::cout << "[Subscription] Name changed to: " << name << std::endl; });
    if (subscriptionId)
    {
        deviceSubscriptionIds_.insert(*subscriptionId);
    }
    else
    {
        std::cout << "Failed to subscribe on NameChanged, error: " << subscriptionId.error() << std::endl;
    }
    subscriptionId = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnNetworkChanged(
        [](const auto& network) { std::cout << "[Subscription] Network changed: state: " << static_cast<int>(network.state) << ", type: " << static_cast<int>(network.type) << std::endl; });
    if (subscriptionId)
    {
        deviceSubscriptionIds_.insert(*subscriptionId);
    }
    else
    {
        std::cout << "Failed to subscribe on NetworkChanged, error: " << subscriptionId.error() << std::endl;
    }
}

void FireboltDemoService::unsubscribeAll()
{
    std::cout << "Unsubscribing..." << std::endl;
    for (const auto& subscriptionId : deviceSubscriptionIds_)
    {
        auto result{Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(subscriptionId)};
        if (!result)
        {
            std::cout << "Device unsubscribe with id: " << subscriptionId << " failed, error: " << result.error()
                      << std::endl;
        }
    }
}

FireboltDemoService::DeviceInfo FireboltDemoService::getAndPrintDeviceValues()
{
    std::cout << "Get and print device values..." << std::endl;
    DeviceInfo result;
    if (auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id())
    {
        std::cout << "Device Id is: " << *id << std::endl;
        result.id = *id;
    }
    else
    {
        std::cout << "Get device id failed, error: << " << id.error() << std::endl;
    }
    if (auto manufacturer = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make())
    {
        std::cout << "Device manufacturer is: " << *manufacturer << std::endl;
        result.manufacturer = *manufacturer;
    }
    else
    {
        std::cout << "Get device manufacturer failed, error: << " << manufacturer.error() << std::endl;
    }
    if (auto model = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model())
    {
        std::cout << "Device model is: " << *model << std::endl;
        result.model = *model;
    }
    else
    {
        std::cout << "Get device model failed, error: << " << model.error() << std::endl;
    }
    if (auto name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name())
    {
        std::cout << "Device name is: " << *name << std::endl;
        result.name = *name;
        currentDeviceName_ = *name;
    }
    else
    {
        std::cout << "Get device name failed, error: << " << name.error() << std::endl;
    }
    if (auto platform = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform())
    {
        std::cout << "Device platform is: " << *platform << std::endl;
        result.platform = *platform;
    }
    else
    {
        std::cout << "Get device platform failed, error: << " << platform.error() << std::endl;
    }
    if (auto type = Firebolt::IFireboltAccessor::Instance().DeviceInterface().type())
    {
        std::cout << "Device type is: " << *type << std::endl;
        result.type = *type;
    }
    else
    {
        std::cout << "Get device type failed, error: << " << type.error() << std::endl;
    }
    if (auto uid = Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid())
    {
        std::cout << "Device uid is: " << *uid << std::endl;
        result.uid = *uid;
    }
    else
    {
        std::cout << "Get device uid failed, error: << " << uid.error() << std::endl;
    }
    if (auto version = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version())
    {
        std::cout << "SDL version is: " << version->sdk.major << "." << version->sdk.minor << "." << version->sdk.patch
                  << " " << version->sdk.readable << std::endl;
        std::cout << "API version is: " << version->api.major << "." << version->api.minor << "." << version->api.patch
                  << " " << version->api.readable << std::endl;
        std::cout << "Firmware version is: " << version->firmware.major << "." << version->firmware.minor << "."
                  << version->firmware.patch << " " << version->firmware.readable << std::endl;
        std::cout << "Debug version info is: " << version->debug << std::endl;
    }
    else
    {
        std::cout << "Device version failed, error: << " << version.error() << std::endl;
    }
    if (auto networkInfo = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network())
    {
        std::cout << "Device network is: state: " << static_cast<int>(networkInfo->state) << ", type: " << static_cast<int>(networkInfo->type)
                  << std::endl;
    }
    else
    {
        std::cout << "Get device network failed, error: << " << networkInfo.error() << std::endl;
    }
    if (auto screenResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution())
    {
        std::cout << "Device screen resolution is: " << screenResolution.value()[0] << ", "
                  << screenResolution.value()[1] << std::endl;
    }
    else
    {
        std::cout << "Get device screen resolution failed, error: << " << screenResolution.error() << std::endl;
    }
    if (auto videoResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().videoResolution())
    {
        std::cout << "Device video resolution is: " << videoResolution.value()[0] << ", " << videoResolution.value()[1]
                  << std::endl;
    }
    else
    {
        std::cout << "Get device video resolution failed, error: << " << videoResolution.error() << std::endl;
    }

    return result;
}

void FireboltDemoService::onConnectionChanged(const bool connected, const Firebolt::Error error)
{
    std::unique_lock<std::mutex> lock{mutex_};
    connected_ = connected;
    cv_.notify_one();
}

void FireboltDemoService::deinitialize()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}
