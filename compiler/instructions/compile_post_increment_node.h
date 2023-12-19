#ifndef COMPILE_POST_INCREMENT_NODE_H
#define COMPILE_POST_INCREMENT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_post_increment_node(const mavka::ast::PostIncrementNode* post_increment_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);
}

#endif //COMPILE_POST_INCREMENT_NODE_H
