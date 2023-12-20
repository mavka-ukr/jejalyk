#include "compile_module_node.h"

#include "../compile.h"
#include "compile_body.h"

namespace jejalyk {

NodeCompilationResult* compile_module_node(
    const mavka::ast::ModuleNode* module_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, module_node->start_line,
                       module_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto module_scope = new CompilationScope();
  module_scope->parent = scope;
  scope->assign(module_node->name, nullptr);
  const auto body =
      compile_body(module_node->body, module_scope, options, state, true);
  if (body->error) {
    node_compilation_result->error = body->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      varname(module_node->name) + "=await " + MAVKA_MODULE + "(" + "\"" +
      module_node->name + "\"" + ",async function(module)" + body->result +
      "," + diName + ")";
  return node_compilation_result;
}
}  // namespace jejalyk
