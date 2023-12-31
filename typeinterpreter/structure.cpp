#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* declare_structure(
      Scope* scope,
      mavka::ast::ASTNode* node,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      mavka::ast::ASTNode* parent,
      std::vector<mavka::ast::GenericNode*> parent_generic_definitions) {
    const auto structure_structure_subject = scope->get_root_structure();

    const auto structure_object = new Object();
    Scope* scope_with_generics = scope->make_proxy();

    structure_object->structure = structure_structure_subject->types[0];
    structure_object->name = name;
    structure_object->this_is_declaration = true;

    for (int i = 0; i < generic_definitions.size(); ++i) {
      const auto generic_definition_node = generic_definitions[i];

      const auto generic_definition = new GenericDefinition();
      generic_definition->object = structure_object;
      generic_definition->index = i;
      generic_definition->name = generic_definition_node->name;

      structure_object->generic_definitions.push_back(generic_definition);
      scope_with_generics->variables.insert_or_assign(
          generic_definition->name, Subject::create(generic_definition));
    }

    if (parent == nullptr) {
      structure_object->parent = scope->create_object_instance_type();
      structure_object->parent_js = js::make_id("обʼєкт");
    } else {
      return error_from_ast(parent, "Наслідування тимчасово не підтримується.");
      // const auto parent_result = scope->compile_node(parent);
      // if (parent_result->error) {
      //   return parent_result;
      // }
      //
      // if (!parent_result->value->is_structure(scope)) {
      //   return error_from_ast(parent, "Предок має бути структурою.");
      // }
      //
      // structure_object->parent = parent_result->value->types[0];
      // structure_object->parent_js = parent_result->js_node;
    }

    return success(Subject::create(structure_object));
  }

  Result* complete_structure(Scope* scope,
                             bool mockup,
                             mavka::ast::ASTNode* node,
                             Subject* structure_subject,
                             std::vector<mavka::ast::ParamNode*> params) {
    const auto diia_structure_subject = scope->get_root_diia();

    Type* structure_type = nullptr;
    Object* structure_object = nullptr;
    Scope* scope_with_generics = scope->make_proxy();
    std::vector<Subject*> generic_definition_subjects;

    // створити()
    const auto diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];
    diia_object->is_diia_async = false;
    diia_object->name = "створити";
    Scope* diia_scope_with_generics = scope->make_proxy();
    std::vector<Subject*> diia_generic_definition_subjects;

    structure_type = structure_subject->types[0];
    structure_object = structure_type->object;

    if (!structure_object->this_is_declaration) {
      return error("[INTERNAL BUG] Структура \"" + structure_object->name +
                   "\" вже визначена.");
    }

    structure_object->this_is_declaration = false;

    for (const auto generic_definition :
         structure_object->generic_definitions) {
      const auto generic_definition_subject =
          Subject::create(generic_definition);

      scope_with_generics->variables.insert_or_assign(
          generic_definition->name, generic_definition_subject);
      generic_definition_subjects.push_back(generic_definition_subject);

      // створити()
      const auto diia_generic_definition = new GenericDefinition();
      diia_generic_definition->object = diia_object;
      diia_generic_definition->index = generic_definition->index;
      diia_generic_definition->name = generic_definition->name;
      diia_scope_with_generics->variables.insert_or_assign(
          generic_definition->name, Subject::create(diia_generic_definition));
      diia_object->generic_definitions.push_back(diia_generic_definition);
      diia_generic_definition_subjects.push_back(
          Subject::create(diia_generic_definition));
    }

    for (const auto param_node : params) {
      const auto param = new Param();
      param->name = param_node->name;
      const auto types_result =
          scope_with_generics->compile_types(param_node->types);
      if (types_result->error) {
        return types_result;
      }
      param->types = types_result->value;
      if (param_node->value) {
        const auto param_value_result = scope->compile_node(param_node->value);
        if (param_value_result->error) {
          return param_value_result;
        }
        param->value = param_value_result->value;
        param->value_js_node = param_value_result->js_node;
      }
      param->variadic = param_node->variadic;

      if (param_node->ee) {
        if (param_node->name == "створити") {
          return error_from_ast(
              param_node,
              "Неможливо перевизначити спеціальну властивість \"створити\".");
        }
        for (const auto& [property_name, property_subject] :
             structure_object->properties) {
          if (property_name == param_node->name) {
            return error_from_ast(param_node, "Спеціальну властивість \"" +
                                                  param_node->name +
                                                  "\" вже визначено.");
          }
        }
        structure_object->properties.insert_or_assign(param_node->name,
                                                      param->types);
      } else {
        for (const auto sparam : structure_object->params) {
          if (sparam->name == param_node->name) {
            return error_from_ast(
                param_node,
                "Властивість \"" + param_node->name + "\" вже визначено.");
          }
        }
        for (const auto& [method_name, method_type] :
             structure_object->methods) {
          if (method_name == param_node->name) {
            return error_from_ast(
                param_node, "Дію \"" + param_node->name + "\" вже визначено.");
          }
        }

        // todo: handle parent

        structure_object->params.push_back(param);

        // створити()
        const auto diia_param = new Param();
        diia_param->name = param_node->name;
        const auto diia_types_result =
            diia_scope_with_generics->compile_types(param_node->types);
        if (diia_types_result->error) {
          return diia_types_result;
        }
        diia_param->types = diia_types_result->value;
        diia_param->value = param->value;
        diia_param->value_js_node = param->value_js_node;
        diia_param->variadic = param_node->variadic;
        diia_object->params.push_back(diia_param);
      }
    }

    // for (const auto method_declaration_node : method_declarations) {
    //   const auto method_declaration_result =
    //       scope_with_generics->compile_node(method_declaration_node);
    //   if (method_declaration_result->error) {
    //     return method_declaration_result;
    //   }
    //
    //   if (method_declaration_node->ee) {
    //     if (method_declaration_node->name == "створити") {
    //       return error_from_ast(
    //           method_declaration_node,
    //           "Неможливо перевизначити спеціальну властивість
    //           \"створити\".");
    //     }
    //     for (const auto& [property_name, property_subject] :
    //          structure_object->properties) {
    //       if (property_name == method_declaration_node->name) {
    //         return error_from_ast(method_declaration_node,
    //                               "Спеціальну властивість \"" +
    //                                   method_declaration_node->name +
    //                                   "\" вже визначено.");
    //       }
    //     }
    //     structure_object->properties.insert_or_assign(
    //         method_declaration_node->name, method_declaration_result->value);
    //   } else {
    //     for (const auto param : structure_object->params) {
    //       if (param->name == method_declaration_node->name) {
    //         return error_from_ast(method_declaration_node,
    //                               "Властивість \"" +
    //                                   method_declaration_node->name +
    //                                   "\" вже визначено.");
    //       }
    //     }
    //     for (const auto& [method_name, method_type] :
    //          structure_object->methods) {
    //       if (method_name == method_declaration_node->name) {
    //         return error_from_ast(
    //             method_declaration_node,
    //             "Дію \"" + method_declaration_node->name + "\" вже
    //             визначено.");
    //       }
    //     }
    //
    //     // todo: handle parent
    //
    //     structure_object->methods.insert_or_assign(
    //         method_declaration_node->name,
    //         method_declaration_result->value->types[0]);
    //   }
    // }

    diia_object->return_types = Subject::create(structure_type->create_instance(
        scope, diia_generic_definition_subjects));
    const auto diia_subject = Subject::create(diia_object);

    structure_object->properties.insert_or_assign("створити", diia_subject);

    if (!structure_object->properties.contains("чародія_викликати")) {
      structure_object->properties.insert_or_assign("чародія_викликати",
                                                    diia_subject);
    }

    if (mockup) {
      return success(structure_subject, new js::JsEmptyNode());
    } else {
      // мСтруктура("назва", предок, function (...) { ... })
      const auto js_function = new js::JsFunctionNode();
      js_function->body = new js::JsBody();
      for (const auto param : structure_object->params) {
        js_function->params.push_back(js::make_id("мs"));
        if (param->value_js_node) {
          // а = 2
          js_function->params.push_back(
              js::make_assign(js::make_id(param->name),
                              js::make_maybe_nested(param->value_js_node)));
        } else {
          // а
          js_function->params.push_back(js::make_id(param->name));
        }
        // мs.а = а
        const auto js_chain = js::make_chain("мs", param->name);
        js_function->body->nodes.push_back(
            js::make_assign(js_chain, js::make_id(param->name)));
      }
      // js_function->body->nodes.push_back(js::make_call(
      //     js::make_chain(
      //         js::make_access(structure_object->parent_js, js::make_id("М")),
      //         js::make_id("заповнити")),
      //     {js::make_id("мs")}));
      for (const auto& [method_name, method_type] : structure_object->methods) {
        const auto method_js_function = new js::JsFunctionNode();
        method_js_function->body = new js::JsBody();
        // назва[М].методи.метод(мs, ...arguments)
        const auto method_js_call = js::make_call(
            js::make_chain(
                js::make_chain(js::make_access(structure_object->name, "М"),
                               js::make_id("методи")),
                js::make_id(method_name)),
            {js::make_id("мs"), js::make_id("...arguments")});
        method_js_function->body->nodes.push_back(
            js::make_return(method_js_call));
        // мs.а = мДія("назва", function (...) { ... })
        const auto method_js_chain = js::make_chain("мs", method_name);
        const auto method_js_call2 =
            js::make_call(js::make_id("мДія"),
                          {js::make_string(method_name), method_js_function});
        js_function->body->nodes.push_back(js::make_assign(
            method_js_chain, method_js_call2));
      }

      // return мs
      js_function->body->nodes.push_back(js::make_return(js::make_id("мs")));
      const auto js_call = js::make_call(js::make_id("мСтруктура"), {js::make_string(structure_object->name), structure_object->parent_js, js_function});

      return success(structure_subject, js_call);
    }
  }
} // namespace typeinterpreter