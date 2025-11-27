# Copyright 2023 Comcast Cable Communications Management, LLC
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
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(FireboltClient)

if (NOT PROJECT_VERSION)
    set(VERSION_STRING "0.1.0-unknown")

    find_package(Git QUIET)

    if (GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0 --match "v[0-9]*.[0-9]*.[0-9]*"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
    endif ()

    if (GIT_VERSION)
        string(REGEX REPLACE "^v" "" VERSION_STRING "${GIT_VERSION}")
    endif ()

    if(VERSION_STRING STREQUAL "0.1.0-unknown" AND EXISTS "${CMAKE_SOURCE_DIR}/.version")
        file(READ "${CMAKE_SOURCE_DIR}/.version" VERSION_STRING)
        string(STRIP ${VERSION_STRING} VERSION_STRING)
    endif()

    set(PROJECT_VERSION "${VERSION_STRING}")#dmc CACHE STRING "Project version string")
endif ()

if(EXISTS "${CMAKE_SOURCE_DIR}/.transport.version")
    file(READ "${CMAKE_SOURCE_DIR}/.transport.version" FIREBOLT_TRANSPORT_VERSION)
    string(STRIP ${FIREBOLT_TRANSPORT_VERSION} FIREBOLT_TRANSPORT_VERSION)
else()
    message(FATAL_ERROR "Could not determine firebolt-native-transport version from .transport.version")
endif()

set(VERSION ${PROJECT_VERSION})
string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1" PROJECT_VERSION_MAJOR ${PROJECT_VERSION})
string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\2" PROJECT_VERSION_MINOR ${PROJECT_VERSION})
string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\3" PROJECT_VERSION_PATCH ${PROJECT_VERSION})

message(STATUS "Project version: ${PROJECT_VERSION}")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ENABLE_TESTS "Build openrpc native test" OFF)
option(DISCOVER_UT "Discover all Unit Tests" ON)
option(DISCOVER_CT "Discover all Component Tests" ON)
option(TRANSPORT_LINKAGE_STATIC "Link transport library statically (ON) or shared (OFF)" OFF)
option(ENABLE_DEMO_APP "Build demo app" OFF)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${SYSROOT_PATH}/usr" CACHE INTERNAL "" FORCE)
    set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
endif()

list(APPEND CMAKE_PREFIX_PATH
    "${SYSROOT_PATH}/usr/share/cmake")

list(APPEND CMAKE_MODULE_PATH
    "${SYSROOT_PATH}/usr/share/cmake"
    "${SYSROOT_PATH}/usr/lib/cmake"
)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)

if (ENABLE_DEMO_APP)
    add_subdirectory(demo)
endif()

if (ENABLE_TESTS)
    add_subdirectory(test)
endif()
