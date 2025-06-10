
import { test, expect  } from "@jest/globals"
import { Settings } from "../../build/javascript/src/firebolt";

test('Log level tests', () => {
    Settings.setLogLevel("DEBUG")
    expect(Settings.getLogLevel()).toBe("DEBUG")
})
