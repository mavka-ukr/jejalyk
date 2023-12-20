#include "compile_wait_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_wait_node(const mavka::ast::WaitNode* wait_node,
                                         CompilationScope* scope,
                                         CompilationOptions* options,
                                         CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value = compile_node(wait_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  node_compilation_result->result = "await " + value->result;
  return node_compilation_result;
}
}  // namespace jejalyk
