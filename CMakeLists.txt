cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parser)

add_executable(jejalyk jejalyk.cpp)
#add_executable(jejalyk_node jejalyk.cpp)
#add_executable(jejalyk_web jejalyk.cpp)

target_link_libraries(jejalyk mavka_parser)
#target_link_libraries(jejalyk_node mavka_parser)
#target_link_libraries(jejalyk_web mavka_parser)

#set_target_properties(jejalyk_node PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE")
#set_target_properties(jejalyk_node PROPERTIES LINK_FLAGS "-lembind -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE")
#set_target_properties(jejalyk_web PROPERTIES LINK_FLAGS "-lembind -sASYNCIFY=1 -sENVIRONMENT=web")