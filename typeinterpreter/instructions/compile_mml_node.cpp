#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mml_node(Scope* scope, mavka::ast::MMLNode* mml_node) {
    return error_from_ast(mml_node, "МРМ тимчасово недоступна.");
  }
} // namespace typeinterpreter