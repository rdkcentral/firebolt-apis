import Setup from '../Setup'
import { Platform } from '../../dist/firebolt.js'

test('Sub-modules exist', () => {
    expect(typeof Platform.Device).toBe('object')
    expect(typeof Platform.Localization).toBe('object')
    expect(typeof Platform.Accessibility).toBe('object')
});

