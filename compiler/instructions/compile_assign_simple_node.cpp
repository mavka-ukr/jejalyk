#include "compile_assign_simple_node.h"

#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_assign_simple_node(const mavka::ast::AssignSimpleNode* assign_simple_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        if (assign_simple_node->op == "=") {
            const auto node_compilation_result = new NodeCompilationResult();
            const auto assign_name = assign_simple_node->name;
            const auto compiled_assign_value = compile_node(assign_simple_node->value, scope, options);
            if (compiled_assign_value->error) {
                node_compilation_result->error = compiled_assign_value->error;
                return node_compilation_result;
            }
            if (const auto assign_error = scope->assign(assign_name)) {
                node_compilation_result->error = assign_error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(assign_name) + "=" + compiled_assign_value->result;
            return node_compilation_result;
        } else {
            auto operation = assign_simple_node->op;
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
            const auto new_assign_simple_node = new mavka::ast::AssignSimpleNode();
            new_assign_simple_node->name = assign_simple_node->name;
            new_assign_simple_node->op = "=";
            const auto arithmetic_node = new mavka::ast::ArithmeticNode();
            const auto identifier_node = new mavka::ast::IdentifierNode();
            identifier_node->name = assign_simple_node->name;
            arithmetic_node->left = identifier_node;
            arithmetic_node->right = assign_simple_node->value;
            arithmetic_node->op = operation;
            new_assign_simple_node->value = arithmetic_node;
            return compile_assign_simple_node(new_assign_simple_node, scope, options);
        }
    }
}
