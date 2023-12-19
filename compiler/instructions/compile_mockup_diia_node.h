#ifndef COMPILE_MOCKUP_DIIA_NODE_H
#define COMPILE_MOCKUP_DIIA_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_mockup_diia_node(const mavka::ast::MockupDiiaNode* mockup_diia_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);
}

#endif //COMPILE_MOCKUP_DIIA_NODE_H
