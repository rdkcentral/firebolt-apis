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
#include "json_engine.h"
#include "gtest/gtest.h"

class SecureStorageTest : public ::testing::Test
{
protected:
    std::map<std::string, Firebolt::SecureStorage::StorageScope> ScopeMap =
        {{"device", Firebolt::SecureStorage::StorageScope::DEVICE},
         {"account", Firebolt::SecureStorage::StorageScope::ACCOUNT}};

protected:
    JsonEngine jsonEngine;
};

TEST_F(SecureStorageTest, get)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";

    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(ScopeMap[scope], key);
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("SecureStorage.get");
    ;
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(SecureStorageTest, clear)
{
    std::string scope = "account";

    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(ScopeMap[scope]);
    ASSERT_TRUE(result) << "error on clear";
}

TEST_F(SecureStorageTest, remove)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";

    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(ScopeMap[scope], key);
    ASSERT_TRUE(result) << "error on remove";
}

TEST_F(SecureStorageTest, set)
{
    std::string scope = "device";
    std::string key = "authRefreshToken";
    std::string value = "VGhpcyBub3QgYSByZWFsIHRva2VuLgo";
    float ttl = 600.0f;

    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().set(ScopeMap[scope], key, value,
                                                                             Firebolt::SecureStorage::StorageOptions{ttl});
    ASSERT_TRUE(result) << "Error on set";
}

TEST_F(SecureStorageTest, setForApp)
{
    std::string appId = "foo";
    std::string scope = "device";
    std::string key = "authRefreshToken";
    std::string value = "VGhpcyBub3QgYSByZWFsIHRva2VuLgo";
    float ttl = 600.0f;

    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .setForApp(appId, ScopeMap[scope], key, value, Firebolt::SecureStorage::StorageOptions{ttl});
    ASSERT_TRUE(result) << "Error on set";
}

TEST_F(SecureStorageTest, removeForApp)
{
    std::string appId = "foo";
    std::string scope = "account";
    std::string key = "authRefreshToken";

    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().removeForApp(appId, ScopeMap[scope], key);
    ASSERT_TRUE(result) << "Error on remove";
}

TEST_F(SecureStorageTest, clearForApp)
{
    std::string appId = "foo";
    std::string scope = "account";

    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clearForApp(appId, ScopeMap[scope]);
    ASSERT_TRUE(result) << "Error on clear";
}
