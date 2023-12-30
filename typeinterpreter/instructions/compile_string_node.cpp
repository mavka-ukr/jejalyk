#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_string_node(Scope* scope,
                              mavka::ast::StringNode* string_node) {
    // todo: interpolate
    const auto string_structure = scope->get_root_text();
    const auto string_result = string_structure->create_instance(scope, {});
    const auto js_string_node = new jejalyk::js::JsStringNode();
    js_string_node->value = string_node->value;
    return success(string_result->value, js_string_node);
  }
} // namespace typeinterpreter