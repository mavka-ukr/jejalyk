#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Options* Options::clone() {
    const auto options_clone = new Options();
    options_clone->parent = this;
    options_clone->root_module_path = this->root_module_path;
    options_clone->current_module_path = this->current_module_path;
    options_clone->std_code = this->std_code;
    options_clone->args = this->args;
    options_clone->allow_js = this->allow_js;
    options_clone->get_module_name = this->get_module_name;
    options_clone->get_module_path = this->get_module_path;
    options_clone->get_module_code = this->get_module_code;
    options_clone->get_remote_module_name = this->get_remote_module_name;
    options_clone->get_remote_module_path = this->get_remote_module_path;
    options_clone->get_remote_module_code = this->get_remote_module_code;
    return options_clone;
  }
} // namespace typeinterpreter