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

    const auto type = new Type(object);
    type->generic_types = generic_types;

    return type;
  }

  bool Type::has(std::string name) {
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

  Subject* Type::get(std::string name) {
    if (!this->has(name)) {
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
      const auto processed_method_type = new Type(processed_method_object);
      return new Subject({processed_method_type});
    }
    return nullptr;
  }

  Result* Type::set(Scope* scope,
                    mavka::ast::ASTNode* node,
                    const std::string& name,
                    Subject* value) {
    if (this->has(name)) {
      const auto types = this->get(name);
      if (!scope->check_subjects(value, types)) {
        return error_from_ast(
            node, "Неправильний тип значення для властивості \"" + name +
                      "\": очікується \"" + types->types_string() +
                      "\", отримано \"" + value->types_string() + "\".");
      }
      return success(types);
    } else {
      return error_from_ast(
          node,
          "Неможливо встановити не визначену властивість \"" + name + "\".");
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
      //   return error_from_ast(
      //       node, "Неможливо викликати \"" + this->object->name + "\".");
      // }
      if (generic_types.empty() && !this->object->generic_definitions.empty()) {
        for (const auto generic_definition :
             this->object->generic_definitions) {
          generic_types.push_back(scope->create_object_instance_subject());
        }
      }
      if (generic_types.size() < this->object->generic_definitions.size()) {
        return error_from_ast(node, "Недостатньо аргументів шаблону.");
      }
      if (generic_types.size() > this->object->generic_definitions.size()) {
        return error_from_ast(node, "Забагато аргументів шаблону.");
      }
      if (args.size() < this->object->params.size()) {
        return error_from_ast(node, "Недостатньо аргументів.");
      }
      if (args.size() > this->object->params.size()) {
        return error_from_ast(node, "Забагато аргументів.");
      }
      for (int i = 0; i < this->object->params.size(); ++i) {
        const auto param = this->object->params[i];
        const auto arg = args[i];
        const auto processed_types_result =
            process_subject_generics(this->object, generic_types, param->types);
        if (!scope->check_subjects(arg, processed_types_result)) {
          if (this->object->name.empty()) {
            return error_from_ast(
                node, "Неправильний тип аргументу параметра \"" + param->name +
                          "\": очікується \"" +
                          processed_types_result->types_string() +
                          "\", отримано \"" + arg->types_string() + "\".");
          } else {
            return error_from_ast(
                node, "Неправильний тип аргументу параметра \"" + param->name +
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
    if (this->has("чародія_викликати")) {
      const auto value = this->get("чародія_викликати");
      return value->call(scope, node, generic_types, args);
    }
    return error_from_ast(node, "Неможливо викликати тип.");
  }

  Result* Type::get_element(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (this->has("чародія_отримати")) {
      return this->get("чародія_отримати")->call(scope, node, {}, {value});
    }
    return error_from_ast(
        node, "Неможливо отримати спеціальну властивість з типу \"" +
                  this->get_type_name() + "\".");
  }

  Result* Type::set_element(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* element,
                            Subject* value) {
    if (this->has("чародія_покласти")) {
      return this->get("чародія_покласти")
          ->call(scope, node, {}, {element, value});
    }
    return error_from_ast(
        node, "Неможливо встановити спеціальну властивість з типу \"" +
                  this->get_type_name() + "\".");
  }

  Result* Type::plus(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    if (this->has("чародія_додати")) {
      return this->get("чародія_додати")->call(scope, node, {}, {value});
    }
    if (this->is_object(scope)) {
      return success(scope->create_object_instance_subject());
    }
    return error_from_ast(node, "Неможливо виконати додавання для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::minus(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    if (this->has("чародія_відняти")) {
      return this->get("чародія_відняти")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати віднімання для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::multiply(Scope* scope,
                         mavka::ast::ASTNode* node,
                         Subject* value) {
    if (this->has("чародія_помножити")) {
      return this->get("чародія_помножити")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати множення для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::divide(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (this->has("чародія_поділити")) {
      return this->get("чародія_поділити")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати ділення для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::divmod(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (this->has("чародія_остача")) {
      return this->get("чародія_остача")->call(scope, node, {}, {value});
    }
    return error_from_ast(node,
                          "Неможливо виконати ділення з остачею для "
                          "типу \"" +
                              this->get_type_name() + "\".");
  }

  Result* Type::divdiv(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (this->has("чародія_частка")) {
      return this->get("чародія_частка")->call(scope, node, {}, {value});
    }
    return error_from_ast(node,
                          "Неможливо чародія_частка для "
                          "типу \"" +
                              this->get_type_name() + "\".");
  }

  Result* Type::pow(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    if (this->has("чародія_степінь")) {
      return this->get("чародія_степінь")->call(scope, node, {}, {value});
    }
    return error_from_ast(node,
                          "Неможливо виконати піднесення до степені "
                          "для типу \"" +
                              this->get_type_name() + "\".");
  }

  Result* Type::bw_not(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_дні")) {
      return this->get("чародія_дні")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо виконати двійкове ні для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::bw_xor(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (this->has("чародія_вабо")) {
      return this->get("чародія_вабо")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати чародія_вабо для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::bw_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    if (this->has("чародія_дабо")) {
      return this->get("чародія_дабо")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати чародія_дабо для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::bw_and(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (this->has("чародія_ді")) {
      return this->get("чародія_ді")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати чародія_ді для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::bw_shift_left(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value) {
    if (this->has("чародія_вліво")) {
      return this->get("чародія_вліво")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо виконати чародія_вліво для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::bw_shift_right(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    if (this->has("чародія_вправо")) {
      return this->get("чародія_вправо")->call(scope, node, {}, {value});
    }
    return error_from_ast(node,
                          "Неможливо виконати чародія_вправо для типу \"" +
                              this->get_type_name() + "\".");
  }

  Result* Type::negative(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_відʼємне")) {
      return this->get("чародія_відʼємне")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо виконати відʼємне для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::positive(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_додатнє")) {
      return this->get("чародія_додатнє")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо виконати додатнє для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::post_decrement(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_зменшити_після")) {
      return this->get("чародія_зменшити_після")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо чародія_зменшити_після для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::post_increment(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_збільшити_після")) {
      return this->get("чародія_збільшити_після")->call(scope, node, {}, {});
    }
    return error_from_ast(node,
                          "Неможливо чародія_збільшити_після для типу \"" +
                              this->get_type_name() + "\".");
  }

  Result* Type::pre_decrement(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_зменшити")) {
      return this->get("чародія_зменшити")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо чародія_зменшити для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::pre_increment(Scope* scope, mavka::ast::ASTNode* node) {
    if (this->has("чародія_збільшити")) {
      return this->get("чародія_збільшити")->call(scope, node, {}, {});
    }
    return error_from_ast(node, "Неможливо чародія_збільшити для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_greater(Scope* scope,
                             mavka::ast::ASTNode* node,
                             Subject* value) {
    if (this->has("чародія_більше")) {
      return this->get("чародія_більше")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо чародія_більше для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_lesser(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (this->has("чародія_менше")) {
      return this->get("чародія_менше")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо чародія_менше для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_greater_or_eq(Scope* scope,
                                   mavka::ast::ASTNode* node,
                                   Subject* value) {
    if (this->has("чародія_не_менше")) {
      return this->get("чародія_не_менше")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо чародія_не_менше для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_lesser_or_eq(Scope* scope,
                                  mavka::ast::ASTNode* node,
                                  Subject* value) {
    if (this->has("чародія_не_більше")) {
      return this->get("чародія_не_більше")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо чародія_не_більше для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_contains(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value) {
    if (this->has("чародія_містить")) {
      return this->get("чародія_містить")->call(scope, node, {}, {value});
    }
    return error_from_ast(node, "Неможливо чародія_містить для типу \"" +
                                    this->get_type_name() + "\".");
  }

  Result* Type::comp_contains_not(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (this->has("чародія_містить")) {
      const auto logical_structure_subject = scope->get_root_logical();
      return logical_structure_subject->create_instance(scope, {});
    }
    return error_from_ast(node, "Неможливо чародія_містить для типу \"" +
                                    this->get_type_name() + "\".");
  }

  bool Type::is_iterator(Scope* scope) {
    const auto iterator_structure_subject = scope->get_root_iterator();

    if (this->generic_definition) {
      return false;
    }

    return this->object->structure->object == iterator_structure_subject->types[0]->object;
  }

  Result* Type::get_iterator_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_iterator(scope)) {
      return error_from_ast(node, "Неможливо отримати тип ітератора.");
    }

    return success(this->generic_types[0]);
  }

  bool Type::is_awaiting(Scope* scope) {
    const auto iterator_structure_subject = scope->get_root()->get("очікування");

    if (this->generic_definition) {
      return false;
    }

    return this->object->structure->object == iterator_structure_subject->types[0]->object;
  }

  Result* Type::get_awaiting_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_awaiting(scope)) {
      return error_from_ast(node, "Неможливо отримати тип очікування.");
    }

    return success(this->generic_types[0]);
  }
} // namespace typeinterpreter