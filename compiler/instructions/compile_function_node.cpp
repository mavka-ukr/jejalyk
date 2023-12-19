#include "compile_function_node.h"

#include "compile_diia_body.h"
#include "compile_params.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_function_node(const mavka::ast::FunctionNode* function_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, function_node->start_line,
                                             function_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto function_scope = new CompilationScope();
        function_scope->parent = scope;
        const auto params_compilation_result = compile_params(function_node->params, function_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_diia_body(function_node->body, function_node->params, function_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_DIIA + "(null," +
                                          compiled_params + "," + (function_node->async ? "async " : "") +
                                          "function(args)" + body->result + "," + diName + ")";
        return node_compilation_result;
    }
}
