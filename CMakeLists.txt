cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parser)

add_executable(jejalyk jejalyk.cpp)

target_link_libraries(jejalyk mavka_parser)

set_target_properties(jejalyk PROPERTIES LINK_FLAGS "-s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")