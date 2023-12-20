#include "compile_as_node.h"

#include "../compile.h"

namespace jejalyk {
NodeCompilationResult* compile_as_node(const mavka::ast::AsNode* as_node,
                                       CompilationScope* scope,
                                       CompilationOptions* options,
                                       CompilationState* state) {
  // const auto diName = scope->put_debug(options->current_module_path,
  // as_node->start_line,
  //                                      as_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  node_compilation_result->error = new CompilationError();
  node_compilation_result->error->path = options->current_module_path;
  node_compilation_result->error->line = as_node->start_line;
  node_compilation_result->error->column = as_node->start_column;
  node_compilation_result->error->message =
      "Вказівка \"як\" тимчасово не працює.";
  return node_compilation_result;
  // const auto left = compile_node(as_node->left, scope, options);
  // if (left->error) {
  //     node_compilation_result->error = left->error;
  //     return node_compilation_result;
  // }
  // const auto right = compile_node(as_node->right, scope, options);
  // if (right->error) {
  //     node_compilation_result->error = right->error;
  //     return node_compilation_result;
  // }
  // node_compilation_result->result = MAVKA_AS + "(" + left->result + "," +
  // right->result + "," + diName + ")"; return node_compilation_result;
    }
}
