/*
 * Copyright 2024 Comcast Cable Communications Management, LLC
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
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <types/fb-errors.h>

#if !(defined COMPONENT_TEST || defined UNIT_TEST)
  #error "This file must be included only for Unit Tests or Component Tests"
#endif

using namespace ::testing;

#define REMOVE_QUOTES(s) (s.substr(1, s.length() - 2))
#define STRING_TO_BOOL(s) (s == "true" ? true : false)


inline std::string capitalizeFirstChar(std::string str) {
    if (!str.empty()) {
        str[0] = std::toupper(str[0]);
    }
    return str;
}

class JsonEngine
{
    private:
        std::ifstream _file;
        nlohmann::json _data;

    public:

        JsonEngine()
        {
            _data = read_json_from_file();
        }

        ~JsonEngine(){
            if (_file.is_open())
                _file.close();
        }

        nlohmann::json  get_value(const std::string& method_name)
        {
            for (const auto &method : _data["methods"])
            {
                if (method.contains("name") && (method["name"] == method_name))
                {
                    return method["examples"][0]["result"]["value"];
                }
            }
            return nlohmann::json{};
        }

        nlohmann::json read_json_from_file()
        {
            std::string filename = UT_OPEN_RPC_FILE;
            std::ifstream file(filename);
            if (!file.is_open())
            {
                throw std::runtime_error("Could not open file: " + filename);
            }

            nlohmann::json j;
            file >> j;
            return j;
        }

        nlohmann::json resolve_reference(const nlohmann::json &full_schema, const std::string &ref)
        {
            if (ref.find("#/") != 0)
            {
                throw std::invalid_argument("Only internal references supported");
            }

            std::string path = ref.substr(2);
            std::istringstream ss(path);
            std::string token;
            nlohmann::json current = full_schema;

            while (std::getline(ss, token, '/'))
            {
                if (current.contains(token))
                {
                    current = current[token];
                }
                else
                {
                    throw std::invalid_argument("Invalid reference path: " + ref);
                }
            }

            return current;
        }

        nlohmann::json process_schema(nlohmann::json schema, const nlohmann::json &full_schema)
        {
            if (schema.is_object())
            {
                if (schema.contains("$ref"))
                {
                    std::string ref = schema["$ref"];
                    schema = resolve_reference(full_schema, ref);
                }

                for (auto &el : schema.items())
                {
                    el.value() = process_schema(el.value(), full_schema);
                }
            }
            else if (schema.is_array())
            {
                for (auto &el : schema)
                {
                    el = process_schema(el, full_schema);
                }
            }

            return schema;
        }

        void MockRequest(const nlohmann::json& message)
        {
            std::string methodName = capitalizeFirstChar(message["method"]);

            /* TODO: Add a flag here that will be set to true if the method name is found in the rpc block, u
               Use the flag to validate "Method not found" or other errors from SDK if applicable */
            for (const auto &method : _data["methods"])
            {
                if (method.contains("name") && (method["name"] == methodName))
                {
                    // Method name validation
                    EXPECT_EQ(methodName, method["name"]);

                    // ID Validation
                    // TODO: Check if id gets incremented by 1 for each request
                    // EXPECT_THAT(message->Id, AllOf(Ge(1),Le(std::numeric_limits<int>::max())));

                    // Schema validation
                    const nlohmann::json requestParams = message["params"];
                    if(method["params"].empty()) {
                        std::cout << "Schema validation for empty parameters" << std::endl;
                        EXPECT_EQ(requestParams, "{}"_json);
                    }
                    else {
                        nlohmann::json_schema::json_validator validator(nullptr, nlohmann::json_schema::default_string_format_check);
                        const nlohmann::json openRPCParams = method["params"];
                        for (auto& item : openRPCParams.items()) {
                            std::string key = item.key();
                            nlohmann::json currentSchema = item.value();
                            std::string paramName = currentSchema["name"];
                            if (requestParams.contains(paramName)) {
                                nlohmann::json dereferenced_schema = process_schema(currentSchema, _data);
                                try{
                                    validator.set_root_schema(dereferenced_schema["schema"]);
                                    validator.validate(requestParams[paramName]);
                                    std::cout << "Schema validation succeeded" << std::endl;
                                }
                                catch (const std::exception &e){
                                    FAIL() << "Schema validation error: " << e.what() << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }

        Firebolt::Error MockResponse(nlohmann::json &message)
        {
            std::string methodName = capitalizeFirstChar(message["method"]);
            for (const auto &method : _data["methods"])
            {
                if (method.contains("name") && (method["name"] == methodName))
                {
                    message["result"] = method["examples"][0]["result"]["value"];
                    return Firebolt::Error::None;
                }
            }
            return Firebolt::Error::General;
        }
};

