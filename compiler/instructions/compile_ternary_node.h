#ifndef COMPILE_TERNARY_NODE_H
#define COMPILE_TERNARY_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_ternary_node(const mavka::ast::TernaryNode* ternary_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);
}

#endif //COMPILE_TERNARY_NODE_H
