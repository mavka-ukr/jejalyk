#include "compile_mockup_subject_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_subject_node(const mavka::ast::MockupSubjectNode* mockup_subject_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_subject_node->name;
        scope->assign(name);
        return node_compilation_result;
    }
}
