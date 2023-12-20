#include "../compile.h"
#include "compile_body.h"
#include "compile_node.h"
#include "compile_wait_node.h"

namespace jejalyk {
NodeCompilationResult* compile_while_node(
    const mavka::ast::WhileNode* while_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  const auto condition =
      compile_node(while_node->condition, scope, options, state);
  if (condition->error) {
    node_compilation_result->error = condition->error;
    return node_compilation_result;
  }
  const auto while_scope = new CompilationMicroScope();
  while_scope->parent = scope;
  const auto body =
      compile_body(while_node->body, while_scope, options, state, true);
  if (body->error) {
    node_compilation_result->error = body->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      "while(" + condition->result + ")" + body->result + "";
  return node_compilation_result;
}
}  // namespace jejalyk
