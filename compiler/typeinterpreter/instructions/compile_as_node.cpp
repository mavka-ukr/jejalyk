#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_as_node(Scope* scope, mavka::ast::AsNode* as_node) {
    return error_from_ast(as_node, "Вказівка \"як\" тимчасово недоступна.");
  }
} // namespace typeinterpreter