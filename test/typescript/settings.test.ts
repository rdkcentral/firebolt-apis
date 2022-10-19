import Setup from "../Setup"

import { test, expect  } from "@jest/globals"
import { Settings } from "../../dist/lib/firebolt";

test('Log level tests', () => {
    Settings.setLogLevel("DEBUG")
    expect(Settings.getLogLevel()).toBe("DEBUG")
})
