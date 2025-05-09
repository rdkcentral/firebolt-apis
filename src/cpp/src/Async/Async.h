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
// #include "error.h"
namespace FireboltSDK
{

class Async
{
private:
    Async();

public:
    virtual ~Async();
    Async(const Async&) = delete;
    Async& operator=(const Async&) = delete;

public:
    typedef std::function<Firebolt::Error(Async& parent, void*)> DispatchFunction;

    class Job : public WPEFramework::Core::IDispatch
    {
    protected:
        Job(Async& parent, const string& method, const DispatchFunction lambda, void* usercb)
            : _parent(parent), _method(method), _lambda(lambda), _usercb(usercb)
        {
        }

    public:
        Job() = delete;
        Job(const Job&) = delete;
        Job& operator=(const Job&) = delete;

        ~Job() = default;

    public:
        static WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>
        Create(Async& parent, const string& method, const DispatchFunction lambda, void* usercb);

        void Dispatch() override { _lambda(_parent, _usercb); }

    private:
        Async& _parent;
        string _method;
        DispatchFunction _lambda;
        void* _usercb;
    };

public:
    struct CallbackData
    {
        const DispatchFunction lambda;
        WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job;
        uint32_t id;
    };

    using CallbackMap = std::map<void*, CallbackData>;
    using MethodMap = std::map<string, CallbackMap>;

private:
    static constexpr uint32_t DefaultId = 0xFFFFFFFF;
    static constexpr uint32_t DefaultWaitTime = WPEFramework::Core::infinite;

public:
    static Async& Instance();
    static void Dispose();
    void Configure(Transport<WPEFramework::Core::JSON::IElement>* transport);

public:
    template <typename RESPONSE, typename PARAMETERS, typename CALLBACK>
    Firebolt::Error Invoke(const string& method, const PARAMETERS& parameters, const CALLBACK& callback, void* usercb,
                           uint32_t waitTime = DefaultWaitTime)
    {
        Firebolt::Error status = Firebolt::Error::None;
        if (_transport != nullptr)
        {
            Transport<WPEFramework::Core::JSON::IElement>* transport = _transport;
            std::function<void(void* usercb, void* response, Firebolt::Error status)> actualCallback = callback;
            DispatchFunction lambda = [actualCallback, transport, method, parameters,
                                       waitTime](Async& parent, void* usercb) -> Firebolt::Error
            {
                RESPONSE response;
                uint32_t id = DefaultId;
                Firebolt::Error status = transport->InvokeAsync(method, parameters, id);
                if (status == Firebolt::Error::None && parent.IsActive(method, usercb) == true)
                {
                    parent.UpdateEntry(method, usercb, id);
                    status = transport->WaitForResponse(id, response, waitTime);
                    if (status == Firebolt::Error::None && parent.IsActive(method, usercb) == true)
                    {
                        WPEFramework::Core::ProxyType<RESPONSE>* jsonResponse =
                            new WPEFramework::Core::ProxyType<RESPONSE>();
                        *jsonResponse = WPEFramework::Core::ProxyType<RESPONSE>::Create();
                        (*jsonResponse)->FromString(response);
                        actualCallback(usercb, jsonResponse, status);
                        parent.RemoveEntry(method, usercb);
                    }
                }
                return (status);
            };

            _adminLock.Lock();
            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job =
                WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(
                    WPEFramework::Core::ProxyType<Async::Job>::Create(*this, method, lambda, usercb));
            CallbackData callbackData = {lambda, job, DefaultId};
            MethodMap::iterator index = _methodMap.find(method);
            if (index != _methodMap.end())
            {
                CallbackMap::iterator callbackIndex = index->second.find(usercb);
                if (callbackIndex == index->second.end())
                {
                    index->second.emplace(std::piecewise_construct, std::forward_as_tuple(usercb),
                                          std::forward_as_tuple(callbackData));
                }
            }
            else
            {

                CallbackMap callbackMap;
                callbackMap.emplace(std::piecewise_construct, std::forward_as_tuple(usercb),
                                    std::forward_as_tuple(callbackData));
                _methodMap.emplace(std::piecewise_construct, std::forward_as_tuple(method),
                                   std::forward_as_tuple(callbackMap));
            }
            _adminLock.Unlock();

            WPEFramework::Core::IWorkerPool::Instance().Submit(job);
        }

        return status;
    }

    Firebolt::Error Abort(const string& method, void* usercb)
    {
        RemoveEntry(method, usercb);
        return (Firebolt::Error::None);
    }

    void UpdateEntry(const string& method, void* usercb, uint32_t id)
    {
        _adminLock.Lock();
        MethodMap::iterator index = _methodMap.find(method);
        if (index != _methodMap.end())
        {
            CallbackMap::iterator callbackIndex = index->second.find(usercb);
            if (callbackIndex != index->second.end())
            {
                callbackIndex->second.id = id;
            }
        }
        _adminLock.Unlock();
    }

    void RemoveEntry(const string& method, void* usercb)
    {
        _adminLock.Lock();
        MethodMap::iterator index = _methodMap.find(method);
        if (index != _methodMap.end())
        {
            CallbackMap::iterator callbackIndex = index->second.find(usercb);
            if (callbackIndex != index->second.end())
            {
                if (IsValidJob(callbackIndex->second))
                {
                    WPEFramework::Core::IWorkerPool::Instance().Revoke(callbackIndex->second.job);
                }
                index->second.erase(callbackIndex);
                if (index->second.size() == 0)
                {
                    _methodMap.erase(index);
                }
            }
        }
        _adminLock.Unlock();
    }

    bool IsActive(const string& method, void* usercb)
    {
        bool valid = false;
        _adminLock.Lock();
        MethodMap::iterator index = _methodMap.find(method);
        if (index != _methodMap.end())
        {
            CallbackMap::iterator callbackIndex = index->second.find(usercb);
            if (callbackIndex != index->second.end())
            {
                valid = true;
            }
        }
        _adminLock.Unlock();
        return valid;
    }

private:
    void Clear();
    inline bool IsValidJob(CallbackData& callbackData)
    {
        return (callbackData.job.IsValid() && (callbackData.id == DefaultId));
    }

private:
    MethodMap _methodMap;
    WPEFramework::Core::CriticalSection _adminLock;
    Transport<WPEFramework::Core::JSON::IElement>* _transport;

    static Async* _singleton;
};
} // namespace FireboltSDK
