#include "compile_test_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_test_node(const mavka::ast::TestNode* test_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto left = compile_node(test_node->left, scope, options);
        if (left->error) {
            node_compilation_result->error = left->error;
            return node_compilation_result;
        }
        const auto right = compile_node(test_node->right, scope, options);
        if (right->error) {
            node_compilation_result->error = right->error;
            return node_compilation_result;
        }
        if (test_node->op == "і") {
            node_compilation_result->result = "(" + left->result + ")&&(" + right->result + ")";
        } else if (test_node->op == "або") {
            node_compilation_result->result = "(" + left->result + ")||(" + right->result + ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = test_node->start_line;
            node_compilation_result->error->column = test_node->start_column;
            node_compilation_result->error->message = "unsupported test operation: " + test_node->op;
        }
        return node_compilation_result;
    }
}
