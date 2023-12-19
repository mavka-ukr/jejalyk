#ifndef COMPILE_BITWISE_NODE_H
#define COMPILE_BITWISE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_bitwise_node(const mavka::ast::BitwiseNode* bitwise_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);
}

#endif //COMPILE_BITWISE_NODE_H
