#ifndef COMPILE_COMPARISON_NODE_H
#define COMPILE_COMPARISON_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_comparison_node(const mavka::ast::ComparisonNode* comparison_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);
}

#endif //COMPILE_COMPARISON_NODE_H
