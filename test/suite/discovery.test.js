import Setup from '../Setup'
import { Discovery } from '../../dist/firebolt.js'

test('watched(contentId)', () => {
    return Discovery.watched('abc').then(success => {
        expect(success).toBe(true)
    })
})

