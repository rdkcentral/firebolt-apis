import { test, expect } from "@jest/globals";
import { Localization } from "../../build/javascript/src/firebolt";
test("locality", () => {
    return Localization.locality().then((res) => {
        expect(res).toBe("Philadelphia");
    });
});
test("postalCode", () => {
    return Localization.postalCode().then((res) => {
        expect(res).toBe("19103");
    });
});
test("countryCode", () => {
    return Localization.countryCode().then((res) => {
        expect(res).toBe("US");
    });
});
test("language", () => {
    return Localization.language().then((res) => {
        expect(res).toBe("en");
    });
});
test("locale", () => {
    return Localization.locale().then((res) => {
        expect(res).toBe("en-US");
    });
});
test("additionalInfo", () => {
    return Localization.additionalInfo().then((res) => {
        expect(typeof res).toBe("object");
    });
});
test("latlon", () => {
    return Localization.latlon().then((res) => {
        expect([39.9549, 75.1699]).toEqual(expect.arrayContaining(res));
    });
});
test("listen() languageChanged event.", () => {
    return Localization.listen("languageChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() languageChanged event.", () => {
    return Localization.once("languageChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("clear()", () => {
    const result = Localization.clear(2);
    expect(result).toBeFalsy();
});
