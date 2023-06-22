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
project_version(1.0.0)

set(TESTLIB ${PROJECT_NAME})

message("Setup ${TESTLIB} v${PROJECT_VERSION}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(${NAMESPACE}Core CONFIG REQUIRED)

file(GLOB CPP_SOURCES *.cpp)
add_library(${TESTLIB} STATIC ${CPP_SOURCES} CoreSDKTestGeneratedCode.c)

target_link_libraries(${TESTLIB}
	PRIVATE
	${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
        ${NAMESPACE}Core::${NAMESPACE}Core
)

target_include_directories(${TESTLIB}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<BUILD_INTERFACE:${SYSROOT_PATH}/usr/include>
)

set_target_properties(${TESTLIB} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    LINK_WHAT_YOU_USE TRUE
    FRAMEWORK FALSE
)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(TESTAPP FireboltCoreSDKTestApp)

message("Setup ${TESTAPP} v${PROJECT_VERSION}")

add_executable(${TESTAPP} Main.c)

target_link_libraries(${TESTAPP}
    PRIVATE
        ${TESTLIB}
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

install(
    TARGETS ${TESTLIB} EXPORT ${TESTLIB}Targets
    LIBRARY DESTINATION lib COMPONENT libs
     PUBLIC_HEADER DESTINATION include/${FIREBOLT_NAMESPACE}Test COMPONENT devel   # headers for mac (note the different component -> different package)
        INCLUDES DESTINATION include/${FIREBOLT_NAMESPACE}Test # headers
)

InstallCMakeConfig(TARGETS ${TESTLIB})
InstallCMakeConfigs(TARGET ${TESTLIB} DESTINATION ${FIREBOLT_NAMESPACE})
InstallHeaders(TARGET ${TESTLIB} HEADERS . NAMESPACE ${FIREBOLT_NAMESPACE} DESTINATION FireboltTest)
InstallLibraries(TARGET ${TESTLIB} LIBRARIES ${TESTLIB} DESTINATION ${FIREBOLT_NAMESPACE})

add_custom_command(
    TARGET ${TESTAPP}
    POST_BUILD
    COMMENT "=================== Installing TestApp ======================"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${TESTAPP} ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
)
