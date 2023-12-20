#ifndef COMPILE_TAKE_MODULE_NODE_H
#define COMPILE_TAKE_MODULE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_take_module_node(
      const mavka::ast::TakeModuleNode* take_module_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_TAKE_MODULE_NODE_H