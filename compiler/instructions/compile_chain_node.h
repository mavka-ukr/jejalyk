#ifndef COMPILE_CHAIN_NODE_H
#define COMPILE_CHAIN_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_chain_node(const mavka::ast::ChainNode* chain_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);
}

#endif //COMPILE_CHAIN_NODE_H
