#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_call_node(Scope* scope, mavka::ast::CallNode* call_node) {
    const auto value_result = scope->compile_node(call_node->value);
    if (value_result->error) {
      return value_result;
    }

    std::vector<Subject*> generic_types;
    for (const auto& generic_type_nodes : call_node->generics) {
      Subject* generic_subject = nullptr;
      for (const auto type_value_single_node : generic_type_nodes) {
        const auto type_value_single_result =
            scope->compile_node(type_value_single_node);
        if (type_value_single_result->error) {
          return type_value_single_result;
        }
        generic_subject = type_value_single_result->value;
      }
      generic_types.push_back(generic_subject);
    }

    std::vector<Subject*> args;
    std::vector<jejalyk::js::JsNode*> js_args;
    for (const auto arg_node : call_node->args) {
      const auto arg_result = scope->compile_node(arg_node->value);
      if (arg_result->error) {
        return arg_result;
      }
      args.push_back(arg_result->value);
      js_args.push_back(arg_result->js_node);
    }

    const auto result =
        value_result->value->call(scope, call_node, generic_types, args);

    if (value_result->value->is_diia(scope)) {
      // а(б)
      result->js_node = js::make_call(value_result->js_node, js_args);
    } else {
      // а.чародія_викликати(б)
      const auto js_chain = js::make_chain(value_result->js_node,
                                           js::make_id("чародія_викликати"));

      result->js_node = js::make_call(js_chain, js_args);
    }

    return result;
  }
} // namespace jejalyk::typeinterpreter