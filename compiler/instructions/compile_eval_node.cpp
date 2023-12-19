#include "compile_eval_node.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* eval_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        if (!options->allow_js) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = eval_node->start_line;
            node_compilation_result->error->column = eval_node->start_column;
            node_compilation_result->error->message =
                    "JS-розширення вимкнені. Додайте опцію \"--розширення=1\", щоб увімкнути.";
            return node_compilation_result;
        }
        if (tools::instanceof<mavka::ast::StringNode>(eval_node->value)) {
            const auto string_value = dynamic_cast<mavka::ast::StringNode *>(eval_node->value)->value;
            node_compilation_result->result = "/* --- js --- */\n" + string_value + "\n/* --- /js --- */";
        } else {
            const auto eval_value = compile_node(eval_node->value, scope, options);
        }
        return node_compilation_result;
    }
}
