# - FindCurl.cmake
# Finds the CURL library and includes
# This will define:
#
#   CURL_FOUND          - TRUE if CURL is found
#   CURL_INCLUDE_DIRS   - The directory where curl/curl.h is found
#   CURL_LIBRARIES      - The path to the CURL library
#   CURL_VERSION_STRING - Detected version of libcurl
#
# and will define the imported target:
#
#   CURL::libcurl

find_path(CURL_INCLUDE_DIR
    NAMES curl/curl.h
    PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
)

find_library(CURL_LIBRARY
    NAMES curl libcurl
    PATHS
        /usr/lib
        /usr/local/lib
        /usr/lib/x86_64-linux-gnu
        /opt/local/lib
)

# Check version
if (CURL_INCLUDE_DIR AND EXISTS "${CURL_INCLUDE_DIR}/curl/curlver.h")
    file(STRINGS "${CURL_INCLUDE_DIR}/curl/curlver.h" _curl_version_str
        REGEX "^#define[ \t]+LIBCURL_VERSION[ \t]+\"[^\"]+\"")
    string(REGEX REPLACE "^#define[ \t]+LIBCURL_VERSION[ \t]+\"([^\"]+)\".*" "\\1"
        CURL_VERSION_STRING "${_curl_version_str}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Curl
    REQUIRED_VARS CURL_LIBRARY CURL_INCLUDE_DIR
    VERSION_VAR CURL_VERSION_STRING)

if (CURL_FOUND)
    set(CURL_LIBRARIES ${CURL_LIBRARY})
    set(CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIR})

    if (NOT TARGET CURL::libcurl)
        add_library(CURL::libcurl UNKNOWN IMPORTED)
        set_target_properties(CURL::libcurl PROPERTIES
            IMPORTED_LOCATION "${CURL_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIR}")
    endif()
endif()

mark_as_advanced(CURL_INCLUDE_DIR CURL_LIBRARY)
