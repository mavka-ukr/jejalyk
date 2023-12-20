#include "compile_bitwise_not_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_bitwise_not_node(
    const mavka::ast::BitwiseNotNode* bitwise_not_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName = state->put_debug(options->current_module_path,
                                       bitwise_not_node->start_line,
                                       bitwise_not_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto compiled_value =
      compile_node(bitwise_not_node->value, scope, options, state);
  if (compiled_value->error) {
    node_compilation_result->error = compiled_value->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      MAVKA_BIT_NOT + "(" + compiled_value->result + "," + diName + ")";
  return node_compilation_result;
}
}  // namespace jejalyk
