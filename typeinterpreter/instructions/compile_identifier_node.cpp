#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_identifier_node(Scope* scope,
                                  mavka::ast::IdentifierNode* identifier_node) {
    if (!scope->has(identifier_node->name)) {
      return error_from_ast(
          identifier_node,
          "Субʼєкт \"" + identifier_node->name + "\" не визначено.");
    }

    const auto subject = scope->get(identifier_node->name);
    debug_print_got_from_scope(scope, identifier_node->name, subject);
    return success(subject, js::make_id(identifier_node->name));
  }
} // namespace jejalyk::typeinterpreter