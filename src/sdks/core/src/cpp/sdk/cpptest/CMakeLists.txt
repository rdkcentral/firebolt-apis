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

cmake_minimum_required(VERSION 3.3)

project(FireboltCoreSDKTests)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${SYSROOT_PATH}/usr" CACHE INTERNAL "" FORCE)
    set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH
	"${SYSROOT_PATH}/usr/lib/cmake"
	"${SYSROOT_PATH}/tools/cmake")
message("FIREBOLT_PATH inside cmake " ${FIREBOLT_PATH})
if (FIREBOLT_PATH)
    set(CMAKE_FIREBOLT_PATH
        "${FIREBOLT_PATH}/usr/lib/cmake/Firebolt"
	"${FIREBOLT_PATH}/usr/lib/cmake/FireboltSDK")
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_FIREBOLT_PATH})
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_FIREBOLT_PATH})
else ()
   set(FIREBOLT_PATH "${SYSROOT_PATH}" CACHE INTERNAL "" FORCE)
endif ()

find_package(WPEFramework CONFIG REQUIRED)
find_package(${NAMESPACE}Core CONFIG REQUIRED)
find_package(Firebolt CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDK CONFIG REQUIRED)

# Manually add the library
add_library(nlohmann_json_schema_validator SHARED IMPORTED)
set_target_properties(nlohmann_json_schema_validator PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/build/_deps/nlohmann_json_schema_validator-src/libnlohmann_json_schema_validator.a
)
add_library(gmock_main SHARED IMPORTED)
set_target_properties(gmock_main PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/lib/libgmock.a
)
add_library(gtest SHARED IMPORTED)
set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/lib/libgtest.a
)

add_library(gtest_main SHARED IMPORTED)
set_target_properties(gtest_main PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/lib/libgtest_main.a
)

include_directories(${CMAKE_SOURCE_DIR}/build/_deps/json-src/include)

set(TESTAPP TestFireboltCore)

message("Setup ${TESTAPP}")

if(UNIT_TEST STREQUAL "ON")
    add_definitions(-DUNIT_TEST)

    file(GLOB UNIT_TESTS "unit/advertisingTest.cpp")

    add_executable(${TESTAPP} 
        CoreSDKTest.cpp 
        Unit.cpp 
        ${UNIT_TESTS}
    )
else()
    add_executable(${TESTAPP} 
    CoreSDKTest.cpp 
    Main.cpp 
    )
endif()

target_link_libraries(${TESTAPP}
    PRIVATE
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
        nlohmann_json_schema_validator
        gmock_main
        gtest_main
        gtest
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${FIREBOLT_PATH}/usr/include/${FIREBOLT_NAMESPACE}SDK>
        $<BUILD_INTERFACE:${FIREBOLT_PATH}/usr/include/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/../build/_deps/nlohmann_json-src/include/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/../build/_deps/nlohmann_json_schema_validator-src/src/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/../>
)

if (POLYMORPHICS_REDUCER_METHODS)
    target_compile_definitions(${TESTAPP}
        PUBLIC
            POLYMORPHICS_REDUCER_METHODS=1)
endif()

set_target_properties(${TESTAPP} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

add_custom_command(
    TARGET ${TESTAPP}
    POST_BUILD
    COMMENT "=================== Installing TestApp ======================"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${TESTAPP} ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
)