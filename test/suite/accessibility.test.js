import Setup from '../Setup'
import { Accessibility } from '../../dist/firebolt.js'

test('closedCaptions() settings', () => {
    return Accessibility.closedCaptions().then(settings => {
        expect(settings.enabled).toBe(true)
        expect(settings.styles.fontFamily).toBe('Monospace sans-serif')
        expect(settings.styles.fontSize).toBe(1)
        expect(settings.styles.fontColor).toBe('#ffffff')
        expect(settings.styles.fontEdge).toBe('none')
        expect(settings.styles.fontEdgeColor).toBe('#7F7F7F')
        expect(settings.styles.fontOpacity).toBe(100)
        expect(settings.styles.backgroundColor).toBe('#000000')
        expect(settings.styles.backgroundOpacity).toBe(100)
        expect(settings.styles.textAlign).toBe('center')
        expect(settings.styles.textAlignVertical).toBe('middle')

    })
});

test('voiceGuidance() settings', () => {
    return Accessibility.voiceGuidance().then(settings => {
        expect(settings.enabled).toBe(true)
        expect(settings.speed).toBe(5)
    })
});
