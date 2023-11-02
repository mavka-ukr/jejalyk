cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 17)

add_executable(jejalyk jejalyk.cpp)

set_target_properties(jejalyk PROPERTIES LINK_FLAGS "-s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")
