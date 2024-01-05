#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_take_pak_node(Scope* scope,
                                mavka::ast::TakePakNode* take_pak_node) {
    const auto get_pak_result = scope->get_options()->get_pak(
        take_pak_node->name, take_pak_node->version, take_pak_node->as,
        scope->get_options());
    if (!get_pak_result->error.empty()) {
      return scope->error(take_pak_node, get_pak_result->error);
    }
    return success(nullptr, new js::JsEmptyNode());
  }
} // namespace jejalyk::typeinterpreter