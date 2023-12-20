#include "compile_give_node.h"
#include "../../tools.h"
#include "../compile.h"

namespace jejalyk {
NodeCompilationResult* compile_give_node(const mavka::ast::GiveNode* give_node,
                                         CompilationScope* scope,
                                         CompilationOptions* options,
                                         CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, give_node->start_line,
                       give_node->start_column);

  const auto node_compilation_result = new NodeCompilationResult();
  const auto elements = new std::vector<std::string>();
  for (const auto& element : give_node->elements) {
    if (!element->as.empty()) {
      elements->push_back(MAVKA_GIVE + "(module,\"" + element->as + "\"," +
                          varname(element->name) + "," + diName + ")");
    } else {
      elements->push_back(MAVKA_GIVE + "(module,\"" + element->name + "\"," +
                          varname(element->name) + "," + diName + ")");
    }
  }
  node_compilation_result->result = tools::implode(*elements, ";\n");
  return node_compilation_result;
}
}  // namespace jejalyk
