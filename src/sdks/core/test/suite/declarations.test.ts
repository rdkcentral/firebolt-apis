import { transport } from '../../../../../test/TransportHarness.js'
import MockTransport from '../../build/javascript/src/Transport/MockTransport.mjs'

import { test, expect } from "@jest/globals"
import { Lifecycle, Device, Discovery } from "../../build/javascript/src/firebolt";

let listenerId: number

/*
class DiscoveryProvider implements Discovery.Discovery {
  async purchasedContent(
    parameters: Discovery.PurchasedContentParameters
  ): Promise<Discovery.PurchasedContentResult> {

    return Promise.resolve({
      expires: '',
      totalCount: 5,
      entries: []
    });
  }
  async entityInfo(
    parameters: Discovery.EntityInfoParameters
  ): Promise<Discovery.EntityInfoResult> {

    return Promise.resolve({
      entity: {
        entityType: 'program',
        identifiers: {
          entityId: '123'
        },
        programType: Discovery.ProgramType.MOVIE,
        title: 'A title'
      },
      expires: ''
    });
  }
 
}
*/

test('Able to get TypeScript listenerId', () => {
    return Lifecycle.listen('inactive', () => { }).then((id: number) => {
        listenerId = id
        expect(listenerId > 0).toBe(true)
    })
})

test('Able to get resolution', () => {
    return Device.screenResolution().then((res: [number, number]) => {
        expect(res[0] > 0).toBe(true)
        expect(res[1] > 0).toBe(true)
    })
})
/*
test('purchaseContent', () => {
    let totalCount = 0;
    transport.onSend((json) => {
        let [module, method] = json.method.split('.')
        expect(module).toBe('Discovery')

        if (method === 'purchasedContent') {
            totalCount = json.params.result.totalCount
            MockTransport.receiveMessage(JSON.stringify({ jsonrpc: "2.0", result: { "value": true }, id: json.id }))
        }
    })
    let result = Discovery.purchasedContent({
        expires: '',
        totalCount: 5,
        entries: [
        ]
    }).then(() => {
        expect(totalCount).toBe(5)
    });


})

const result: Discovery.EntityInfoResult = {
    entity: {
        "entityType": "program",
        "identifiers": {
            "entityId": "123"
        },
        "programType": Discovery.ProgramType.MOVIE,
        "title": "A title"
    },
    "expires": ""
}

test('entityInfo', () => {
     let totalCount = 0;
    transport.onSend((json) => {
        let [module, method] = json.method.split('.')
        expect(module).toBe('Discovery')

        if (method === 'entityInfo') {

            totalCount = json.params.result.totalCount
            MockTransport.receiveMessage(JSON.stringify({ jsonrpc: "2.0", result:  true , id: json.id }))
        }
    })
    return Discovery.entityInfo(result).then((r) => {
      
        expect(r).toBe(true)
        
    })
})

test('entityInfo pull', () => {
    let resolver
    const p = new Promise((resolve, reject) => {
        resolver = resolve
    })

    Discovery.entityInfo((request: Discovery.EntityInfoParameters) => {
        setTimeout(_ => {
            resolver()
        }, 1000)

        return Promise.resolve(result)
    })

    
    Setup.emit('discovery', 'pullEntityInfo', {
        correlationId: '123',
        parameters: {
            entityId: '123'
        }
    })
    
    let result2: Discovery.EntityInfoResult = sent.find(message => message.method === 'entityInfo').params.result
    expect(result2.entity.identifiers.entityId).toBe("123")

    return p
})
*/