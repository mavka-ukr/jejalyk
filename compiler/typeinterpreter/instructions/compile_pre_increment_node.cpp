#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_pre_increment_node(
      Scope* scope,
      mavka::ast::PreIncrementNode* pre_increment_node) {
    return error_from_ast(pre_increment_node,
                          "Префіксний інкремент тимчасово недоступний.");
  }
} // namespace typeinterpreter