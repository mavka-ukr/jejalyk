#ifndef COMPILE_MODULE_NODE_H
#define COMPILE_MODULE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_module_node(const mavka::ast::ModuleNode* module_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);
}

#endif //COMPILE_MODULE_NODE_H
