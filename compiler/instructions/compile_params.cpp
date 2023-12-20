#include "compile_params.h"

#include "../../tools.h"
#include "../compile.h"
#include "compile_node.h"
#include "compile_types.h"

namespace jejalyk {
  DiiaParamsCompilationResult* compile_params(
      std::vector<mavka::ast::ParamNode*> params,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new DiiaParamsCompilationResult();
    std::vector<std::string> compiled_params;
    for (int i = 0; i < params.size(); ++i) {
      const auto param = params[i];
      const auto param_name = param->name;
      scope->define(param_name, new CompilationSubject());
      std::string compiled_param_type = "undefined";
      std::string compiled_param_value = "undefined";
      const auto type_compilation_result =
          compile_types(param->types, scope, options, state);
      if (type_compilation_result->error) {
        node_compilation_result->error = type_compilation_result->error;
        return node_compilation_result;
      }
      const auto value_compilation_result =
          compile_node(param->value, scope, options, state);
      if (value_compilation_result->error) {
        node_compilation_result->error = value_compilation_result->error;
        return node_compilation_result;
      }
      const auto compilation_object_diia_param =
          new CompilationObjectDiiaParam();
      compilation_object_diia_param->index = i;
      compilation_object_diia_param->name = param_name;
      compilation_object_diia_param->subject = type_compilation_result->subject;
      compilation_object_diia_param->value = value_compilation_result->subject;
      compilation_object_diia_param->variadic = param->variadic;
      node_compilation_result->diia_params.push_back(
          compilation_object_diia_param);
      std::string param_string =
          (param->variadic ? MAVKA_VPARAM : MAVKA_PARAM) + "(" + "\"" +
          param_name + "\"";
      if (compiled_param_type != "undefined") {
        param_string += "," + compiled_param_type;
      }
      if (compiled_param_value != "undefined") {
        param_string += "," + compiled_param_value;
      }
      compiled_params.push_back(param_string + ")");
    }
    node_compilation_result->result =
        "[" + tools::implode(compiled_params, ",") + "]";
    return node_compilation_result;
  }
}  // namespace jejalyk
