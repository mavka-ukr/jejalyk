#include "compile_each_node.h"

#include "compile_body.h"
#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_each_node(const mavka::ast::EachNode* each_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, each_node->start_line,
                                             each_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(each_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        const auto each_scope = new CompilationMicroScope();
        each_scope->parent = scope;
        each_scope->assign(each_node->name);
        if (!each_node->keyName.empty()) {
            each_scope->assign(each_node->keyName);
        }
        const auto body = compile_body(each_node->body, each_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        if (each_node->keyName.empty()) {
            node_compilation_result->result =
                    "for(" + varname(each_node->name) + " of " + MAVKA_VALUES_ITERATOR + "(" + value->result
                    + "," + diName + "))" + body->result + "";
        } else {
            node_compilation_result->result =
                    "for([" + varname(each_node->keyName) + "," + varname(each_node->name) +
                    "] of " + MAVKA_ENTRIES_ITERATOR + "(" + value->result
                    + "," + diName + "))" + body->result + "";
        }
        return node_compilation_result;
    }
}
