#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
  NodeCompilationResult* compile_arg_node(const mavka::ast::ArgNode* arg_node,
                                          CompilationScope* scope,
                                          CompilationOptions* options,
                                          CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();
    if (arg_node->spread) {
      node_compilation_result->error = new CompilationError();
      node_compilation_result->error->path = options->current_module_path;
      node_compilation_result->error->line = arg_node->start_line;
      node_compilation_result->error->column = arg_node->start_column;
      node_compilation_result->error->message =
          "Оператор розгортання не підтримується в аргументах.";
      return node_compilation_result;
    }
    const auto value = compile_node(arg_node->value, scope, options, state);
    if (value->error) {
      node_compilation_result->error = value->error;
      return node_compilation_result;
    }
    if (arg_node->name.empty()) {
      const auto index = std::to_string(arg_node->index);
      node_compilation_result->subject = value->subject;
      node_compilation_result->result = index + ":" + value->result;
    } else {
      const auto name = arg_node->name;
      node_compilation_result->subject = value->subject;
      node_compilation_result->result = name + ":" + value->result;
    }
    return node_compilation_result;
  }
}
