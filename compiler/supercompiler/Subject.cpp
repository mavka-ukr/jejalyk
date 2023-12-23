#include "compiler.h"

namespace supercompiler {
  bool Subject::is_structure(Scope* scope) {
    if (this->types.size() == 1) {
      const auto empty_subject = scope->get("пусто");
      if (this->types[0] == empty_subject->types[0]) {
        return true;
      }
      const auto structure_structure_subject = scope->get("Структура");
      if (this->types[0] == structure_structure_subject->types[0]) {
        return true;
      }
      if (this->types[0]->generic) {
        return true;
      }
      auto structure = this->types[0]->structure;
      while (structure) {
        if (structure == structure_structure_subject->types[0]) {
          return true;
        }
        structure = structure->structure_parent;
      }
    }
    return false;
  }

  bool Subject::is_diia(Scope* scope) {
    if (this->types.size() == 1) {
      const auto diia_structure_subject = scope->get("Дія");
      if (this->types[0]->structure == diia_structure_subject->types[0]) {
        return true;
      }
    }
    return false;
  }

  Subject* Subject::create_instance() {
    const auto subject = new Subject();
    for (const auto type : this->types) {
      subject->types.push_back(type->create_instance());
    }
    return subject;
  }

  bool Subject::check_types(std::vector<Subject*> generics, Subject* value) {
    const auto newval = new Subject();
    for (const auto type : value->types) {
      if (type->generic) {
        const auto index = type->generic->index;
        const auto generic_subject = generics[index];
        for (const auto itype : generic_subject->create_instance()->types) {
          newval->types.push_back(itype);
        }
      } else {
        newval->types.push_back(type);
      }
    }
    value = newval;
    if (this->types.empty() && value->types.empty()) {
      return true;
    }
    if (this->types.empty()) {
      return true;
    }
    if (value->types.empty()) {
      return true;
    }
    for (const auto type : this->types) {
      auto structure = type->structure;
      while (structure) {
        for (const auto vtype : value->types) {
          if (vtype->structure == structure) {
            return true;
          }
        }
        structure = structure->structure_parent;
      }
    }
    return false;
  }

  bool Subject::instance_of(Subject* value) {
    auto structure = this->types[0]->structure;
    while (structure) {
      if (value->types[0] == structure) {
        return true;
      }
      structure = structure->structure_parent;
    }
    return false;
  }

  Result* Subject::call(std::vector<Subject*> generics,
                        std::vector<Subject*> args,
                        Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->call(generics, args, scope);
    }
    return error("Неможливо викликати.");
  }

  Result* Subject::call_named(std::map<std::string, Subject*> args,
                              Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->call_named(args, scope);
    }
    return error("Неможливо викликати.");
  }

  Result* Subject::set(std::string name, Subject* value) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->set(name, value);
    }
    return error("Неможливо встановити.");
  }

  Result* Subject::set_element(Subject* element, Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->set_element(element, value, scope);
    }
    return error("Неможливо встановити елемент.");
  }

  Subject* Subject::get(std::string name) {
    if (this->types.empty()) {
      return new Subject();
    }
    if (this->types.size() == 1) {
      return this->types[0]->get(name);
    }
    return nullptr;
  }

  Result* Subject::get_element(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->get_element(value, scope);
    }
    return error("Неможливо отримати елемент.");
  }

  bool Subject::has(std::string name) {
    if (this->types.empty()) {
      return true;
    }
    if (this->types.size() == 1) {
      return this->types[0]->has(name);
    }
    return false;
  }

  Result* Subject::plus(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->plus(value, scope);
    }
    return error("Неможливо додати.");
  }

  Result* Subject::minus(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->minus(value, scope);
    }
    return error("Неможливо відняти.");
  }

  Result* Subject::multiply(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->multiply(value, scope);
    }
    return error("Неможливо помножити.");
  }

  Result* Subject::divide(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->divide(value, scope);
    }
    return error("Неможливо поділити.");
  }

  Result* Subject::divdiv(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->divdiv(value, scope);
    }
    return error("Неможливо divdiv.");
  }

  Result* Subject::pow(Subject* value, Scope* scope) {
    if (this->types.empty()) {
      return success(new Subject());
    }
    if (this->types.size() == 1) {
      return this->types[0]->pow(value, scope);
    }
    return error("Неможливо піднести до степеня.");
  }

  std::string Subject::types_string(std::vector<Subject*> generics) {
    std::vector<std::string> types;
    for (const auto type : this->types) {
      if (type->structure) {
        types.push_back("\"" + type->structure->structure_name + "\"");
      } else {
        if (type->generic) {
          if (generics.size() <= type->generic->index) {
            types.push_back("\"[GENERIC BUG OUT OF INDEX]\"");
          } else {
            const auto generic_subject = generics[type->generic->index];
            types.push_back(
                generic_subject->create_instance()->types_string(generics));
          }
        } else {
          types.push_back("\"[SUBJECT WITHOUT STRUCTURE]\"");
        }
      }
    }
    return jejalyk::tools::implode(types, " або ");
  }
}