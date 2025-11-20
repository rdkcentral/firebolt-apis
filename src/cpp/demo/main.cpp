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
{
    try
    {
        std::cout << "Firebolt Client POC Demo" << std::endl;

        FireboltDemoService service;

        std::cout << "Lifecycle" << std::endl;
        service.lifecycle();
        std::cout << std::endl;
        std::cout << "All subscribers are registered, events can be sent to the app from mock" << std::endl;
        while (1) {
            std::cout << "Press 'q' to quit" << std::endl;
            std::string input;
            getline(std::cin, input);
            if (input == "q")
            {
                break;
            }
        }
        service.unsubscribeAll();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "Firebolt error: " << e.what() << std::endl;
        return 1;
    }
}
