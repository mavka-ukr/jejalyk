#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_method_declaration_node(
      Scope* scope,
      mavka::ast::MethodDeclarationNode* method_declaration_node) {
    const auto diia_scope = scope->make_child();

    return scope->compile_diia(diia_scope, method_declaration_node->async,
                               method_declaration_node->name,
                               method_declaration_node->generics,
                               method_declaration_node->params,
                               method_declaration_node->return_types, nullptr);
  }
} // namespace typeinterpreter