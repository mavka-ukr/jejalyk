#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_anon_diia_node(Scope* scope,
                                 mavka::ast::AnonDiiaNode* anon_diia_node) {
    const auto diia_scope = scope->make_child();

    return scope->compile_diia(diia_scope, anon_diia_node->async, "",
                               anon_diia_node->generics, anon_diia_node->params,
                               anon_diia_node->return_types,
                               &anon_diia_node->body);
  }
} // namespace typeinterpreter