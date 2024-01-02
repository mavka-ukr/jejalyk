#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_pre_increment_node(
      Scope* scope,
      mavka::ast::PreIncrementNode* pre_increment_node) {
    return scope->error(pre_increment_node,
                          "Префіксний інкремент тимчасово недоступний.");
  }
} // namespace typeinterpreter