#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_pre_decrement_node(
      Scope* scope,
      mavka::ast::PreDecrementNode* pre_decrement_node) {
    return scope->error(pre_decrement_node,
                        "Префіксний декремент тимчасово недоступний.");
  }
} // namespace typeinterpreter