#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_post_increment_node(
      Scope* scope,
      mavka::ast::PostIncrementNode* post_increment_node) {
    return error_from_ast(post_increment_node,
                          "Постфіксний інкремент тимчасово недоступний.");
  }
} // namespace typeinterpreter