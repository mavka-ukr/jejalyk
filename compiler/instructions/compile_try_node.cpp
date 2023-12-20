#include "compile_try_node.h"

#include "../compile.h"
#include "compile_body.h"

namespace jejalyk {
NodeCompilationResult* compile_try_node(const mavka::ast::TryNode* try_node,
                                        CompilationScope* scope,
                                        CompilationOptions* options,
                                        CompilationState* state) {
  const auto node_compilation_result = new NodeCompilationResult();
  const auto try_scope = new CompilationMicroScope();
  try_scope->parent = scope;
  const auto body =
      compile_body(try_node->body, try_scope, options, state, false);
  if (body->error) {
    node_compilation_result->error = body->error;
    return node_compilation_result;
  }
  scope->assign(try_node->name, nullptr);
  const auto catch_scope = new CompilationMicroScope();
  catch_scope->parent = scope;
  const auto catch_body =
      compile_body(try_node->catch_body, catch_scope, options, state, false);
  if (catch_body->error) {
    node_compilation_result->error = catch_body->error;
    return node_compilation_result;
  }
  node_compilation_result->result = R"(
try {
)" + body->result + R"(
}catch(e){
if(e){
if(e instanceof Падіння){
e=e.значення;
}
}
)" + varname(try_node->name) + R"(=e;
)" + catch_body->result + R"(
}
)";
  return node_compilation_result;
    }
}
