#include "compile_node.h"
#include "compile_type_value_node.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_type_value_single_node(
        mavka::ast::TypeValueSingleNode* type_value_single_node,
        CompilationScope* scope,
        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(type_value_single_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = value->result;
        return node_compilation_result;
    }
}
