#include "compile_mockup_object_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_object_node(const mavka::ast::MockupObjectNode* mockup_object_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_object_node->name;
        scope->assign(name);
        return node_compilation_result;
    }
}
