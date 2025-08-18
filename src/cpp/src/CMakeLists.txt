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

set(TARGET ${PROJECT_NAME})
message("Setup ${TARGET} v${PROJECT_VERSION}")

file(GLOB SOURCES *.cpp json_types/*.cpp)

add_library(${TARGET} ${FIREBOLT_LIBRARY_TYPE}
    ${SOURCES}
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(FireboltTransport CONFIG REQUIRED)
find_package(WPEFramework CONFIG REQUIRED)
find_package(WPEFrameworkWebSocket CONFIG REQUIRED)
find_package(WPEFrameworkCore CONFIG REQUIRED)

target_link_libraries(${TARGET}
    PRIVATE
        WPEFrameworkWebSocket::WPEFrameworkWebSocket
        WPEFrameworkCore::WPEFrameworkCore
    PUBLIC
        FireboltTransport::FireboltTransport
)

target_include_directories(${TARGET}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/json_types>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${FIREBOLT_NAMESPACE}>
)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(TARGETS ${TARGET}
    EXPORT ${TARGET}Targets
    ARCHIVE DESTINATION lib COMPONENT libs  # static lib
    LIBRARY DESTINATION lib COMPONENT libs  # shared lib
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/${FIREBOLT_NAMESPACE}
    FILES_MATCHING PATTERN "*.h")

install(
    FILES ${CMAKE_BINARY_DIR}/src/${TARGET}Config.cmake
    DESTINATION lib/cmake/${FIREBOLT_NAMESPACE})

InstallCMakeConfig(TARGETS ${TARGET})
InstallPackageConfig(TARGETS ${TARGET} DESCRIPTION "Firebolt Native SDK Library")
