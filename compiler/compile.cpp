#include "compile.h"

#include "../ast.h"
#include "../parser.h"

namespace jejalyk {
  std::string varname(const std::string& name) {
    return "м_" + name;
  }

  bool CompilationState::has_module(const std::string& name) {
    return modules.contains(name);
  }

  std::string CompilationState::get_module(const std::string& name) {
    return modules.find(name)->second;
  }

  void CompilationState::set_module(const std::string& name, std::string code) {
    modules.insert_or_assign(name, code);
  }

  std::string CompilationState::put_debug(const std::string& path,
                                          const size_t& line,
                                          const size_t& column) {
    if (!store_debug) {
      return "";
    }
    const auto debug_id = std::to_string(debug.size());
    const auto debug_name = "DI" + debug_id;
    debug[debug_name] = "\"" + path + ":" + std::to_string(line) + ":" +
                        std::to_string(column) + "\"";
    return debug_name;
  }

  CompilationError* CompilationScope::define(const std::string& name,
                                             CompilationSubject* subject) {
    subjects.insert_or_assign(name, subject);
    return nullptr;
  }

  CompilationError* CompilationScope::assign(const std::string& name,
                                             CompilationSubject* subject) {
    if (!has_local(name)) {
      return compilation_error_from_message(
          "[BUG] Неможливо перевизначити субʼєкт \"" + name + "\".");
    }
    const auto local_subject = get_local(name);
    if (!local_subject->can_set(subject)) {
      return compilation_error_from_message(
          "Неможливо перевизначити субʼєкт \"" + name + "\".");
    }
    subjects.insert_or_assign(name, subject);
    return nullptr;
  }

  CompilationSubject* CompilationScope::get_local(
      const std::string& name) const {
    const auto subject_it = subjects.find(name);
    if (subject_it != subjects.end()) {
      return subject_it->second;
    }
    return nullptr;
  }

  bool CompilationScope::has_local(const std::string& name) const {
    const auto subject_it = subjects.find(name);
    if (subject_it != subjects.end()) {
      return true;
    }
    return false;
  }

  CompilationSubject* CompilationScope::get(const std::string& name) const {
    if (const auto subject = get_local(name)) {
      return subject;
    }
    if (parent) {
      return parent->get(name);
    }
    return nullptr;
  }

  bool CompilationScope::has(const std::string& name) const {
    if (has_local(name)) {
      return true;
    }
    if (parent) {
      return parent->has(name);
    }
    return false;
  }

  CompilationScope* CompilationScope::root() {
    if (parent) {
      return parent->root();
    }
    return this;
  }

  CompilationError* CompilationMicroScope::assign(const std::string& name,
                                                  CompilationSubject* subject) {
    return parent->assign(name, subject);
  }

  CompilationSubject* CompilationMicroScope::get(
      const std::string& name) const {
    return parent->get(name);
  }

  CompilationSubject* CompilationMicroScope::get_local(
      const std::string& name) const {
    return parent->get_local(name);
  }

  bool CompilationMicroScope::has_local(const std::string& name) const {
    return parent->has_local(name);
  }

  bool CompilationMicroScope::has(const std::string& name) const {
    return parent->has(name);
  }

  CompilationScope* CompilationMicroScope::root() {
    return parent->root();
  }

  bool CompilationSubject::can_set(CompilationSubject* subject) {
    return true;
  }

  NodeCompilationResult* CompilationObject::get(std::string name,
                                                CompilationScope* scope,
                                                CompilationOptions* options) {
    if (this->properties.contains(name)) {
      const auto p = this->properties.find(name)->second;
      const auto node_compilation_result = new NodeCompilationResult();
      node_compilation_result->subject = p;
      return node_compilation_result;
    }
    const auto node_compilation_result = new NodeCompilationResult();
    node_compilation_result->error = new CompilationError();
    node_compilation_result->error->message =
        "Неможливо отримати властивість \"" + name + "\".";
    return node_compilation_result;
  }

  NodeCompilationResult* CompilationObject::call(
      std::vector<CompilationSubject*> args,
      CompilationScope* scope,
      CompilationOptions* options) {
    const auto node_compilation_result = new NodeCompilationResult();
    if (this->is_diia()) {
      for (const auto& diia_param : this->diia_params) {
        if (diia_param->index >= args.size()) {
          node_compilation_result->error = new CompilationError();
          node_compilation_result->error->message =
              "Неможливо викликати дію, не вистачає аргументів.";
          return node_compilation_result;
        }
        const auto arg = args[diia_param->index];
        if (!arg) {
          node_compilation_result->error = new CompilationError();
          node_compilation_result->error->message =
              "[BUG] Неможливо викликати дію.";
          return node_compilation_result;
        }
        if (diia_param->subject) {
          if (!arg->is_subject(diia_param->subject)) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->message =
                "Неможливо викликати дію.";
            return node_compilation_result;
          }
        }
      }
    } else {
      const auto diia = this->get("чародія_викликати", scope, options);
      if (diia->error) {
        node_compilation_result->error = diia->error;
        return node_compilation_result;
      }
      const auto call_result = diia->subject->call(args, scope, options);
      if (call_result->error) {
        node_compilation_result->error = call_result->error;
        return node_compilation_result;
      }
      node_compilation_result->subject = call_result->subject;
    }
    return node_compilation_result;
  }

  bool CompilationObject::is(CompilationObject* object) {
    CompilationObject* structure = this->structure;
    while (structure) {
      if (structure == object) {
        return true;
      }
      structure = structure->structure_parent;
    }
    return false;
  }

  bool CompilationObject::is_subject(CompilationSubject* subject) {
    for (auto const type : subject->types) {
      if (this->is(type)) {
        return true;
      }
    }
    return false;
  }

  CompilationObject* CompilationObject::create_instance() {
    const auto instance = new CompilationObject();
    instance->type = CompilationObject::OBJECT;
    instance->structure = this;
    return instance;
  }

  NodeCompilationResult* CompilationSubject::call(
      std::vector<CompilationSubject*> args,
      CompilationScope* scope,
      CompilationOptions* options) {
    const auto node_compilation_result = new NodeCompilationResult();
    if (types.size() == 1) {
      const auto type = types[0];
      return type->call(args, scope, options);
    } else {
      node_compilation_result->error = new CompilationError();
      node_compilation_result->error->message =
          "Неможливо викликати субʼєкт з декількох типів.";
      return node_compilation_result;
    }
    return node_compilation_result;
  }

  bool CompilationSubject::is_subject(CompilationSubject* subject) {
    for (const auto type : this->types) {
      if (type->is_subject(subject)) {
        return true;
      }
    }
    return false;
  }

  CompilationOptions* CompilationOptions::clone() {
    const auto clone = new CompilationOptions();
    clone->parent = this;
    clone->root_module_path = root_module_path;
    clone->current_module_path = current_module_path;
    clone->std_code = std_code;
    clone->body_depth = body_depth;
    clone->allow_js = allow_js;
    clone->get_module_name = get_module_name;
    clone->get_module_path = get_module_path;
    clone->get_module_code = get_module_code;
    clone->get_remote_module_name = get_remote_module_name;
    clone->get_remote_module_path = get_remote_module_path;
    clone->get_remote_module_code = get_remote_module_code;
    return clone;
  }
}  // namespace jejalyk
