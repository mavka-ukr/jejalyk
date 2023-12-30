#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_take_module_node(
      Scope* scope,
      mavka::ast::TakeModuleNode* take_module_node) {
    return error_from_ast(take_module_node,
                          "Взяття модуля тимчасово недоступне.");
  }
} // namespace typeinterpreter