#include "compile_structure_node.h"

#include "compile_node.h"
#include "compile_structure_params.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_structure_node(const mavka::ast::StructureNode* structure_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, structure_node->start_line,
                                             structure_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        scope->assign(structure_node->name);
        const auto compiled_params = compile_structure_params(structure_node->params, scope, options);
        if (compiled_params->error) {
            node_compilation_result->error = compiled_params->error;
            return node_compilation_result;
        }
        std::string parent = "undefined";
        if (structure_node->parent) {
            const auto compiled_parent = compile_node(structure_node->parent, scope, options);
            if (compiled_parent->error) {
                node_compilation_result->error = compiled_parent->error;
                return node_compilation_result;
            }
            parent = compiled_parent->result;
        }
        node_compilation_result->result = varname(structure_node->name) + "=" + MAVKA_STRUCTURE + "(" + "\""
                                          + structure_node->name + "\"" + "," +
                                          compiled_params->result + "," + parent + "," + diName + ")";
        return node_compilation_result;
    }
}
