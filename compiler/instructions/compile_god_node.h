#ifndef COMPILE_GOD_NODE_H
#define COMPILE_GOD_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);
}

#endif //COMPILE_GOD_NODE_H
