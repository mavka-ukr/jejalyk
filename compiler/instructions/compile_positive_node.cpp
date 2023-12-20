#include "compile_positive_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {

NodeCompilationResult* compile_positive_node(
    const mavka::ast::PositiveNode* positive_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, positive_node->start_line,
                       positive_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value = compile_node(positive_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      MAVKA_POSITIVE + "(" + value->result + "," + diName + ")";
  return node_compilation_result;
}
}  // namespace jejalyk