#include "compile_params.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
                                          CompilationScope* scope,
                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_params;
        for (int i = 0; i < params.size(); ++i) {
            const auto param = params[i];
            const auto param_name = param->name;
            scope->assign(param_name);
            std::string compiled_param_type = "undefined";
            std::string compiled_param_value = "undefined";
            // todo: handle type
            std::string param_string = (param->variadic ? MAVKA_VPARAM : MAVKA_PARAM) + "(" + "\"" + param_name + "\"";
            if (compiled_param_type != "undefined") {
                param_string += "," + compiled_param_type;
            }
            if (compiled_param_value != "undefined") {
                param_string += "," + compiled_param_value;
            }
            compiled_params.push_back(param_string + ")");
        }
        node_compilation_result->result = "[" + tools::implode(compiled_params, ",") + "]";
        return node_compilation_result;
    }
}
