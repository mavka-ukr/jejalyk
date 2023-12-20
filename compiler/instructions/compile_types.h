#ifndef COMPILE_TYPES_H
#define COMPILE_TYPES_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  CompilationResult* compile_types(std::vector<mavka::ast::ASTNode*> types,
                                   CompilationScope* scope,
                                   CompilationOptions* options,
                                   CompilationState* state);
}

#endif  // COMPILE_TYPES_H
