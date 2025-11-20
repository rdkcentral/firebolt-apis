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
import { VoiceGuidance } from "../../build/javascript/src/firebolt-manage";

test("VoiceGuidance.enabled()", () => {
  return VoiceGuidance.enabled().then((res) => {
    expect(res).toEqual(true);
  });
});

test("VoiceGuidance.speed()", () => {
  return VoiceGuidance.speed().then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("VoiceGuidance.listen() for onEnabledChanged event", () => {
  return VoiceGuidance.listen("onEnabledChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("VoiceGuidance.once() for onEnabledChanged event", () => {
  return VoiceGuidance.once("onEnabledChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("VoiceGuidance.listen() for onSpeedChanged event", () => {
  return VoiceGuidance.listen("onSpeedChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("VoiceGuidance.once() for onSpeedChanged event", () => {
  return VoiceGuidance.once("onSpeedChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("VoiceGuidance.clear()", () => {
  const result = VoiceGuidance.clear(-1000);
  expect(result).toBeFalsy();
});
