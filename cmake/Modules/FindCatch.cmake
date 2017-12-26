find_path(Catch_INCLUDE_DIR NAMES catch/catch.hpp)
mark_as_advanced(Catch_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Catch REQUIRED_VARS Catch_INCLUDE_DIR)

set(Catch_INCLUDE_DIRS ${Catch_INCLUDE_DIR})
