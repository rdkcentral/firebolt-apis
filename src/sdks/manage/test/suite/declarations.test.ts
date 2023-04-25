import { test, expect } from "@jest/globals";
import {
  ClosedCaptions,
  Account,
  Device,
  LifecycleManagement,
} from "../../build/javascript/src/firebolt-manage";

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

test("Lifecycle.provide() declarations", () => {
  LifecycleManagement.provide(
    "xrn:firebolt:capability:lifecycle:state",
    new LCMProvider()
  );
  expect(1).toBe(1);
});
