#ifndef COMPILE_WAIT_NODE_H
#define COMPILE_WAIT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_wait_node(const mavka::ast::WaitNode* wait_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);
}

#endif //COMPILE_WAIT_NODE_H
