#ifndef COMPILE_ANON_DIIA_NODE_H
#define COMPILE_ANON_DIIA_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_anon_diia_node(
      const mavka::ast::AnonDiiaNode* anon_diia_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_ANON_DIIA_NODE_H
