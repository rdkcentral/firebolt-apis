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
import Localization from "../dist/lib/Localization/index.mjs";

describe("Localization API", () => {
  test("country returns 'US'", async () => {
    await expect(Localization.country()).resolves.toBe("US");
  });

  test("preferredAudioLanguages returns expected array", async () => {
    await expect(Localization.preferredAudioLanguages()).resolves.toEqual([
      "spa",
      "eng",
    ]);
  });

  test("presentationLanguage returns 'en-US'", async () => {
    await expect(Localization.presentationLanguage()).resolves.toBe("en-US");
  });
});
