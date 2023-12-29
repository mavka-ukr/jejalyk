#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_function_node(Scope* scope,
                                mavka::ast::FunctionNode* function_node) {
    const auto diia_scope = scope->make_child();

    const auto diia_declaration_result = scope->declare_diia(
        diia_scope, function_node, function_node->async, "", {},
        function_node->params, function_node->return_types);
    if (diia_declaration_result->error) {
      return diia_declaration_result;
    }

    return scope->complete_diia(false, diia_scope, function_node,
                                diia_declaration_result->value,
                                &function_node->body);
  }
} // namespace typeinterpreter