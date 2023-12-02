#------------------- LIBRARY CONFIGURATION ------------------------------------

set(MAVKA_PARSER mavka_parser CACHE INTERNAL "")
set(MAVKA_PARSER_SRC
        ast.cpp
        MavkaLexer.cpp
        MavkaLexer.h
        MavkaParser.cpp
        MavkaParser.h
        MavkaParserBaseListener.cpp
        MavkaParserBaseListener.h
        MavkaParserListener.cpp
        MavkaParserListener.h
)

add_subdirectory(antlr4-cpp-runtime)

add_library(${MAVKA_PARSER} ${MAVKA_PARSER_SRC})

target_include_directories(${MAVKA_PARSER} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${MAVKA_PARSER} antlr4_cpp_runtime)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${MAVKA_PARSER} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${MAVKA_PARSER} PRIVATE
        -w -O3
    )
    target_compile_options(${MAVKA_PARSER} PUBLIC
        -Wno-attributes
    )
endif()
