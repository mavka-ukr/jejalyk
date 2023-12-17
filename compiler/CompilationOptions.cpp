#include "CompilationOptions.h"

namespace jejalyk {
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
}
