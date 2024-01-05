#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  bool Options::has_module(std::string path) {
    if (this->parent) {
      return this->parent->has_module(path);
    }
    return this->modules.contains(path);
  }

  void Options::set_module(std::string path, Module* module) {
    if (this->parent) {
      this->parent->set_module(path, module);
    } else {
      this->modules.insert_or_assign(path, module);
    }
  }

  Module* Options::get_module(std::string path) {
    if (this->parent) {
      return this->parent->get_module(path);
    }
    if (this->modules.contains(path)) {
      return this->modules[path];
    }
    return nullptr;
  }

  bool Options::is_extensions_allowed() const {
    return this->arg_extensions == "1";
  }

  bool Options::is_strict_mode() const {
    return this->arg_strictness == "1";
  }

  Options* Options::clone() {
    const auto options_clone = new Options();
    options_clone->parent = this;
    options_clone->main_module_path = this->main_module_path;
    options_clone->root_module_path = this->root_module_path;
    options_clone->current_module_path = this->current_module_path;
    options_clone->std_code = this->std_code;
    options_clone->args = this->args;
    options_clone->arg_extensions = this->arg_extensions;
    options_clone->arg_strictness = this->arg_strictness;
    options_clone->get_module_name = this->get_module_name;
    options_clone->get_module_path = this->get_module_path;
    options_clone->get_module_code = this->get_module_code;
    options_clone->get_pak = this->get_pak;
    return options_clone;
  }
} // namespace jejalyk::typeinterpreter