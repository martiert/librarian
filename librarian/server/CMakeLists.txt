project(server)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED system program_options)
find_package(SimpleWebServer REQUIRED)
include_directories(${SimpleWebServer_INCLUDE_DIRS})

set(src src/main.cpp)

add_executable(server ${src})
target_link_libraries(server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
