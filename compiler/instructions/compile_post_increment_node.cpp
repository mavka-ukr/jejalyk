#include "compile_post_increment_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_post_increment_node(const mavka::ast::PostIncrementNode* post_increment_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, post_increment_node->start_line,
                                             post_increment_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(post_increment_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POST_INCREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }
}
