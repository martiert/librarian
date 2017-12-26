find_package(Catch REQUIRED)

include_directories(${Library_INCLUDE_DIRS} ${Catch_INCLUDE_DIRS})
add_executable(library_tests test_library.cpp main.cpp)
target_link_libraries(library_tests library)

enable_testing()
add_test(NAME library_tests COMMAND library_tests)
add_dependencies(check library_tests)
