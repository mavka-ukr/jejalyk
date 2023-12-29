#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_eval_node(Scope* scope, mavka::ast::EvalNode* eval_node) {
    return error_from_ast(eval_node, "Не реалізовано.");
  }
} // namespace typeinterpreter