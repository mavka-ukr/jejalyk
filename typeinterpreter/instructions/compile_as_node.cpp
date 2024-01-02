#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_as_node(Scope* scope, mavka::ast::AsNode* as_node) {
    return scope->error(as_node, "Вказівка \"як\" тимчасово недоступна.");
  }
} // namespace typeinterpreter