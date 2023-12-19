#include "compile_mockup_diia_node.h"
#include "../compile.h"

namespace jejalyk {

    NodeCompilationResult* compile_mockup_diia_node(const mavka::ast::MockupDiiaNode* mockup_diia_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_diia_node->name;
        scope->assign(name);
        return node_compilation_result;
    }
}
