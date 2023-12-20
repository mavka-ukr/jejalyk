#include "compile_array_node.h"

#include "../../tools.h"
#include "compile_node.h"

namespace jejalyk {
  NodeCompilationResult* compile_array_node(
      const mavka::ast::ArrayNode* array_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();
    std::vector<std::string> compiled_elements;
    for (const auto& element : array_node->elements) {
      const auto element_compilation_result =
          compile_node(element, scope, options, state);
      if (element_compilation_result->error) {
        node_compilation_result->error = element_compilation_result->error;
        return node_compilation_result;
      }
      compiled_elements.push_back(element_compilation_result->result);
    }
    node_compilation_result->subject = create_list_instance_subject(scope);
    node_compilation_result->result =
        "[" + tools::implode(compiled_elements, ",") + "]";
    return node_compilation_result;
  }
}  // namespace jejalyk
