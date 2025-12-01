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
#include "accessibility_impl.h"
#include "advertising_impl.h"
#include "device_impl.h"
#include "display_impl.h"
#include "fireboltclient_version.h"
#include "lifecycle_impl.h"
#include "localization_impl.h"
#include "presentation_impl.h"
#include "stats_impl.h"
#include <firebolt/gateway.h>

namespace Firebolt
{
class FireboltAccessorImpl : public IFireboltAccessor
{
public:
    FireboltAccessorImpl()
        : accessibility_(Firebolt::Helpers::GetHelperInstance()),
          advertising_(Firebolt::Helpers::GetHelperInstance()),
          device_(Firebolt::Helpers::GetHelperInstance()),
          display_(Firebolt::Helpers::GetHelperInstance()),
          lifecycle_(Firebolt::Helpers::GetHelperInstance()),
          localization_(Firebolt::Helpers::GetHelperInstance()),
          presentation_(Firebolt::Helpers::GetHelperInstance()),
          stats_(Firebolt::Helpers::GetHelperInstance())
    {
    }

    FireboltAccessorImpl(const FireboltAccessorImpl&) = delete;
    FireboltAccessorImpl& operator=(const FireboltAccessorImpl&) = delete;

    ~FireboltAccessorImpl() { unsubscribeAll(); }

    Firebolt::Error Connect(const Firebolt::Config& config, OnConnectionChanged listener) override
    {
        auto result = Firebolt::Transport::GetGatewayInstance().connect(config, listener);
        FIREBOLT_LOG_NOTICE("Client", "Version: %s", Version::String);
        return result;
    }

    Firebolt::Error Disconnect() override
    {
        unsubscribeAll();
        return Firebolt::Transport::GetGatewayInstance().disconnect();
    }

    Accessibility::IAccessibility& AccessibilityInterface() override { return accessibility_; }
    Advertising::IAdvertising& AdvertisingInterface() override { return advertising_; }
    Device::IDevice& DeviceInterface() override { return device_; }
    Display::IDisplay& DisplayInterface() override { return display_; }
    Lifecycle::ILifecycle& LifecycleInterface() override { return lifecycle_; }
    Localization::ILocalization& LocalizationInterface() override { return localization_; }
    Presentation::IPresentation& PresentationInterface() override { return presentation_; }
    Stats::IStats& StatsInterface() override { return stats_; }

private:
    void unsubscribeAll()
    {
        accessibility_.unsubscribeAll();
        lifecycle_.unsubscribeAll();
        localization_.unsubscribeAll();
        presentation_.unsubscribeAll();
    }

private:
    Accessibility::AccessibilityImpl accessibility_;
    Advertising::AdvertisingImpl advertising_;
    Device::DeviceImpl device_;
    Display::DisplayImpl display_;
    Lifecycle::LifecycleImpl lifecycle_;
    Localization::LocalizationImpl localization_;
    Presentation::PresentationImpl presentation_;
    Stats::StatsImpl stats_;
};

/* static */ IFireboltAccessor& IFireboltAccessor::Instance()
{
    static FireboltAccessorImpl impl;
    return impl;
}
} // namespace Firebolt
