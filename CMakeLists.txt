cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(parser)

add_executable(jejalyk jejalyk_bin.cpp)
add_executable(jejalyk_node jejalyk_wasm.cpp)
add_executable(jejalyk_web jejalyk_wasm.cpp)
add_executable(optimized_jejalyk_node jejalyk_wasm.cpp)
add_executable(optimized_jejalyk_web jejalyk_wasm.cpp)

target_link_libraries(jejalyk mavka_parser)
target_link_libraries(jejalyk_node mavka_parser)
target_link_libraries(jejalyk_web mavka_parser)
target_link_libraries(optimized_jejalyk_node mavka_parser)
target_link_libraries(optimized_jejalyk_web mavka_parser)

target_compile_options(jejalyk PRIVATE -fexceptions)
target_compile_options(jejalyk_node PRIVATE -fexceptions)
target_compile_options(jejalyk_web PRIVATE -fexceptions)
target_compile_options(optimized_jejalyk_node PRIVATE -fexceptions)
target_compile_options(optimized_jejalyk_web PRIVATE -fexceptions)

set_target_properties(jejalyk PROPERTIES OUTPUT_NAME "джеджалик")
set_target_properties(jejalyk_node PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE")
set_target_properties(jejalyk_web PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_ES6=1 -sMODULARIZE")
set_target_properties(optimized_jejalyk_node PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE")
set_target_properties(optimized_jejalyk_web PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_ES6=1 -sMODULARIZE")
