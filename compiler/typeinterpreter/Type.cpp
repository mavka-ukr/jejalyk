#include "typeinterpreter.h"

namespace typeinterpreter {
  bool Type::is_diia(Scope* scope) {
    const auto diia_structure_subject = scope->get_root()->get("Дія");
    return this->object->structure->object ==
           diia_structure_subject->types[0]->object;
  }

  bool Type::is_structure(Scope* scope) {
    const auto structure_subject = scope->get_root()->get("Структура");
    if (this->generic_definition) {
      return false;
    }
    return this->object->structure->object ==
           structure_subject->types[0]->object;
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
      std::cout
          << "[BUG] Type::create_instance() called for type with generic_types"
          << std::endl;
    }

    if (this->generic_definition) {
      return this;
    }

    if (!this->is_structure(scope)) {
      std::cout << "[BUG] Type::create_instance() called for non-structure"
                << std::endl;
    }

    const auto object = new Object();
    object->structure = this;

    const auto type = new Type(object);
    type->generic_types = generic_types;

    return type;
  }

  bool Type::has(std::string name) {
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
    if (this->object->structure->object->methods.contains(name)) {
      const auto method_type = this->object->structure->object->methods[name];
      const auto processed_method_object = new Object();
      processed_method_object->structure = method_type->object->structure;
      processed_method_object->name = method_type->object->name;
      processed_method_object->generic_definitions =
          method_type->object->generic_definitions;
      for (const auto param : method_type->object->params) {
        const auto newparam = new Param();
        newparam->name = param->name;
        newparam->types = process_subject_generics(
            this->object->structure->object, this->generic_types, param->types);
        newparam->value = param->value;
        newparam->variadic = param->variadic;
        processed_method_object->params.push_back(newparam);
      }
      processed_method_object->return_types = process_subject_generics(
          this->object->structure->object, this->generic_types,
          method_type->object->return_types);
      const auto processed_method_type = new Type(processed_method_object);
      return new Subject({processed_method_type});
    }
    for (const auto param : this->object->structure->object->params) {
      if (param->name == name) {
        return process_subject_generics(this->object->structure->object,
                                        this->generic_types, param->types);
      }
    }
    return nullptr;
  }

  Result* Type::call(Scope* scope,
                     mavka::ast::ASTNode* node,
                     std::vector<Subject*> generic_types,
                     std::vector<Subject*> args) {
    debug_print_call(this, generic_types, args);
    if (this->is_diia(scope) || this->is_structure(scope)) {
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
          return error_from_ast(
              node, "Неправильний тип аргументу параметра \"" + param->name +
                        "\": очікується \"" +
                        processed_types_result->types_string() +
                        "\", отримано \"" + arg->types_string() + "\".");
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
    return error("Неможливо отримати спеціальну властивість з типу \"" + this->get_type_name() + "\".");
  }
} // namespace typeinterpreter