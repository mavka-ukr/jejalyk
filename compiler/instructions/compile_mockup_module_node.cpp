#include "compile_mockup_module_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_module_node(const mavka::ast::MockupModuleNode* mockup_module_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_module_node->name;
        scope->assign(name);
        return node_compilation_result;
    }
}
