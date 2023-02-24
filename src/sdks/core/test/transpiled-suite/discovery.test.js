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
import { test, expect } from "@jest/globals";
import { Discovery } from "../../build/javascript/src/firebolt";
test("watched(entityId)", () => {
    return Discovery.watched("abc").then((success) => {
        expect(success).toBe(true);
    });
});
test("policy()", () => {
    return Discovery.policy().then((res) => {
        expect(res.enableRecommendations).toBeTruthy();
        expect(res.rememberWatchedPrograms).toBeTruthy();
        expect(res.shareWatchHistory).toBeTruthy();
    });
});
test("policy(subscriber)", () => {
    return Discovery.policy((policy) => { }).then((res) => {
        expect(res).toBe(1);
    });
});
test("entityInfo(EntityInfoResult)", () => {
    const dummyData = {
        expires: new Date().toISOString(),
        entity: {
            identifiers: {
                assetId: "test123",
            },
            title: "Test",
            entityType: "program",
            programType: Discovery.ProgramType.MOVIE,
        },
    };
    return Discovery.entityInfo(dummyData).then((res) => {
        expect(res).toBeTruthy();
    });
});
test("watchNext(title?: LocalizedString, identifiers?: ContentIdentifiers, expires?: string, images?: object)", () => {
    return Discovery.watchNext("abc").then((success) => {
        expect(success).toBe(true);
    });
});
test("entitlements(entitlements: Entitlement[])", () => {
    const dummyData = [
        {
            entitlementId: "test123",
            startTime: `${new Date().getTime()}`,
            endTime: `${new Date().getTime() + 1}`,
        },
    ];
    return Discovery.entitlements(dummyData).then((res) => {
        expect(res).toBeTruthy();
    });
});
test("launch(appId)", () => {
    return Discovery.launch("test123").then((res) => {
        expect(res).toBeTruthy();
    });
});
test("signIn(appId)", () => {
    const dummyData = [
        {
            entitlementId: "test123",
            startTime: `${new Date().getTime()}`,
            endTime: `${new Date().getTime() + 1}`,
        },
    ];
    return Discovery.signIn(dummyData).then((res) => {
        expect(res).toBeTruthy();
    });
});
test("signOut()", () => {
    return Discovery.signOut().then((res) => {
        expect(res).toBeTruthy();
    });
});
test("purchasedContent()", () => {
    const dummyData = {
        expires: `${new Date().toISOString}`,
        totalCount: 2,
        entries: [
            {
                identifiers: {
                    assetId: "test123",
                },
                title: "TEST",
                entityType: "program",
                programType: Discovery.ProgramType.MOVIE,
            },
        ],
    };
    return Discovery.purchasedContent(dummyData).then((res) => {
        expect(res).toBeTruthy();
    });
});
test("listen() navigateTo event.", () => {
    return Discovery.listen("navigateTo", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() navigateTo event.", () => {
    return Discovery.once("navigateTo", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() policyChanged event.", () => {
    return Discovery.listen("policyChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() policyChanged event.", () => {
    return Discovery.once("policyChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() pullEntityInfo event.", () => {
    return Discovery.listen("pullEntityInfo", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() pullEntityInfo event.", () => {
    return Discovery.once("pullEntityInfo", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() pullPurchasedContent event.", () => {
    return Discovery.listen("pullPurchasedContent", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() pullPurchasedContent event.", () => {
    return Discovery.once("pullPurchasedContent", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("clear()", () => {
    const result = Discovery.clear(2);
    expect(result).toBeFalsy();
});
