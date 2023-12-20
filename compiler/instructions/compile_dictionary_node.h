#ifndef COMPILE_DICTIONARY_NODE_H
#define COMPILE_DICTIONARY_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_dictionary_node(
      const mavka::ast::DictionaryNode* dictionary_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);

}

#endif  // COMPILE_DICTIONARY_NODE_H
