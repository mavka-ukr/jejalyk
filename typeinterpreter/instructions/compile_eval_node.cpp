#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_eval_node(Scope* scope, mavka::ast::EvalNode* eval_node) {
    if (!scope->get_options()->allow_js) {
      return error_from_ast(eval_node, scope, "Розширення вимкнені.");
    }

    const auto js_raw_node = new jejalyk::js::JsRawNode();
    js_raw_node->code = tools::trim(eval_node->value);

    return success(scope->create_object_instance_subject(), js_raw_node);
  }
} // namespace jejalyk::typeinterpreter