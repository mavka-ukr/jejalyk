#include "compile_continue_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_continue_node(mavka::ast::ContinueNode* continue_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        // todo: handle only loops
        node_compilation_result->result = "continue";
        return node_compilation_result;
    }
}
