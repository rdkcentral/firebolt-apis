#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2025 Sky UK
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

macro(project_version)
    string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1" _VERSION_MAJOR "${ARGV0}")
    string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\2" _VERSION_MINOR "${ARGV0}")
    string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\3" _VERSION_PATCH "${ARGV0}")

    set(PROJECT_VERSION_MAJOR ${_VERSION_MAJOR})
    set(PROJECT_VERSION_MINOR ${_VERSION_MINOR})
    set(PROJECT_VERSION_PATCH ${_VERSION_PATCH})

    set(PROJECT_VERSION ${_VERSION_MAJOR}.${_VERSION_MINOR}.${_VERSION_PATCH})
    set(VERSION ${PROJECT_VERSION})
endmacro()

