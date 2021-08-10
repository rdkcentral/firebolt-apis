import Setup from '../Setup'
import { Metrics } from '../../dist/firebolt.js'

test('Sign-in / Sign-out', () => {
    Metrics.startContent('abc')
    Metrics.stopContent('abc')
    expect(1).toBe(1) // make sure it didn't crash...
})

