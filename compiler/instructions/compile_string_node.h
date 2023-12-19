#ifndef COMPILE_STRING_NODE_H
#define COMPILE_STRING_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_string_node(const mavka::ast::StringNode* string_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);
}

#endif //COMPILE_STRING_NODE_H
