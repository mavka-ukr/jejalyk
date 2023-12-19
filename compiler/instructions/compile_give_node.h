#ifndef COMPILE_GIVE_NODE_H
#define COMPILE_GIVE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_give_node(const mavka::ast::GiveNode* give_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);
}

#endif //COMPILE_GIVE_NODE_H
