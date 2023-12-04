cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parser)

add_executable(main main.cpp
)
#add_executable(jejalyk_wasm jejalyk_wasm.cpp)

target_link_libraries(main mavka_parser)
#target_link_libraries(jejalyk_wasm mavka_parser)

#set_target_properties(jejalyk_wasm PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE")
