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
    return Localization.locality().then((res) => {
        expect(res).toBe("Philadelphia");
    });
});
test("Localization.countryCode()", () => {
    return Localization.countryCode().then((res) => {
        expect(res).toBe("US");
    });
});
test("Localization.language()", () => {
    return Localization.language().then((res) => {
        expect(res).toBe("en");
    });
});
test("Localization.locale()", () => {
    return Localization.locale().then((res) => {
        expect(res).toBe("en-US");
    });
});
test("Localization.locale()", () => {
    return Localization.locale().then((res) => {
        expect(res).toBe("en-US");
    });
});
test("Localization.listen()", () => {
    return Localization.listen("localityChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Localization.once()", () => {
    return Localization.once("localityChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Localization.clear()", () => {
    const result = Localization.clear(1);
    expect(result).toBe(undefined);
});
test("Device.postalCode()", () => {
    return Localization.postalCode().then((res) => {
        expect(res).toEqual("19103");
    });
});
