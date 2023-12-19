#include "compile_anon_diia_node.h"
#include "compile_params.h"
#include "compile_diia_body.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_anon_diia_node(const mavka::ast::AnonDiiaNode* anon_diia_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, anon_diia_node->start_line,
                                             anon_diia_node->start_column);

        const auto node_compilation_result = new NodeCompilationResult();
        const auto anon_diia_scope = new CompilationScope();
        anon_diia_scope->parent = scope;
        const auto params_compilation_result = compile_params(anon_diia_node->params, anon_diia_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_diia_body(anon_diia_node->body, anon_diia_node->params, anon_diia_scope, options,
                                            true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_DIIA + "(null," +
                                          compiled_params + "," + (anon_diia_node->async ? "async " : "") +
                                          "function(args)" + body->result + "," + diName + ")";
        return node_compilation_result;
    }
}
