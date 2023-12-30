#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_anon_diia_node(Scope* scope,
                                 mavka::ast::AnonDiiaNode* anon_diia_node) {
    const auto diia_scope = scope->make_child();

    const auto diia_declaration_result = declare_diia(
        scope, diia_scope, anon_diia_node, anon_diia_node->async, "", {},
        anon_diia_node->params, anon_diia_node->return_types);
    if (diia_declaration_result->error) {
      return diia_declaration_result;
    }

    return complete_diia(scope, false, diia_scope, anon_diia_node,
                         diia_declaration_result->value, &anon_diia_node->body);
  }
} // namespace jejalyk::typeinterpreter