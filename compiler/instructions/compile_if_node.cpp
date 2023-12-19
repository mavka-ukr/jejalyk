#include "compile_if_node.h"

#include "compile_body.h"
#include "compile_node.h"
#include "../compile.h"

namespace jejalyk {
    NodeCompilationResult* compile_if_node(const mavka::ast::IfNode* if_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(if_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto if_scope = new CompilationMicroScope();
        if_scope->parent = scope;
        const auto body = compile_body(if_node->body, if_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        if (!if_node->else_body.empty()) {
            const auto else_if_scope = new CompilationMicroScope();
            else_if_scope->parent = scope;
            const auto else_body = compile_body(if_node->else_body, else_if_scope, options, true);
            if (else_body->error) {
                node_compilation_result->error = else_body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "if(" + condition->result + ")" + body->result + "else" + else_body->
                                              result + "";
        } else {
            node_compilation_result->result = "if(" + condition->result + ")" + body->result + "";
        }
        return node_compilation_result;
    }
}
