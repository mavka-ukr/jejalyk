#include "compile_identifier_node.h"

#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_identifier_node(
      const mavka::ast::IdentifierNode* identifier_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();
    if (!scope->has(identifier_node->name)) {
      node_compilation_result->error = new CompilationError();
      node_compilation_result->error->path = options->current_module_path;
      node_compilation_result->error->line = identifier_node->start_line;
      node_compilation_result->error->column = identifier_node->start_column;
      node_compilation_result->error->message =
          "Субʼєкт \"" + identifier_node->name + "\" не визначено.";
      return node_compilation_result;
    }
    node_compilation_result->subject = scope->get(identifier_node->name);
    node_compilation_result->result = varname(identifier_node->name);
    return node_compilation_result;
}
}
