#include "compile_from_to_simple_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_from_to_simple_node(
    const mavka::ast::FromToSimpleNode* from_to_simple_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  const auto from =
      compile_node(from_to_simple_node->from, scope, options, state);
  if (from->error) {
    node_compilation_result->error = from->error;
    return node_compilation_result;
  }
  const auto to = compile_node(from_to_simple_node->to, scope, options, state);
  if (to->error) {
    node_compilation_result->error = to->error;
    return node_compilation_result;
  }
  node_compilation_result->result =
      MAVKA_FROM_TO + "(" + from->result + "," + to->result + ",\"" +
      from_to_simple_node->toSymbol + "\"," + MAVKA_FROM_TO_FN + "(\"+\",1))";
  return node_compilation_result;
}

}  // namespace jejalyk
