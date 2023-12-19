#include "compile_call_node.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_call_node(const mavka::ast::CallNode* call_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, call_node->start_line,
                                             call_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(call_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        const auto args = new std::vector<std::string>();
        for (const auto& arg: call_node->args) {
            const auto arg_compilation_result = compile_node(arg, scope, options);
            if (arg_compilation_result->error) {
                node_compilation_result->error = arg_compilation_result->error;
                return node_compilation_result;
            }
            args->push_back(arg_compilation_result->result);
        }
        const auto args_string = tools::implode(*args, ",");
        node_compilation_result->result = MAVKA_CALL + "(" + value->result + ",{" + args_string + "}," + diName + ")";
        return node_compilation_result;
    }
}
