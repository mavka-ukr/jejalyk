#include "compile_negative_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_negative_node(
    const mavka::ast::NegativeNode* negative_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, negative_node->start_line,
                       negative_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value = compile_node(negative_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      MAVKA_NEGATIVE + "(" + value->result + "," + diName + ")";
  return node_compilation_result;
}
}  // namespace jejalyk
