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

macro(GetSubDirs subdirs currentdir)
    file(GLOB subdirectories RELATIVE ${currentdir} ${currentdir}/*)
    set(subdirs "")
    foreach(subdir ${subdirectories})
        if (IS_DIRECTORY ${currentdir}/${subdir})
            list(APPEND subdirs ${subdir})
        endif()
    endforeach()
endmacro()

function(InstallHeaders)
    set(optionsArgs EXCLUDE_ROOT_DIR)
    set(oneValueArgs TARGET NAMESPACE SOURCE DESTINATION)
    set(multiValueArgs HEADERS)

    cmake_parse_arguments(Argument "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
    if (Argument_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to InstallHeaders(): \"${Argument_UNPARSED_ARGUMENTS}\"")
    endif()
    if (Argument_HEADERS)
        add_custom_command(
            TARGET ${Argument_TARGET}
            POST_BUILD
            COMMENT "=================== Installing Headers ======================"
        )
        foreach(directory ${Argument_HEADERS})
            if (Argument_EXCLUDE_ROOT_DIR)
                set(destination ${Argument_DESTINATION})
            else()
                set(destination ${Argument_DESTINATION}/${directory})
            endif()

            if (Argument_SOURCE)
                set(source ${Argument_SOURCE})
            else()
                set(source ${CMAKE_CURRENT_LIST_DIR})
            endif()

            GetSubDirs(subdirs ${source}/${directory})
            list(APPEND subdirs ${directory})

            foreach(subdir ${subdirs})
                if (NOT subdir STREQUAL ".")
                    set(dest ${destination}/${subdir})
                    file(GLOB headers "${source}/${directory}/${subdir}/*.h")
                    if (headers)
                        install(
                            DIRECTORY "${source}/${directory}/${subdir}"
                            DESTINATION include/${dest}
                            FILES_MATCHING PATTERN "*.h")
                    endif()
                endif()
            endforeach(subdir)
        endforeach(directory)
    endif()
endfunction(InstallHeaders)
