#ifndef COMPILE_PRE_INCREMENT_NODE_H
#define COMPILE_PRE_INCREMENT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_pre_increment_node(const mavka::ast::PreIncrementNode* pre_increment_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);
}

#endif //COMPILE_PRE_INCREMENT_NODE_H
