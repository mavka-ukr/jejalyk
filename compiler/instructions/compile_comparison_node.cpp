#include "compile_comparison_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_comparison_node(
    const mavka::ast::ComparisonNode* comparison_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName = state->put_debug(options->current_module_path,
                                       comparison_node->start_line,
                                       comparison_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto compiled_left =
      compile_node(comparison_node->left, scope, options, state);
  if (compiled_left->error) {
    node_compilation_result->error = compiled_left->error;
    return node_compilation_result;
  }
  const auto compiled_right =
      compile_node(comparison_node->right, scope, options, state);
  if (compiled_right->error) {
    node_compilation_result->error = compiled_right->error;
    return node_compilation_result;
  }
  if (comparison_node->op == "==" || comparison_node->op == "рівно") {
    node_compilation_result->result = MAVKA_EQ + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
    node_compilation_result->result =
        "!" + MAVKA_EQ + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (comparison_node->op == "<" || comparison_node->op == "менше") {
    node_compilation_result->result = MAVKA_LT + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == "<=" ||
             comparison_node->op == "не більше") {
    node_compilation_result->result = MAVKA_LE + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == ">" || comparison_node->op == "більше") {
    node_compilation_result->result = MAVKA_GT + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
    node_compilation_result->result = MAVKA_GE + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == "є") {
    node_compilation_result->result = MAVKA_IS + "(" + compiled_left->result +
                                      "," + compiled_right->result + "," +
                                      diName + ")";
  } else if (comparison_node->op == "не є") {
    node_compilation_result->result =
        "!" + MAVKA_IS + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (comparison_node->op == "містить") {
    node_compilation_result->result =
        MAVKA_CONTAINS + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else if (comparison_node->op == "не містить") {
    node_compilation_result->result =
        "!" + MAVKA_CONTAINS + "(" + compiled_left->result + "," +
        compiled_right->result + "," + diName + ")";
  } else {
    node_compilation_result->error = new CompilationError();
    node_compilation_result->error->path = options->current_module_path;
    node_compilation_result->error->line = comparison_node->start_line;
    node_compilation_result->error->column = comparison_node->start_column;
    node_compilation_result->error->message =
        "unsupported comparison operation: " + comparison_node->op;
  }
        return node_compilation_result;
    }
}
