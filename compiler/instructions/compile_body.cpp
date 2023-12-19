#include "compile_body.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
NodeCompilationResult* compile_body(const std::vector<mavka::ast::ASTNode *>& body,
                                        CompilationScope* scope,
                                        CompilationOptions* options,
                                        const bool wrap,
                                        const std::string& before,
                                        const bool handle_return) {
        const auto options_clone = options->clone();
        options_clone->body_depth = options->body_depth + 1;
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_body;
        size_t i = 0;
        for (const auto node: body) {
            if (i == body.size() - 1 && handle_return) {
                if (!tools::instanceof<mavka::ast::ReturnNode>(node) &&
                    !tools::instanceof<mavka::ast::EachNode>(node) &&
                    !tools::instanceof<mavka::ast::WhileNode>(node) &&
                    !tools::instanceof<mavka::ast::IfNode>(node) &&
                    !tools::instanceof<mavka::ast::BreakNode>(node) &&
                    !tools::instanceof<mavka::ast::ContinueNode>(node)
                ) {
                    const auto node_compilation_result = compile_node(node, scope, options_clone);
                    if (node_compilation_result->error) {
                        node_compilation_result->error = node_compilation_result->error;
                        return node_compilation_result;
                    }
                    if (node_compilation_result->result.empty()) {
                        continue;
                    }
                    compiled_body.push_back("return " + node_compilation_result->result);
                    break;
                }
            }
            const auto item_node_compilation_result = compile_node(node, scope, options_clone);
            if (item_node_compilation_result->error) {
                item_node_compilation_result->error = item_node_compilation_result->error;
                return item_node_compilation_result;
            }
            if (item_node_compilation_result->result.empty()) {
                continue;
            }
            compiled_body.push_back(item_node_compilation_result->result);
            i++;
        }
        if (!before.empty()) {
            compiled_body.insert(compiled_body.begin(), before);
        }
        std::vector<std::string> vars;
        for (auto subject: scope->subjects) {
            if (subject.first == "я") {
                continue;
            }
            if (subject.first == "предок") {
                continue;
            }
            vars.push_back(varname(subject.first));
        }
        if (!vars.empty()) {
            compiled_body.insert(compiled_body.begin(), "var " + tools::implode(vars, ","));
        }
        const auto prefix = tools::repeat_string("  ", options->body_depth);
        const auto prefix_pre = tools::repeat_string("  ", options->body_depth - 1);
        node_compilation_result->result = (wrap ? "{\n" : "") + tools::implode_with_prefix(compiled_body, ";\n", prefix)
                                          + ";\n" +
                                          (wrap ? (prefix_pre + "}") : "");
        return node_compilation_result;
    }
}
