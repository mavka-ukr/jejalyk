#include "compile_each_node.h"

#include "../compile.h"
#include "compile_body.h"
#include "compile_node.h"

namespace jejalyk {

NodeCompilationResult* compile_each_node(const mavka::ast::EachNode* each_node,
                                         CompilationScope* scope,
                                         CompilationOptions* options,
                                         CompilationState* state) {
  const auto diName =
      state->put_debug(options->current_module_path, each_node->start_line,
                       each_node->start_column);
  const auto node_compilation_result = new NodeCompilationResult();
  const auto value = compile_node(each_node->value, scope, options, state);
  if (value->error) {
    node_compilation_result->error = value->error;
    return node_compilation_result;
  }
  const auto each_scope = new CompilationMicroScope();
  each_scope->parent = scope;
  each_scope->define(each_node->name, new CompilationSubject());
  if (!each_node->keyName.empty()) {
    each_scope->define(each_node->keyName, new CompilationSubject());
  }
  const auto body =
      compile_body(each_node->body, each_scope, options, state, true);
  if (body->error) {
    node_compilation_result->error = body->error;
    return node_compilation_result;
  }
  if (each_node->keyName.empty()) {
    node_compilation_result->result =
        "for(" + varname(each_node->name) + " of " + MAVKA_VALUES_ITERATOR +
        "(" + value->result + "," + diName + "))" + body->result + "";
  } else {
    node_compilation_result->result =
        "for([" + varname(each_node->keyName) + "," + varname(each_node->name) +
        "] of " + MAVKA_ENTRIES_ITERATOR + "(" + value->result + "," + diName +
        "))" + body->result + "";
  }
  return node_compilation_result;
}
}  // namespace jejalyk
