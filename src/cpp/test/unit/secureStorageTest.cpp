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

#include "unit.h"

class SecureStorageTest : public ::testing::Test
{
protected:
    JsonEngine* jsonEngine;

    void SetUp() override { jsonEngine = new JsonEngine(); }

    void TearDown() override { delete jsonEngine; }
};

TEST_F(SecureStorageTest, get)
{
    std::string expectedValues = jsonEngine->get_value("SecureStorage.get");
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                             "authRefreshToken");
    ASSERT_TRUE(result) << "Error on calling SecureStorage.get() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), *result) << "Error: wrong SecureStorage.get returned by "
                                                         "SecureStorage.get()";
}

TEST_F(SecureStorageTest, clear)
{
    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(
        Firebolt::SecureStorage::StorageScope::ACCOUNT);
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.clear() method";
}

TEST_F(SecureStorageTest, remove)
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                                "authRefreshToken");
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.remove() method";
}

TEST_F(SecureStorageTest, set)
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .set(Firebolt::SecureStorage::StorageScope::DEVICE, "authRefreshToken",
                           "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.set() method";
}

TEST_F(SecureStorageTest, setForApp)
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .setForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken",
                                 "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.setForApp() method";
}

TEST_F(SecureStorageTest, removeForApp)
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .removeForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken");
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.removeForApp() method";
}

TEST_F(SecureStorageTest, clearForApp)
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .clearForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT);
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling SecureStorage.removeForApp() method";
}
