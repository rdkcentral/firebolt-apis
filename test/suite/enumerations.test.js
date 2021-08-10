import Setup from '../Setup'
import { Lifecycle } from '../../dist/firebolt.js'
import { Device } from '../../dist/firebolt.js'

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
    expect(Device.AudioProfile.DOLBY_DIGITAL_5_1_PLUS).toBe("dolbyDigital5.1+")
    expect(Device.AudioProfile.DOLBY_ATMOS).toBe("dolbyAtmos")
    expect(Device.AudioProfile.DOLBY_DIGITAL_5_1).toBe("dolbyDigital5.1")
    expect(Device.AudioProfile.DOLBY_DIGITAL_7_1).toBe("dolbyDigital7.1")
    expect(Device.AudioProfile.DOLBY_DIGITAL_7_1_PLUS).toBe("dolbyDigital7.1+")
});
