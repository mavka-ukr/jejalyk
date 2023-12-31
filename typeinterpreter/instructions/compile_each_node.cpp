#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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
      if (loop_scope->has_local(each_node->name)) {
        return error_1(each_node, each_node->name);
      }
      if (value_result->value->is_iterator(loop_scope)) {
        // перебрати а як х
        const auto iterator_type_result =
            value_result->value->get_iterator_type(loop_scope,
                                                   each_node->value);
        if (iterator_type_result->error) {
          return iterator_type_result;
        }
        loop_scope->set_local(each_node->name, iterator_type_result->value);
        scope->put_additional_node_before(js::make_var(iterator_name));
        scope->put_additional_variable(each_node->name);

        const auto compiled_body = loop_scope->compile_body(each_node->body);
        if (compiled_body->error) {
          return compiled_body;
        }

        // х = _мit_0.значення
        const auto js_name_assign =
            js::make_assign(js::make_id(each_node->name),
                            js::make_chain(iterator_name, "значення"));
        compiled_body->js_body->nodes.insert(
            compiled_body->js_body->nodes.begin(), js_name_assign);

        scope->variables.erase(each_node->name);

        const auto js_for_node = new js::JsForNode();

        // _мit_0 = а
        const auto js_initial_assign =
            js::make_assign(js::make_id(iterator_name), value_result->js_node);
        js_for_node->init = js_initial_assign;

        // !_мit_0.завершено
        const auto js_condition_chain =
            js::make_chain(iterator_name, "завершено");
        js_for_node->condition = js::make_not(js_condition_chain);

        // _мit_0.далі()
        const auto js_next_chain = js::make_chain(iterator_name, "далі");
        js_for_node->update = js::make_call(js_next_chain, {});

        js_for_node->body = compiled_body->js_body;

        js_for_node->cleanup = new js::JsBody();
        // _мit_0 = undefined
        const auto js_cleanup_iterator_assign = js::make_assign(
            js::make_id(iterator_name), js::make_id("undefined"));
        js_for_node->cleanup->nodes.push_back(js_cleanup_iterator_assign);

        return success(nullptr, js_for_node);
      } else if (value_result->value->has("чародія_перебір")) {
        // перебрати а.чародія_перебір() як х
        const auto iterator_diia_type_result =
            value_result->value->get("чародія_перебір");
        if (iterator_diia_type_result->error) {
          return iterator_diia_type_result;
        }
        const auto iterator_diia_return_types =
            iterator_diia_type_result->value->call(loop_scope, each_node->value,
                                                   {}, {});
        if (iterator_diia_return_types->value->is_iterator(loop_scope)) {
          const auto iterator_type_result =
              iterator_diia_return_types->value->get_iterator_type(
                  loop_scope, each_node->value);
          if (iterator_type_result->error) {
            return iterator_type_result;
          }
          loop_scope->set_local(each_node->name, iterator_type_result->value);
          scope->put_additional_node_before(js::make_var(iterator_name));
          scope->put_additional_variable(each_node->name);

          const auto compiled_body = loop_scope->compile_body(each_node->body);
          if (compiled_body->error) {
            return compiled_body;
          }

          // х = _мit_0.значення
          const auto js_name_assign =
              js::make_assign(js::make_id(each_node->name),
                              js::make_chain(iterator_name, "значення"));
          compiled_body->js_body->nodes.insert(
              compiled_body->js_body->nodes.begin(), js_name_assign);

          scope->variables.erase(each_node->name);

          const auto js_for_node = new js::JsForNode();

          // _мit_0 = а.чародія_перебір()
          const auto js_initial_assign = js::make_assign(
              js::make_id(iterator_name),
              js::make_call(js::make_chain(value_result->js_node,
                                           js::make_id("чародія_перебір")),
                            {}));
          js_for_node->init = js_initial_assign;

          // !_мit_0.завершено
          const auto js_condition_chain =
              js::make_chain(iterator_name, "завершено");
          js_for_node->condition = js::make_not(js_condition_chain);

          // _мit_0.далі()
          const auto js_next_chain = js::make_chain(iterator_name, "далі");
          js_for_node->update = js::make_call(js_next_chain, {});

          js_for_node->body = compiled_body->js_body;

          js_for_node->cleanup = new js::JsBody();
          // _мit_0 = undefined
          const auto js_cleanup_iterator_assign = js::make_assign(
              js::make_id(iterator_name), js::make_id("undefined"));
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
      if (loop_scope->has_local(each_node->name)) {
        return error_1(each_node, each_node->name);
      }
      if (loop_scope->has_local(each_node->keyName)) {
        return error_1(each_node, each_node->keyName);
      }
      return error_from_ast(each_node, "Перебір з ключем тимчасово недоступний.");
    }
  }
} // namespace typeinterpreter