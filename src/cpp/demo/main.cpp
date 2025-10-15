/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
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
 */

#include "FireboltDemoService.h"
#include <exception>
#include <iostream>

int main()
try
{
    std::cout << "Firebolt SDK POC Demo\n";

    FireboltDemoService service;

    std::string input;
    while (1) {
        service.ownDemo();
        std::cout << "Press a key to rerun, 's' for subscribe  or 'q' to quit" << std::endl;
        getline(std::cin, input);
        if (false) {
        } else if (input == "s") {
            service.ownSubscriptionDemo();
        } else if (input == "q") {
            break;
        }
    }

    return 0;
}
catch (const std::exception& e)
{
    std::cout << "Firebolt SDK error: " << e.what() << std::endl;
    return -1;
}
