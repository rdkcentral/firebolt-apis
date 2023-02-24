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

import { test, expect } from "@jest/globals";
import { Account } from "../../build/javascript/src/firebolt-manage";

test("Account.session()", () => {
  const expTime: number = new Date().getTime() + 100;
  return Account.session("Test_Token", expTime).then((res: void) => {
    expect(res).toEqual({});
  });
});

test("Account.provide() with blank object", () => {
  expect(() => {
    Account.provide("xrn:firebolt:capability:token:session", {});
  }).toThrow();
});

// Events Test cases

// test("Account.listen() for requestSession event", () => {
//   return Account.listen("requestSession", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Account.once() for requestSession event", () => {
//   return Account.once("requestSession", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Account.clear()", () => {
//   const result = Account.clear(2);
//   expect(result).toBeFalsy();
// });
