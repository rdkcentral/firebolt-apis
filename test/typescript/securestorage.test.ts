/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import { test, expect } from "@jest/globals";
import { SecureStorage } from "../../dist/lib/firebolt";

const value = "VGhpcyBub3QgYSByZWFsIHRva2VuLgo="
const authTokenKey = "authRefreshToken"

test("get() for type Device", () => {
  return SecureStorage.get(SecureStorage.StorageScope.DEVICE, authTokenKey).then((securestorage) => {
    expect(securestorage).toBe(value);
  });
});

test("get() for type Account", () => {
  return SecureStorage.get(SecureStorage.StorageScope.ACCOUNT, authTokenKey).then((securestorage) => {
    expect(securestorage).toBe(value);
  });
});

test("set() for type device", () => {
  return SecureStorage.set(SecureStorage.StorageScope.DEVICE, authTokenKey, value, {
    ttl: 600
  }).then((res) => {
    expect(res).toEqual({});
  });
});

test("set() for type account", () => {
  return SecureStorage.set(SecureStorage.StorageScope.ACCOUNT, authTokenKey, value).then((res) => {
    expect(res).toEqual({});
  });
});

test("remove() for type device", () => {
  return SecureStorage.remove(SecureStorage.StorageScope.DEVICE, authTokenKey).then((res) => {
    expect(res).toEqual({});
  });
});

test("remove() for type account", () => {
  return SecureStorage.remove(SecureStorage.StorageScope.ACCOUNT, authTokenKey).then((res) => {
    expect(res).toEqual({});
  });
});