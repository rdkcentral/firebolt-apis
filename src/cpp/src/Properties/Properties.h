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

#pragma once

#include "Accessor/Accessor.h"
#include "Event/Event.h"

namespace FireboltSDK
{

class Properties
{
public:
    Properties(const Properties&) = delete;
    Properties& operator=(const Properties&) = delete;

    Properties() = default;
    ~Properties() = default;

public:
    template <typename RESPONSETYPE>
    static Firebolt::Error Get(const string& propertyName, WPEFramework::Core::ProxyType<RESPONSETYPE>& response)
    {
        Firebolt::Error status = Firebolt::Error::General;
        Transport<WPEFramework::Core::JSON::IElement>* transport = Accessor::Instance().GetTransport();
        if (transport != nullptr)
        {
            JsonObject parameters;
            RESPONSETYPE responseType;
            status = transport->Invoke(propertyName, parameters, responseType);
            if (status == Firebolt::Error::None)
            {
                ASSERT(response.IsValid() == false);
                if (response.IsValid() == true)
                {
                    response.Release();
                }
                response = WPEFramework::Core::ProxyType<RESPONSETYPE>::Create();
                (*response) = responseType;
            }
        }
        else
        {
            FIREBOLT_LOG_ERROR(Logger::Category::OpenRPC, Logger::Module<Accessor>(),
                               "Error in getting Transport err = %d", status);
        }

        return status;
    }

    template <typename PARAMETERS, typename RESPONSETYPE>
    static Firebolt::Error Get(const string& propertyName, const PARAMETERS& parameters,
                               WPEFramework::Core::ProxyType<RESPONSETYPE>& response)
    {
        Firebolt::Error status = Firebolt::Error::General;
        Transport<WPEFramework::Core::JSON::IElement>* transport = Accessor::Instance().GetTransport();
        if (transport != nullptr)
        {
            RESPONSETYPE responseType;
            status = transport->Invoke(propertyName, parameters, responseType);
            if (status == Firebolt::Error::None)
            {
                ASSERT(response.IsValid() == false);
                if (response.IsValid() == true)
                {
                    response.Release();
                }
                response = WPEFramework::Core::ProxyType<RESPONSETYPE>::Create();
                (*response) = responseType;
            }
        }
        else
        {
            FIREBOLT_LOG_ERROR(Logger::Category::OpenRPC, Logger::Module<Accessor>(),
                               "Error in getting Transport err = %d", status);
        }

        return status;
    }

    template <typename RESPONSETYPE> static Firebolt::Error Get(const string& propertyName, RESPONSETYPE& response)
    {
        Firebolt::Error status = Firebolt::Error::General;
        Transport<WPEFramework::Core::JSON::IElement>* transport = Accessor::Instance().GetTransport();
        if (transport != nullptr)
        {
            JsonObject parameters;
            status = transport->Invoke(propertyName, parameters, response);
        }
        else
        {
            FIREBOLT_LOG_ERROR(Logger::Category::OpenRPC, Logger::Module<Accessor>(),
                               "Error in getting Transport err = %d", status);
        }

        return status;
    }

    template <typename PARAMETERS, typename RESPONSETYPE>
    static Firebolt::Error Get(const string& propertyName, const PARAMETERS& parameters, RESPONSETYPE& response)
    {
        Firebolt::Error status = Firebolt::Error::General;
        Transport<WPEFramework::Core::JSON::IElement>* transport = Accessor::Instance().GetTransport();
        if (transport != nullptr)
        {
            status = transport->Invoke(propertyName, parameters, response);
        }
        else
        {
            FIREBOLT_LOG_ERROR(Logger::Category::OpenRPC, Logger::Module<Accessor>(),
                               "Error in getting Transport err = %d", status);
        }

        return status;
    }

    template <typename PARAMETERS> static Firebolt::Error Set(const string& propertyName, const PARAMETERS& parameters)
    {
        Firebolt::Error status = Firebolt::Error::General;
        Transport<WPEFramework::Core::JSON::IElement>* transport = Accessor::Instance().GetTransport();
        if (transport != nullptr)
        {
            JsonObject responseType;
            status = transport->Invoke(propertyName, parameters, responseType);
        }
        else
        {
            FIREBOLT_LOG_ERROR(Logger::Category::OpenRPC, Logger::Module<Accessor>(),
                               "Error in getting Transport err = %d", status);
        }

        return status;
    }

    template <typename RESULT, typename CALLBACK>
    static Firebolt::Error Subscribe(const string& propertyName, JsonObject& paramsters, const CALLBACK& callback,
                                     void* usercb, const void* userdata)
    {
        return Event::Instance().Subscribe<RESULT, CALLBACK>(EventName(propertyName), paramsters, callback, usercb,
                                                             userdata);
    }

    static Firebolt::Error Unsubscribe(const string& propertyName, void* usercb)
    {
        return Event::Instance().Unsubscribe(EventName(propertyName), usercb);
    }

private:
    static inline string EventName(const string& propertyName)
    {
        size_t pos = propertyName.find_first_of('.');
        string eventName = propertyName;
        if (pos != std::string::npos)
        {
            eventName[pos + 1] = std::toupper(eventName[pos + 1]);
            eventName = string(eventName.substr(0, pos + 1) + "on" + eventName.substr(pos + 1) + "Changed");
        }
        return eventName;
    }
};
} // namespace FireboltSDK
