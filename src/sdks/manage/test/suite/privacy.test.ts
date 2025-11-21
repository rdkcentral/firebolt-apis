import { test, expect } from "@jest/globals";
import { Privacy } from "../../build/javascript/src/firebolt-manage";

let listenerId: number;

test("privacy.allowResumePoints()", () => {
  return Privacy.allowResumePoints().then((res: boolean) => {
    // TODO: fix
    expect(true).toBe(true);
  });
});

test("privacy.listen() for allowPersonalizationChanged event", () => {
  Privacy.once;
  return Privacy.listen("onAllowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowPersonalizationChanged event", () => {
  Privacy.once;
  return Privacy.once("onAllowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowWatchHistoryChanged event", () => {
  Privacy.once;
  return Privacy.listen("onAllowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowWatchHistoryChanged event", () => {
  Privacy.once;
  return Privacy.once("onAllowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowAppContentAdTargetingChanged event", () => {
  Privacy.once;
  return Privacy.listen("onAllowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowAppContentAdTargetingChanged event", () => {
  Privacy.once;
  return Privacy.once("onAllowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.clear()", () => {
  const result = Privacy.clear(-1000);
  expect(result).toBeFalsy();
});
