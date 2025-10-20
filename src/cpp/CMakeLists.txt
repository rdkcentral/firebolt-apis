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
include(HelperFunctions)

project(FireboltSDK)
project_version("1.0.0")

option(FIREBOLT_ENABLE_STATIC_LIB "Create Firebolt library as Static library" OFF)
option(ENABLE_TESTS "Build openrpc native test" OFF)
option(ENABLE_UNIT_TESTS "Build openrpc native test" OFF)
option(ENABLE_DEMO_APP "Build demo app" OFF)

if (FIREBOLT_ENABLE_STATIC_LIB)
    set(FIREBOLT_LIBRARY_TYPE STATIC)
    add_compile_definitions(FIREBOLTSDK_STATIC_DEFINE)
else ()
    set(FIREBOLT_LIBRARY_TYPE SHARED)
endif ()

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

if (ENABLE_UNIT_TESTS)
    enable_testing()
    set(ENABLE_TESTS ON)
    add_compile_definitions(UNIT_TEST)
    add_compile_definitions(UT_OPEN_RPC_FILE="firebolt-core-open-rpc.json")
endif ()

add_subdirectory(src)

if (ENABLE_DEMO_APP)
    add_subdirectory(demo)
endif()

if (ENABLE_TESTS)
    add_subdirectory(test)
endif()
