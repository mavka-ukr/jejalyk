#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_take_pak_node(Scope* scope,
                                mavka::ast::TakePakNode* take_pak_node) {
    return error_from_ast(take_pak_node, "Взяття паку тимчасово недоступне.");
  }
} // namespace typeinterpreter