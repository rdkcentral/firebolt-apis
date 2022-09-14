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

    config: {
  "adServerUrl": "http://demo.v.fwmrm.net/ad/p/1",
  "adServerUrlTemplate": "http://demo.v.fwmrm.net/ad/p/1?flag=+sltp+exvt+slcb+emcr+amcb+aeti&prof=12345:caf_allinone_profile &nw=12345&mode=live&vdur=123&caid=a110523018&asnw=372464&csid=gmott_ios_tablet_watch_live_ESPNU&ssnw=372464&vip=198.205.92.1&resp=vmap1&metr=1031&pvrn=12345&vprn=12345&vcid=1X0Ce7L3xRWlTeNhc7br8Q%3D%3D",
  "adNetworkId": "519178",
  "adProfileId": "12345:caf_allinone_profile",
  "adSiteSectionId": "caf_allinone_profile_section",
  "adOptOut": true,
  "privacyData": "ew0KICAicGR0IjogImdkcDp2MSIsDQogICJ1c19wcml2YWN5IjogIjEtTi0iLA0KICAibG10IjogIjEiIA0KfQ0K",
  "ifaValue": "01234567-89AB-CDEF-GH01-23456789ABCD",
  "ifa": "ewogICJ2YWx1ZSI6ICIwMTIzNDU2Ny04OUFCLUNERUYtR0gwMS0yMzQ1Njc4OUFCQ0QiLAogICJpZmFfdHlwZSI6ICJzc3BpZCIsCiAgImxtdCI6ICIwIgp9Cg==",
  "appName": "FutureToday",
  "appBundleId": "FutureToday.comcast",
  "distributorAppId": "1001",
  "deviceAdAttributes": "ewogICJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjogIjEyMzQiCn0=",
  "coppa": 0,
  "authenticationEntity": "60f72475281cfba3852413bd53e957f6"
},

    policy: function () { return MockProps.mock('advertising', 'policy', arguments, {
  "skipRestriction": "adsUnwatched",
  "limitAdTracking": false
}) },

    advertisingId: {
  "ifa": "01234567-89AB-CDEF-GH01-23456789ABCD",
  "ifa_type": "idfa",
  "lmt": "0"
},

    deviceAttributes: {},

    appBundleId: "operator.app"
}