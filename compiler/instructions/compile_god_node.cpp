#include "compile_god_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->error = new CompilationError();
        node_compilation_result->error->path = options->current_module_path;
        node_compilation_result->error->line = node->start_line;
        node_compilation_result->error->column = node->start_column;
        node_compilation_result->error->message = "Бог тимчасово не працює.";
        return node_compilation_result;
    }
}
