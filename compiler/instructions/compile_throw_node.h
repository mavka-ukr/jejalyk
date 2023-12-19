#ifndef COMPILE_THROW_NODE_H
#define COMPILE_THROW_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_throw_node(const mavka::ast::ThrowNode* throw_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options);
}

#endif //COMPILE_THROW_NODE_H
