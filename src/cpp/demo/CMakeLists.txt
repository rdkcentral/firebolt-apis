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

if (NOT CMAKE_PROJECT_NAME)
    project(FireboltCoreSDKDemo)
    cmake_minimum_required(VERSION 3.10)

    if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX "${SYSROOT_PATH}/usr" CACHE INTERNAL "" FORCE)
        set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
    endif()

    list(APPEND CMAKE_MODULE_PATH
        "${SYSROOT_PATH}/usr/lib/cmake"
        "${SYSROOT_PATH}/tools/cmake"
    )
endif ()

message("Setup ${PROJECT_NAME}")

find_package(FireboltTransport CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    FireboltDemoService.cpp
    main.cpp)

if (NOT ENABLE_DEMO_APP)
    find_package(FireboltSDK CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            FireboltSDK::FireboltSDK
    )
else()
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            FireboltSDK
    )
endif ()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION bin
)
