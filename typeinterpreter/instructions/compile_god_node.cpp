#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_god_node(Scope* scope, mavka::ast::GodNode* god_node) {
    return scope->error(god_node, "Бог тимчасово недоступний.");
  }
} // namespace jejalyk::typeinterpreter