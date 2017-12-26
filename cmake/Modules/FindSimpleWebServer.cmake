find_path(SimpleWebServer_INCLUDE_DIR NAMES
    simple-web-server/server_http.hpp
    simple-web-server/server_https.hpp)
mark_as_advanced(SimpleWebServer_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SimpleWebServer REQUIRED_VARS SimpleWebServer_INCLUDE_DIR)

set(SimpleWebServer_INCLUDE_DIRS ${SimpleWebServer_INCLUDE_DIR})
