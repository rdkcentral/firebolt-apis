import { test, expect } from "@jest/globals";
import {
  ClosedCaptions,
  Account,
  Device,
  LifecycleManagement,
} from "../../build/javascript/src/firebolt-manage";

class AccPovider implements Account.SessionProvider {
  session(
    parameters: void,
    session: Account.FocusableProviderSession
  ): Promise<object> {
    return Promise.resolve(null);
  }
}

class LCMProvider implements LifecycleManagement.StateProvider {
  ready(
    parameters: LifecycleManagement.LifecycleReadyParameters,
    session: LifecycleManagement.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
  close(
    parameters: LifecycleManagement.LifecycleCloseParameters,
    session: LifecycleManagement.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
  finished(
    parameters: LifecycleManagement.LifecycleFinishedParameters,
    session: LifecycleManagement.ProviderSession
  ): Promise<void> {
    return Promise.resolve(null);
  }
}

test("Account.provide() declarations", () => {
  Account.provide("xrn:firebolt:capability:token:session", new AccPovider());
  expect(1).toBe(1);
});

test("Lifecycle.provide() declarations", () => {
  LifecycleManagement.provide(
    "xrn:firebolt:capability:lifecycle:state",
    new LCMProvider()
  );
  expect(1).toBe(1);
});
