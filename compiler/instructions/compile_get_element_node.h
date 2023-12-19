#ifndef COMPILE_GET_ELEMENT_NODE_H
#define COMPILE_GET_ELEMENT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_get_element_node(const mavka::ast::GetElementNode* get_element_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);
}

#endif //COMPILE_GET_ELEMENT_NODE_H
