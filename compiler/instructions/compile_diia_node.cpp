#include "compile_diia_node.h"

#include "../compile.h"
#include "compile_diia_body.h"
#include "compile_params.h"
#include "compile_types.h"

namespace jejalyk {
  NodeCompilationResult* compile_diia_node(
      const mavka::ast::DiiaNode* diia_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();

    const auto diia_scope = new CompilationScope();
    diia_scope->parent = scope;

    const auto params_compilation_result =
        compile_params(diia_node->params, diia_scope, options, state);
    if (params_compilation_result->error) {
      node_compilation_result->error = params_compilation_result->error;
      return node_compilation_result;
    }
    const auto compiled_params = params_compilation_result->result;

    const auto compiled_return_type =
        compile_types(diia_node->return_types, diia_scope, options, state);
    if (compiled_return_type->error) {
      node_compilation_result->error = compiled_return_type->error;
      return node_compilation_result;
    }

    if (diia_node->structure.empty()) {
      const auto compilation_subject = create_diia_instance_subject(
          diia_node->name, params_compilation_result->diia_params,
          compiled_return_type->subject, scope);
      if (const auto define_error =
              scope->define(diia_node->name, compilation_subject)) {
        node_compilation_result->error = define_error;
        return node_compilation_result;
      }

      const auto body = compile_diia_body(diia_node->body, diia_node->params,
                                          diia_scope, options, state, true);
      if (body->error) {
        node_compilation_result->error = body->error;
        return node_compilation_result;
      }
      node_compilation_result->result =
          varname(diia_node->name) + "=" + MAVKA_DIIA + "(" + "\"" +
          diia_node->name + "\"" + "," + compiled_params + "," +
          (diia_node->async ? "async " : "") + "function(args)" + body->result +
          ")";
    } else {
      const auto structure_subject = scope->get(diia_node->structure);
      diia_scope->define("я", structure_subject);
      diia_scope->define("предок", nullptr);
      const auto body =
          compile_diia_body(diia_node->body, diia_node->params, diia_scope,
                            options, state, true, true);
      if (body->error) {
        node_compilation_result->error = body->error;
        return node_compilation_result;
      }
      node_compilation_result->result =
          MAVKA_SET_METHOD + "(" + varname(diia_node->structure) + "," +
          MAVKA_METHOD + "(\"" + diia_node->name + "\"," + compiled_params +
          ",function(м_я,args)" + body->result + "))";
    }
    return node_compilation_result;
}

}
