#ifndef COMPILE_TRY_NODE_H
#define COMPILE_TRY_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_try_node(const mavka::ast::TryNode* try_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);
}

#endif //COMPILE_TRY_NODE_H
