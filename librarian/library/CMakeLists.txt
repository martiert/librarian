project(library)

set(CMAKE_BUILD_TYPE Debug)
set(Library_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/api)
add_subdirectory(src)

if (${BUILD_TESTING})
  add_subdirectory(test)
endif (${BUILD_TESTING})
