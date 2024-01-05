#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_call_node(Scope* scope, mavka::ast::CallNode* call_node) {
    const auto value_result = scope->compile_node(call_node->value);
    if (value_result->error) {
      return value_result;
    }

    std::vector<Subject*> generic_types;
    for (const auto& generic_type_nodes : call_node->generics) {
      const auto generic_result = scope->compile_types(generic_type_nodes);
      if (generic_result->error) {
        return generic_result;
      }
      generic_types.push_back(generic_result->value);
    }

    std::vector<Subject*> args;
    std::vector<js::JsNode*> js_args;

    if (value_result->value->is_object(scope)) {
      if (scope->get_options()->is_strict_mode()) {
        return scope->error(
            call_node,
            "Неможливо скомпілювати виклик обʼєкта. Ви можете викликати обʼєкт "
            "динамічно без перевірки типів через \"Дія.викликати(значення, "
            "[аргументи])\".");
      } else {
        for (const auto& arg_node : call_node->args) {
          if (!arg_node->name.empty()) {
            return scope->error(arg_node,
                                "Неможливо скомпілювати виклик значення типу "
                                "\"обʼєкт\" з назвами параметрів.");
          }
          const auto arg_value_result = scope->compile_node(arg_node->value);
          if (arg_value_result->error) {
            return arg_value_result;
          }
          args.push_back(arg_value_result->value);
          js_args.push_back(arg_value_result->js_node);
        }

        // а.чародія_викликати(б)
        const auto js_chain =
            js::make_chain(value_result->js_node, js::make_id(JJ_MAG_CALL));
        const auto js_call = js::make_call(js_chain, js_args);

        return success(value_result->value, js_call);
      }
    }

    Subject* diia = nullptr;

    if (value_result->value->is_diia(scope)) {
      diia = value_result->value;
    } else if (value_result->value->has_diia(scope, JJ_MAG_CALL)) {
      const auto magic_diia_result = value_result->value->get(
          scope, mavka::ast::get_ast_node(call_node->value), JJ_MAG_CALL);
      if (magic_diia_result->error) {
        return magic_diia_result;
      }
      diia = magic_diia_result->value;
    }
    if (diia) {
      const auto diia_params = diia->types[0]->object->params;
      bool named = false;
      if (call_node->args.empty()) {
        named = false;
      } else {
        if (!call_node->args[0]->name.empty()) {
          named = true;
        }
      }
      if (named) {
        // named
        for (const auto diia_param : diia_params) {
          mavka::ast::ArgNode* arg_node = nullptr;
          for (const auto call_arg_node : call_node->args) {
            if (call_arg_node->name == diia_param->name) {
              arg_node = call_arg_node;
              break;
            }
          }
          if (arg_node) {
            const auto arg_value_result = scope->compile_node(arg_node->value);
            if (arg_value_result->error) {
              return arg_value_result;
            }
            if (arg_value_result->value->is_method(scope)) {
              return scope->error(
                  mavka::ast::get_ast_node(arg_node->value),
                  "Не можна передавати дію обʼєкта як значення.");
            }
            args.push_back(arg_value_result->value);
            js_args.push_back(arg_value_result->js_node);
          } else {
            if (diia_param->value) {
              args.push_back(diia_param->value);
              js_args.push_back(js::make_id("undefined"));
            } else {
              return scope->error(call_node, "Пропущено аргумент \"" +
                                                 diia_param->name + "\".");
            }
          }
        }
      } else {
        // positioned
        const Param* last_param = nullptr;
        if (!diia_params.empty()) {
          last_param = diia_params.back();
        }
        if (last_param != nullptr) {
          if (last_param->variadic) {
            const auto variadic_subject = new Subject();
            std::vector<js::JsNode*> variadic_js_nodes;
            for (size_t i = 0; i < diia_params.size() - 1; ++i) {
              const auto diia_param = diia_params[i];
              Subject* arg = nullptr;

              if (i >= call_node->args.size()) {
                if (diia_param->value) {
                  arg = diia_param->value;
                  args.push_back(diia_param->types);
                  js_args.push_back(js::make_id("undefined"));
                } else {
                  return scope->error(call_node, "Пропущено аргумент \"" +
                                                     diia_param->name + "\".");
                }
              } else {
                const auto arg_value_result =
                    scope->compile_node(call_node->args[i]->value);
                if (arg_value_result->error) {
                  return arg_value_result;
                }
                arg = arg_value_result->value;
                args.push_back(arg);
                js_args.push_back(arg_value_result->js_node);
              }
            }
            for (size_t i = diia_params.size() - 1; i < call_node->args.size();
                 ++i) {
              const auto arg_value_result =
                  scope->compile_node(call_node->args[i]->value);
              if (arg_value_result->error) {
                return arg_value_result;
              }
              variadic_subject->merge_types(arg_value_result->value);
              variadic_js_nodes.push_back(arg_value_result->js_node);
            }
            variadic_subject->fix_types(scope);
            const auto variadic_array_result =
                scope->get_root_list()->create_instance(scope,
                                                        {variadic_subject});
            if (variadic_array_result->error) {
              return variadic_array_result;
            }
            args.push_back(variadic_array_result->value);
            js_args.push_back(js::make_array(variadic_js_nodes));
          } else {
            for (int i = 0; i < diia_params.size(); ++i) {
              const auto diia_param = diia_params[i];
              Subject* arg = nullptr;
              if (i >= call_node->args.size()) {
                if (diia_param->value) {
                  arg = diia_param->value;
                  args.push_back(diia_param->types);
                  js_args.push_back(js::make_id("undefined"));
                } else {
                  return scope->error(call_node, "Пропущено аргумент \"" +
                                                     diia_param->name + "\".");
                }
              } else {
                const auto arg_value_result =
                    scope->compile_node(call_node->args[i]->value);
                if (arg_value_result->error) {
                  return arg_value_result;
                }
                if (arg_value_result->value->is_method(scope)) {
                  return scope->error(
                      mavka::ast::get_ast_node(call_node->args[i]->value),
                      "Не можна передавати дію обʼєкта як значення.");
                }
                arg = arg_value_result->value;
                args.push_back(arg);
                js_args.push_back(arg_value_result->js_node);
              }
            }
          }
        } else {
          if (!args.empty()) {
            return scope->error(call_node, "Забагато аргументів.");
          }
        }
      }
    }

    const auto result =
        value_result->value->call(scope, call_node, generic_types, args);

    if (value_result->value->is_diia(scope)) {
      // а(б)
      result->js_node = js::make_call(value_result->js_node, js_args);
    } else {
      // а.чародія_викликати(б)
      const auto js_chain = js::make_chain(value_result->js_node,
                                           js::make_id(JJ_MAG_CALL));

      result->js_node = js::make_call(js_chain, js_args);
    }

    return result;
  }
} // namespace jejalyk::typeinterpreter