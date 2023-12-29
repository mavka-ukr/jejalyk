#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_anon_diia_node(Scope* scope,
                                 mavka::ast::AnonDiiaNode* anon_diia_node) {
    const auto diia_scope = scope->make_child();

    const auto diia_declaration_result = scope->declare_diia(
        diia_scope, anon_diia_node, anon_diia_node->async, "", {},
        anon_diia_node->params, anon_diia_node->return_types);
    if (diia_declaration_result->error) {
      return diia_declaration_result;
    }

    return scope->complete_diia(false, diia_scope, anon_diia_node,
                                diia_declaration_result->value,
                                &anon_diia_node->body);
  }
} // namespace typeinterpreter