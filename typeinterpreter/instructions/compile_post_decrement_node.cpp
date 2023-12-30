#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_post_decrement_node(
      Scope* scope,
      mavka::ast::PostDecrementNode* post_decrement_node) {
    return error_from_ast(post_decrement_node,
                          "Постфіксний декремент тимчасово недоступний.");
  }
} // namespace typeinterpreter