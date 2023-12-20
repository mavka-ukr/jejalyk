#include "compile_break_node.h"
#include "../compile.h"

namespace jejalyk {
NodeCompilationResult* compile_break_node(
    const mavka::ast::BreakNode* break_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  // todo: handle only loops
  node_compilation_result->result = "break";
  return node_compilation_result;
}
}  // namespace jejalyk
