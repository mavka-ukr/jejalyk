#ifndef COMPILE_MOCKUP_SUBJECT_NODE_H
#define COMPILE_MOCKUP_SUBJECT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_subject_node(const mavka::ast::MockupSubjectNode* mockup_subject_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);
}

#endif //COMPILE_MOCKUP_SUBJECT_NODE_H
