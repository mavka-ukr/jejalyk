#ifndef COMPILE_MOCKUP_OBJECT_NODE_H
#define COMPILE_MOCKUP_OBJECT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_mockup_object_node(const mavka::ast::MockupObjectNode* mockup_object_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);
}

#endif //COMPILE_MOCKUP_OBJECT_NODE_H
