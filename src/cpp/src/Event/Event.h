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

#include "Module.h"
#include "Transport/Transport.h"
#include "error.h"
namespace FireboltSDK
{

static constexpr uint32_t DefaultWaitTime = 1000;

class Event : public IEventHandler
{
public:
    typedef std::function<Firebolt::Error(void*, const void*, const string& parameters)> DispatchFunction;

private:
    enum State : uint8_t
    {
        IDLE,
        EXECUTING,
        REVOKED
    };

    struct CallbackData
    {
        const DispatchFunction lambda;
        const void* userdata;
        State state;
    };
    using CallbackMap = std::map<void*, CallbackData>;
    using EventMap = std::map<string, CallbackMap>;

    class Response : public WPEFramework::Core::JSON::Container
    {
    public:
        Response& operator=(const Response&) = delete;
        Response() : WPEFramework::Core::JSON::Container(), Listening(false) { Add(_T("listening"), &Listening); }
        Response(const Response& copy) : WPEFramework::Core::JSON::Container(), Listening(copy.Listening)
        {
            Add(_T("listening"), &Listening);
        }
        ~Response() override = default;

    public:
        WPEFramework::Core::JSON::Boolean Listening;
    };

private:
    Event();

public:
    ~Event() override;
    static Event& Instance();
    static void Dispose();
    void Configure(Transport<WPEFramework::Core::JSON::IElement>* transport);

public:
    template <typename RESULT, typename CALLBACK>
    Firebolt::Error Subscribe(const string& eventName, const CALLBACK& callback, void* usercb, const void* userdata)
    {
        JsonObject jsonParameters;
        return Subscribe<RESULT, CALLBACK>(eventName, jsonParameters, callback, usercb, userdata);
    }

    template <typename RESULT, typename CALLBACK>
    Firebolt::Error Subscribe(const string& eventName, JsonObject& jsonParameters, const CALLBACK& callback,
                              void* usercb, const void* userdata)
    {
        Firebolt::Error status = Firebolt::Error::General;
        if (_transport != nullptr)
        {

            status = Assign<RESULT, CALLBACK>(eventName, callback, usercb, userdata);
            if (status == Firebolt::Error::None)
            {
                Response response;

                WPEFramework::Core::JSON::Variant Listen = true;
                jsonParameters.Set(_T("listen"), Listen);
                string parameters;
                jsonParameters.ToString(parameters);

                status = _transport->Subscribe<Response>(eventName, parameters, response);

                if (status != Firebolt::Error::None)
                {
                    Revoke(eventName, usercb);
                }
                else if ((response.Listening.IsSet() == true) && (response.Listening.Value() == true))
                {
                    status = Firebolt::Error::None;
                }
            }
        }

        return status;
    }

    Firebolt::Error Unsubscribe(const string& eventName, void* usercb);

private:
    template <typename PARAMETERS, typename CALLBACK>
    Firebolt::Error Assign(const string& eventName, const CALLBACK& callback, void* usercb, const void* userdata)
    {
        Firebolt::Error status = Firebolt::Error::General;
        std::function<void(void* usercb, const void* userdata, void* parameters)> actualCallback = callback;
        DispatchFunction implementation = [actualCallback](void* usercb, const void* userdata,
                                                           const string& parameters) -> Firebolt::Error
        {
            WPEFramework::Core::ProxyType<PARAMETERS>* inbound = new WPEFramework::Core::ProxyType<PARAMETERS>();
            *inbound = WPEFramework::Core::ProxyType<PARAMETERS>::Create();
            (*inbound)->FromString(parameters);
            actualCallback(usercb, userdata, static_cast<void*>(inbound));
            return (Firebolt::Error::None);
        };
        CallbackData callbackData = {implementation, userdata, State::IDLE};

        _adminLock.Lock();
        EventMap::iterator eventIndex = _eventMap.find(eventName);
        if (eventIndex != _eventMap.end())
        {
            CallbackMap::iterator callbackIndex = eventIndex->second.find(usercb);
            if (callbackIndex == eventIndex->second.end())
            {
                eventIndex->second.emplace(std::piecewise_construct, std::forward_as_tuple(usercb),
                                           std::forward_as_tuple(callbackData));
                status = Firebolt::Error::None;
            }
        }
        else
        {

            CallbackMap callbackMap;
            callbackMap.emplace(std::piecewise_construct, std::forward_as_tuple(usercb),
                                std::forward_as_tuple(callbackData));
            _eventMap.emplace(std::piecewise_construct, std::forward_as_tuple(eventName),
                              std::forward_as_tuple(callbackMap));
            status = Firebolt::Error::None;
        }

        _adminLock.Unlock();
        return status;
    }
    Firebolt::Error Revoke(const string& eventName, void* usercb);

private:
    void Clear();
    Firebolt::Error ValidateResponse(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& jsonResponse,
                                     bool& enabled) override;
    Firebolt::Error
    Dispatch(const string& eventName,
             const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& jsonResponse) override;

private:
    EventMap _eventMap;
    WPEFramework::Core::CriticalSection _adminLock;
    Transport<WPEFramework::Core::JSON::IElement>* _transport;

    static Event* _singleton;
};
} // namespace FireboltSDK