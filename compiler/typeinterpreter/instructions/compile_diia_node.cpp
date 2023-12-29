#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_diia_node(Scope* scope, mavka::ast::DiiaNode* diia_node) {
    const auto diia_scope = scope->make_child();
    const auto diia_compilation_result = scope->compile_diia(
        diia_scope, diia_node->async, diia_node->name, diia_node->generics,
        diia_node->params, diia_node->return_types, &diia_node->body);
    if (diia_compilation_result->error) {
      return diia_compilation_result;
    }
    // todo: handle structure
    scope->set_local(diia_node->name, diia_compilation_result->value);
    return diia_compilation_result;
  }
} // namespace typeinterpreter