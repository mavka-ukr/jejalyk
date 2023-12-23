#include "compiler.h"

namespace supercompiler {
  Object* Object::create_instance() {
    const auto instance = new Object();
    instance->structure = this;
    for (const auto param : this->structure_params) {
      // instance->properties.insert_or_assign(param->name, param->types);
    }
    for (const auto method : this->structure_methods) {
      // instance->properties.insert_or_assign(method.first, method.second);
    }
    return instance;
  }

  Subject* Object::get(std::string name) {
    for (const auto prop : this->properties) {
      if (prop.first == name) {
        return prop.second;
      }
    }
    for (const auto param : this->structure->structure_params) {
      if (param->name == name) {
        return param->types;
      }
    }
    for (const auto method : this->structure->structure_methods) {
      if (method.first == name) {
        return method.second;
      }
    }
    return nullptr;
  }

  Result* Object::set(std::string name, Subject* value) {
    if (!this->has(name)) {
      return error("Властивість \"" + name + "\" не визначено для \"" +
                   this->structure->structure_name + "\".");
    }
    const auto property_subject = this->get(name);
    if (!value->check_types(property_subject)) {
      const auto error_result = new Result();
      error_result->error = new Error();
      error_result->error->message =
          "Значення властивості \"" + name + "\" не відповідає її типу.";
      return error_result;
    }
    return success(value);
  }

  Result* Object::set_element(Subject* element, Subject* value, Scope* scope) {
    if (!this->has("чародія_покласти")) {
      return error("unsupported set element");
    }
    return this->get("чародія_покласти")->call({}, {element, value}, scope);
  }

  bool Object::has(std::string name) {
    for (const auto prop : this->properties) {
      if (prop.first == name) {
        return true;
      }
    }
    for (const auto param : this->structure->structure_params) {
      if (param->name == name) {
        return true;
      }
    }
    for (const auto method : this->structure->structure_methods) {
      if (method.first == name) {
        return true;
      }
    }
    return false;
  }

  Result* Object::call(std::vector<Subject*> generics,
                       std::vector<Subject*> args,
                       Scope* scope) {
    if (this->has("чародія_викликати")) {
      if (const auto magic_diia = this->get("чародія_викликати")) {
        return magic_diia->call(generics, args, scope);
      }
    }
    if (this->is_diia(scope)) {
      if (generics.size() < this->diia_generics.size()) {
        return error("Недостаня кількість аргументів узагальнення.");
      }
      if (generics.size() > this->diia_generics.size()) {
        return error("Забагато аргументів узагальнення.");
      }
      if (args.size() > this->diia_params.size()) {
        if (this->diia_params.empty() ||
            !this->diia_params[this->diia_params.size() - 1]->variadic) {
          return error("Забагато аргументів.");
        }
      }
      for (const auto param : this->diia_params) {
        if (param->variadic) {
          break;
        }
        if (args.size() > param->index) {
          const auto arg = args[param->index];
          if (!arg->check_types(param->types)) {
            return error("Аргумент \"" + param->name +
                         "\" не відповідає його типу: очікується " +
                         param->types->types_string() + ", отримано " +
                         arg->types_string() + ".");
          }
        } else {
          if (param->value) {
            continue;
          }

          return error("Недостатня кількість аргументів.");
        }
      }
      return success(this->diia_return);
    }
    std::cout << this->properties.size() << std::endl;
    return error("Неможливо викликати \"" + this->structure->structure_name +
                 "\".");
  }

  Result* Object::call_named(std::map<std::string, Subject*> args,
                             Scope* scope) {
    if (this->has("чародія_викликати")) {
      if (const auto magic_diia = this->get("чародія_викликати")) {
        return magic_diia->call_named(args, scope);
      }
    }
    if (this->is_diia(scope)) {
      for (const auto param : this->diia_params) {
        if (!args.contains(param->name)) {
          if (!param->value) {
            return error("Аргумент \"" + param->name + "\" не вказано.");
          }
        }
        const auto arg = args[param->name];
        if (!arg->check_types(param->types)) {
          return error("Аргумент \"" + param->name +
                       "\" не відповідає його типу.");
        }
      }
      return success(this->diia_return);
    }
    return error("Неможливо викликати \"" + this->structure->structure_name +
                 "\".");
  }

  Result* Object::get_element(Subject* value, Scope* scope) {
    if (!this->has("чародія_отримати")) {
      return error("unsupported get element");
    }
    return this->get("чародія_отримати")->call({}, {value}, scope);
  }

  bool Object::is_diia(Scope* scope) {
    return this->structure == scope->get("Дія")->types[0];
  }

  Result* Object::plus(Subject* value, Scope* scope) {
    if (this->has("чародія_додати")) {
      return this->get("чародія_додати")->call({}, {value}, scope);
    }
    return error("Чародію додавання для \"" + this->structure->structure_name +
                 "\" не визначено.");
  }

  Result* Object::minus(Subject* value, Scope* scope) {
    if (this->has("чародія_відняти")) {
      return this->get("чародія_відняти")->call({}, {value}, scope);
    }
    return error("Неможливо відняти \"" + this->structure->structure_name +
                 "\" і " + value->types_string() + ".");
  }

  Result* Object::multiply(Subject* value, Scope* scope) {
    if (this->has("чародія_помножити")) {
      return this->get("чародія_помножити")->call({}, {value}, scope);
    }
    return error("Неможливо помножити \"" + this->structure->structure_name +
                 "\" і " + value->types_string() + ".");
  }

  Result* Object::divide(Subject* value, Scope* scope) {
    if (this->has("чародія_поділити")) {
      return this->get("чародія_поділити")->call({}, {value}, scope);
    }
    return error("Неможливо поділити \"" + this->structure->structure_name +
                 "\" і " + value->types_string() + ".");
  }

  Result* Object::divdiv(Subject* value, Scope* scope) {
    if (this->has("чародія_поділити_за_модулем_частка")) {
      return this->get("чародія_поділити_за_модулем_частка")
          ->call({},{value}, scope);
    }
    return error("Неможливо чародія_поділити_за_модулем_частка \"" +
                 this->structure->structure_name + "\" і " +
                 value->types_string() + ".");
  }

  Result* Object::pow(Subject* value, Scope* scope) {
    if (this->has("чародія_піднести_до_степеня")) {
      return this->get("чародія_піднести_до_степеня")->call({},{value}, scope);
    }
    return error("Неможливо чародія_піднести_до_степеня \"" +
                 this->structure->structure_name + "\" і " +
                 value->types_string() + ".");
  }
}