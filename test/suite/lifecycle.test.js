import Setup from '../Setup'
import { Lifecycle } from '../../dist/firebolt.js'

const callback = jest.fn()
const startupState = Lifecycle.state()

beforeAll(()=> {
    Lifecycle.listen((event, _) => {
        callback(event)
    })

    Lifecycle.once('foreground', () => {
        Lifecycle.close('userExit')
    })
    
    Lifecycle.once('unloading', () => {
        Lifecycle.finished()
    })
    
    let p = new Promise( (resolve, reject) => {
        Lifecycle.once('unloading', _ => {
            resolve()
        })
    })

    Lifecycle.ready()

    return p
})

test('App starts up in the \'initializing\' state', () => {
    expect(startupState).toBe('initializing')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(1, 'inactive')
})

test('App moves to the \'foreground\' state next', () => {
    expect(callback).nthCalledWith(2, 'foreground')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(3, 'inactive')
})

test('App moves to the \'unloading\' state next', () => {
    expect(callback).nthCalledWith(4, 'unloading')
},)
