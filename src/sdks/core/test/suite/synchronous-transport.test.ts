/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
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

import transport from "../../../../../test/helpers/synchronous-transport.mjs";

// These all get set synchronously, so we'll update them as they happen
let sendCalled: boolean = false;
let inactiveListened: boolean = false;
let callbackWiredUp: boolean = false;

transport.onSend((json) => {
  // we'll assert on this later...
  sendCalled = true;
  if (json.method.toLowerCase() === "device.name") {
    // we'll assert on this later...
    inactiveListened = true;

    // we'll assert on this later...
    callbackWiredUp = true;
    let response = {
      jsonrpc: "2.0",
      id: json.id,
      result: "Test Name",
    };
    // catching errors, so all tests don't fail if this breaks
    try {
      // send back the onInactive event immediately, to test for race conditions
      transport.response(response);
    } catch (err) {
      // fail silenetly (the boolean-based tests below will figure it out...)
    }
  }
});

import { test, expect, beforeAll } from "@jest/globals";
import { Lifecycle, Device } from "../../build/javascript/src/firebolt";

Lifecycle.ready();

// Wire up our synchronous transport layer before the SDK loads
beforeAll(() => {
  return new Promise((resolve, reject) => {
    setTimeout(resolve, 1000);
  });
});

test("Transport injected before SDK", () => {
  expect(transport.instantiatedBeforeSdk()).toBe(true);
});

test("Transport send method working", () => {
  expect(sendCalled).toBe(true);
});

test("Transport was sent `Lifecycle.onInactive` listener", () => {
  expect(
    !!transport
      .history()
      .find((json) => json.method.toLowerCase() === "lifecycle.oninactive")
  ).toBe(true);
});

test("Transport `receive` callback wired up", () => {
  return Device.name().then((name) => {
    expect(name).toBe("Test Name");
  });
});
