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
import { Localization } from "../../build/javascript/src/firebolt-manage";

test("Localization.locality()", () => {
  return Localization.locality().then((res: string) => {
    expect(res).toBe("Philadelphia");
  });
});

test("Localization.countryCode()", () => {
  return Localization.countryCode().then((res: string) => {
    expect(res).toBe("US");
  });
});

test("Localization.language()", () => {
  return Localization.language().then((res: string) => {
    expect(res).toBe("en");
  });
});

test("Localization.locale()", () => {
  return Localization.locale().then((res: string) => {
    expect(res).toBe("en-US");
  });
});

test("Localization.locale()", () => {
  return Localization.locale().then((res: string) => {
    expect(res).toBe("en-US");
  });
});

test("Localization.listen()", () => {
  return Localization.listen("onLocalityChanged", () => {}).then(
    (res: Number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("Localization.once()", () => {
  return Localization.once("onLocalityChanged", () => {}).then((res: Number) => {
    expect(res > 0).toBe(true);
  });
});

test("Localization.clear()", () => {
  const result = Localization.clear(-1000);
  expect(result).toBeFalsy();
});

test("Device.postalCode()", () => {
  return Localization.postalCode().then((res: string) => {
    expect(res).toEqual("19103");
  });
});
