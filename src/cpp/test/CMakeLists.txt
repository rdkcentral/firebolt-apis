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

cmake_minimum_required(VERSION 3.3)

set(TESTAPP TestFireboltCore)

message("Setup ${TESTAPP}")

find_package(FireboltTransport CONFIG REQUIRED)

add_executable(${TESTAPP} CoreSDKTest.cpp Main.cpp)

target_link_libraries(${TESTAPP}
    PRIVATE
        FireboltTransport::FireboltTransport
        FireboltSDK
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
)

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

if(ENABLE_UNIT_TESTS)
    set(UNIT_TESTS_APP FireboltCoreUnitTests)

    message("Setup ${UNIT_TESTS_APP}")

    find_package(nlohmann_json_schema_validator)
    find_package(GTest)

    file(GLOB UNIT_TESTS "unit/*")

    add_executable(${UNIT_TESTS_APP}
        CoreSDKTest.cpp
        Unit.cpp
        ${UNIT_TESTS}
    )

    target_link_libraries(${UNIT_TESTS_APP}
        PRIVATE
            FireboltSDK
            FireboltTransport::FireboltTransport
            nlohmann_json_schema_validator::validator
            GTest::gtest
    )

    target_include_directories(${UNIT_TESTS_APP}
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
            $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
    )

    set_target_properties(${UNIT_TESTS_APP} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
    )

    include(GoogleTest)
    gtest_discover_tests(${UNIT_TESTS_APP})
endif()

if(ENABLE_COVERAGE)
    include(${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake)

    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${CMAKE_SOURCE_DIR}/build/*"
        "${CMAKE_SOURCE_DIR}/cmake/*"
        "${CMAKE_SOURCE_DIR}/include/*"
        "${CMAKE_SOURCE_DIR}/test/*"
        "/usr/include/*")

    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES ${UNIT_TESTS_APP})

    setup_target_for_coverage_gcovr_html(
        NAME ${COVERAGE_MAIN}
        BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
        EXECUTABLE ctest
        EXECUTABLE_ARGS "--test-dir ../build/ --output-on-failure"
        DEPENDENCIES ${COVERAGE_DEPENDENCIES}
    )
endif()
