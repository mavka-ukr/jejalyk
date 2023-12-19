#include "compile_get_element_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_get_element_node(const mavka::ast::GetElementNode* get_element_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, get_element_node->start_line,
                                             get_element_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(get_element_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        const auto index = compile_node(get_element_node->index, scope, options);
        if (index->error) {
            node_compilation_result->error = index->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_GET_ELEMENT + "(" + value->result + "," + index->result + "," + diName +
                                          ")";
        return node_compilation_result;
    }
}
