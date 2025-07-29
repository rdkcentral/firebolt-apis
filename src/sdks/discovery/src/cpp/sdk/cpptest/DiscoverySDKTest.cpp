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

#include <unistd.h>
#include <cstring>
#include <string>
#include <cassert>
#include "DiscoverySDKTest.h"

using namespace std;
bool DiscoverySDKTest::_connected;
DiscoverySDKTest::OnUserInterestNotification DiscoverySDKTest::_userInterestNotification;

#ifdef GATEWAY_BIDIRECTIONAL

const nlohmann::json DiscoverySDKTest::userInterestEvent = {
    {"method", "content.onUserInterest"},
    {"payload", {
        {"name", "interest"},
        {"appId", "cool-app"},
        {"type", "interest"},
        {"reason", "playlist"},
        {"entity", {
            {"identifiers", {
                {"entityId", "345"},
                {"entityType", "program"},
                {"programType", "movie"}
            }},
            {"info", {
                {"title", "Cool Runnings"},
                {"synopsis", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc."},
                {"releaseDate", "1993-01-01T00:00:00.000Z"},
                {"contentRatings", {
                    {
                        {"scheme", "US-Movie"},
                        {"rating", "PG"}
                    },
                    {
                        {"scheme", "CA-Movie"},
                        {"rating", "G"}
                    }
                }}
            }}
        }}   
     }}
};


void DiscoverySDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "Event triggered: " << event["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalEventPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + event["method"].dump() + ", \"params\": " + event["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
    std::cout << "[ADITYA] trigger_cmd: " << trigger_cmd << std::endl;
}

void DiscoverySDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "Provider triggered: " << provider["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + provider["method"].dump() + ", \"params\": " + provider["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

std::string InterestTypeToString(Firebolt::Discovery::InterestType interestType) {
    switch (interestType) {
        case Firebolt::Discovery::InterestType::INTEREST:
            return "interest";
        case Firebolt::Discovery::InterestType::DISINTEREST:
            return "disinterest";
        default:
            return "unknown";
    }
}

std::string InterestReasonToString(Firebolt::Discovery::InterestReason interestReason) {
    switch (interestReason) {
        case Firebolt::Discovery::InterestReason::PLAYLIST:
            return "playlist";
        case Firebolt::Discovery::InterestReason::REACTION:
            return "reaction";
        case Firebolt::Discovery::InterestReason::RECORDING:
            return "recording";
        default:
            return "unknown";
    }
}


#endif

void DiscoverySDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    if (!_connected) {
        cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
        _connected = connected;
    }
}

void DiscoverySDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = "{\
            \"waitTime\": 100000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": " + url + "}";

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void DiscoverySDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool DiscoverySDKTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false)) {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    usleep(5000);
    return _connected;
}

template<typename T>
using EnumMap = std::unordered_map<T, string>;
template <typename T>
inline const string& ConvertFromEnum(EnumMap<T> enumMap, T type)
{
    return enumMap[type];
}
template <typename T>
inline const T ConvertToEnum(EnumMap<T> enumMap, const string& str)
{
     T value;
     for (auto element: enumMap) {
          if (element.second == str) {
              value = element.first;
              break;
          }
     }
     return value;
}

std::string ContentRatingSchemeToString(Firebolt::Entertainment::ContentRatingScheme scheme)
{
    switch (scheme)
    {
    case Firebolt::Entertainment::ContentRatingScheme::CA_MOVIE:
        return "CA-Movie";
    case Firebolt::Entertainment::ContentRatingScheme::CA_TV:
        return "CA-TV";
    case Firebolt::Entertainment::ContentRatingScheme::CA_MOVIE_FR:
        return "CA-Movie_Fr";
    case Firebolt::Entertainment::ContentRatingScheme::CA_TV_FR:
        return "CA-TV_Fr";
    case Firebolt::Entertainment::ContentRatingScheme::US_MOVIE:
        return "US-Movie";
    case Firebolt::Entertainment::ContentRatingScheme::US_TV:
        return "US-TV";
    default:
        return "UNKNOWN";
    }
}

void DiscoverySDKTest::OnUserInterestNotification::onUserInterest(const Firebolt::Content::InterestEvent &interest)
{
    cout << "onUserInterest() notification \n";

#ifdef GATEWAY_BIDIRECTIONAL
	assert(interest.appId == userInterestEvent["payload"]["appId"]);
    assert(InterestTypeToString(interest.type) == userInterestEvent["payload"]["type"]);
    assert(InterestReasonToString(interest.reason) == userInterestEvent["payload"]["reason"]);
    assert(interest.entity.info->title.value() == userInterestEvent["payload"]["entity"]["info"]["title"]);
    assert(interest.entity.info->synopsis.value() == userInterestEvent["payload"]["entity"]["info"]["synopsis"]);
    assert(interest.entity.info->releaseDate.value() == userInterestEvent["payload"]["entity"]["info"]["releaseDate"]);
    size_t i = 0;
    for (const auto &rating : interest.entity.info->contentRatings.value())
    {
        assert(ContentRatingSchemeToString(rating.scheme) == userInterestEvent["payload"]["entity"]["info"]["contentRatings"][i]["scheme"]);
        i++;
    }
    size_t j = 0;
    for (const auto &ratings : interest.entity.info->contentRatings.value())
    {
        assert(ratings.rating == userInterestEvent["payload"]["entity"]["info"]["contentRatings"][j]["rating"]);
        j++;
    }
#endif
}

void DiscoverySDKTest::SubscribeUserInterest()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ContentInterface().subscribe(_userInterestNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Content.UserInterest is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Subscribe Content.UserInterest failed. " + errorMessage);
    }
}

void DiscoverySDKTest::UnsubscribeUserInterest()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ContentInterface().unsubscribe(_userInterestNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Content.UserInterest is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Unsubscribe Content.UserInterest failed." + errorMessage);
    }
}

void DiscoverySDKTest::RequestUserInterest()
{
    Firebolt::Discovery::InterestType type = Firebolt::Discovery::InterestType::INTEREST;
    Firebolt::Discovery::InterestReason reason = Firebolt::Discovery::InterestReason::REACTION;
    Firebolt::Error error = Firebolt::Error::None;

    Firebolt::IFireboltAccessor::Instance().ContentInterface().requestUserInterest(type, reason, &error);
    
    if (error == Firebolt::Error::None) {
        cout << "Content.requestuserInterest call is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Content.requestUserInterest failed." + errorMessage);
    }
}
