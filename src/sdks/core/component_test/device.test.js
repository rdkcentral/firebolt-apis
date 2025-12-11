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

import "./utils/bootstrap.mjs";

import { test, expect, describe } from "@jest/globals";
import Device from "../dist/lib/Device/index.mjs";

describe("Device API", () => {
  test("uid returns expected value", async () => {
    await expect(Device.uid()).resolves.toBe(
      "ee6723b8-7ab3-462c-8d93-dbf61227998e"
    );
  });

  test("deviceClass returns expected value", async () => {
    await expect(Device.deviceClass()).resolves.toBe("ott");
  });
});
