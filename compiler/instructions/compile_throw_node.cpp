#include "compile_throw_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_throw_node(
    const mavka::ast::ThrowNode* throw_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, throw_node->start_line,
                       throw_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value = compile_node(throw_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      "throw new Падіння(" + value->result + "," + diName + ")";
  return node_compilation_result;
}
}
