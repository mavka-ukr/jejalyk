#include "compile_structure_params.h"

#include "../../tools.h"
#include "../compile.h"
#include "compile_node.h"
#include "compile_types.h"

namespace jejalyk {
  StructureParamsCompilationResult* compile_structure_params(
      const std::vector<mavka::ast::StructureParamNode*>& params,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new StructureParamsCompilationResult();
    std::vector<std::string> compiled_params;
    for (int i = 0; i < params.size(); ++i) {
      const auto param = params[i];
      const auto param_name = param->name;
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
      const auto compilation_object_structure_param =
          new CompilationObjectStructureParam();
      compilation_object_structure_param->index = i;
      compilation_object_structure_param->name = param_name;
      compilation_object_structure_param->subject =
          type_compilation_result->subject;
      compilation_object_structure_param->value =
          value_compilation_result->subject;
      node_compilation_result->structure_params.push_back(
          compilation_object_structure_param);
      std::string param_string = MAVKA_PARAM + "(" + "\"" + param_name + "\"";
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
