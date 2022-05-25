/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import Setup from '../Setup'
import { Lifecycle } from '../../dist/lib/firebolt.mjs'
import { Device } from '../../dist/lib/firebolt.mjs'

test('Lifecycle.CloseReason', () => {
    expect(Lifecycle.CloseReason.USER_EXIT).toBe("userExit")
    expect(Lifecycle.CloseReason.REMOTE_BUTTON).toBe("remoteButton")
    expect(Lifecycle.CloseReason.ERROR).toBe("error")    
});

test('Lifecycle.LifecycleState', () => {
    expect(Lifecycle.LifecycleState.INACTIVE).toBe("inactive")
    expect(Lifecycle.LifecycleState.FOREGROUND).toBe("foreground")
    expect(Lifecycle.LifecycleState.BACKGROUND).toBe("background")
    expect(Lifecycle.LifecycleState.INITIALIZING).toBe("initializing")
    expect(Lifecycle.LifecycleState.SUSPENDED).toBe("suspended")
    expect(Lifecycle.LifecycleState.UNLOADING).toBe("unloading")
});

test('Device.AudioProfile', () => {
    expect(Device.AudioProfile.DOLBY_DIGITAL_PLUS).toBe("dolbyDigitalPlus")
    expect(Device.AudioProfile.DOLBY_ATMOS).toBe("dolbyAtmos")
    expect(Device.AudioProfile.DOLBY_DIGITAL).toBe("dolbyDigital")
});
