#ifndef COMPILE_PARAMS_H
#define COMPILE_PARAMS_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  DiiaParamsCompilationResult* compile_params(
      std::vector<mavka::ast::ParamNode*> params,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);

}

#endif  // COMPILE_PARAMS_H
