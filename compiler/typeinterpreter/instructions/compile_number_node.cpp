#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_number_node(Scope* scope,
                              mavka::ast::NumberNode* number_node) {
    const auto number_structure = scope->get_root()->get("число");
    const auto number_result = number_structure->create_instance(scope, {});
    const auto js_number_node = new jejalyk::js::JsNumberNode();
    js_number_node->value = number_node->value;
    return success(number_result->value, js_number_node);
  }
} // namespace typeinterpreter