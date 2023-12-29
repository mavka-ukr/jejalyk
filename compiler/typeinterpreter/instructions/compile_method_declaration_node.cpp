#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_method_declaration_node(
      Scope* scope,
      mavka::ast::MethodDeclarationNode* method_declaration_node) {
    const auto diia_scope = scope->make_child();

    const auto diia_declaration_result = scope->declare_diia(
        diia_scope, method_declaration_node, method_declaration_node->async,
        method_declaration_node->name, method_declaration_node->generics,
        method_declaration_node->params, method_declaration_node->return_types);
    if (diia_declaration_result->error) {
      return diia_declaration_result;
    }

    return scope->complete_diia(true, diia_scope, method_declaration_node,
                                diia_declaration_result->value, nullptr);
  }
} // namespace typeinterpreter