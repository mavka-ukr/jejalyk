#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_mockup_structure_node(
      Scope* scope,
      mavka::ast::MockupStructureNode* mockup_structure_node) {
    if (!scope->has_local(mockup_structure_node->name)) {
      return error_from_ast(mockup_structure_node,
                            "[INTERNAL BUG] Структура \"" +
                                mockup_structure_node->name +
                                "\" не визначена.");
    }

    const auto structure_subject =
        scope->get_local(mockup_structure_node->name);

    return scope->complete_structure(
        true, mockup_structure_node, structure_subject,
        mockup_structure_node->params, mockup_structure_node->methods);
  }
} // namespace typeinterpreter