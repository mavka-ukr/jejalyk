#ifndef COMPILE_NEGATIVE_NODE_H
#define COMPILE_NEGATIVE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_negative_node(const mavka::ast::NegativeNode* negative_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);
}

#endif //COMPILE_NEGATIVE_NODE_H
