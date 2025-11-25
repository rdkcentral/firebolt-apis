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

#include "./component/utils.h"
#include "firebolt.h"
#include "json_engine.h"

#include "gtest/gtest.h"

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>

#include <curl/curl.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

// curl http get helper function using
std::string httpGet(const std::string& url)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        return "";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION,
        +[](char* ptr, size_t size, size_t nmemb, std::string* data)
        {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? response : "";
}

// curl http post helper function using
std::string httpPost(const std::string& url, const std::string& postData)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        return "";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.size());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION,
        +[](char* ptr, size_t size, size_t nmemb, std::string* data)
        {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? response : "";
}

void triggerRaw(const std::string& payload)
{
    httpPost("http://localhost:3333/api/v1/raw", payload);
}

void triggerEvent(const std::string& method, const std::string& params)
{
    nlohmann::json eventMessage;
    eventMessage["method"] = method;
    eventMessage["result"] = nlohmann::json::parse(params);

    httpPost("http://localhost:3333/api/v1/event", eventMessage.dump());
}

void verifyEventSubscription(const Firebolt::Result<Firebolt::SubscriptionId>& id)
{
    if (id)
    {
        std::cout << "Event Subscription is successful." << std::endl;
    }
    else
    {
        FAIL() << "Event Subscription failed. " + toError(id);
    }
}
void verifyUnsubscribeResult(const Firebolt::Result<void>& result)
{

    if (result.error() == Firebolt::Error::None)
    {
        std::cout << "Unsubscribe success" << std::endl;
    }
    else
    {
        FAIL() << "Unsubscribe failed." + toError(result);
    }
}
void verifyEventReceived(std::mutex& mtx, std::condition_variable& cv, bool& eventReceived)
{
    // Wait for the event to be received or timeout after 5 seconds
    std::unique_lock<std::mutex> lock(mtx);
    if (!cv.wait_for(lock, std::chrono::seconds(5), [&] { return eventReceived; }))
    {
        FAIL() << "Did not receive event within timeout";
    }
}
