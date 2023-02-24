import { test, expect } from "@jest/globals";
import {
  ClosedCaptions,
  Account,
  Device,
  Lifecycle,
} from "../../build/javascript/src/firebolt-manage";

class AccPovider implements Account.SessionProvider {
  session(
    parameters: void,
    session: Account.FocusableProviderSession
  ): Promise<object> {
    return Promise.resolve(null);
  }
}

class LCMProvider implements Lifecycle.StateProvider {
  ready(
    parameters: Lifecycle.LifecycleReadyParameters,
    session: Lifecycle.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
  close(
    parameters: Lifecycle.LifecycleCloseParameters,
    session: Lifecycle.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
  finished(
    parameters: Lifecycle.LifecycleFinishedParameters,
    session: Lifecycle.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
}

test("Account.provide() declarations", () => {
  Account.provide("xrn:firebolt:capability:token:session", new AccPovider());
  expect(1).toBe(1);
});

test("Lifecycle.provide() declarations", () => {
  Lifecycle.provide(
    "xrn:firebolt:capability:lifecycle:state",
    new LCMProvider()
  );
  expect(1).toBe(1);
});
