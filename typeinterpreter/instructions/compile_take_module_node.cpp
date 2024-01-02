#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_take_module_node(
      Scope* scope,
      mavka::ast::TakeModuleNode* take_module_node) {
    return scope->error(take_module_node,
                        "Вказівка \"взяти\" тимчасово недоступна.");
  }
} // namespace typeinterpreter