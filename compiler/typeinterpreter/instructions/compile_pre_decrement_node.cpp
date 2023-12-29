#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_pre_decrement_node(
      Scope* scope,
      mavka::ast::PreDecrementNode* pre_decrement_node) {
    return error_from_ast(pre_decrement_node,
                          "Префіксний декремент тимчасово недоступний.");
  }
} // namespace typeinterpreter