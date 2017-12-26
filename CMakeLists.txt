project(librarian)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

include(CTest)
if (${BUILD_TESTING})
  add_custom_target(check ALL ${CMAKE_CTEST_COMMAND} -V)
endif (${BUILD_TESTING})

add_subdirectory(librarian)
