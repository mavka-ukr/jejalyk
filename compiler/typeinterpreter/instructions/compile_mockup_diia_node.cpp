#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_mockup_diia_node(
      Scope* scope,
      mavka::ast::MockupDiiaNode* mockup_diia_node) {
    if (!mockup_diia_node->structure.empty()) {
      return error_from_ast(mockup_diia_node, "Методи тимчасово недоступні.");
    }
    if (!scope->has_local(mockup_diia_node->name)) {
      return error_from_ast(mockup_diia_node, "[INTERNAL BUG] Дія \"" +
                                                  mockup_diia_node->name +
                                                  "\" не визначена.");
    }

    const auto diia_subject = scope->get_local(mockup_diia_node->name);

    const auto diia_scope = scope->make_child();

    return complete_diia(scope, true, diia_scope, mockup_diia_node,
                         diia_subject, nullptr);
  }
} // namespace typeinterpreter