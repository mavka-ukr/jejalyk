#include "compile_types.h"
#include "../compile.h"

namespace jejalyk {

    // TypesCompilationResult* compile_types(std::vector<mavka::ast::ASTNode *> types,
    //                                              CompilationScope* scope,
    //                                              CompilationOptions* options) {
    //     const auto types_compilation_result = new TypesCompilationResult();
    //     std::vector<std::string> compiled_types;
    //     std::vector<CompilationType *> compiled_types_values;
    //     for (int i = 0; i < types.size(); ++i) {
    //         const auto type = types[i];
    //         const auto type_compilation_result = compile_node(type, scope, options);
    //         if (type_compilation_result->error) {
    //             types_compilation_result->error = type_compilation_result->error;
    //             return types_compilation_result;
    //         }
    //         compiled_types.push_back(type_compilation_result->result);
    //         // compiled_types_values.push_back(type_compilation_result->type);
    //     }
    //     types_compilation_result->types = compiled_types_values;
    //     types_compilation_result->result = "[" + tools::implode(compiled_types, ",") + "]";
    //     return types_compilation_result;
    // }

}
