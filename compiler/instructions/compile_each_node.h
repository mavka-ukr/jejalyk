#ifndef COMPILE_EACH_NODE_H
#define COMPILE_EACH_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_each_node(const mavka::ast::EachNode* each_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);
}

#endif //COMPILE_EACH_NODE_H
