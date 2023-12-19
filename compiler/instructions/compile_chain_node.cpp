#include "compile_chain_node.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_chain_node(const mavka::ast::ChainNode* chain_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, chain_node->start_line,
                                             chain_node->start_column);

        const auto node_compilation_result = new NodeCompilationResult();
        const auto left = compile_node(chain_node->left, scope, options);
        if (left->error) {
            node_compilation_result->error = left->error;
            return node_compilation_result;
        }
        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(chain_node->right)) {
            const auto right = dynamic_cast<mavka::ast::IdentifierNode *>(chain_node->right)->name;
            node_compilation_result->result = MAVKA_GET + "(" + left->result + ",\"" + right + "\",null," + diName +
                                              ")";
        } else {
            const auto right = compile_node(chain_node->right, scope, options);
            if (right->error) {
                node_compilation_result->error = right->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_GET + "(" + left->result + "," + right->result + ",null," + diName +
                                              ")";
        }
        return node_compilation_result;
    }
}
