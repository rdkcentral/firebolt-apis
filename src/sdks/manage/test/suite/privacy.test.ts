import { test, expect } from "@jest/globals";
import { Privacy } from "../../build/javascript/src/firebolt-manage";

test("privacy.allowResumePoints()", () => {
  return Privacy.allowResumePoints().then((res: boolean) => {
    // TODO: fix
    expect(true).toBe(true);
  });
});

test("privacy.listen() for allowPersonalizationChanged event", () => {
  return Privacy.listen("allowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowPersonalizationChanged event", () => {
  return Privacy.once("allowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowWatchHistoryChanged event", () => {
  return Privacy.listen("allowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowWatchHistoryChanged event", () => {
  return Privacy.once("allowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowAppContentAdTargetingChanged event", () => {
  return Privacy.listen("allowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowAppContentAdTargetingChanged event", () => {
  return Privacy.once("allowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.clear()", () => {
  const result = Privacy.clear(-1000);
  expect(result).toBeFalsy();
});
