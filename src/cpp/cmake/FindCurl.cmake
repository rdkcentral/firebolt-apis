# - Try to find the glib 2.0 library.
#
# The following are set after configuration is done:
#  CURL_FOUND
#  CURL_INCLUDE_DIRS
#  CURL_LIBRARY_DIRS
#  CURL_LIBRARIES

find_path( CURL_INCLUDE_DIR NAMES curl/curl.h )
find_library( CURL_LIBRARY NAMES curl libcurl  )

# message( "CURL_INCLUDE_DIR include dir = ${CURL_INCLUDE_DIR}" )
# message( "CURL_LIBRARY lib = ${CURL_LIBRARY}" )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY and REQUIRED arguments and set the CURL_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args( CURL DEFAULT_MSG
        CURL_LIBRARY CURL_INCLUDE_DIR )

mark_as_advanced( CURL_INCLUDE_DIR CURL_LIBRARY )

if( CURL_FOUND AND NOT TARGET CURL::libcurl)
    set( CURL_LIBRARIES ${CURL_LIBRARY} )
    set( CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIR} )

    add_library( CURL::libcurl SHARED IMPORTED )
    set_target_properties( CURL::libcurl PROPERTIES
            IMPORTED_LOCATION "${CURL_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIRS}" )
endif()