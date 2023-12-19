#ifndef COMPILE_TAKE_PAK_NODE_H
#define COMPILE_TAKE_PAK_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_take_pak_node(const mavka::ast::TakePakNode* take_pak_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);
}

#endif //COMPILE_TAKE_PAK_NODE_H
