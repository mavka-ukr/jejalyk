#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_god_node(Scope* scope, mavka::ast::GodNode* god_node) {
    return error_from_ast(god_node, "Бог тимчасово недоступний.");
  }
} // namespace typeinterpreter