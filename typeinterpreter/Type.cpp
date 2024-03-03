#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Type* Type::create(Object* object) {
    const auto type = new Type();
    type->object = object;
    return type;
  }

  Type* Type::create(GenericDefinition* generic_definition) {
    const auto type = new Type();
    type->generic_definition = generic_definition;
    return type;
  }

  bool Type::is_diia(Scope* scope) {
    const auto diia_structure_subject = scope->get_root_diia();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           diia_structure_subject->types[0]->object;
  }

  bool Type::is_structure(Scope* scope) {
    if (this->is_empty(scope)) {
      return true;
    }
    const auto structure_subject = scope->get_root_structure();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           structure_subject->types[0]->object;
  }

  bool Type::is_number(Scope* scope) {
    const auto number_structure_subject = scope->get_root_number();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           number_structure_subject->types[0]->object;
  }

  bool Type::is_string(Scope* scope) {
    const auto text_structure_subject = scope->get_root_text();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           text_structure_subject->types[0]->object;
  }

  bool Type::is_array(Scope* scope) {
    const auto text_structure_subject = scope->get_root_list();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           text_structure_subject->types[0]->object;
  }

  bool Type::is_object(Scope* scope) {
    const auto object_structure_subject = scope->get_root_object();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           object_structure_subject->types[0]->object;
  }

  bool Type::is_empty(Scope* scope) {
    const auto empty_structure_subject = scope->get_root_empty();
    if (this->generic_definition) {
      return false;
    }
    return this->object == empty_structure_subject->types[0]->object ||
           this->object->structure->object ==
               empty_structure_subject->types[0]->object;
  }

  bool Type::is_dictionary(Scope* scope) {
    const auto dictionary_structure_subject = scope->get_root_dictionary();
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           dictionary_structure_subject->types[0]->object;
  }

  std::string Type::get_name() {
    if (this->generic_definition) {
      return this->generic_definition->name;
    }
    return this->object->name;
  }

  std::string Type::get_type_name() {
    std::string result = this->generic_definition
                             ? this->generic_definition->name
                             : this->object->structure->object->name;
    std::vector<std::string> generic_names;
    for (const auto generic_type : this->generic_types) {
      generic_names.push_back(generic_type->types_string());
    }
    if (!generic_names.empty()) {
      result += "<" + jejalyk::tools::implode(generic_names, ", ") + ">";
    }
    return result;
  }

  bool Type::is_method(Scope* scope) {
    if (this->object) {
      return this->object->is_diia_method;
    }
    return false;
  }

  Type* Type::create_instance(Scope* scope,
                              std::vector<Subject*> generic_types) {
    if (!this->generic_types.empty()) {
      debug_print_bug(
          "Type::create_instance() called for type with generic_types");
    }

    if (this->generic_definition) {
      return this;
    }

    if (!this->is_structure(scope)) {
      debug_print_bug("Type::create_instance() called for non-structure");
    }

    const auto object = new Object();
    object->structure = this;

    const auto type = create(object);
    if (generic_types.size() == this->object->generic_definitions.size()) {
      type->generic_types = generic_types;
    } else {
      for (const auto generic_definition : this->object->generic_definitions) {
        type->generic_types.push_back(scope->create_object_instance_subject());
      }
    }

    return type;
  }

  bool Type::has(Scope* scope, std::string name) {
    if (!scope->get_options()->is_strict_mode()) {
      if (this->is_object(scope)) {
        return true;
      }
    }
    if (this->generic_definition) {
      return false;
    }
    if (this->object->properties.contains(name)) {
      return true;
    }
    for (const auto param : this->object->structure->object->params) {
      if (param->name == name) {
        return true;
      }
    }
    for (const auto& [method_name, method] :
         this->object->structure->object->methods) {
      if (method_name == name) {
        return true;
      }
    }
    return false;
  }

  Subject* Type::get(Scope* scope, std::string name) {
    if (!scope->get_options()->is_strict_mode()) {
      if (this->is_object(scope)) {
        return scope->create_object_instance_subject();
      }
    }
    if (!this->has(scope, name)) {
      std::cout << "[BUG] Type::get() called for non-existing property"
                << std::endl;
    }
    if (this->object->properties.contains(name)) {
      return this->object->properties[name];
    }
    for (const auto param : this->object->structure->object->params) {
      if (param->name == name) {
        return process_subject_generics(this->object->structure->object,
                                        this->generic_types, param->types);
      }
    }
    if (this->object->structure->object->methods.contains(name)) {
      const auto method_type = this->object->structure->object->methods[name];
      const auto processed_method_object = new Object();
      processed_method_object->structure = method_type->object->structure;
      processed_method_object->name = method_type->object->name;
      processed_method_object->is_diia_async =
          method_type->object->is_diia_async;
      processed_method_object->is_diia_method =
          method_type->object->is_diia_method;
      std::vector<Subject*> generic_definition_subjects;
      for (const auto generic_definition :
           method_type->object->generic_definitions) {
        const auto new_generic_definition = new GenericDefinition();
        new_generic_definition->object = processed_method_object;
        new_generic_definition->index = generic_definition->index;
        new_generic_definition->name = generic_definition->name;
        processed_method_object->generic_definitions.push_back(
            new_generic_definition);
        generic_definition_subjects.push_back(
            Subject::create(new_generic_definition));
      }
      for (const auto param : method_type->object->params) {
        const auto new_param = new Param();
        new_param->name = param->name;
        new_param->types = process_subject_generics(
            this->object->structure->object, this->generic_types, param->types);
        new_param->types = process_subject_generics(
            method_type->object, generic_definition_subjects, new_param->types);
        new_param->value = param->value;
        new_param->value_js_node = param->value_js_node;
        new_param->variadic = param->variadic;
        processed_method_object->params.push_back(new_param);
      }
      processed_method_object->return_types = process_subject_generics(
          this->object->structure->object, this->generic_types,
          method_type->object->return_types);
      processed_method_object->return_types = process_subject_generics(
          method_type->object, generic_definition_subjects,
          processed_method_object->return_types);
      const auto processed_method_type = create(processed_method_object);
      return Subject::create({processed_method_type});
    }
    return nullptr;
  }

  Result* Type::set(Scope* scope,
                    mavka::ast::ASTNode* node,
                    const std::string& name,
                    Subject* value) {
    if (this->has(scope, name)) {
      const auto types = this->get(scope, name);
      if (!scope->check_subjects(value, types)) {
        return scope->error(
            node, "Неправильний тип властивості \"" + name + "\" типу \"" +
                      this->get_type_name() + "\": очікується \"" +
                      types->types_string() + "\", отримано \"" +
                      value->types_string() + "\".");
      }
      return success(types);
    } else {
      if (!scope->get_options()->is_strict_mode()) {
        if (this->is_object(scope)) {
          return success(scope->create_object_instance_subject());
        }
      }
      return scope->error(
          node, "Неможливо встановити не визначену властивість \"" + name +
                    "\" для типу \"" + this->get_type_name() + "\".");
    }
    return success(value);
  }

  Result* Type::call(Scope* scope,
                     mavka::ast::ASTNode* node,
                     std::vector<Subject*> generic_types,
                     std::vector<Subject*> args) {
    debug_print_call(this, generic_types, args);
    if (this->is_diia(scope)) {
      // if (this->object->this_is_declaration) {
      //   return scope->error(
      //       node, "Неможливо викликати \"" + this->object->name + "\".");
      // }
      if (generic_types.empty() && !this->object->generic_definitions.empty()) {
        for (const auto generic_definition :
             this->object->generic_definitions) {
          generic_types.push_back(scope->create_object_instance_subject());
        }
      }
      if (generic_types.size() < this->object->generic_definitions.size()) {
        return scope->error(node, "Недостатньо аргументів шаблону.");
      }
      if (generic_types.size() > this->object->generic_definitions.size()) {
        return scope->error(node, "Забагато аргументів шаблону.");
      }
      if (args.size() < this->object->params.size()) {
        return scope->error(node, "Недостатньо аргументів.");
      }
      if (args.size() > this->object->params.size()) {
        return scope->error(node, "Забагато аргументів.");
      }
      for (int i = 0; i < this->object->params.size(); ++i) {
        const auto param = this->object->params[i];
        const auto arg = args[i];
        const auto processed_types_result =
            process_subject_generics(this->object, generic_types, param->types);
        if (!scope->check_subjects(arg, processed_types_result)) {
          if (this->object->name.empty()) {
            return scope->error(
                node, "Неправильний тип параметра \"" + param->name +
                          "\": очікується \"" +
                          processed_types_result->types_string() +
                          "\", отримано \"" + arg->types_string() + "\".");
          } else {
            return scope->error(
                node, "Неправильний тип параметра \"" + param->name +
                          "\" дії \"" + this->object->name +
                          "\": очікується \"" +
                          processed_types_result->types_string() +
                          "\", отримано \"" + arg->types_string() + "\".");
          }
        }
      }
      return success(process_subject_generics(this->object, generic_types,
                                              this->object->return_types));
    }
    if (this->is_object(scope)) {
      return success(scope->create_object_instance_subject());
    }
    if (this->has(scope, JJ_MAG_CALL)) {
      const auto value = this->get(scope, JJ_MAG_CALL);
      return value->call(scope, node, generic_types, args);
    }
    return scope->error(
        node, "Неможливо викликати \"" + this->get_type_name() + "\".");
  }

  Result* Type::magic_call(Scope* scope,
                           mavka::ast::ASTNode* node,
                           std::string name,
                           std::vector<Subject*> generic_types,
                           std::vector<Subject*> args) {
    if (this->has(scope, name)) {
      return this->get(scope, name)->call(scope, node, generic_types, args);
    }
    if (!scope->get_options()->is_strict_mode()) {
      if (this->is_object(scope)) {
        return success(scope->create_object_instance_subject());
      }
    }
    return error_4(scope, node, name, this);
  }

  bool Type::is_iterator(Scope* scope) {
    const auto iterator_structure_subject = scope->get_root_iterator();

    if (this->generic_definition) {
      return false;
    }

    return this->object->structure->object ==
           iterator_structure_subject->types[0]->object;
  }

  Result* Type::get_iterator_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_iterator(scope)) {
      return scope->error(node, "Неможливо отримати тип ітератора.");
    }

    return success(this->generic_types[0]);
  }

  bool Type::is_awaiting(Scope* scope) {
    const auto iterator_structure_subject =
        scope->get_root()->get("очікування");

    if (this->generic_definition) {
      return false;
    }

    return this->object->structure->object == iterator_structure_subject->types[0]->object;
  }

  Result* Type::get_awaiting_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_awaiting(scope)) {
      return scope->error(node, "Неможливо отримати тип очікування.");
    }

    return success(this->generic_types[0]);
  }
} // namespace typeinterpreter