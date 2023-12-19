#include "compile_from_to_complex_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_from_to_complex_node(
          const mavka::ast::FromToComplexNode* from_to_complex_node,
          CompilationScope* scope,
          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto from = compile_node(from_to_complex_node->from, scope, options);
        if (from->error) {
            node_compilation_result->error = from->error;
            return node_compilation_result;
        }
        const auto to = compile_node(from_to_complex_node->to, scope, options);
        if (to->error) {
            node_compilation_result->error = to->error;
            return node_compilation_result;
        }
        const auto step = compile_node(from_to_complex_node->step, scope, options);
        if (step->error) {
            node_compilation_result->error = step->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_FROM_TO + "(" + from->result + "," + to->result + ",\"" +
                                          from_to_complex_node->toSymbol + "\"," + MAVKA_FROM_TO_FN + "(\"" +
                                          from_to_complex_node->stepSymbol + "\"," + step->result + "))";
        return node_compilation_result;
    }

}
