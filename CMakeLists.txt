cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(syntax)

set(JEJALYK_COMPILER_SRC
        chrono.h
        ast.cpp
        ast.h
        parser.cpp
        parser.h
        tools.cpp
        tools.h
        js/js.h
        jejalyk.cpp
        jejalyk.h
        typeinterpreter/typeinterpreter.cpp
        typeinterpreter/typeinterpreter.h
        typeinterpreter/Type.cpp
        typeinterpreter/Subject.cpp
        typeinterpreter/Scope.cpp
        typeinterpreter/Options.cpp
        typeinterpreter/diia.cpp
        typeinterpreter/structure.cpp
        typeinterpreter/instructions/compile_anon_diia.cpp
        typeinterpreter/instructions/compile_arithmetic_node.cpp
        typeinterpreter/instructions/compile_array_node.cpp
        typeinterpreter/instructions/compile_as_node.cpp
        typeinterpreter/instructions/compile_assign_by_element_node.cpp
        typeinterpreter/instructions/compile_assign_by_identifier_node.cpp
        typeinterpreter/instructions/compile_assign_simple_node.cpp
        typeinterpreter/instructions/compile_bitwise_node.cpp
        typeinterpreter/instructions/compile_bitwise_not_node.cpp
        typeinterpreter/instructions/compile_break_node.cpp
        typeinterpreter/instructions/compile_call_node.cpp
        typeinterpreter/instructions/compile_chain_node.cpp
        typeinterpreter/instructions/compile_comparison_node.cpp
        typeinterpreter/instructions/compile_continue_node.cpp
        typeinterpreter/instructions/compile_dictionary_node.cpp
        typeinterpreter/instructions/compile_diia_node.cpp
        typeinterpreter/instructions/compile_diia_or_mockup_diia_node.cpp
        typeinterpreter/instructions/compile_each_node.cpp
        typeinterpreter/instructions/compile_eval_node.cpp
        typeinterpreter/instructions/compile_from_to_complex_node.cpp
        typeinterpreter/instructions/compile_from_to_simple_node.cpp
        typeinterpreter/instructions/compile_function_node.cpp
        typeinterpreter/instructions/compile_get_element_node.cpp
        typeinterpreter/instructions/compile_give_node.cpp
        typeinterpreter/instructions/compile_god_node.cpp
        typeinterpreter/instructions/compile_identifier_node.cpp
        typeinterpreter/instructions/compile_if_node.cpp
        typeinterpreter/instructions/compile_method_declaration_node.cpp
        typeinterpreter/instructions/compile_mml_node.cpp
        typeinterpreter/instructions/compile_mockup_diia_node.cpp
        typeinterpreter/instructions/compile_mockup_module_node.cpp
        typeinterpreter/instructions/compile_mockup_structure_node.cpp
        typeinterpreter/instructions/compile_mockup_subject_node.cpp
        typeinterpreter/instructions/compile_module_node.cpp
        typeinterpreter/instructions/compile_mrm_diia_node.cpp
        typeinterpreter/instructions/compile_negative_node.cpp
        typeinterpreter/instructions/compile_not_node.cpp
        typeinterpreter/instructions/compile_number_node.cpp
        typeinterpreter/instructions/compile_positive_node.cpp
        typeinterpreter/instructions/compile_post_decrement_node.cpp
        typeinterpreter/instructions/compile_post_increment_node.cpp
        typeinterpreter/instructions/compile_pre_decrement_node.cpp
        typeinterpreter/instructions/compile_pre_increment_node.cpp
        typeinterpreter/instructions/compile_return_node.cpp
        typeinterpreter/instructions/compile_string_node.cpp
        typeinterpreter/instructions/compile_structure_node.cpp
        typeinterpreter/instructions/compile_take_module_node.cpp
        typeinterpreter/instructions/compile_take_pak_node.cpp
        typeinterpreter/instructions/compile_ternary_node.cpp
        typeinterpreter/instructions/compile_test_node.cpp
        typeinterpreter/instructions/compile_throw_node.cpp
        typeinterpreter/instructions/compile_try_node.cpp
        typeinterpreter/instructions/compile_type_value_single_node.cpp
        typeinterpreter/instructions/compile_wait_node.cpp
        typeinterpreter/instructions/compile_while_node.cpp
)

add_executable(jejalyk jejalyk_bin.cpp ${JEJALYK_COMPILER_SRC})
add_executable(jejalyk_node jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
add_executable(jejalyk_web jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
add_executable(optimized_jejalyk jejalyk_bin.cpp ${JEJALYK_COMPILER_SRC})
add_executable(optimized_jejalyk_node jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
add_executable(optimized_jejalyk_web jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})

target_link_libraries(jejalyk mavka_syntax)
target_link_libraries(jejalyk_node mavka_syntax)
target_link_libraries(jejalyk_web mavka_syntax)
target_link_libraries(optimized_jejalyk mavka_syntax)
target_link_libraries(optimized_jejalyk_node mavka_syntax)
target_link_libraries(optimized_jejalyk_web mavka_syntax)

target_compile_options(jejalyk PRIVATE -fexceptions)
target_compile_options(jejalyk_node PRIVATE -fexceptions)
target_compile_options(jejalyk_web PRIVATE -fexceptions)
target_compile_options(optimized_jejalyk PRIVATE -fexceptions -O3)
target_compile_options(optimized_jejalyk_node PRIVATE -fexceptions -O3)
target_compile_options(optimized_jejalyk_web PRIVATE -fexceptions -O3)

set_target_properties(jejalyk PROPERTIES OUTPUT_NAME "джеджалик")
set_target_properties(jejalyk_node PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(jejalyk_web PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(optimized_jejalyk PROPERTIES LINK_FLAGS "-O3")
set_target_properties(optimized_jejalyk_node PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(optimized_jejalyk_web PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
