#include "compile_ternary_node.h"

#include "../compile.h"
#include "compile_body.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_ternary_node(
    const mavka::ast::TernaryNode* ternary_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  const auto condition =
      compile_node(ternary_node->condition, scope, options, state);
  if (condition->error) {
    node_compilation_result->error = condition->error;
    return node_compilation_result;
  }
  const auto true_value =
      compile_body(ternary_node->body, scope, options, state, false);
  if (true_value->error) {
    node_compilation_result->error = true_value->error;
    return node_compilation_result;
  }
  const auto else_body =
      compile_body(ternary_node->else_body, scope, options, state, false);
  if (else_body->error) {
    node_compilation_result->error = else_body->error;
    return node_compilation_result;
  }
  node_compilation_result->result = "(" + condition->result + ")?" +
                                    true_value->result + ":" +
                                    else_body->result;
  return node_compilation_result;
}
}  // namespace jejalyk
