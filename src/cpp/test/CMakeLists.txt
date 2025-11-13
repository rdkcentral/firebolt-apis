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

set(TESTAPP TestFireboltCore)

find_package(FireboltTransport CONFIG REQUIRED)
find_package(Curl REQUIRED )
find_package(GTest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(nlohmann_json_schema_validator CONFIG REQUIRED)

include(GoogleTest)

enable_testing()

add_compile_definitions(UT_OPEN_RPC_FILE="firebolt-core-open-rpc.json")

message("Setup ${TESTAPP}")

add_executable(${TESTAPP} CoreSDKTest.cpp Main.cpp)

target_link_libraries(${TESTAPP}
    PRIVATE
        FireboltTransport::FireboltTransport
        FireboltSDK
        nlohmann_json::nlohmann_json
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
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${TESTAPP} ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
)

set(UNIT_TESTS_APP FireboltCoreUnitTests)

message("Setup ${UNIT_TESTS_APP}")

set(UNIT_TESTS
    "unit/lifecycleTest.cpp"
)

add_executable(${UNIT_TESTS_APP}
    UnitTestsMain.cpp
    ${UNIT_TESTS}
)

target_link_libraries(${UNIT_TESTS_APP}
    PRIVATE
        FireboltSDK
        FireboltTransport::FireboltTransport
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator::validator
        GTest::gtest
        GTest::gmock
)

target_include_directories(${UNIT_TESTS_APP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test/>
)

set_target_properties(${UNIT_TESTS_APP} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/src"
    INSTALL_RPATH "$ORIGIN/../src"
)

if(DISCOVER_UT)
    gtest_discover_tests(${UNIT_TESTS_APP}
        PROPERTIES
            ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/src"
    )
endif()

set(COMPONENT_TESTS_APP FireboltCoreComponentTests)

message("Setup ${COMPONENT_TESTS_APP}")

set(COMPONENT_TESTS
    "component/lifecycleTest.cpp"
)

add_executable(${COMPONENT_TESTS_APP}
    ComponentTestsMain.cpp
    "component/utils.cpp"
    ${COMPONENT_TESTS}
)

target_link_libraries(${COMPONENT_TESTS_APP}
    PRIVATE
        FireboltSDK
        FireboltTransport::FireboltTransport
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator::validator
        CURL::libcurl
        GTest::gtest
        GTest::gmock
)

target_include_directories(${COMPONENT_TESTS_APP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test/>
)

set_target_properties(${COMPONENT_TESTS_APP} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    BUILD_RPATH "${CMAKE_BINARY_DIR}/src"
    INSTALL_RPATH "$ORIGIN/../src"
)

if(DISCOVER_CT)
    gtest_discover_tests(${COMPONENT_TESTS_APP}
        PROPERTIES
            ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/src"
    )
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
