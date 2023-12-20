#include "compile_call_node.h"

#include <iostream>

#include "../../tools.h"
#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
  NodeCompilationResult* compile_call_node(
      const mavka::ast::CallNode* call_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();

    const auto value_compilation_result =
        compile_node(call_node->value, scope, options, state);
    if (value_compilation_result->error) {
      node_compilation_result->error = value_compilation_result->error;
      return node_compilation_result;
    }

    const auto compiled_args = new std::vector<std::string>();
    std::vector<CompilationSubject*> compilation_arg_subjects;
    for (const auto& arg : call_node->args) {
      const auto arg_compilation_result =
          compile_node(arg, scope, options, state);
      if (arg_compilation_result->error) {
        node_compilation_result->error = arg_compilation_result->error;
        return node_compilation_result;
      }
      compiled_args->push_back(arg_compilation_result->result);
      compilation_arg_subjects.push_back(arg_compilation_result->subject);
    }

    const auto call_result = value_compilation_result->subject->call(
        compilation_arg_subjects, scope, options);
    if (call_result->error) {
      node_compilation_result->error = call_result->error;
      return node_compilation_result;
    }

    node_compilation_result->subject = call_result->subject;

    const auto args_string = tools::implode(*compiled_args, ",");
    node_compilation_result->result = MAVKA_CALL + "(" +
                                      value_compilation_result->result + ",{" +
                                      args_string + "})";
    return node_compilation_result;
  }
}  // namespace jejalyk
