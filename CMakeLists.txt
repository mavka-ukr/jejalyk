cmake_minimum_required(VERSION 3.26)
project(jejalyk)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(syntax)

set(JEJALYK_COMPILER_SRC
        compiler/instructions/compile_anon_diia_node.cpp
        compiler/instructions/compile_anon_diia_node.h
        compiler/instructions/compile_arg_node.cpp
        compiler/instructions/compile_arg_node.h
        compiler/instructions/compile_arithmetic_node.cpp
        compiler/instructions/compile_arithmetic_node.h
        compiler/instructions/compile_array_node.cpp
        compiler/instructions/compile_array_node.h
        compiler/instructions/compile_as_node.cpp
        compiler/instructions/compile_as_node.h
        compiler/instructions/compile_assign_by_element_node.cpp
        compiler/instructions/compile_assign_by_element_node.h
        compiler/instructions/compile_assign_by_identifier_node.cpp
        compiler/instructions/compile_assign_by_identifier_node.h
        compiler/instructions/compile_assign_simple_node.cpp
        compiler/instructions/compile_assign_simple_node.h
        compiler/instructions/compile_bitwise_node.cpp
        compiler/instructions/compile_bitwise_node.h
        compiler/instructions/compile_bitwise_not_node.cpp
        compiler/instructions/compile_bitwise_not_node.h
        compiler/instructions/compile_body.cpp
        compiler/instructions/compile_body.h
        compiler/instructions/compile_break_node.cpp
        compiler/instructions/compile_break_node.h
        compiler/instructions/compile_call_node.cpp
        compiler/instructions/compile_call_node.h
        compiler/instructions/compile_chain_node.cpp
        compiler/instructions/compile_chain_node.h
        compiler/instructions/compile_comparison_node.cpp
        compiler/instructions/compile_comparison_node.h
        compiler/instructions/compile_continue_node.cpp
        compiler/instructions/compile_continue_node.h
        compiler/instructions/compile_dictionary_node.cpp
        compiler/instructions/compile_dictionary_node.h
        compiler/instructions/compile_diia_body.cpp
        compiler/instructions/compile_diia_body.h
        compiler/instructions/compile_diia_node.cpp
        compiler/instructions/compile_diia_node.h
        compiler/instructions/compile_each_node.cpp
        compiler/instructions/compile_each_node.h
        compiler/instructions/compile_eval_node.cpp
        compiler/instructions/compile_eval_node.h
        compiler/instructions/compile_from_to_complex_node.cpp
        compiler/instructions/compile_from_to_complex_node.h
        compiler/instructions/compile_from_to_simple_node.cpp
        compiler/instructions/compile_from_to_simple_node.h
        compiler/instructions/compile_function_node.cpp
        compiler/instructions/compile_function_node.h
        compiler/instructions/compile_get_element_node.cpp
        compiler/instructions/compile_get_element_node.h
        compiler/instructions/compile_give_node.cpp
        compiler/instructions/compile_give_node.h
        compiler/instructions/compile_god_node.cpp
        compiler/instructions/compile_god_node.h
        compiler/instructions/compile_identifier_node.cpp
        compiler/instructions/compile_identifier_node.h
        compiler/instructions/compile_if_node.cpp
        compiler/instructions/compile_if_node.h
        compiler/instructions/compile_mockup_diia_node.cpp
        compiler/instructions/compile_mockup_diia_node.h
        compiler/instructions/compile_mockup_module_node.cpp
        compiler/instructions/compile_mockup_module_node.h
        compiler/instructions/compile_mockup_object_node.cpp
        compiler/instructions/compile_mockup_object_node.h
        compiler/instructions/compile_mockup_structure_node.cpp
        compiler/instructions/compile_mockup_structure_node.h
        compiler/instructions/compile_structure_params.cpp
        compiler/instructions/compile_structure_params.h
        compiler/instructions/compile_mockup_subject_node.cpp
        compiler/instructions/compile_mockup_subject_node.h
        compiler/instructions/compile_module_node.cpp
        compiler/instructions/compile_module_node.h
        compiler/instructions/compile_negative_node.cpp
        compiler/instructions/compile_negative_node.h
        compiler/instructions/compile_node.cpp
        compiler/instructions/compile_node.h
        compiler/instructions/compile_not_node.cpp
        compiler/instructions/compile_not_node.h
        compiler/instructions/compile_number_node.cpp
        compiler/instructions/compile_number_node.h
        compiler/instructions/compile_params.cpp
        compiler/instructions/compile_params.h
        compiler/instructions/compile_positive_node.cpp
        compiler/instructions/compile_positive_node.h
        compiler/instructions/compile_post_decrement_node.cpp
        compiler/instructions/compile_post_decrement_node.h
        compiler/instructions/compile_post_increment_node.cpp
        compiler/instructions/compile_post_increment_node.h
        compiler/instructions/compile_pre_decrement_node.cpp
        compiler/instructions/compile_pre_decrement_node.h
        compiler/instructions/compile_pre_increment_node.cpp
        compiler/instructions/compile_pre_increment_node.h
        compiler/instructions/compile_return_node.cpp
        compiler/instructions/compile_return_node.h
        compiler/instructions/compile_string_node.cpp
        compiler/instructions/compile_string_node.h
        compiler/instructions/compile_structure_node.cpp
        compiler/instructions/compile_structure_node.h
        compiler/instructions/compile_structure_params.cpp
        compiler/instructions/compile_structure_params.h
        compiler/instructions/compile_take_module_node.cpp
        compiler/instructions/compile_take_module_node.h
        compiler/instructions/compile_take_pak_node.cpp
        compiler/instructions/compile_take_pak_node.h
        compiler/instructions/compile_ternary_node.cpp
        compiler/instructions/compile_ternary_node.h
        compiler/instructions/compile_test_node.cpp
        compiler/instructions/compile_test_node.h
        compiler/instructions/compile_throw_node.cpp
        compiler/instructions/compile_throw_node.h
        compiler/instructions/compile_try_node.cpp
        compiler/instructions/compile_try_node.h
        compiler/instructions/compile_type_value_node.cpp
        compiler/instructions/compile_type_value_node.h
        compiler/instructions/compile_type_value_single_node.cpp
        compiler/instructions/compile_type_value_single_node.h
        compiler/instructions/compile_types.cpp
        compiler/instructions/compile_types.h
        compiler/instructions/compile_wait_node.cpp
        compiler/instructions/compile_wait_node.h
        compiler/instructions/compile_while_node.cpp
        compiler/instructions/compile_while_node.h
        compiler/compile.cpp
        compiler/compile.h
        parser.cpp
        parser.h
        tools.cpp
        tools.h
)

add_executable(jejalyk jejalyk_bin.cpp
        parser.cpp
        parser.h
        tools.cpp
        tools.h
        compiler/supercompiler/Object.cpp
        compiler/supercompiler/Param.cpp
        compiler/supercompiler/Scope.cpp
        compiler/supercompiler/Subject.cpp
        compiler/supercompiler/compiler.h
        compiler/supercompiler/Error.cpp
        compiler/supercompiler/compile.cpp
)
add_executable(jejalyk_node jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
add_executable(jejalyk_web jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
#add_executable(optimized_jejalyk jejalyk_bin.cpp ${JEJALYK_COMPILER_SRC})
add_executable(optimized_jejalyk_node jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})
add_executable(optimized_jejalyk_web jejalyk_wasm.cpp ${JEJALYK_COMPILER_SRC})

target_link_libraries(jejalyk mavka_syntax)
target_link_libraries(jejalyk_node mavka_syntax)
target_link_libraries(jejalyk_web mavka_syntax)
#target_link_libraries(optimized_jejalyk mavka_syntax)
target_link_libraries(optimized_jejalyk_node mavka_syntax)
target_link_libraries(optimized_jejalyk_web mavka_syntax)

target_compile_options(jejalyk PRIVATE -fexceptions)
target_compile_options(jejalyk_node PRIVATE -fexceptions)
target_compile_options(jejalyk_web PRIVATE -fexceptions)
#target_compile_options(optimized_jejalyk PRIVATE -fexceptions)
target_compile_options(optimized_jejalyk_node PRIVATE -fexceptions)
target_compile_options(optimized_jejalyk_web PRIVATE -fexceptions)

set_target_properties(jejalyk PROPERTIES OUTPUT_NAME "джеджалик")
set_target_properties(jejalyk_node PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(jejalyk_web PROPERTIES LINK_FLAGS "-lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(optimized_jejalyk_node PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=node -sEXPORT_ES6=1 -sMODULARIZE -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
set_target_properties(optimized_jejalyk_web PROPERTIES LINK_FLAGS "-O3 -flto -g0 -lembind -fexceptions -sASYNCIFY=1 -sENVIRONMENT=web -sEXPORT_EXCEPTION_HANDLING_HELPERS -sASYNCIFY_STACK_SIZE=65535")
