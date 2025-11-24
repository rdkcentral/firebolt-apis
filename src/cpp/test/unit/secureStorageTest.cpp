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

#include "securestorage_impl.h"
#include "json_engine.h"
#include "mock_helper.h"

class SecureStorageTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::SecureStorage::SecureStorageImpl secstorImpl_{mockHelper};
};

std::map<std::string, Firebolt::SecureStorage::StorageScope> ScopeMap = {
    {"device", Firebolt::SecureStorage::StorageScope::DEVICE},
    {"account", Firebolt::SecureStorage::StorageScope::ACCOUNT}
};

TEST_F(SecureStorageTest, get)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";

    nlohmann::json expectedParams;
    expectedParams["key"] = key;
    expectedParams["scope"] = scope;

    EXPECT_CALL(mockHelper, getJson("SecureStorage.get", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    auto result = secstorImpl_.get(ScopeMap[scope], key);
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("SecureStorage.get");;
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(SecureStorageTest, clear)
{
    std::string scope = "account";

    nlohmann::json expectedParams;
    expectedParams["scope"] = scope;

    EXPECT_CALL(mockHelper, invoke("SecureStorage.clear", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
            {
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));
    auto result = secstorImpl_.clear(ScopeMap[scope]);
    ASSERT_TRUE(result) << "error on clear";
}

TEST_F(SecureStorageTest, remove)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";

    nlohmann::json expectedParams;
    expectedParams["scope"] = scope;
    expectedParams["key"] = key;

    EXPECT_CALL(mockHelper, invoke("SecureStorage.remove", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
            {
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));

    auto result = secstorImpl_.remove(ScopeMap[scope], key);
    ASSERT_TRUE(result) << "error on remove";
}

TEST_F(SecureStorageTest, set)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";
    std::string value = "VGhpcyBub3QgYSByZWFsIHRva2VuLgo";
    float ttl = 600.0f;

    nlohmann::json expectedParams;
    expectedParams["scope"] = scope;
    expectedParams["key"] = key;
    expectedParams["value"] = value;
    expectedParams["options"] = nlohmann::json{{"ttl", ttl}};


    EXPECT_CALL(mockHelper, invoke("SecureStorage.set", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &parameters)
            {
                lastSetParams = parameters;
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));

    auto result = secstorImpl_.set(ScopeMap[scope], key, value, Firebolt::SecureStorage::StorageOptions{ttl});
    ASSERT_TRUE(result) << "Error on set";

    {
        nlohmann::json expectedParams;
        expectedParams["key"] = key;
        expectedParams["scope"] = scope;

        EXPECT_CALL(mockHelper, getJson("SecureStorage.get", expectedParams))
            .WillOnce(Invoke(
                [&](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
                {
                    return Firebolt::Result<nlohmann::json>{lastSetParams["value"]};
                }));
        auto result = secstorImpl_.get(ScopeMap[scope], key);
        ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.autoLowLatencyModeCapable() method";
        EXPECT_EQ(*result, value);
    }
}

TEST_F(SecureStorageTest, setForApp)
{
    std::string appId = "foo";
    std::string scope = "device";
    std::string key = "authRefreshToken";
    std::string value = "VGhpcyBub3QgYSByZWFsIHRva2VuLgo";
    float ttl = 600.0f;

    nlohmann::json expectedParams;
    expectedParams["appId"] = appId;
    expectedParams["scope"] = scope;
    expectedParams["key"] = key;
    expectedParams["value"] = value;
    expectedParams["options"] = nlohmann::json{{"ttl", ttl}};

    EXPECT_CALL(mockHelper, invoke("SecureStorage.setForApp", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &parameters)
            {
                lastSetParams = parameters;
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));

    auto result = secstorImpl_.setForApp(appId, ScopeMap[scope], key, value, Firebolt::SecureStorage::StorageOptions{ttl});
    ASSERT_TRUE(result) << "Error on set";
}

TEST_F(SecureStorageTest, removeForApp)
{
    std::string appId = "foo";
    std::string scope = "account";
    std::string key = "authRefreshToken";

    nlohmann::json expectedParams;
    expectedParams["appId"] = appId;
    expectedParams["scope"] = scope;
    expectedParams["key"] = key;

    EXPECT_CALL(mockHelper, invoke("SecureStorage.removeForApp", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
            {
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));
    auto result = secstorImpl_.removeForApp(appId, ScopeMap[scope], key);
    ASSERT_TRUE(result) << "Error on remove";
}

TEST_F(SecureStorageTest, clearForApp)
{
    std::string appId = "foo";
    std::string scope = "account";

    nlohmann::json expectedParams;
    expectedParams["appId"] = appId;
    expectedParams["scope"] = scope;

    EXPECT_CALL(mockHelper, invoke("SecureStorage.clearForApp", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
            {
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));
    auto result = secstorImpl_.clearForApp(appId, ScopeMap[scope]);
    ASSERT_TRUE(result) << "Error on clear";
}
