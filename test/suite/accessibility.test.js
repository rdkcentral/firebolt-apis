/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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
