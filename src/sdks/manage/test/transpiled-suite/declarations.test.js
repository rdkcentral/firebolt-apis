import { test, expect } from "@jest/globals";
import { Account, Lifecycle, } from "../../build/javascript/src/firebolt-manage";
class AccPovider {
    session(parameters, session) {
        return Promise.resolve(null);
    }
}
class LCMProvider {
    ready(parameters, session) {
        return Promise.resolve(null);
    }
    close(parameters, session) {
        return Promise.resolve(null);
    }
    finished(parameters, session) {
        return Promise.resolve(null);
    }
}
test("Account.provide() declarations", () => {
    Account.provide("xrn:firebolt:capability:token:session", new AccPovider());
    expect(1).toBe(1);
});
test("Lifecycle.provide() declarations", () => {
    Lifecycle.provide("xrn:firebolt:capability:lifecycle:state", new LCMProvider());
    expect(1).toBe(1);
});
