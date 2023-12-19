#include "compile_not_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_not_node(const mavka::ast::NotNode* not_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, not_node->start_line,
                                             not_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(not_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_NOT + "(" + value->result + "," + diName + ")";
        return node_compilation_result;
    }
}
