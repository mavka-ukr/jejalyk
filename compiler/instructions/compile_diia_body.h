#ifndef COMPILE_DIIA_BODY_H
#define COMPILE_DIIA_BODY_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_diia_body(
      const std::vector<mavka::ast::ASTNode*>& body,
      const std::vector<mavka::ast::ParamNode*>& params,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state,
      const bool wrap = true,
      const bool parent = false);

}

#endif  // COMPILE_DIIA_BODY_H
