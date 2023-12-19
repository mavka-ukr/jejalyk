#include "compile_diia_node.h"

#include "compile_diia_body.h"
#include "compile_params.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_diia_node(const mavka::ast::DiiaNode* diia_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, diia_node->start_line,
                                             diia_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        scope->assign(diia_node->name);
        const auto diia_scope = new CompilationScope();
        diia_scope->parent = scope;
        const auto params_compilation_result = compile_params(diia_node->params, diia_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        if (diia_node->structure.empty()) {
            const auto body = compile_diia_body(diia_node->body, diia_node->params, diia_scope, options, true);
            if (body->error) {
                node_compilation_result->error = body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(diia_node->name) + "=" +
                                              MAVKA_DIIA + "(" + "\"" + diia_node->name
                                              + "\"" + "," +
                                              compiled_params + "," + (diia_node->async ? "async " : "") +
                                              "function(args)" + body->result + "," + diName + ")";
        } else {
            diia_scope->assign("я");
            diia_scope->assign("предок");
            const auto body = compile_diia_body(diia_node->body, diia_node->params, diia_scope, options, true, true);
            if (body->error) {
                node_compilation_result->error = body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_SET_METHOD + "(" + varname(diia_node->structure) + "," +
                                              MAVKA_METHOD + "(\"" + diia_node->name + "\"," +
                                              compiled_params + ",function(м_я,args)" + body->result + ")," + diName +
                                              ")";
        }
        return node_compilation_result;
    }

}
