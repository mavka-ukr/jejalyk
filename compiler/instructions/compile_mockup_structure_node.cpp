#include "compile_mockup_structure_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_structure_node(const mavka::ast::MockupStructureNode* mockup_structure,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_structure->name;
        scope->assign(name);
        return node_compilation_result;
    }

}
