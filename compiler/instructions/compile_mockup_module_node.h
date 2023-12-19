#ifndef COMPILE_MOCKUP_MODULE_NODE_H
#define COMPILE_MOCKUP_MODULE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_mockup_module_node(const mavka::ast::MockupModuleNode* mockup_module_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);
}

#endif //COMPILE_MOCKUP_MODULE_NODE_H
