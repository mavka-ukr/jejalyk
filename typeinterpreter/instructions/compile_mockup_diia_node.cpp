#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mockup_diia_node(
      Scope* scope,
      mavka::ast::MockupDiiaNode* mockup_diia_node) {
    return compile_diia_or_mockup_diia_node(
        scope, mockup_diia_node, true, mockup_diia_node->ee,
        mockup_diia_node->async, mockup_diia_node->structure,
        mockup_diia_node->name, mockup_diia_node->generics,
        mockup_diia_node->params, mockup_diia_node->return_types, nullptr);
  }
} // namespace jejalyk::typeinterpreter