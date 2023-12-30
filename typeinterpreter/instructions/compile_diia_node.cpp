#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_diia_node(Scope* scope, mavka::ast::DiiaNode* diia_node) {
    return compile_diia_or_mockup_diia_node(
        scope, diia_node, false, diia_node->ee, diia_node->async,
        diia_node->structure, diia_node->name, diia_node->generics,
        diia_node->params, diia_node->return_types, &diia_node->body);
  }
} // namespace jejalyk::typeinterpreter