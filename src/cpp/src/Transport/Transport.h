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
#include "error.h"

namespace FireboltSDK
{

using namespace WPEFramework::Core::TypeTraits;

template <typename SOCKETTYPE, typename INTERFACE, typename CLIENT, typename MESSAGETYPE> class CommunicationChannel
{
public:
    typedef std::function<void(const INTERFACE&)> Callback;
    class Entry
    {
    private:
        Entry(const Entry&) = delete;
        Entry& operator=(const Entry& rhs) = delete;
        struct Synchronous
        {
            Synchronous() : _signal(false, true), _response() {}
            WPEFramework::Core::Event _signal;
            std::list<WPEFramework::Core::ProxyType<MESSAGETYPE>> _response;
        };
        struct ASynchronous
        {
            ASynchronous(const uint32_t waitTime, const Callback& completed)
                : _waitTime(WPEFramework::Core::Time::Now().Add(waitTime).Ticks()), _completed(completed)
            {
            }
            uint64_t _waitTime;
            Callback _completed;
        };

    public:
        Entry() : _synchronous(true), _info() {}
        Entry(const uint32_t waitTime, const Callback& completed) : _synchronous(false), _info(waitTime, completed) {}
        ~Entry()
        {
            if (_synchronous == true)
            {
                _info.sync.~Synchronous();
            }
            else
            {
                _info.async.~ASynchronous();
            }
        }

    public:
        const WPEFramework::Core::ProxyType<MESSAGETYPE>& Response() const { return (*(_info.sync._response.begin())); }
        bool Signal(const WPEFramework::Core::ProxyType<MESSAGETYPE>& response)
        {
            if (_synchronous == true)
            {
                _info.sync._response.push_back(response);
                _info.sync._signal.SetEvent();
            }
            else
            {
                _info.async._completed(*response);
            }

            return (_synchronous == false);
        }
        const uint64_t& Expiry() const { return (_info.async._waitTime); }
        void Abort(const uint32_t id)
        {
            if (_synchronous == true)
            {
                _info.sync._signal.SetEvent();
            }
            else
            {
                MESSAGETYPE message;
                ToMessage(id, message, WPEFramework::Core::ERROR_ASYNC_ABORTED);
                _info.async._completed(message);
            }
        }
        bool Expired(const uint32_t id, const uint64_t& currentTime, uint64_t& nextTime)
        {
            bool expired = false;

            if (_synchronous == false)
            {
                if (_info.async._waitTime > currentTime)
                {
                    if (_info.async._waitTime < nextTime)
                    {
                        nextTime = _info.async._waitTime;
                    }
                }
                else
                {
                    MESSAGETYPE message;
                    ToMessage(id, message, WPEFramework::Core::ERROR_TIMEDOUT);
                    _info.async._completed(message);
                    expired = true;
                }
            }
            return (expired);
        }
        bool WaitForResponse(const uint32_t waitTime)
        {
            return (_info.sync._signal.Lock(waitTime) == WPEFramework::Core::ERROR_NONE);
        }

    private:
        void ToMessage(const uint32_t id, WPEFramework::Core::JSONRPC::Message& message, uint32_t error)
        {
            message.Id = id;
            message.Error.Code = error;
            switch (error)
            {
            case WPEFramework::Core::ERROR_ASYNC_ABORTED:
            {
                message.Error.Text = _T("Pending a-sync call has been aborted");
                break;
            }
            case WPEFramework::Core::ERROR_TIMEDOUT:
            {
                message.Error.Text = _T("Pending a-sync call has timed out");
                break;
            }
            }
        }

        bool _synchronous;
        union Info
        {
        public:
            Info() : sync() {}
            Info(const uint32_t waitTime, const Callback& completed) : async(waitTime, completed) {}
            ~Info() {}
            Synchronous sync;
            ASynchronous async;
        } _info;
    };

private:
    class FactoryImpl
    {
    private:
        FactoryImpl(const FactoryImpl&) = delete;
        FactoryImpl& operator=(const FactoryImpl&) = delete;

        class WatchDog
        {
        private:
            WatchDog() = delete;
            WatchDog& operator=(const WatchDog&) = delete;

        public:
            WatchDog(CLIENT* client) : _client(client) {}
            WatchDog(const WatchDog& copy) : _client(copy._client) {}
            ~WatchDog() {}

            bool operator==(const WatchDog& rhs) const { return (rhs._client == _client); }
            bool operator!=(const WatchDog& rhs) const { return (!operator==(rhs)); }

        public:
            uint64_t Timed(const uint64_t scheduledTime) { return (_client->Timed()); }

        private:
            CLIENT* _client;
        };

        friend WPEFramework::Core::SingletonType<FactoryImpl>;

        FactoryImpl()
            : _messageFactory(2), _watchDog(WPEFramework::Core::Thread::DefaultStackSize(), _T("TransportCleaner"))
        {
        }

    public:
        static FactoryImpl& Instance() { return (WPEFramework::Core::SingletonType<FactoryImpl>::Instance()); }

        ~FactoryImpl() {}

    public:
        WPEFramework::Core::ProxyType<MESSAGETYPE> Element(const string&) { return (_messageFactory.Element()); }
        void Trigger(const uint64_t& time, CLIENT* client) { _watchDog.Trigger(time, client); }
        void Revoke(CLIENT* client) { _watchDog.Revoke(client); }

    private:
        WPEFramework::Core::ProxyPoolType<MESSAGETYPE> _messageFactory;
        WPEFramework::Core::TimerType<WatchDog> _watchDog;
    };

    class ChannelImpl
        : public WPEFramework::Core::StreamJSONType<WPEFramework::Web::WebSocketClientType<SOCKETTYPE>, FactoryImpl&, INTERFACE>
    {
    private:
        ChannelImpl(const ChannelImpl&) = delete;
        ChannelImpl& operator=(const ChannelImpl&) = delete;

        typedef WPEFramework::Core::StreamJSONType<WPEFramework::Web::WebSocketClientType<SOCKETTYPE>, FactoryImpl&, INTERFACE>
            BaseClass;

    public:
        ChannelImpl(CommunicationChannel* parent, const WPEFramework::Core::NodeId& remoteNode, const string& path,
                    const string& query, const bool mask)
            : BaseClass(5, FactoryImpl::Instance(), path, _T("JSON"), query, "", false, mask, false,
                        remoteNode.AnyInterface(), remoteNode, 512, 512),
              _parent(*parent)
        {
        }
        ~ChannelImpl() override = default;

    public:
        void Received(WPEFramework::Core::ProxyType<INTERFACE>& response) override
        {
            WPEFramework::Core::ProxyType<MESSAGETYPE> inbound(response);

            ASSERT(inbound.IsValid() == true);
            if (inbound.IsValid() == true)
            {
                _parent.Inbound(inbound);
            }
        }
        void Send(WPEFramework::Core::ProxyType<INTERFACE>& msg) override
        {
#ifdef __DEBUG__
            string message;
            ToMessage(msg, message);
            TRACE_L1("Message: %s send", message.c_str());
#endif
        }
        void StateChange() override { _parent.StateChange(); }
        bool IsIdle() const override { return (true); }

    private:
        void ToMessage(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::IElement>& jsonObject,
                       string& message) const
        {
            WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> inbound(jsonObject);

            ASSERT(inbound.IsValid() == true);
            if (inbound.IsValid() == true)
            {
                inbound->ToString(message);
            }
        }
        void ToMessage(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::IMessagePack>& jsonObject,
                       string& message) const
        {
            WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> inbound(jsonObject);

            ASSERT(inbound.IsValid() == true);
            if (inbound.IsValid() == true)
            {
                std::vector<uint8_t> values;
                inbound->ToBuffer(values);
                if (values.empty() != true)
                {
                    WPEFramework::Core::ToString(values.data(), static_cast<uint16_t>(values.size()), false, message);
                }
            }
        }

    private:
        CommunicationChannel& _parent;
    };

protected:
    CommunicationChannel(const WPEFramework::Core::NodeId& remoteNode, const string& path, const string& query,
                         const bool mask)
        : _channel(this, remoteNode, path, query, mask), _sequence(0)
    {
    }

public:
    ~CommunicationChannel() = default;
    static WPEFramework::Core::ProxyType<CommunicationChannel> Instance(const WPEFramework::Core::NodeId& remoteNode,
                                                                        const string& path, const string& query,
                                                                        const bool mask = true)
    {
        static WPEFramework::Core::ProxyMapType<string, CommunicationChannel> channelMap;

        string searchLine = remoteNode.HostAddress() + '@' + path;

        return (channelMap.template Instance<CommunicationChannel>(searchLine, remoteNode, path, query, mask));
    }

public:
    static void Trigger(const uint64_t& time, CLIENT* client) { FactoryImpl::Instance().Trigger(time, client); }
    static WPEFramework::Core::ProxyType<MESSAGETYPE> Message() { return (FactoryImpl::Instance().Element(string())); }
    uint32_t Sequence() const { return (++_sequence); }
    void Register(CLIENT& client)
    {
        _adminLock.Lock();
        ASSERT(std::find(_observers.begin(), _observers.end(), &client) == _observers.end());
        _observers.push_back(&client);
        if (_channel.IsOpen() == true)
        {
            client.Opened();
        }
        _adminLock.Unlock();
    }
    void Unregister(CLIENT& client)
    {
        _adminLock.Lock();
        typename std::list<CLIENT*>::iterator index(std::find(_observers.begin(), _observers.end(), &client));
        if (index != _observers.end())
        {
            _observers.erase(index);
        }
        FactoryImpl::Instance().Revoke(&client);
        _adminLock.Unlock();
    }

    void Submit(const WPEFramework::Core::ProxyType<INTERFACE>& message) { _channel.Submit(message); }
    bool IsSuspended() const { return (_channel.IsSuspended()); }
    uint32_t Initialize() { return (Open(0)); }
    void Deinitialize() { Close(); }
    bool IsOpen() { return (_channel.IsOpen() == true); }

protected:
    void StateChange()
    {
        _adminLock.Lock();
        typename std::list<CLIENT*>::iterator index(_observers.begin());
        while (index != _observers.end())
        {
            if (_channel.IsOpen() == true)
            {
                (*index)->Opened();
            }
            else
            {
                (*index)->Closed();
            }
            index++;
        }
        _adminLock.Unlock();
    }
    bool Open(const uint32_t waitTime)
    {
        bool result = true;
        if (_channel.IsClosed() == true)
        {
            result = (_channel.Open(waitTime) == WPEFramework::Core::ERROR_NONE);
        }
        return (result);
    }
    void Close() { _channel.Close(WPEFramework::Core::infinite); }

private:
    int32_t Inbound(const WPEFramework::Core::ProxyType<MESSAGETYPE>& inbound)
    {
        int32_t result = WPEFramework::Core::ERROR_UNAVAILABLE;
        _adminLock.Lock();
        typename std::list<CLIENT*>::iterator index(_observers.begin());
        while ((result != WPEFramework::Core::ERROR_NONE) && (index != _observers.end()))
        {
            result = (*index)->Submit(inbound);
            index++;
        }
        _adminLock.Unlock();

        return (result);
    }

private:
    WPEFramework::Core::CriticalSection _adminLock;
    ChannelImpl _channel;
    mutable std::atomic<uint32_t> _sequence;
    std::list<CLIENT*> _observers;
};

class IEventHandler
{
public:
    virtual Firebolt::Error
    ValidateResponse(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& jsonResponse,
                     bool& enabled) = 0;
    virtual Firebolt::Error
    Dispatch(const string& eventName,
             const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& jsonResponse) = 0;
    virtual ~IEventHandler() = default;
};

template <typename INTERFACE> class Transport
{
private:
    using Channel =
        CommunicationChannel<WPEFramework::Core::SocketStream, INTERFACE, Transport, WPEFramework::Core::JSONRPC::Message>;
    using Entry = typename CommunicationChannel<WPEFramework::Core::SocketStream, INTERFACE, Transport,
                                                WPEFramework::Core::JSONRPC::Message>::Entry;
    using PendingMap = std::unordered_map<uint32_t, Entry>;
    using EventMap = std::map<string, uint32_t>;
    typedef std::function<uint32_t(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& jsonResponse,
                                   bool& enabled)>
        EventResponseValidatioionFunction;

    class CommunicationJob : public WPEFramework::Core::IDispatch
    {
    protected:
        CommunicationJob(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& inbound,
                         class Transport* parent)
            : _inbound(inbound), _parent(parent)
        {
        }

    public:
        CommunicationJob() = delete;
        CommunicationJob(const CommunicationJob&) = delete;
        CommunicationJob& operator=(const CommunicationJob&) = delete;

        ~CommunicationJob() = default;

    public:
        static WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>
        Create(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& inbound,
               class Transport* parent);

        void Dispatch() override { _parent->Inbound(_inbound); }

    private:
        const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> _inbound;
        class Transport* _parent;
    };

    class ConnectionJob : public WPEFramework::Core::IDispatch
    {
    protected:
        ConnectionJob(class Transport* parent) : _parent(parent) {}

    public:
        ConnectionJob() = delete;
        ConnectionJob(const ConnectionJob&) = delete;
        ConnectionJob& operator=(const ConnectionJob&) = delete;

        ~ConnectionJob() = default;

    public:
        static WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> Create(class Transport* parent);

        void Dispatch() override
        {
            if (Firebolt::Error::None != _parent->WaitForLinkReady())
            {
                _parent->NotifyStatus(Firebolt::Error::Timedout);
            }
        }

    private:
        const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> _inbound;
        class Transport* _parent;
    };

protected:
    static constexpr uint32_t DefaultWaitTime = 10000;

    inline void Announce() { _channel->Register(*this); }

private:
    static constexpr const TCHAR* PathPrefix = _T("/");

public:
    typedef std::function<void(const bool connected, const Firebolt::Error error)> Listener;

public:
    Transport() = delete;
    Transport(const Transport&) = delete;
    Transport& operator=(Transport&) = delete;
    Transport(const WPEFramework::Core::URL& url, const uint32_t waitTime, const Listener listener)
        : _adminLock(), _connectId(WPEFramework::Core::NodeId(url.Host().Value().c_str(), url.Port().Value())),
          _channel(Channel::Instance(_connectId,
                                     ((url.Path().Value().rfind(PathPrefix, 0) == 0)
                                          ? url.Path().Value()
                                          : string(PathPrefix + url.Path().Value())),
                                     url.Query().Value(), true)),
          _eventHandler(nullptr), _pendingQueue(), _scheduledTime(0), _waitTime(waitTime), _listener(listener),
          _connected(false), _status(Firebolt::Error::NotConnected)
    {
        _channel->Register(*this);
        WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job =
            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(
                WPEFramework::Core::ProxyType<Transport::ConnectionJob>::Create(this));
        WPEFramework::Core::IWorkerPool::Instance().Submit(job);
    }

    virtual ~Transport()
    {
        _channel->Unregister(*this);

        for (auto& element : _pendingQueue)
        {
            element.second.Abort(element.first);
        }
    }

public:
    inline bool IsOpen() { return _channel->IsOpen(); }

    void Revoke(const string& eventName)
    {
        _adminLock.Lock();
        _eventMap.erase(eventName);
        _adminLock.Unlock();
    }

    void SetEventHandler(IEventHandler* eventHandler) { _eventHandler = eventHandler; }

    template <typename PARAMETERS, typename RESPONSE>
    Firebolt::Error Invoke(const string& method, const PARAMETERS& parameters, RESPONSE& response)
    {
        Entry slot;
        uint32_t id = _channel->Sequence();
        Firebolt::Error result = Send(method, parameters, id);
        if (result == Firebolt::Error::None)
        {
            result = WaitForResponse<RESPONSE>(id, response, _waitTime);
        }

        return (result);
    }

    template <typename PARAMETERS>
    Firebolt::Error InvokeAsync(const string& method, const PARAMETERS& parameters, uint32_t& id)
    {
        Entry slot;
        id = _channel->Sequence();
        return Send(method, parameters, id);
    }

    template <typename RESPONSE>
    Firebolt::Error WaitForResponse(const uint32_t& id, RESPONSE& response, const uint32_t waitTime)
    {
        int32_t result = WPEFramework::Core::ERROR_TIMEDOUT;
        _adminLock.Lock();
        typename PendingMap::iterator index = _pendingQueue.find(id);
        Entry& slot(index->second);
        _adminLock.Unlock();

        if (slot.WaitForResponse(waitTime) == true)
        {
            WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> jsonResponse = slot.Response();

            // See if we have a jsonResponse, maybe it was just the connection
            // that closed?
            if (jsonResponse.IsValid() == true)
            {
                if (jsonResponse->Error.IsSet() == true)
                {
                    result = jsonResponse->Error.Code.Value();
                }
                else
                {
                    result = WPEFramework::Core::ERROR_NONE;
                    if ((jsonResponse->Result.IsSet() == true) && (jsonResponse->Result.Value().empty() == false))
                    {
                        FromMessage((INTERFACE*)&response, *jsonResponse);
                    }
                }
            }
        }
        else
        {
            result = WPEFramework::Core::ERROR_TIMEDOUT;
        }
        _adminLock.Lock();
        _pendingQueue.erase(id);
        _adminLock.Unlock();
        return FireboltErrorValue(result);
    }

    void Abort(uint32_t id)
    {
        _adminLock.Lock();
        typename PendingMap::iterator index = _pendingQueue.find(id);
        Entry& slot(index->second);
        _adminLock.Unlock();
        slot.Abort(id);
    }

    template <typename RESPONSE>
    Firebolt::Error Subscribe(const string& eventName, const string& parameters, RESPONSE& response)
    {
        Entry slot;
        uint32_t id = _channel->Sequence();
        Firebolt::Error result = Send(eventName, parameters, id);
        if (result == Firebolt::Error::None)
        {
            _adminLock.Lock();
            _eventMap.emplace(std::piecewise_construct, std::forward_as_tuple(eventName), std::forward_as_tuple(~0));
            _adminLock.Unlock();

            result = WaitForEventResponse(id, eventName, response, _waitTime);
        }

        return (result);
    }

    Firebolt::Error Unsubscribe(const string& eventName, const string& parameters)
    {
        Revoke(eventName);
        Entry slot;
        uint32_t id = _channel->Sequence();

        return Send(eventName, parameters, id);
    }

    void NotifyStatus(Firebolt::Error status) { _listener(false, status); }

    Firebolt::Error WaitForLinkReady()
    {
        uint32_t waiting = _waitTime;
        static constexpr uint32_t SLEEPSLOT_TIME = 100;

        // Right, a wait till connection is closed is requested..
        while ((waiting > 0) && (IsOpen() == false) && (_status == Firebolt::Error::NotConnected))
        {

            uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);

            // Right, lets sleep in slices of 100 ms
            SleepMs(sleepSlot);

            waiting -= (waiting == WPEFramework::Core::infinite ? 0 : sleepSlot);
        }
        return (((waiting == 0) || (IsOpen() == true)) ? Firebolt::Error::None : Firebolt::Error::Timedout);
    }

private:
    friend Channel;
    inline bool IsEvent(const uint32_t id, string& eventName)
    {
        _adminLock.Lock();
        for (auto& event : _eventMap)
        {
            if (event.second == id)
            {
                eventName = event.first;
                break;
            }
        }
        _adminLock.Unlock();
        return (eventName.empty() != true);
    }
    uint64_t Timed()
    {
        uint64_t result = ~0;
        uint64_t currentTime = WPEFramework::Core::Time::Now().Ticks();

        // Lets see if some callback are expire. If so trigger and remove...
        _adminLock.Lock();

        typename PendingMap::iterator index = _pendingQueue.begin();

        while (index != _pendingQueue.end())
        {

            if (index->second.Expired(index->first, currentTime, result) == true)
            {
                index = _pendingQueue.erase(index);
            }
            else
            {
                index++;
            }
        }
        _scheduledTime = (result != static_cast<uint64_t>(~0) ? result : 0);

        _adminLock.Unlock();

        return (_scheduledTime);
    }

    virtual void Opened()
    {
        _status = Firebolt::Error::None;
        if (_connected != true)
        {
            _connected = true;
            _listener(_connected, _status);
        }
    }

    void Closed()
    {
        // Abort any in progress RPC command:
        _adminLock.Lock();

        // See if we issued anything, if so abort it..
        while (_pendingQueue.size() != 0)
        {

            _pendingQueue.begin()->second.Abort(_pendingQueue.begin()->first);
            _pendingQueue.erase(_pendingQueue.begin());
        }

        _adminLock.Unlock();
        if (_connected != false)
        {
            _connected = false;
            _listener(_connected, _status);
        }
    }

    int32_t Submit(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& inbound)
    {
        int32_t result = WPEFramework::Core::ERROR_UNAVAILABLE;
        WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job =
            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(
                WPEFramework::Core::ProxyType<Transport::CommunicationJob>::Create(inbound, this));
        WPEFramework::Core::IWorkerPool::Instance().Submit(job);
        return result;
    }

    int32_t Inbound(const WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& inbound)
    {
        int32_t result = WPEFramework::Core::ERROR_INVALID_SIGNATURE;

        ASSERT(inbound.IsValid() == true);

        if ((inbound->Id.IsSet() == true) && (inbound->Result.IsSet() || inbound->Error.IsSet()))
        {
            // Looks like this is a response..
            ASSERT(inbound->Parameters.IsSet() == false);
            ASSERT(inbound->Designator.IsSet() == false);

            _adminLock.Lock();

            // See if we issued this..
            typename PendingMap::iterator index = _pendingQueue.find(inbound->Id.Value());

            if (index != _pendingQueue.end())
            {

                if (index->second.Signal(inbound) == true)
                {
                    _pendingQueue.erase(index);
                }

                result = WPEFramework::Core::ERROR_NONE;
                _adminLock.Unlock();
            }
            else
            {
                _adminLock.Unlock();
                string eventName;
                if (IsEvent(inbound->Id.Value(), eventName))
                {
                    _eventHandler->Dispatch(eventName, inbound);
                }
            }
        }

        return (result);
    }

    template <typename PARAMETERS>
    Firebolt::Error Send(const string& method, const PARAMETERS& parameters, const uint32_t& id)
    {
        int32_t result = WPEFramework::Core::ERROR_UNAVAILABLE;

        if ((_channel.IsValid() == true) && (_channel->IsSuspended() == true))
        {
            result = WPEFramework::Core::ERROR_ASYNC_FAILED;
        }
        else if (_channel.IsValid() == true)
        {

            result = WPEFramework::Core::ERROR_ASYNC_FAILED;

            WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> message(Channel::Message());
            message->Id = id;
            message->Designator = method;
            ToMessage(parameters, message);

            _adminLock.Lock();

            typename std::pair<typename PendingMap::iterator, bool> newElement =
                _pendingQueue.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple());
            ASSERT(newElement.second == true);

            if (newElement.second == true)
            {

                _adminLock.Unlock();

                _channel->Submit(WPEFramework::Core::ProxyType<INTERFACE>(message));

                message.Release();
                result = WPEFramework::Core::ERROR_NONE;
            }
        }
        return FireboltErrorValue(result);
    }

    static constexpr uint32_t WAITSLOT_TIME = 100;
    template <typename RESPONSE>
    Firebolt::Error WaitForEventResponse(const uint32_t& id, const string& eventName, RESPONSE& response,
                                         const uint32_t waitTime)
    {
        Firebolt::Error result = Firebolt::Error::Timedout;
        _adminLock.Lock();
        typename PendingMap::iterator index = _pendingQueue.find(id);
        Entry& slot(index->second);
        _adminLock.Unlock();

        uint8_t waiting = waitTime;
        do
        {
            uint32_t waitSlot = (waiting > WAITSLOT_TIME ? WAITSLOT_TIME : waiting);
            if (slot.WaitForResponse(waitSlot) == true)
            {
                WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message> jsonResponse = slot.Response();

                // See if we have a jsonResponse, maybe it was just the connection
                // that closed?
                if (jsonResponse.IsValid() == true)
                {
                    if (jsonResponse->Error.IsSet() == true)
                    {
                        result = FireboltErrorValue(jsonResponse->Error.Code.Value());
                    }
                    else
                    {
                        if ((jsonResponse->Result.IsSet() == true) && (jsonResponse->Result.Value().empty() == false))
                        {
                            bool enabled;
                            result = _eventHandler->ValidateResponse(jsonResponse, enabled);
                            if (result == Firebolt::Error::None)
                            {
                                FromMessage((INTERFACE*)&response, *jsonResponse);
                                if (enabled)
                                {
                                    _adminLock.Lock();
                                    typename EventMap::iterator index = _eventMap.find(eventName);
                                    if (index != _eventMap.end())
                                    {
                                        index->second = id;
                                    }
                                    _adminLock.Unlock();
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                result = Firebolt::Error::Timedout;
            }
            waiting -= (waiting == WPEFramework::Core::infinite ? 0 : waitSlot);
        } while ((result != Firebolt::Error::None) && (waiting > 0));
        _adminLock.Lock();
        _pendingQueue.erase(id);
        _adminLock.Unlock();

        return result;
    }

public:
    void FromMessage(WPEFramework::Core::JSON::IElement* response, const WPEFramework::Core::JSONRPC::Message& message) const
    {
        response->FromString(message.Result.Value());
    }

    void FromMessage(WPEFramework::Core::JSON::IMessagePack* response,
                     const WPEFramework::Core::JSONRPC::Message& message) const
    {
        string value = message.Result.Value();
        std::vector<uint8_t> result(value.begin(), value.end());
        response->FromBuffer(result);
    }

private:
    void ToMessage(const string& parameters,
                   WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& message) const
    {
        if (parameters.empty() != true)
        {
            message->Parameters = parameters;
        }
    }

    template <typename PARAMETERS>
    void ToMessage(PARAMETERS& parameters,
                   WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& message) const
    {
        ToMessage((INTERFACE*)(&parameters), message);
        return;
    }

    void ToMessage(WPEFramework::Core::JSON::IMessagePack* parameters,
                   WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& message) const
    {
        std::vector<uint8_t> values;
        parameters->ToBuffer(values);
        if (values.empty() != true)
        {
            string strValues(values.begin(), values.end());
            message->Parameters = strValues;
        }
        return;
    }

    void ToMessage(WPEFramework::Core::JSON::IElement* parameters,
                   WPEFramework::Core::ProxyType<WPEFramework::Core::JSONRPC::Message>& message) const
    {
        string values;
        parameters->ToString(values);
        if (values.empty() != true)
        {
            message->Parameters = values;
        }
        return;
    }

    Firebolt::Error FireboltErrorValue(const uint32_t error)
    {

        Firebolt::Error fireboltError = static_cast<Firebolt::Error>(error);
        switch (error)
        {
        case WPEFramework::Core::ERROR_NONE:
            fireboltError = Firebolt::Error::None;
            break;
        case WPEFramework::Core::ERROR_GENERAL:
        case WPEFramework::Core::ERROR_UNAVAILABLE:
            fireboltError = Firebolt::Error::General;
            break;
        case WPEFramework::Core::ERROR_TIMEDOUT:
            fireboltError = Firebolt::Error::Timedout;
            break;
        default:
            break;
        }

        return fireboltError;
    }

private:
    WPEFramework::Core::CriticalSection _adminLock;
    WPEFramework::Core::NodeId _connectId;
    WPEFramework::Core::ProxyType<Channel> _channel;
    IEventHandler* _eventHandler;
    PendingMap _pendingQueue;
    EventMap _eventMap;
    uint64_t _scheduledTime;
    uint32_t _waitTime;
    Listener _listener;
    bool _connected;
    Firebolt::Error _status;
};
} // namespace FireboltSDK