import Setup from '../Setup'
import { Device } from '../../dist/firebolt.js'

const version = require('../../package.json').version.split('-')[0].split('.')

test(`Device.version() to be ${version[0]}.${version[1]}.${version[2]}`, () => {
    return Device.version().then( v => {
        expect(v.sdk.major).toBe(parseInt(version[0]))
        expect(v.sdk.minor).toBe(parseInt(version[1]))
        expect(v.sdk.patch).toBe(parseInt(version[2]))
    })
});