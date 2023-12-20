#include "compile_arithmetic_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
  NodeCompilationResult* compile_arithmetic_node(
      const mavka::ast::ArithmeticNode* arithmetic_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto diName = state->put_debug(options->current_module_path,
                                         arithmetic_node->start_line,
                                         arithmetic_node->start_column);

    const auto node_compilation_result = new NodeCompilationResult();

    const auto compiled_left =
        compile_node(arithmetic_node->left, scope, options, state);
    if (compiled_left->error) {
      node_compilation_result->error = compiled_left->error;
      return node_compilation_result;
    }
    const auto compiled_right =
        compile_node(arithmetic_node->right, scope, options, state);
    if (compiled_right->error) {
      node_compilation_result->error = compiled_right->error;
      return node_compilation_result;
    }
    if (arithmetic_node->op == "+") {
      node_compilation_result->result =
          MAVKA_ADD + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "-") {
      node_compilation_result->result =
          MAVKA_SUB + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "*") {
      node_compilation_result->result =
          MAVKA_MUL + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "/") {
      node_compilation_result->result =
          MAVKA_DIV + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "%") {
      node_compilation_result->result =
          MAVKA_MOD + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "//") {
      node_compilation_result->result =
          MAVKA_DIV_DIV + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else if (arithmetic_node->op == "**") {
      node_compilation_result->result =
          MAVKA_POW + "(" + compiled_left->result + "," +
          compiled_right->result + "," + diName + ")";
    } else {
      node_compilation_result->error = new CompilationError();
      node_compilation_result->error->path = options->current_module_path;
      node_compilation_result->error->line = arithmetic_node->start_line;
      node_compilation_result->error->column = arithmetic_node->start_column;
      node_compilation_result->error->message =
          "unsupported arithmetic operation: " + arithmetic_node->op;
    }
    node_compilation_result->subject = new CompilationSubject();
    return node_compilation_result;
  }
}  // namespace jejalyk
