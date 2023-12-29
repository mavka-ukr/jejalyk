#include "typeinterpreter.h"

namespace typeinterpreter {
  Result* declare_structure(
      Scope* scope,
      mavka::ast::ASTNode* node,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      mavka::ast::ASTNode* parent,
      std::vector<mavka::ast::GenericNode*> parent_generic_definitions) {
    const auto structure_structure_subject = scope->get_root_structure();
    const auto object_subject = scope->get_root_object();

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
      structure_object->parent = object_subject->types[0];
    } else {
      // todo: handle parent
    }

    return success(Subject::create(structure_object));
  }

  Result* complete_structure(
      Scope* scope,
      bool mockup,
      mavka::ast::ASTNode* node,
      Subject* structure_subject,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::MethodDeclarationNode*> method_declarations) {
    Type* structure_type = nullptr;
    Object* structure_object = nullptr;
    Scope* scope_with_generics = scope->make_proxy();
    std::vector<Subject*> generic_definition_subjects;

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
    }

    for (const auto param_node : params) {
      const auto param = new Param();
      param->name = param_node->name;
      param->types = new Subject();
      for (const auto type_value_single_node : param_node->types) {
        const auto type_value_single_result =
            scope_with_generics->compile_node(type_value_single_node);
        if (type_value_single_result->error) {
          return type_value_single_result;
        }

        param->types->merge_types(type_value_single_result->value);
      }
      param->types->fix_types(scope);
      param->value = nullptr;
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
        for (const auto param : structure_object->params) {
          if (param->name == param_node->name) {
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
      }
    }

    for (const auto method_declaration_node : method_declarations) {
      const auto method_declaration_result =
          scope_with_generics->compile_node(method_declaration_node);
      if (method_declaration_result->error) {
        return method_declaration_result;
      }

      if (method_declaration_node->ee) {
        if (method_declaration_node->name == "створити") {
          return error_from_ast(
              method_declaration_node,
              "Неможливо перевизначити спеціальну властивість \"створити\".");
        }
        for (const auto& [property_name, property_subject] :
             structure_object->properties) {
          if (property_name == method_declaration_node->name) {
            return error_from_ast(method_declaration_node,
                                  "Спеціальну властивість \"" +
                                      method_declaration_node->name +
                                      "\" вже визначено.");
          }
        }
        structure_object->properties.insert_or_assign(
            method_declaration_node->name, method_declaration_result->value);
      } else {
        for (const auto param : structure_object->params) {
          if (param->name == method_declaration_node->name) {
            return error_from_ast(method_declaration_node,
                                  "Властивість \"" +
                                      method_declaration_node->name +
                                      "\" вже визначено.");
          }
        }
        for (const auto& [method_name, method_type] :
             structure_object->methods) {
          if (method_name == method_declaration_node->name) {
            return error_from_ast(
                method_declaration_node,
                "Дію \"" + method_declaration_node->name + "\" вже визначено.");
          }
        }

        // todo: handle parent

        structure_object->methods.insert_or_assign(
            method_declaration_node->name,
            method_declaration_result->value->types[0]);
      }
    }

    const auto diia_structure_subject = scope->get_root_diia();

    const auto diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];
    diia_object->name = "створити";
    diia_object->is_diia_async = false;
    diia_object->params = structure_object->params;
    diia_object->return_types = Subject::create(
        structure_type->create_instance(scope, generic_definition_subjects));
    const auto diia_subject = Subject::create(diia_object);

    structure_object->properties.insert_or_assign("створити", diia_subject);

    if (!structure_object->properties.contains("чародія_викликати")) {
      structure_object->properties.insert_or_assign("чародія_викликати",
                                                    diia_subject);
    }

    if (mockup) {
      return success(structure_subject, new jejalyk::js::JsEmptyNode());
    } else {
      const auto js_call_node = new jejalyk::js::JsCallNode();
      const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
      js_call_id_node->name = "мСтрк";
      js_call_node->value = js_call_id_node;
      js_call_node->arguments = {jejalyk::js::string(structure_object->name),
                                 jejalyk::js::null()};

      return success(structure_subject, js_call_node);
    }
  }
} // namespace typeinterpreter