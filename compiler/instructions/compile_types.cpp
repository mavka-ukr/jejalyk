#include "compile_types.h"

#include "../../tools.h"
#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
  CompilationResult* compile_types(std::vector<mavka::ast::ASTNode*> types,
                                   CompilationScope* scope,
                                   CompilationOptions* options,
                                   CompilationState* state) {
    const auto types_compilation_result = new CompilationResult();
    std::vector<std::string> compiled_types;
    std::vector<CompilationObject*> compiled_types_values;
    for (const auto type : types) {
      const auto type_compilation_result =
          compile_node(type, scope, options, state);
      if (type_compilation_result->error) {
        types_compilation_result->error = type_compilation_result->error;
        return types_compilation_result;
      }
      compiled_types.push_back(type_compilation_result->result);
      compiled_types_values.push_back(
          type_compilation_result->subject->types[0]);
    }
    const auto subject = new CompilationSubject();
    subject->types = compiled_types_values;
    types_compilation_result->subject = subject;
    types_compilation_result->result =
        "[" + tools::implode(compiled_types, ",") + "]";
    return types_compilation_result;
  }

}  // namespace jejalyk
