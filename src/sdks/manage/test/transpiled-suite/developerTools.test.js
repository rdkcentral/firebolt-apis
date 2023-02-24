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
import { DeveloperTools } from "../../build/javascript/src/firebolt-manage";
test("DeveloperTools.find()", () => {
    const output = DeveloperTools.find(() => { }, () => { });
    const result = typeof output.stop;
    expect(result).toBe("function");
});
test("DeveloperTools.pair()", () => {
    return DeveloperTools.pair("Test_ID").then((res) => {
        expect(res).toEqual({});
    });
});
test("DeveloperTools.unpair()", () => {
    return DeveloperTools.unpair("Test_ID").then((res) => {
        expect(res).toEqual({});
    });
});
// Events Test cases
// test("DeveloperTools.listen() for toolAvailable event", () => {
//   return DeveloperTools.listen("toolAvailable", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });
// test("DeveloperTools.once() for toolAvailable event", () => {
//   return DeveloperTools.once("toolAvailable", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });
// test("DeveloperTools.listen() for toolUnavailable event", () => {
//   return DeveloperTools.listen("toolUnavailable", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });
// test("DeveloperTools.once() for toolUnavailable event", () => {
//   return DeveloperTools.once("toolUnavailable", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });
// test("DeveloperTools.clear()", () => {
//   const result = DeveloperTools.clear(2);
//   expect(result).toBeFalsy();
// });
