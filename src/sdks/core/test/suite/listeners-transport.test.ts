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

const win = globalThis || window;

import { test, expect } from "@jest/globals";
import { Lifecycle, Discovery } from "../../build/javascript/src/firebolt";

// holds test transport layer state, e.g. callback
const state = {
  callback: Function,
};

let navigateToListenCount: number = 0;
let callbackWiredUp: boolean = false;
let sendCalled: boolean = false;

const transport = {
  send: function (message: string) {
    sendCalled = true;
    const json = JSON.parse(message);
    if (json.method.toLowerCase() === "discovery.onnavigateto") {
      // we'll assert on this later...
      navigateToListenCount++;
      if (state.callback) {
        // we'll assert on this later...
        callbackWiredUp = true;
        let response = {
          jsonrpc: "2.0",
          id: json.id,
          result: true,
        };
        // catching errors, so all tests don't fail if this breaks
        try {
          // send back the onInactive event immediately, to test for race conditions
          state.callback(JSON.stringify(response));
        } catch (err) {
          // fail silenetly (the boolean-based tests below will figure it out...)
        }
      }
    }
  },
  receive: function (callback: FunctionConstructor) {
    // store the callback
    state.callback = callback;
  },
};

win.__firebolt.setTransportLayer(transport);

// listen twice, using event-specific call FIRST
Discovery.listen("navigateTo", (value: Discovery.NavigationIntent) => {
  callbackWiredUp = true;
});

Discovery.listen("navigateTo", (value: Discovery.NavigationIntent) => {
  /* this just adds more listen calls to make sure we don't spam */
});
Discovery.listen((event: string, value: object) => {
  /* testing both listen signatures */
});
Discovery.listen((event: string, value: object) => {
  /* testing both listen signatures */
});

Lifecycle.ready();

test("Transport injected after SDK", () => {
  expect(callbackWiredUp).toBe(true);
});

test("Transport send method working", () => {
  expect(sendCalled).toBe(true);
});

test("Transport was sent listeners", () => {
  expect(navigateToListenCount).toBeGreaterThan(0);
});

test("Transport was sent each listener only once", () => {
  expect(navigateToListenCount).toBe(1);
});
