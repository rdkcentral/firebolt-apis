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

import { jest, test, expect, beforeAll } from "@jest/globals";
import { testHarness } from "../../../../../test/Setup";
import { Lifecycle } from "../../build/javascript/src/firebolt";

let readyResolved: boolean = false;
let readyCalled: boolean = false;
let readyMetricCalled: boolean = false;
let readyMetricCalledAfterResolve: boolean = false;

testHarness.onSend = function (module: string, method: string) {
  if (module === "lifecycle" && method === "ready") {
    readyCalled = true;
  } else if (module === "metrics" && method === "ready") {
    readyMetricCalled = true;

    if (readyResolved) {
      readyMetricCalledAfterResolve = true;
    }
  }
};

const callback = jest.fn();
const startupState: Lifecycle.LifecycleState = Lifecycle.state();

beforeAll(() => {
  Lifecycle.listen((event: string, _) => {
    callback(event);
  });

  Lifecycle.once("foreground", () => {
    Lifecycle.close(Lifecycle.CloseReason.USER_EXIT);
  });

  Lifecycle.once("unloading", () => {
    Lifecycle.finished();
  });

  let p = new Promise<void>((resolve, reject) => {
    Lifecycle.once("unloading", (_) => {
      resolve();
    });
  });

  Lifecycle.ready().then((_) => {
    readyResolved = true;
  });

  return p;
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

test('App moves to the "inactive" state next', () => {
  expect(callback).nthCalledWith(1, "inactive");
});

test('App moves to the "foreground" state next', () => {
  expect(callback).nthCalledWith(2, "foreground");
});

test('App moves to the "inactive" state next', () => {
  expect(callback).nthCalledWith(3, "inactive");
});

test('App moves to the "unloading" state next', () => {
  expect(callback).nthCalledWith(4, "unloading");
});

test("listen() background event.", () => {
  return Lifecycle.listen("background", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() background event.", () => {
  return Lifecycle.once("background", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() foreground event.", () => {
  return Lifecycle.listen("foreground", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() foreground event.", () => {
  return Lifecycle.once("foreground", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() inactive event.", () => {
  return Lifecycle.listen("inactive", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() inactive event.", () => {
  return Lifecycle.once("inactive", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() suspended event.", () => {
  return Lifecycle.listen("suspended", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() suspended event.", () => {
  return Lifecycle.once("suspended", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() unloading event.", () => {
  return Lifecycle.listen("unloading", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() unloading event.", () => {
  return Lifecycle.once("unloading", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("clear()", () => {
  const result: boolean = Lifecycle.clear(-1000);
  expect(result).toBeFalsy();
});
