#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mml_node(Scope* scope, mavka::ast::MMLNode* mml_node) {
    return scope->error(mml_node, "МРМ тимчасово недоступна.");
  }
} // namespace jejalyk::typeinterpreter