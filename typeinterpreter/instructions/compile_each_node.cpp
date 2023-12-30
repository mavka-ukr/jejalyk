#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_each_node(Scope* scope, mavka::ast::EachNode* each_node) {
    const auto value_result = scope->compile_node(each_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto loop_scope = scope->make_proxy();
    loop_scope->is_loop = true;

    loop_scope->increment_iterator_count();
    const auto iterator_count = loop_scope->get_iterator_count();
    const auto iterator_name = "_мit_" + std::to_string(iterator_count);

    if (each_node->keyName.empty()) {
      if (scope->has_local(each_node->name)) {
        return error_1(each_node, each_node->name);
      }
      if (value_result->value->is_iterator(scope)) {
        const auto iterator_type_result =
            value_result->value->get_iterator_type(scope, each_node->value);
        if (iterator_type_result->error) {
          return iterator_type_result;
        }
        scope->set_local(each_node->name, iterator_type_result->value);
        scope->put_additional_node_before(jejalyk::js::var(iterator_name));

        const auto compiled_body = loop_scope->compile_body(each_node->body);
        if (compiled_body->error) {
          return compiled_body;
        }

        const auto js_for_node = new jejalyk::js::JsForNode();
        const auto js_initial_assign = new jejalyk::js::JsAssignNode();
        js_initial_assign->identifier = jejalyk::js::id(iterator_name);
        js_initial_assign->value = value_result->js_node;
        js_for_node->init = js_initial_assign;

        const auto js_condition_chain = new jejalyk::js::JsChainNode();
        js_condition_chain->left = jejalyk::js::id(iterator_name);
        js_condition_chain->right = jejalyk::js::id("завершено");
        const auto js_condition_not_node = new jejalyk::js::JsNotNode();
        js_condition_not_node->value = js_condition_chain;
        js_for_node->condition = js_condition_not_node;

        const auto js_next_chain = new jejalyk::js::JsChainNode();
        js_next_chain->left = jejalyk::js::id(iterator_name);
        js_next_chain->right = jejalyk::js::id("далі");
        const auto js_next_call_node = new jejalyk::js::JsCallNode();
        js_next_call_node->value = js_next_chain;
        js_for_node->update = js_next_call_node;

        js_for_node->body = compiled_body->js_body;
        const auto js_name_assign_node = new jejalyk::js::JsAssignNode();
        js_name_assign_node->identifier = jejalyk::js::id(each_node->name);
        const auto js_name_assign_node_chain = new jejalyk::js::JsChainNode();
        js_name_assign_node_chain->left = jejalyk::js::id(iterator_name);
        js_name_assign_node_chain->right = jejalyk::js::id("значення");
        js_name_assign_node->value = js_name_assign_node_chain;
        js_for_node->body->nodes.insert(js_for_node->body->nodes.begin(),
                                        js_name_assign_node);
        js_for_node->cleanup = new jejalyk::js::JsBody();
        const auto js_cleanup_iterator_assign = new jejalyk::js::JsAssignNode();
        js_cleanup_iterator_assign->identifier = jejalyk::js::id(iterator_name);
        js_cleanup_iterator_assign->value = jejalyk::js::id("undefined");
        js_for_node->cleanup->nodes.push_back(js_cleanup_iterator_assign);

        return success(nullptr, js_for_node);
      } else if (value_result->value->has("чародія_перебір")) {
        const auto iterator_diia_type_result =
            value_result->value->get("чародія_перебір");
        if (iterator_diia_type_result->error) {
          return iterator_diia_type_result;
        }
        const auto iterator_diia_return_types =
            iterator_diia_type_result->value->call(scope, each_node->value, {},
                                                   {});
        if (iterator_diia_return_types->value->is_iterator(scope)) {
          const auto iterator_type_result =
              iterator_diia_return_types->value->get_iterator_type(
                  scope, each_node->value);
          if (iterator_type_result->error) {
            return iterator_type_result;
          }
          scope->set_local(each_node->name, iterator_type_result->value);
          scope->put_additional_node_before(jejalyk::js::var(iterator_name));

          const auto compiled_body = loop_scope->compile_body(each_node->body);
          if (compiled_body->error) {
            return compiled_body;
          }

          const auto js_for_node = new jejalyk::js::JsForNode();
          const auto js_initial_assign = new jejalyk::js::JsAssignNode();
          js_initial_assign->identifier = jejalyk::js::id(iterator_name);
          const auto js_initial_assign_call_chain =
              new jejalyk::js::JsChainNode();
          js_initial_assign_call_chain->left = value_result->js_node;
          js_initial_assign_call_chain->right =
              jejalyk::js::id("чародія_перебір");
          const auto js_initial_assign_call = new jejalyk::js::JsCallNode();
          js_initial_assign_call->value = js_initial_assign_call_chain;
          js_initial_assign->value = js_initial_assign_call;
          js_for_node->init = js_initial_assign;

          const auto js_condition_chain = new jejalyk::js::JsChainNode();
          js_condition_chain->left = jejalyk::js::id(iterator_name);
          js_condition_chain->right = jejalyk::js::id("завершено");
          const auto js_condition_not_node = new jejalyk::js::JsNotNode();
          js_condition_not_node->value = js_condition_chain;
          js_for_node->condition = js_condition_not_node;

          const auto js_next_chain = new jejalyk::js::JsChainNode();
          js_next_chain->left = jejalyk::js::id(iterator_name);
          js_next_chain->right = jejalyk::js::id("далі");
          const auto js_next_call_node = new jejalyk::js::JsCallNode();
          js_next_call_node->value = js_next_chain;
          js_for_node->update = js_next_call_node;

          js_for_node->body = compiled_body->js_body;
          const auto js_name_assign_node = new jejalyk::js::JsAssignNode();
          js_name_assign_node->identifier = jejalyk::js::id(each_node->name);
          const auto js_name_assign_node_chain = new jejalyk::js::JsChainNode();
          js_name_assign_node_chain->left = jejalyk::js::id(iterator_name);
          js_name_assign_node_chain->right = jejalyk::js::id("значення");
          js_name_assign_node->value = js_name_assign_node_chain;
          js_for_node->body->nodes.insert(js_for_node->body->nodes.begin(),
                                          js_name_assign_node);
          js_for_node->cleanup = new jejalyk::js::JsBody();
          const auto js_cleanup_iterator_assign =
              new jejalyk::js::JsAssignNode();
          js_cleanup_iterator_assign->identifier =
              jejalyk::js::id(iterator_name);
          js_cleanup_iterator_assign->value = jejalyk::js::id("undefined");
          js_for_node->cleanup->nodes.push_back(js_cleanup_iterator_assign);

          return success(nullptr, js_for_node);
        } else {
          return error_from_ast(
              each_node, "Неможливо перебрати \"" +
                             value_result->value->types_string() + "\".");
        }
      } else {
        return error_from_ast(each_node,
                              "Неможливо перебрати \"" +
                                  value_result->value->types_string() + "\".");
      }
    } else {
      if (scope->has_local(each_node->name)) {
        return error_1(each_node, each_node->name);
      }
      if (scope->has_local(each_node->keyName)) {
        return error_1(each_node, each_node->keyName);
      }
      return error_from_ast(each_node, "Перебір з ключем тимчасово недоступний.");
      }

      return success(nullptr);
  }
} // namespace typeinterpreter