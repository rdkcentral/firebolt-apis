
import { test, expect } from '@jest/globals';
import { Metrics } from '../../dist/lib/firebolt';


test('startContent', () => {
    return Metrics.startContent().then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('stopContent', () => {
    return Metrics.stopContent().then((res:boolean) => {
        expect(res).toBe(true);
    });
});


test('mediaLoadStart', () => {
    return Metrics.mediaLoadStart('string').then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaPlay', () => {
    return Metrics.mediaPlay('string').then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaPlaying', () => {
    return Metrics.mediaPlaying('string').then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaPause', () => {
    return Metrics.mediaPause('string').then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaWaiting', () => {
    return Metrics.mediaWaiting('string').then((res:boolean) => {
        expect(res).toBe(true);
    });
});


test('mediaProgress', () => {
    return Metrics.mediaProgress( 'string', 2).then((res:boolean) => {
        expect(res).toBe(true);
    });
});


test('mediaSeeking', () => {
    return Metrics.mediaSeeking(('string')).then((res:boolean) => {
        expect(res).toBe(true);
    });
});


test('mediaSeeked', () => {
    return Metrics.mediaSeeked(('string')).then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaRateChange', () => {
    return Metrics.mediaRateChange('string', 5).then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaRenditionChange', () => {
    return Metrics.mediaRenditionChange('string', 2, 2, 2,"num").then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('action', () => {
    return Metrics.action('user', "num").then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('error', () => {
    return Metrics.error(Metrics.ErrorType.NETWORK, "num", "num", true).then((res:boolean) => {
        expect(res).toBe(true);
    });
});

test('mediaEnded', () => {
    return Metrics.mediaEnded(('string')).then((res:boolean) => {
        expect(res).toBe(true);
    });
});





