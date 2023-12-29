#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_function_node(Scope* scope,
                                mavka::ast::FunctionNode* function_node) {
    const auto diia_scope = scope->make_child();

    return scope->compile_diia(
        diia_scope, function_node->async, "", {}, function_node->params,
        function_node->return_types, &function_node->body);
  }
} // namespace typeinterpreter