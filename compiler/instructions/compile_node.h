#ifndef COMPILE_NODE_H
#define COMPILE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options);
}

#endif //COMPILE_NODE_H
