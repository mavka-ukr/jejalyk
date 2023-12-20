#include "compile_diia_body.h"

#include "../../tools.h"
#include "../compile.h"
#include "compile_body.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_diia_body(
    const std::vector<mavka::ast::ASTNode*>& body,
    const std::vector<mavka::ast::ParamNode*>& params,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state,
    const bool wrap,
    const bool parent) {
  const auto node_compilation_result = new NodeCompilationResult();
  std::vector<std::string> before;
  if (parent) {
    before.emplace_back("var м_предок=" + MAVKA_PARENT + "(м_я)");
  }
  for (int i = 0; i < params.size(); ++i) {
    const auto param = params[i];
    if (param->value) {
      const auto compiled_value =
          compile_node(param->value, scope, options, state);
      if (compiled_value->error) {
        node_compilation_result->error = compiled_value->error;
        return node_compilation_result;
      }
      before.push_back(varname(param->name) + "=args[" + std::to_string(i) +
                       "]===undefined?args[\"" + param->name +
                       "\"]===undefined?(" + compiled_value->result +
                       "):args[\"" + param->name + "\"]:args[" +
                       std::to_string(i) + "]");
    } else {
      if (param->variadic) {
        before.push_back(varname(param->name) + "=args[\"" + param->name +
                         "\"]===undefined?Object.values(args).slice(" +
                         std::to_string(i) + "):args[\"" + param->name + "\"]");
      } else {
        before.push_back(varname(param->name) + "=args[" + std::to_string(i) +
                         "]===undefined?args[\"" + param->name + "\"]:args[" +
                         std::to_string(i) + "]");
      }
    }
  }
  const auto body_compilation_result = compile_body(
      body, scope, options, state, wrap, tools::implode(before, ";\n"), true);
  if (body_compilation_result->error) {
    node_compilation_result->error = body_compilation_result->error;
    return node_compilation_result;
  }
  node_compilation_result->result = body_compilation_result->result;
  return node_compilation_result;
    }
}
