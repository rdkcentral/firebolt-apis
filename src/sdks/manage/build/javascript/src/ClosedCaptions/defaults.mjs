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

    enabled: function () { return MockProps.mock('closedcaptions', 'enabled', arguments, true) },

    fontFamily: function () { return MockProps.mock('closedcaptions', 'fontFamily', arguments, "Monospace sans-serif") },

    fontSize: function () { return MockProps.mock('closedcaptions', 'fontSize', arguments, 1) },

    fontColor: function () { return MockProps.mock('closedcaptions', 'fontColor', arguments, "#ffffff") },

    fontEdge: function () { return MockProps.mock('closedcaptions', 'fontEdge', arguments, "none") },

    fontEdgeColor: function () { return MockProps.mock('closedcaptions', 'fontEdgeColor', arguments, "#000000") },

    fontOpacity: function () { return MockProps.mock('closedcaptions', 'fontOpacity', arguments, 100) },

    backgroundColor: function () { return MockProps.mock('closedcaptions', 'backgroundColor', arguments, "#000000") },

    backgroundOpacity: function () { return MockProps.mock('closedcaptions', 'backgroundOpacity', arguments, 100) },

    textAlign: function () { return MockProps.mock('closedcaptions', 'textAlign', arguments, "center") },

    textAlignVertical: function () { return MockProps.mock('closedcaptions', 'textAlignVertical', arguments, "middle") },

    setEnabled: null,

    setFontFamily: null,

    setFontSize: null,

    setFontColor: null,

    setFontEdge: null,

    setFontEdgeColor: null,

    setFontOpacity: null,

    setBackgroundColor: null,

    setBackgroundOpacity: null,

    setTextAlign: null,

    setTextAlignVertical: null
}