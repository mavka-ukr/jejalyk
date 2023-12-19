#ifndef COMPILE_DIIA_NODE_H
#define COMPILE_DIIA_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_diia_node(const mavka::ast::DiiaNode* diia_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);
}

#endif //COMPILE_DIIA_NODE_H
