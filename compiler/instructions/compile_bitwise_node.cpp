#include "compile_bitwise_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_bitwise_node(
    const mavka::ast::BitwiseNode* bitwise_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, bitwise_node->start_line,
                       bitwise_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto compiled_left =
      compile_node(bitwise_node->left, scope, options, state);
  if (compiled_left->error) {
    node_compilation_result->error = compiled_left->error;
    return node_compilation_result;
  }
  const auto compiled_right =
      compile_node(bitwise_node->right, scope, options, state);
  if (compiled_right->error) {
    node_compilation_result->error = compiled_right->error;
    return node_compilation_result;
  }
  if (bitwise_node->op == "&") {
    node_compilation_result->result =
        MAVKA_BIT_AND + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (bitwise_node->op == "|") {
    node_compilation_result->result =
        MAVKA_BIT_OR + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (bitwise_node->op == "^") {
    node_compilation_result->result =
        MAVKA_BIT_XOR + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (bitwise_node->op == "<<") {
    node_compilation_result->result =
        MAVKA_BIT_LSHIFT + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (bitwise_node->op == ">>") {
    node_compilation_result->result =
        MAVKA_BIT_RSHIFT + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else {
    node_compilation_result->error = new CompilationError();
    node_compilation_result->error->path = options->current_module_path;
    node_compilation_result->error->line = bitwise_node->start_line;
    node_compilation_result->error->column = bitwise_node->start_column;
    node_compilation_result->error->message =
        "unsupported bitwise operation: " + bitwise_node->op;
  }
  return node_compilation_result;
}
}  // namespace jejalyk
