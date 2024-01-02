#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_take_pak_node(Scope* scope,
                                mavka::ast::TakePakNode* take_pak_node) {
    return scope->error(take_pak_node,
                        "Вказівка \"взяти пак\" тимчасово недоступна.");
  }
} // namespace typeinterpreter