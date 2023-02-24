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

import Transport from '../Transport/index.mjs'
import Events from '../Events/index.mjs'
import { registerEvents } from '../Events/index.mjs'
import Prop from '../Prop/index.mjs'

registerEvents('ClosedCaptions', Object.values(["enabledChanged","fontFamilyChanged","fontSizeChanged","fontColorChanged","fontEdgeChanged","fontEdgeColorChanged","fontOpacityChanged","backgroundColorChanged","backgroundOpacityChanged","textAlignChanged","textAlignVerticalChanged"]))



function enabled() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'enabled', {  }, callbackOrValue, false, false, 0)
}
function fontFamily() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontFamily', {  }, callbackOrValue, false, false, 0)
}
function fontSize() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontSize', {  }, callbackOrValue, false, false, 0)
}
function fontColor() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontColor', {  }, callbackOrValue, false, false, 0)
}
function fontEdge() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontEdge', {  }, callbackOrValue, false, false, 0)
}
function fontEdgeColor() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontEdgeColor', {  }, callbackOrValue, false, false, 0)
}
function fontOpacity() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'fontOpacity', {  }, callbackOrValue, false, false, 0)
}
function backgroundColor() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'backgroundColor', {  }, callbackOrValue, false, false, 0)
}
function backgroundOpacity() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'backgroundOpacity', {  }, callbackOrValue, false, false, 0)
}
function textAlign() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'textAlign', {  }, callbackOrValue, false, false, 0)
}
function textAlignVertical() {
  const callbackOrValue = arguments[0]
  return Prop.prop('closedcaptions',  'textAlignVertical', {  }, callbackOrValue, false, false, 0)
}
// onEnabledChanged API is handled via listen('enabledChanged', (data) => void)
// onFontFamilyChanged API is handled via listen('fontFamilyChanged', (data) => void)
// onFontSizeChanged API is handled via listen('fontSizeChanged', (data) => void)
// onFontColorChanged API is handled via listen('fontColorChanged', (data) => void)
// onFontEdgeChanged API is handled via listen('fontEdgeChanged', (data) => void)
// onFontEdgeColorChanged API is handled via listen('fontEdgeColorChanged', (data) => void)
// onFontOpacityChanged API is handled via listen('fontOpacityChanged', (data) => void)
// onBackgroundColorChanged API is handled via listen('backgroundColorChanged', (data) => void)
// onBackgroundOpacityChanged API is handled via listen('backgroundOpacityChanged', (data) => void)
// onTextAlignChanged API is handled via listen('textAlignChanged', (data) => void)
// onTextAlignVerticalChanged API is handled via listen('textAlignVerticalChanged', (data) => void)

    function listen(...args) {
      return Events.listen('closedcaptions', ...args)
    } 
    
    function once(...args) {
      return Events.once('closedcaptions', ...args)
    }
    
    function clear(...args) {
      return Events.clear('closedcaptions', ...args)
    }
    
export default {

  events: {
    enabledChanged:'enabledChanged',
    fontFamilyChanged:'fontFamilyChanged',
    fontSizeChanged:'fontSizeChanged',
    fontColorChanged:'fontColorChanged',
    fontEdgeChanged:'fontEdgeChanged',
    fontEdgeColorChanged:'fontEdgeColorChanged',
    fontOpacityChanged:'fontOpacityChanged',
    backgroundColorChanged:'backgroundColorChanged',
    backgroundOpacityChanged:'backgroundOpacityChanged',
    textAlignChanged:'textAlignChanged',
    textAlignVerticalChanged:'textAlignVerticalChanged'
  },
enabled,
  fontFamily,
  fontSize,
  fontColor,
  fontEdge,
  fontEdgeColor,
  fontOpacity,
  backgroundColor,
  backgroundOpacity,
  textAlign,
  textAlignVertical,
  listen,
  once,
  clear
}