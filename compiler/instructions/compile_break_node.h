#ifndef COMPILE_BREAK_NODE_H
#define COMPILE_BREAK_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_break_node(const mavka::ast::BreakNode* break_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);
}

#endif //COMPILE_BREAK_NODE_H
