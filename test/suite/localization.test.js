import Setup from '../Setup'
import { Localization } from '../../dist/firebolt.js'

test('locality to be Philadelphia', () => {
    return Localization.locality().then( locality => {
        expect(locality).toBe('Philadelphia')
    })
});

