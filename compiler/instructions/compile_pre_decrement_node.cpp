#include "compile_pre_decrement_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_pre_decrement_node(const mavka::ast::PreDecrementNode* pre_decrement_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, pre_decrement_node->start_line,
                                             pre_decrement_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(pre_decrement_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_PRE_DECREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }
}
