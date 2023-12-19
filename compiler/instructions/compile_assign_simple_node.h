#ifndef COMPILE_ASSIGN_SIMPLE_NODE_H
#define COMPILE_ASSIGN_SIMPLE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_assign_simple_node(const mavka::ast::AssignSimpleNode* assign_simple_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);
}

#endif //COMPILE_ASSIGN_SIMPLE_NODE_H
