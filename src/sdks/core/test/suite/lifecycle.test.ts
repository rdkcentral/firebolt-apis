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

import { transport } from '../../../../../test/TransportHarness.js'
import MockTransport from '../../build/javascript/src/Transport/MockTransport.mjs'
import { jest, test, expect, beforeAll } from "@jest/globals";

import { Lifecycle } from "../../build/javascript/src/firebolt";

let readyResolved: boolean = false;
let readyCalled: boolean = false;
let readyMetricCalled: boolean = false;
let readyMetricCalledAfterResolve: boolean = false;

transport.onSend((json) => {

  if (json && json.method) {

    let [module, method] = json.method.split('.');

    if (module === "Lifecycle" && method === "ready") {
      readyCalled = true;
    }
    else if (module === "Metrics" && method === "ready") {
      readyMetricCalled = true;
      if (readyResolved) {
        readyMetricCalledAfterResolve = true;
      }

    }
  }
})

const callback = jest.fn(
  (eventName) => {
    console.log(`Lifecycle Event: ${eventName}`);
  }
);
const startupState: Lifecycle.LifecycleState = Lifecycle.state();

beforeAll(() => {

  Lifecycle.once("onForeground", () => {
    Lifecycle.close(Lifecycle.CloseReason.USER_EXIT);
  });

  MockTransport.event("Lifecycle", "onInactive", null);

  Lifecycle.ready().then((_) => {
    readyResolved = true;
  }).catch((err) => {
    readyResolved = true;
    console.error("Error in Lifecycle.ready: ", err);
  });

  MockTransport.event("Lifecycle", "onForeground", null);

  let p = new Promise<void>((resolve, reject) => {
    Lifecycle.once("onUnloading", (_) => {
      setTimeout(() => {
        resolve();
      }, 100);
    });
  });
  MockTransport.event("Lifecycle", "onUnloading", null);

  return p
});

test("Lifecycle.ready Promise resolved", () => {
  expect(readyCalled).toBe(true);
  expect(readyResolved).toBe(true);
});

test("Lifecycle.ready calls Metrics.ready", () => {
  expect(readyMetricCalled).toBe(true);
  expect(readyMetricCalledAfterResolve).toBe(true);
});

test('App starts up in the "initializing" state', () => {
  expect(startupState).toBe("initializing");
});
/*
test('App moves to the "inactive" state next', () => {
  expect(callback).nthCalledWith(1, "onInactive");
});

test('App moves to the "foreground" state next', () => {
  expect(callback).nthCalledWith(2, "onForeground");
});

test('App moves to the "unloading" state next', () => {
  expect(callback).nthCalledWith(3, "onUnloading");
});
*/
test("listen() background event.", () => {
  return Lifecycle.listen("onBackground", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() background event.", () => {
  return Lifecycle.once("onBackground", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() foreground event.", () => {
  return Lifecycle.listen("onForeground", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() foreground event.", () => {
  return Lifecycle.once("onForeground", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() inactive event.", () => {
  return Lifecycle.listen("onInactive", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() inactive event.", () => {
  return Lifecycle.once("onInactive", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() suspended event.", () => {
  return Lifecycle.listen("onSuspended", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() suspended event.", () => {
  return Lifecycle.once("onSuspended", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() unloading event.", () => {
  return Lifecycle.listen("onUnloading", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() unloading event.", () => {
  return Lifecycle.once("onUnloading", callback).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("clear()", () => {
  const result: boolean = Lifecycle.clear(-1000);
  expect(result).toBeFalsy();
});
