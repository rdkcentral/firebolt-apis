import Setup from '../Setup'
import { Advertising } from '../../dist/firebolt.js'

test('policy()', () => {
    return Advertising.policy().then(policy => {
        expect(policy.skipRestriction).toBe('adsUnwatched')
        expect(policy.limitAdTracking).toBe(false)
    })
});
