#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_eval_node(Scope* scope, mavka::ast::EvalNode* eval_node) {
    if (!scope->get_options()->is_extensions_allowed()) {
      return scope->error(eval_node, "Розширення вимкнені.");
    }

    const auto js_raw_node = new jejalyk::js::JsRawNode();
    js_raw_node->code =
        "//[JS]\n" + tools::trim(eval_node->value) + "\n//[/JS]";

    return success(scope->create_object_instance_subject(), js_raw_node);
  }
} // namespace jejalyk::typeinterpreter