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
import MockProps from "../Prop/MockProps.mjs"

export default {

    closedCaptions: {
  "enabled": true,
  "styles": {
    "fontFamily": "Monospace sans-serif",
    "fontSize": 1,
    "fontColor": "#ffffff",
    "fontEdge": "none",
    "fontEdgeColor": "#7F7F7F",
    "fontOpacity": 100,
    "backgroundColor": "#000000",
    "backgroundOpacity": 100,
    "textAlign": "center",
    "textAlignVertical": "middle"
  }
},

    closedCaptionsSettings: function () { return MockProps.mock('accessibility', 'closedCaptionsSettings', arguments, {
  "enabled": true,
  "styles": {
    "fontFamily": "Monospace sans-serif",
    "fontSize": 1,
    "fontColor": "#ffffff",
    "fontEdge": "none",
    "fontEdgeColor": "#7F7F7F",
    "fontOpacity": 100,
    "backgroundColor": "#000000",
    "backgroundOpacity": 100,
    "textAlign": "center",
    "textAlignVertical": "middle"
  }
}) },

    voiceGuidance: {
  "enabled": true,
  "speed": 5
},

    voiceGuidanceSettings: function () { return MockProps.mock('accessibility', 'voiceGuidanceSettings', arguments, {
  "enabled": true,
  "speed": 5
}) }
}