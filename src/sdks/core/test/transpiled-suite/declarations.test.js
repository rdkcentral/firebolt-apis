import Setup from "../../../../../test/Setup";
import { sent } from "../../../../../test/Setup";
import { test, expect } from "@jest/globals";
import { Lifecycle, Device, Discovery } from "../../build/javascript/src/firebolt";
let listenerId;
test('Able to get TypeScript listenerId', () => {
    return Lifecycle.listen('inactive', () => { }).then((id) => {
        listenerId = id;
        expect(listenerId > 0).toBe(true);
    });
});
test('Able to get resolution', () => {
    return Device.screenResolution().then((res) => {
        expect(res[0] > 0).toBe(true);
        expect(res[1] > 0).toBe(true);
    });
});
test('purchaseContent', () => {
    return Discovery.purchasedContent({
        expires: '',
        totalCount: 5,
        entries: []
    }).then(() => {
        let result = sent.find(message => message.method === 'purchasedContent').params.result;
        expect(result.totalCount).toBe(5);
        expect(typeof result.totalCount).toBe('number');
    });
});
const result = {
    entity: {
        "entityType": "program",
        "identifiers": {
            "entityId": "123"
        },
        "programType": Discovery.ProgramType.MOVIE,
        "title": "A title"
    },
    "expires": ""
};
test('entityInfo', () => {
    return Discovery.entityInfo(result).then(() => {
        let result = sent.find(message => message.method === 'entityInfo').params.result;
        expect(result.entity.identifiers.entityId).toBe("123");
    });
});
test('entityInfo pull', () => {
    let resolver;
    const p = new Promise((resolve, reject) => {
        resolver = resolve;
    });
    Discovery.entityInfo((request) => {
        setTimeout(_ => {
            resolver();
        }, 1000);
        return Promise.resolve(result);
    });
    Setup.emit('discovery', 'pullEntityInfo', {
        correlationId: '123',
        parameters: {
            entityId: '123'
        }
    });
    let result2 = sent.find(message => message.method === 'entityInfo').params.result;
    expect(result2.entity.identifiers.entityId).toBe("123");
    return p;
});
