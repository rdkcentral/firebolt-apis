import { test, expect } from "@jest/globals";
import { Localization } from "../../build/javascript/src/firebolt";
test("locality", () => {
  return Localization.locality().then((res: string) => {
    expect(res).toBe("Philadelphia");
  });
});
test("postalCode", () => {
  return Localization.postalCode().then((res: string) => {
    expect(res).toBe("19103");
  });
});
test("countryCode", () => {
  return Localization.countryCode().then((res: string) => {
    expect(res).toBe("US");
  });
});
test("language", () => {
  return Localization.language().then((res: string) => {
    expect(res).toBe("en");
  });
});
test("locale", () => {
  return Localization.locale().then((res: string) => {
    expect(res).toBe("en-US");
  });
});
test("additionalInfo", () => {
  return Localization.additionalInfo().then((res: object) => {
    expect(typeof res).toBe("object");
  });
});
test("latlon", () => {
  return Localization.latlon().then((res: Array<Number>) => {
    expect([39.9549, 75.1699]).toEqual(expect.arrayContaining(res));
  });
});

test("listen() languageChanged event.", () => {
  return Localization.listen("languageChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("once() languageChanged event.", () => {
  return Localization.once("languageChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("clear()", () => {
  const result: boolean = Localization.clear(2);
  expect(result).toBeFalsy();
});
