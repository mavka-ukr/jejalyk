#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_mockup_structure_node(
      Scope* scope,
      mavka::ast::MockupStructureNode* mockup_structure_node) {
    const auto structure_compilation_result = scope->compile_structure(
        mockup_structure_node->name, mockup_structure_node->generics, "", {},
        mockup_structure_node->params, mockup_structure_node->methods);
    if (structure_compilation_result->error) {
      return structure_compilation_result;
    }
    scope->set_local(mockup_structure_node->name,
                     structure_compilation_result->value);
    return success(structure_compilation_result->value,
                   new jejalyk::js::JsEmptyNode());
  }
} // namespace typeinterpreter