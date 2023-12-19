#ifndef COMPILE_AS_NODE_H
#define COMPILE_AS_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_as_node(const mavka::ast::AsNode* as_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);
}

#endif //COMPILE_AS_NODE_H
