#ifndef COMPILE_CALL_NODE_H
#define COMPILE_CALL_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_call_node(const mavka::ast::CallNode* call_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);
}

#endif //COMPILE_CALL_NODE_H
