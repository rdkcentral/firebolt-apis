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




function ready() {
  return Transport.send('metrics', 'ready', {})
}

function signIn() {
  return Transport.send('metrics', 'signIn', {})
}

function signOut() {
  return Transport.send('metrics', 'signOut', {})
}



function startContent(entityId) {

  const transforms = null

  return Transport.send('metrics', 'startContent', { entityId }, transforms)
}

function stopContent(entityId) {

  const transforms = null

  return Transport.send('metrics', 'stopContent', { entityId }, transforms)
}

function page(pageId) {

  const transforms = null

  return Transport.send('metrics', 'page', { pageId }, transforms)
}

function action(category, type, parameters) {

  const transforms = null

  return Transport.send('metrics', 'action', { category, type, parameters }, transforms)
}

function error(type, code, description, visible, parameters) {

  const transforms = null

  return Transport.send('metrics', 'error', { type, code, description, visible, parameters }, transforms)
}

function mediaLoadStart(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaLoadStart', { entityId }, transforms)
}

function mediaPlay(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaPlay', { entityId }, transforms)
}

function mediaPlaying(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaPlaying', { entityId }, transforms)
}

function mediaPause(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaPause', { entityId }, transforms)
}

function mediaWaiting(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaWaiting', { entityId }, transforms)
}

function mediaProgress(entityId, progress) {

  const transforms = null

  return Transport.send('metrics', 'mediaProgress', { entityId, progress }, transforms)
}

function mediaSeeking(entityId, target) {

  const transforms = null

  return Transport.send('metrics', 'mediaSeeking', { entityId, target }, transforms)
}

function mediaSeeked(entityId, position) {

  const transforms = null

  return Transport.send('metrics', 'mediaSeeked', { entityId, position }, transforms)
}

function mediaRateChange(entityId, rate) {

  const transforms = null

  return Transport.send('metrics', 'mediaRateChange', { entityId, rate }, transforms)
}

function mediaRenditionChange(entityId, bitrate, width, height, profile) {

  const transforms = null

  return Transport.send('metrics', 'mediaRenditionChange', { entityId, bitrate, width, height, profile }, transforms)
}

function mediaEnded(entityId) {

  const transforms = null

  return Transport.send('metrics', 'mediaEnded', { entityId }, transforms)
}

export default {


  ErrorType: {
    NETWORK: 'network',
    MEDIA: 'media',
    RESTRICTION: 'restriction',
    ENTITLEMENT: 'entitlement',
    OTHER: 'other'
  },

startContent,
  stopContent,
  page,
  action,
  error,
  mediaLoadStart,
  mediaPlay,
  mediaPlaying,
  mediaPause,
  mediaWaiting,
  mediaProgress,
  mediaSeeking,
  mediaSeeked,
  mediaRateChange,
  mediaRenditionChange,
  mediaEnded
}

export {
  ready,
  signIn,
  signOut
}