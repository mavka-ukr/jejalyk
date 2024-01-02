#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_method_declaration_node(
      Scope* scope,
      mavka::ast::MethodDeclarationNode* method_declaration_node) {
    return scope->error(method_declaration_node,
                        "Методи тимчасово недоступні.");
  }
} // namespace jejalyk::typeinterpreter