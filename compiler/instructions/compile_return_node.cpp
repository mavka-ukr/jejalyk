#include "compile_return_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_return_node(const mavka::ast::ReturnNode* return_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(return_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "return " + value->result;
        return node_compilation_result;
    }
}
