#ifndef COMPILE_PRE_DECREMENT_NODE_H
#define COMPILE_PRE_DECREMENT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_pre_decrement_node(const mavka::ast::PreDecrementNode* pre_decrement_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);
}

#endif //COMPILE_PRE_DECREMENT_NODE_H
