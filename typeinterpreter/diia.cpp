#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* declare_diia(
      Scope* scope,
      Scope* diia_scope,
      mavka::ast::ASTNode* node,
      bool async,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types) {
    const auto diia_structure_subject = scope->get_root_diia();

    Object* diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];
    diia_object->name = name;
    diia_object->is_diia_async = async;

    Subject* diia_subject = Subject::create(diia_object);
    Scope* scope_with_generics = diia_scope->make_proxy();
    std::vector<Subject*> generic_definition_subjects;

    for (int i = 0; i < generic_definitions.size(); ++i) {
      const auto generic_definition_node = generic_definitions[i];

      const auto generic_definition = new GenericDefinition();
      generic_definition->object = diia_object;
      generic_definition->index = i;
      generic_definition->name = generic_definition_node->name;

      diia_object->generic_definitions.push_back(generic_definition);

      const auto generic_definition_subject =
          Subject::create(generic_definition);

      scope_with_generics->variables.insert_or_assign(
          generic_definition->name, generic_definition_subject);

      generic_definition_subjects.push_back(generic_definition_subject);
    }

    const auto return_types_subject = new Subject();
    for (const auto return_type_node : return_types) {
      const auto compiled_return_type =
          scope_with_generics->compile_node(return_type_node);
      if (compiled_return_type->error) {
        return compiled_return_type;
      }
      return_types_subject->merge_types(compiled_return_type->value);
    }
    return_types_subject->fix_types(scope);
    if (async) {
      const auto awaiting_structure_subject = scope->get_root_awaiting();
      const auto awaiting_instance_result =
          awaiting_structure_subject->create_instance(scope,
                                                      {return_types_subject});
      if (awaiting_instance_result->error) {
        return awaiting_instance_result;
      }
      diia_object->return_types = awaiting_instance_result->value;
    } else {
      diia_object->return_types = return_types_subject;
    }

    for (const auto param_node : params) {
      for (const auto param : diia_object->params) {
        if (param->name == param_node->name) {
          return error_from_ast(param_node, "Параметр \"" + param_node->name +
                                                "\" вже визначено.");
        }
      }

      const auto param = new Param();
      param->name = param_node->name;
      param->types = new Subject();
      for (const auto type_value_single_node : param_node->types) {
        const auto type_value_single_result =
            scope_with_generics->compile_node(type_value_single_node);
        if (type_value_single_result->error) {
          return type_value_single_result;
        }
        for (const auto param_type : type_value_single_result->value->types) {
          param->types->add_type(param_type);
        }
      }
      param->types->fix_types(scope);
      param->value = nullptr;
      param->variadic = param_node->variadic;

      diia_object->params.push_back(param);
    }

    return success(diia_subject);
  }

  Result* complete_diia(Scope* scope,
                        bool mockup,
                        Scope* diia_scope,
                        mavka::ast::ASTNode* node,
                        Subject* diia_subject,
                        std::vector<mavka::ast::ASTNode*>* body) {
    Result* compiled_body = nullptr;
    Object* diia_object = diia_subject->types[0]->object;

    if (mockup) {
      return success(diia_subject, new jejalyk::js::JsEmptyNode());
    } else {
      if (body != nullptr) {
        diia_scope->diia_object = diia_object;
        diia_scope->is_async = diia_object->is_diia_async;

        compiled_body = diia_scope->compile_body(*body);
        if (compiled_body->error) {
          return compiled_body;
        }
      }

      const auto js_function_node = new jejalyk::js::JsFunctionNode();
      js_function_node->async = diia_object->is_diia_async;
      for (const auto param : diia_object->params) {
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = param->name;
        js_function_node->params.push_back(js_id_node);
      }
      if (compiled_body) {
        js_function_node->body = compiled_body->js_body;
      }

      const auto js_call_node = new jejalyk::js::JsCallNode();
      const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
      js_call_id_node->name = "мДія";
      js_call_node->value = js_call_id_node;
      js_call_node->arguments = {jejalyk::js::string(diia_object->name),
                                 jejalyk::js::null(), js_function_node};

      return success(diia_subject, js_call_node);
    }
  }
}