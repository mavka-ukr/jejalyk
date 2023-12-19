#include "compile_number_node.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_number_node(const mavka::ast::NumberNode* number_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = number_node->value;
        return node_compilation_result;
    }
}
