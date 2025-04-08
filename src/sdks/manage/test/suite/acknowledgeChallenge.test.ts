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
import { AcknowledgeChallenge } from "../../build/javascript/src/firebolt-manage";

/* not compilable with bidirectional, disabling until mismatch resolved
class ACKPovider implements AcknowledgeChallenge.ChallengeProvider {
  challenge(
    parameters: object,
    session: AcknowledgeChallenge.FocusableProviderSession
  ): Promise<AcknowledgeChallenge.GrantResult> {
    return Promise.resolve(null);
  }
}

test("AcknowledgeChallenge.provide() declarations", () => {
  AcknowledgeChallenge.provide(
    "xrn:firebolt:capability:usergrant:acknowledgechallenge",
    new ACKPovider()
  );
  expect(1).toBe(1);
});
*/

test("AcknowledgeChallenge.provide() with blank object", () => {
  expect(() => {
    AcknowledgeChallenge.provide(
      null
    );
  }).toThrow();
});

// Events Test cases

// test("AcknowledgeChallenge.listen() for requestChallenge event", () => {
//   return AcknowledgeChallenge.listen("requestChallenge", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });

// test("AcknowledgeChallenge.once() for requestChallenge event", () => {
//   return AcknowledgeChallenge.once("requestChallenge", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });

// test("AcknowledgeChallenge.clear()", () => {
//   const result = AcknowledgeChallenge.clear(2);
//   expect(result).toBeFalsy();
// });
