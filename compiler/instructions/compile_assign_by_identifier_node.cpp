#include "compile_assign_by_identifier_node.h"
#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_assign_by_identifier_node(
        const mavka::ast::AssignByIdentifierNode* assign_by_identifier_node,
        CompilationScope* scope,
        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, assign_by_identifier_node->start_line,
                                             assign_by_identifier_node->start_column);
        if (assign_by_identifier_node->op == "=") {
            const auto node_compilation_result = new NodeCompilationResult();
            const auto assign_left = compile_node(assign_by_identifier_node->left, scope, options);
            if (assign_left->error) {
                node_compilation_result->error = assign_left->error;
                return node_compilation_result;
            }
            const auto assign_value = compile_node(assign_by_identifier_node->value, scope, options);
            if (assign_value->error) {
                node_compilation_result->error = assign_value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_SET + "(" + assign_left->result + ",\"" +
                                              assign_by_identifier_node->identifier + "\"," + assign_value->result +
                                              "," + diName + ")";
            return node_compilation_result;
        } else {
            auto operation = assign_by_identifier_node->op;
            if (operation == "+=") {
                operation = "+";
            }
            if (operation == "-=") {
                operation = "-";
            }
            if (operation == "*=") {
                operation = "*";
            }
            if (operation == "/=") {
                operation = "/";
            }
            if (operation == "%=") {
                operation = "%";
            }
            if (operation == "//=") {
                operation = "//";
            }
            if (operation == "**=") {
                operation = "**";
            }
            const auto new_assign_by_identifier_node = new mavka::ast::AssignByIdentifierNode();
            new_assign_by_identifier_node->left = assign_by_identifier_node->left;
            new_assign_by_identifier_node->identifier = assign_by_identifier_node->identifier;
            new_assign_by_identifier_node->op = "=";
            const auto arithmetic_node = new mavka::ast::ArithmeticNode();
            const auto chain_node = new mavka::ast::ChainNode();
            chain_node->left = assign_by_identifier_node->left;
            const auto identifier_node = new mavka::ast::IdentifierNode();
            identifier_node->name = assign_by_identifier_node->identifier;
            chain_node->right = identifier_node;
            arithmetic_node->left = chain_node;
            arithmetic_node->right = assign_by_identifier_node->value;
            arithmetic_node->op = operation;
            new_assign_by_identifier_node->value = arithmetic_node;
            return compile_assign_by_identifier_node(new_assign_by_identifier_node, scope, options);
        }
    }
}
