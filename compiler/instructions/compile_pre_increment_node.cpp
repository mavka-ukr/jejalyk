#include "compile_pre_increment_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_pre_increment_node(
    const mavka::ast::PreIncrementNode* pre_increment_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName = state->put_debug(options->current_module_path,
                                       pre_increment_node->start_line,
                                       pre_increment_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value =
      compile_node(pre_increment_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  node_compilation_result->result = MAVKA_PRE_INCREMENT + "(" + value->result +
                                    ",(v)=>{" + value->result + "=v;}," +
                                    diName + ")";
  return node_compilation_result;
}
}  // namespace jejalyk
