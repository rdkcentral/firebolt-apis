/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
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
 */

#include "jsondata_accessibility.h"

namespace WPEFramework
{
/* FontFamily  */
ENUM_CONVERSION_BEGIN(Firebolt::Accessibility::FontFamily){Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF,
                                                           _T("monospaced_serif")},
    {Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF, _T("proportional_serif")},
    {Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF, _T("monospaced_sanserif")},
    {Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, _T("proportional_sanserif")},
    {Firebolt::Accessibility::FontFamily::SMALLCAPS, _T("smallcaps")},
    {Firebolt::Accessibility::FontFamily::CURSIVE, _T("cursive")},
    {Firebolt::Accessibility::FontFamily::CASUAL, _T("casual")},
    ENUM_CONVERSION_END(Firebolt::Accessibility::FontFamily)

    /* FontEdge  */
    ENUM_CONVERSION_BEGIN(Firebolt::Accessibility::FontEdge){Firebolt::Accessibility::FontEdge::NONE, _T("none")},
    {Firebolt::Accessibility::FontEdge::RAISED, _T("raised")},
    {Firebolt::Accessibility::FontEdge::DEPRESSED, _T("depressed")},
    {Firebolt::Accessibility::FontEdge::UNIFORM, _T("uniform")},
    {Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT, _T("drop_shadow_left")},
    {Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT, _T("drop_shadow_right")},
    ENUM_CONVERSION_END(Firebolt::Accessibility::FontEdge)
} // namespace WPEFramework
