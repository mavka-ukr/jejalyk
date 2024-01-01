#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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
    scope->put_ignore_variable(mockup_structure_node->name);

    return complete_structure(scope, true, mockup_structure_node,
                              structure_subject, mockup_structure_node->params);
  }
} // namespace jejalyk::typeinterpreter