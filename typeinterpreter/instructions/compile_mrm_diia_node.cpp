#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mrm_diia_node(Scope* scope,
                                mavka::ast::MRMDiiaNode* mrm_diia_node) {
    const auto parser_result = mavka::parser::parse(
        mrm_diia_node->body,
        scope->get_options()->current_module_path + ":" +
            std::to_string(mrm_diia_node->start_line) + ":" +
            std::to_string(mrm_diia_node->start_column) + ":МРМ-дія");
    if (parser_result->error) {
      return scope->error(mrm_diia_node, "Не вдалось розібрати МРМ-дію.");
    }
    const auto program_node = parser_result->program_node;
    auto body = program_node->body;
    if (!body.empty()) {
      const auto last_node = body.back();
      if (dynamic_cast<mavka::ast::ASTValueNode*>(
              mavka::ast::get_ast_node(last_node))) {
        const auto return_node = new mavka::ast::ReturnNode();
        return_node->value = last_node;
        body.pop_back();
        body.push_back(mavka::ast::make_ast_some(return_node));
      }
    }

    const auto anon_diia_node = new mavka::ast::AnonDiiaNode();
    anon_diia_node->start_line = mrm_diia_node->start_line;
    anon_diia_node->start_column = mrm_diia_node->start_column;
    anon_diia_node->end_line = mrm_diia_node->end_line;
    anon_diia_node->end_column = mrm_diia_node->end_column;
    anon_diia_node->body = body;

    const auto call_node = new mavka::ast::CallNode();
    call_node->start_line = mrm_diia_node->start_line;
    call_node->start_column = mrm_diia_node->start_column;
    call_node->end_line = mrm_diia_node->end_line;
    call_node->end_column = mrm_diia_node->end_column;
    call_node->value = mavka::ast::make_ast_some(anon_diia_node);

    return compile_call_node(scope, call_node);
  }
} // namespace jejalyk::typeinterpreter