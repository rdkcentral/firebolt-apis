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
import { ClosedCaptions } from "../../build/javascript/src/firebolt-manage";
test("ClosedCaptions.enabled()", () => {
    return ClosedCaptions.enabled().then((res) => {
        expect(res).toBe(true);
    });
});
test("ClosedCaptions.fontFamily()", () => {
    return ClosedCaptions.fontFamily().then((res) => {
        expect(res).toEqual("Monospace sans-serif");
    });
});
test("ClosedCaptions.fontSize()", () => {
    return ClosedCaptions.fontSize().then((res) => {
        expect(res).toBe(1);
    });
});
test("ClosedCaptions.fontColor()", () => {
    return ClosedCaptions.fontColor().then((res) => {
        expect(res).toEqual("#ffffff");
    });
});
test("ClosedCaptions.fontEdge()", () => {
    return ClosedCaptions.fontEdge().then((res) => {
        expect(res).toEqual("none");
    });
});
test("ClosedCaptions.fontEdgeColor()", () => {
    return ClosedCaptions.fontEdgeColor().then((res) => {
        expect(res).toEqual("#000000");
    });
});
test("ClosedCaptions.fontOpacity()", () => {
    return ClosedCaptions.fontOpacity().then((res) => {
        expect(res).toBe(100);
    });
});
test("ClosedCaptions.backgroundColor()", () => {
    return ClosedCaptions.backgroundColor().then((res) => {
        expect(res).toEqual("#000000");
    });
});
test("ClosedCaptions.backgroundOpacity()", () => {
    return ClosedCaptions.backgroundOpacity().then((res) => {
        expect(res).toBe(100);
    });
});
test("ClosedCaptions.textAlign()", () => {
    return ClosedCaptions.textAlign().then((res) => {
        expect(res).toEqual("center");
    });
});
test("ClosedCaptions.textAlignVertical()", () => {
    return ClosedCaptions.textAlignVertical().then((res) => {
        expect(res).toEqual("middle");
    });
});
test("ClosedCaptions.listen()", () => {
    return ClosedCaptions.listen("fontColorChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("ClosedCaptions.once()", () => {
    return ClosedCaptions.once("fontColorChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("clear", () => {
    const result = ClosedCaptions.clear(1);
    expect(result).toBe(undefined);
});
