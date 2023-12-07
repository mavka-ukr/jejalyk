#pragma once

#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "ast.hpp"
#include "tools.hpp"

namespace mavka::parser {
    class ASTResult {
    public:
        ast::ASTNode* node;
    };

    inline ASTResult* any_to_ast_result(std::any any) {
        return std::any_cast<ASTResult *>(any);
    }

    inline ASTResult* create_ast_result(ast::ASTNode* node) {
        const auto ast_result = new ASTResult();
        ast_result->node = node;
        return ast_result;
    }

    inline std::vector<ast::ASTNode *> processASTBody(const std::vector<ast::ASTNode *>& body) {
        std::vector<ast::ASTNode *> result;
        for (auto& item: body) {
            if (jejalyk::tools::instanceof<ast::IdentifierNode>(item)) {
                const auto identifier_node = dynamic_cast<ast::IdentifierNode *>(item);
                if (identifier_node->name == "break") {
                    result.push_back(new ast::BreakNode());
                    continue;
                }
                if (identifier_node->name == "continue") {
                    result.push_back(new ast::ContinueNode());
                    continue;
                }
            }

            if (item) {
                result.push_back(item);
            }
        }
        return result;
    }

    class MavkaASTVisitor final : public MavkaParserBaseVisitor {
    public:
        std::any visitFile(MavkaParser::FileContext* ctx) override {
            return visitProgram(ctx->f_program);
        }

        std::any visitProgram(MavkaParser::ProgramContext* context) override {
            std::vector<ast::ASTNode *> body;
            for (const auto program_element: context->program_element()) {
                const auto ast_result = any_to_ast_result(visitProgram_element(program_element));
                body.push_back(ast_result->node);
            }
            body = processASTBody(body);
            const auto program_node = new ast::ProgramNode();
            program_node->body = body;
            return create_ast_result(program_node);
        }

        std::any visitProgram_element(MavkaParser::Program_elementContext* context) override {
            if (context->module()) {
                return visitModule(context->module());
            }
            if (context->structure()) {
                return visitStructure(context->structure());
            }
            if (context->mockup()) {
                return visitMockup(context->mockup());
            }
            if (context->diia()) {
                return visitDiia(context->diia());
            }
            if (context->if_()) {
                return visitIf(context->if_());
            }
            if (context->each()) {
                return visitEach(context->each());
            }
            if (context->while_()) {
                return visitWhile(context->while_());
            }
            if (context->try_()) {
                return visitTry(context->try_());
            }
            if (context->expr()) {
                return visitExpr(context->expr());
            }
            if (context->throw_()) {
                return visitThrow(context->throw_());
            }
            if (context->eval()) {
                return visitEval(context->eval());
            }
            if (context->wait_assign()) {
                return visitWait_assign(context->wait_assign());
            }
            if (context->assign()) {
                return visitAssign(context->assign());
            }
            if (context->give()) {
                return visitGive(context->give());
            }
            return create_ast_result(nullptr);
        }

        std::any visitModule(MavkaParser::ModuleContext* context) override {
            const auto module_node = new ast::ModuleNode();
            module_node->name = context->m_name->getText();
            if (context->module_body()) {
                std::any module_body = visitModule_body(context->module_body());
                module_node->body = std::any_cast<std::vector<ast::ASTNode *>>(module_body);
            }
            return create_ast_result(module_node);
        }

        std::any visitModule_body(MavkaParser::Module_bodyContext* context) override {
            std::vector<ast::ASTNode *> body;
            for (const auto module_element: context->module_body_element()) {
                const auto ast_result = any_to_ast_result(visitModule_body_element(module_element));
                body.push_back(ast_result->node);
            }
            body = processASTBody(body);
            return body;
        }

        std::any visitModule_body_element(MavkaParser::Module_body_elementContext* context) override {
            if (context->module()) {
                return visitModule(context->module());
            }
            if (context->structure()) {
                return visitStructure(context->structure());
            }
            if (context->mockup()) {
                return visitMockup(context->mockup());
            }
            if (context->diia()) {
                return visitDiia(context->diia());
            }
            if (context->if_()) {
                return visitIf(context->if_());
            }
            if (context->each()) {
                return visitEach(context->each());
            }
            if (context->while_()) {
                return visitWhile(context->while_());
            }
            if (context->try_()) {
                return visitTry(context->try_());
            }
            if (context->expr()) {
                return visitExpr(context->expr());
            }
            if (context->throw_()) {
                return visitThrow(context->throw_());
            }
            if (context->eval()) {
                return visitEval(context->eval());
            }
            if (context->wait_assign()) {
                return visitWait_assign(context->wait_assign());
            }
            if (context->assign()) {
                return visitAssign(context->assign());
            }
            if (context->give()) {
                return visitGive(context->give());
            }
            return create_ast_result(nullptr);
        }

        std::any visitStructure(MavkaParser::StructureContext* context) override {
            const std::string name = context->s_name->getText();
            const auto params = std::any_cast<std::vector<ast::ASTNode *>>(
                visitStructure_elements(context->structure_elements())
            );
            const auto structure_node = new ast::StructureNode();
            structure_node->name = name;
            structure_node->params = std::vector<ast::StructureParamNode *>();
            for (auto& param: params) {
                if (jejalyk::tools::instanceof<ast::StructureParamNode>(param)) {
                    structure_node->params.push_back(dynamic_cast<ast::StructureParamNode *>(param));
                }
            }
            return create_ast_result(structure_node);
        }

        std::any visitStructure_elements(MavkaParser::Structure_elementsContext* context) override {
            std::vector<ast::ASTNode *> elements;
            for (const auto structure_element: context->structure_element()) {
                const auto ast_result = any_to_ast_result(visitStructure_element(structure_element));
                elements.push_back(ast_result->node);
            }
            return elements;
        }

        std::any visitStructure_element(MavkaParser::Structure_elementContext* context) override {
            if (context->structure_param()) {
                return visitStructure_param(context->structure_param());
            }
            return create_ast_result(nullptr);
        }

        std::any visitStructure_param(MavkaParser::Structure_paramContext* context) override {
            const std::string name = context->sp_name->getText();
            ast::ASTNode* type = nullptr;
            if (context->sp_type) {
                type = any_to_ast_result(visitType_value(context->sp_type))->node;
            }
            ast::ASTNode* value = nullptr;
            if (context->sp_value) {
                value = any_to_ast_result(visitParam_value(context->sp_value))->node;
            }
            const auto structure_param_node = new ast::StructureParamNode();
            structure_param_node->name = name;
            structure_param_node->type = type;
            structure_param_node->value = value;
            return create_ast_result(structure_param_node);
        }

        std::any visitMockup(MavkaParser::MockupContext* context) override {
            if (context->mockup_module()) {
                return visitMockup_module(context->mockup_module());
            }
            if (context->mockup_structure()) {
                return visitMockup_structure(context->mockup_structure());
            }
            if (context->mockup_diia()) {
                return visitMockup_diia(context->mockup_diia());
            }
            if (context->mockup_subject()) {
                return visitMockup_subject(context->mockup_subject());
            }
            if (context->mockup_object()) {
                return visitMockup_object(context->mockup_object());
            }
            return create_ast_result(nullptr);
        }

        std::any visitMockup_module(MavkaParser::Mockup_moduleContext* context) override {
            const auto mockup_module_node = new ast::MockupModuleNode();
            mockup_module_node->name = context->mm_name->getText();
            if (context->mm_elements) {
                mockup_module_node->elements = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitMockup_body(context->mm_elements)
                );
            }
            return create_ast_result(mockup_module_node);
        }

        std::any visitMockup_structure(MavkaParser::Mockup_structureContext* context) override {
            const auto mockup_structure_node = new ast::MockupStructureNode();
            mockup_structure_node->name = context->ms_name->getText();
            if (context->ms_elements) {
                mockup_structure_node->params = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitMockup_body(context->ms_elements)
                );
            }
            return create_ast_result(mockup_structure_node);
        }

        std::any visitMockup_diia(MavkaParser::Mockup_diiaContext* context) override {
            const auto mockup_diia_node = new ast::MockupDiiaNode();
            mockup_diia_node->async = context->md_async != nullptr;
            mockup_diia_node->name = context->md_name->getText();
            if (context->md_params) {
                mockup_diia_node->params = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitParams(context->md_params)
                );
            }
            if (context->md_type) {
                mockup_diia_node->result = any_to_ast_result(visitType_value(context->md_type))->node;
            }
            return create_ast_result(mockup_diia_node);
        }

        std::any visitMockup_subject(MavkaParser::Mockup_subjectContext* context) override {
            const auto mockup_subject_node = new ast::MockupSubjectNode();
            mockup_subject_node->name = context->ms_name->getText();
            mockup_subject_node->type = any_to_ast_result(visitType_value(context->ms_type))->node;
            return create_ast_result(mockup_subject_node);
        }

        std::any visitMockup_object(MavkaParser::Mockup_objectContext* context) override {
            const auto mockup_object_node = new ast::MockupObjectNode();
            mockup_object_node->name = context->mo_name->getText();
            if (context->mo_elements) {
                mockup_object_node->elements = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitMockup_body(context->mo_elements)
                );
            }
            return create_ast_result(mockup_object_node);
        }

        std::any visitDiia(MavkaParser::DiiaContext* context) override {
            const auto diia_node = new ast::DiiaNode();
            diia_node->async = context->d_async != nullptr;
            diia_node->structure = context->d_structure ? context->d_structure->getText() : "";
            diia_node->name = context->d_name->getText();
            if (context->d_params) {
                diia_node->params = std::any_cast<std::vector<ast::ParamNode *>>(
                    visitParams(context->d_params)
                );
            }
            if (context->d_type) {
                diia_node->type = any_to_ast_result(visitType_value(context->d_type))->node;
            }
            if (context->d_body) {
                diia_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitBody(context->d_body)
                );
            }
            return create_ast_result(diia_node);
        }

        std::any visitIf(MavkaParser::IfContext* context) override {
            const auto if_node = new ast::IfNode();
            if_node->condition = any_to_ast_result(visitExpr(context->i_value))->node;
            if_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                visitBody(context->i_body)
            );
            if (context->i_else_body) {
                if_node->else_body = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitBody(context->i_else_body)
                );
            }
            return create_ast_result(if_node);
        }

        std::any visitEach(MavkaParser::EachContext* context) override {
            const auto each_node = new ast::EachNode();
            if (context->e_iterator) {
                each_node->value = any_to_ast_result(visitExpr(context->e_iterator))->node;
            }
            if (context->e_fromto) {
                each_node->value = any_to_ast_result(visitFromto(context->e_fromto))->node;
            }
            each_node->keyName = context->e_key_name ? context->e_key_name->getText() : "";
            each_node->name = context->e_name->getText();
            if (context->e_body) {
                each_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitBody(context->e_body)
                );
            }
            return create_ast_result(each_node);
        }

        // todo: fromto

        std::any visitWhile(MavkaParser::WhileContext* context) override {
            const auto while_node = new ast::WhileNode();
            while_node->condition = any_to_ast_result(visitExpr(context->w_value))->node;
            if (context->w_body) {
                while_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitBody(context->w_body)
                );
            }
            return create_ast_result(while_node);
        }

        std::any visitTry(MavkaParser::TryContext* context) override {
            const auto try_node = new ast::TryNode();
            try_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                visitBody(context->t_body)
            );
            try_node->name = context->tc_name->getText();
            try_node->catch_body = std::any_cast<std::vector<ast::ASTNode *>>(
                visitBody(context->tc_body)
            );
            return create_ast_result(try_node);
        }

        std::any visitExpr(MavkaParser::ExprContext* context) {
            if (jejalyk::tools::instanceof<MavkaParser::SimpleContext>(context)) {
                const auto simple_context = dynamic_cast<MavkaParser::SimpleContext *>(context);
                return visitValue(simple_context->value());
            }
            if (jejalyk::tools::instanceof<MavkaParser::WaitContext>(context)) {
                const auto wait_context = dynamic_cast<MavkaParser::WaitContext *>(context);
                return visitWait(wait_context);
            }
            if (jejalyk::tools::instanceof<MavkaParser::FunctionContext>(context)) {
                const auto function_context = dynamic_cast<MavkaParser::FunctionContext *>(context);
                return visitFunction(function_context);
            }
            if (jejalyk::tools::instanceof<MavkaParser::Anonymous_diiaContext>(context)) {
                const auto anonymous_diia_context = dynamic_cast<MavkaParser::Anonymous_diiaContext *>(context);
                return visitAnonymous_diia(anonymous_diia_context);
            }
            return create_ast_result(nullptr);
        }

        std::any visitValue(MavkaParser::ValueContext* context) {
            if (jejalyk::tools::instanceof<MavkaParser::NumberContext>(context)) {
                return visitNumber(dynamic_cast<MavkaParser::NumberContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::String_valueContext>(context)) {
                return visitString_value(dynamic_cast<MavkaParser::String_valueContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::IdContext>(context)) {
                return visitId(dynamic_cast<MavkaParser::IdContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::ChainContext>(context)) {
                return visitChain(dynamic_cast<MavkaParser::ChainContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::CallContext>(context)) {
                return visitCall(dynamic_cast<MavkaParser::CallContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Get_elementContext>(context)) {
                return visitGet_element(dynamic_cast<MavkaParser::Get_elementContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::PositiveContext>(context)) {
                return visitPositive(dynamic_cast<MavkaParser::PositiveContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::NegativeContext>(context)) {
                return visitNegative(dynamic_cast<MavkaParser::NegativeContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Pre_decrementContext>(context)) {
                return visitPre_decrement(dynamic_cast<MavkaParser::Pre_decrementContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Pre_incrementContext>(context)) {
                return visitPre_increment(dynamic_cast<MavkaParser::Pre_incrementContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Post_decrementContext>(context)) {
                return visitPost_decrement(dynamic_cast<MavkaParser::Post_decrementContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Post_incrementContext>(context)) {
                return visitPost_increment(dynamic_cast<MavkaParser::Post_incrementContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::NotContext>(context)) {
                return visitNot(dynamic_cast<MavkaParser::NotContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Bitwise_notContext>(context)) {
                return visitBitwise_not(dynamic_cast<MavkaParser::Bitwise_notContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::NestedContext>(context)) {
                return visitNested(dynamic_cast<MavkaParser::NestedContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Call_exprContext>(context)) {
                return visitCall_expr(dynamic_cast<MavkaParser::Call_exprContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::AsContext>(context)) {
                return visitAs(dynamic_cast<MavkaParser::AsContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Arithmetic_mulContext>(context)) {
                return visitArithmetic_mul(dynamic_cast<MavkaParser::Arithmetic_mulContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::Arithmetic_addContext>(context)) {
                return visitArithmetic_add(dynamic_cast<MavkaParser::Arithmetic_addContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::BitwiseContext>(context)) {
                return visitBitwise(dynamic_cast<MavkaParser::BitwiseContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::ComparisonContext>(context)) {
                return visitComparison(dynamic_cast<MavkaParser::ComparisonContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::TestContext>(context)) {
                return visitTest(dynamic_cast<MavkaParser::TestContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::TernaryContext>(context)) {
                return visitTernary(dynamic_cast<MavkaParser::TernaryContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::ArrayContext>(context)) {
                return visitArray(dynamic_cast<MavkaParser::ArrayContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::DictionaryContext>(context)) {
                return visitDictionary(dynamic_cast<MavkaParser::DictionaryContext *>(context));
            }
            if (jejalyk::tools::instanceof<MavkaParser::GodContext>(context)) {
                return visitGod(dynamic_cast<MavkaParser::GodContext *>(context));
            }
            return create_ast_result(nullptr);
        }

        std::any visitNumber(MavkaParser::NumberContext* context) override {
            const auto number_node = new ast::NumberNode();
            number_node->value = context->getText();
            return create_ast_result(number_node);
        }

        std::any visitString_value(MavkaParser::String_valueContext* context) override {
            const auto string_node = new ast::StringNode();
            string_node->value = context->getText();
            if (string_node->value.starts_with(R"(""")")) {
                string_node->value = string_node->value.substr(3, string_node->value.length() - 6);
            } else {
                string_node->value = string_node->value.substr(1, string_node->value.length() - 2);
            }
            return create_ast_result(string_node);
        }

        std::any visitId(MavkaParser::IdContext* context) override {
            const auto identifier_node = new ast::IdentifierNode();
            identifier_node->name = context->getText();
            return create_ast_result(identifier_node);
        }

        std::any visitIdentifier(MavkaParser::IdentifierContext* context) override {
            const auto identifier_node = new ast::IdentifierNode();
            identifier_node->name = context->getText();
            return create_ast_result(identifier_node);
        }

        std::any visitExtended_identifier(MavkaParser::Extended_identifierContext* context) override {
            const auto identifier_node = new ast::IdentifierNode();
            identifier_node->name = context->getText();
            return create_ast_result(identifier_node);
        }

        std::any visitChain(MavkaParser::ChainContext* context) override {
            const auto chain_node = new ast::ChainNode();
            chain_node->left = any_to_ast_result(visitValue(context->c_left))->node;
            chain_node->right = any_to_ast_result(visitExtended_identifier(context->c_right))->node;
            return create_ast_result(chain_node);
        }

        std::any visitCall(MavkaParser::CallContext* context) override {
            const auto call_node = new ast::CallNode();
            call_node->value = any_to_ast_result(visitValue(context->c_value))->node;
            if (context->c_args) {
                call_node->args = std::any_cast<std::vector<ast::ArgNode *>>(
                    visitArgs(context->c_args)
                );
            }
            if (context->c_named_args) {
                call_node->args = std::any_cast<std::vector<ast::ArgNode *>>(
                    visitNamed_args(context->c_named_args)
                );
            }
            return create_ast_result(call_node);
        }

        std::any visitGet_element(MavkaParser::Get_elementContext* context) override {
            const auto get_element_node = new ast::GetElementNode();
            get_element_node->value = any_to_ast_result(visitValue(context->ge_left))->node;
            get_element_node->index = any_to_ast_result(visitExpr(context->ge_element))->node;
            return create_ast_result(get_element_node);
        }

        std::any visitPositive(MavkaParser::PositiveContext* context) override {
            const auto positive_node = new ast::PositiveNode();
            positive_node->value = any_to_ast_result(visitValue(context->p_value))->node;
            return create_ast_result(positive_node);
        }

        std::any visitNegative(MavkaParser::NegativeContext* context) override {
            const auto negative_node = new ast::NegativeNode();
            negative_node->value = any_to_ast_result(visitValue(context->n_value))->node;
            return create_ast_result(negative_node);
        }

        std::any visitNested(MavkaParser::NestedContext* context) override {
            return visitExpr(context->n_value);
        }

        std::any visitAs(MavkaParser::AsContext* context) override {
            const auto as_node = new ast::AsNode();
            as_node->left = any_to_ast_result(visitValue(context->a_left))->node;
            as_node->right = any_to_ast_result(visitValue(context->a_right))->node;
            return create_ast_result(as_node);
        }

        std::any visitArithmetic_mul(MavkaParser::Arithmetic_mulContext* context) override {
            const auto arithmetic_node = new ast::ArithmeticNode();
            arithmetic_node->left = any_to_ast_result(visitValue(context->a_left))->node;
            arithmetic_node->right = any_to_ast_result(visitValue(context->a_right))->node;
            arithmetic_node->op = context->a_operation->getText();
            return create_ast_result(arithmetic_node);
        }

        std::any visitArithmetic_add(MavkaParser::Arithmetic_addContext* context) override {
            const auto arithmetic_node = new ast::ArithmeticNode();
            arithmetic_node->left = any_to_ast_result(visitValue(context->a_left))->node;
            arithmetic_node->right = any_to_ast_result(visitValue(context->a_right))->node;
            arithmetic_node->op = context->a_operation->getText();
            return create_ast_result(arithmetic_node);
        }

        std::any visitComparison(MavkaParser::ComparisonContext* context) override {
            const auto comparison_node = new ast::ComparisonNode();
            comparison_node->left = any_to_ast_result(visitValue(context->c_left))->node;
            comparison_node->right = any_to_ast_result(visitValue(context->c_right))->node;
            comparison_node->op = context->c_operation->getText();
            return create_ast_result(comparison_node);
        }

        std::any visitTest(MavkaParser::TestContext* context) override {
            const auto test_node = new ast::TestNode();
            test_node->left = any_to_ast_result(visitValue(context->t_left))->node;
            test_node->right = any_to_ast_result(visitValue(context->t_right))->node;
            test_node->op = context->t_operation->getText();
            return create_ast_result(test_node);
        }

        std::any visitArray(MavkaParser::ArrayContext* context) override {
            const auto array_node = new ast::ArrayNode();
            if (context->a_elements) {
                array_node->elements = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitArray_elements(context->a_elements)
                );
            }
            return create_ast_result(array_node);
        }

        std::any visitArray_elements(MavkaParser::Array_elementsContext* context) override {
            std::vector<ast::ASTNode *> elements;
            for (const auto array_element: context->array_element()) {
                const auto ast_result = any_to_ast_result(visitArray_element(array_element));
                elements.push_back(ast_result->node);
            }
            return elements;
        }

        std::any visitArray_element(MavkaParser::Array_elementContext* context) override {
            return visitExpr(context->ae_value);
        }

        std::any visitDictionary(MavkaParser::DictionaryContext* context) override {
            const auto dictionary_node = new ast::DictionaryNode();
            if (context->d_args) {
                dictionary_node->elements = std::any_cast<std::map<std::string, ast::ASTNode *>>(
                    visitDictionary_args(context->d_args)
                );
            }
            return create_ast_result(dictionary_node);
        }

        std::any visitDictionary_args(MavkaParser::Dictionary_argsContext* context) override {
            std::map<std::string, ast::ASTNode *> elements;
            for (const auto dictionary_arg: context->dictionary_arg()) {
                const auto value = any_to_ast_result(visitExpr(dictionary_arg->da_value))->node;
                if (dictionary_arg->da_name_id) {
                    elements[dictionary_arg->da_name_id->getText()] = value;
                } else if (dictionary_arg->da_name_string) {
                    const auto name_string = dictionary_arg->da_name_string->getText();
                    if (name_string.starts_with(R"(""")")) {
                        elements[name_string.substr(3, name_string.length() - 6)] = value;
                    } else {
                        elements[name_string.substr(1, name_string.length() - 2)] = value;
                    }
                }
            }
            return elements;
        }

        std::any visitWait(MavkaParser::WaitContext* context) override {
            const auto wait_node = new ast::WaitNode();
            wait_node->value = any_to_ast_result(visitValue(context->w_value))->node;
            return create_ast_result(wait_node);
        }

        std::any visitFunction(MavkaParser::FunctionContext* context) override {
            const auto function_node = new ast::FunctionNode();
            function_node->async = context->f_async != nullptr;
            if (context->f_params) {
                function_node->params = std::any_cast<std::vector<ast::ParamNode *>>(
                    visitParams(context->f_params)
                );
            }
            if (context->f_type) {
                function_node->type = any_to_ast_result(visitType_value(context->f_type))->node;
            }
            if (context->f_body) {
                const auto function_node_body = any_to_ast_result(visitExpr(context->f_body))->node;
                function_node->body.push_back(function_node_body);
            }
            return create_ast_result(function_node);
        }

        std::any visitAnonymous_diia(MavkaParser::Anonymous_diiaContext* context) override {
            const auto function_node = new ast::AnonDiiaNode();
            function_node->async = context->d_async != nullptr;
            if (context->d_params) {
                function_node->params = std::any_cast<std::vector<ast::ParamNode *>>(
                    visitParams(context->d_params)
                );
            }
            if (context->d_type) {
                function_node->type = any_to_ast_result(visitType_value(context->d_type))->node;
            }
            if (context->d_body) {
                function_node->body = std::any_cast<std::vector<ast::ASTNode *>>(
                    visitBody(context->d_body)
                );
            }
            return create_ast_result(function_node);
        }

        std::any visitThrow(MavkaParser::ThrowContext* context) override {
            const auto throw_node = new ast::ThrowNode();
            throw_node->value = any_to_ast_result(visitExpr(context->t_value))->node;
            return create_ast_result(throw_node);
        }

        std::any visitEval(MavkaParser::EvalContext* context) override {
            const auto eval_node = new ast::EvalNode();
            eval_node->value = any_to_ast_result(visitValue(context->e_value))->node;
            return create_ast_result(eval_node);
        }

        std::any visitWait_assign(MavkaParser::Wait_assignContext* context) override {
            // const auto assign_node = visitAssign(context->wa_assign);
            // const auto wait_node = new WaitNode();
            // wait_node->value = any_to_ast_result(assign_node)->node;
            // assign_node->node = wait_node;
            // return create_ast_result(assign_node);
            return create_ast_result(nullptr);
        }

        std::any visitAssign(MavkaParser::AssignContext* context) override {
            if (context->assign_simple()) {
                return visitAssign_simple(context->assign_simple());
            }
            if (context->assign_complex()) {
                return visitAssign_complex(context->assign_complex());
            }
            return create_ast_result(nullptr);
        }

        std::any visitAssign_simple(MavkaParser::Assign_simpleContext* context) override {
            const auto assign_simple_node = new ast::AssignSimpleNode();
            assign_simple_node->name = context->as_identifier->ID()->getText();
            if (context->as_type) {
                assign_simple_node->type = any_to_ast_result(visitType_value(context->as_type))->node;
            }
            assign_simple_node->op = context->assign_symbol()->getText();
            assign_simple_node->value = any_to_ast_result(visitExpr(context->as_value))->node;
            return create_ast_result(assign_simple_node);
        }

        std::any visitAssign_complex(MavkaParser::Assign_complexContext* context) override {
            const auto assign_complex_node = new ast::AssignComplexNode();
            assign_complex_node->left = any_to_ast_result(visitAssign_complex_left(context->ac_left))->node;
            assign_complex_node->right = any_to_ast_result(visitAssign_complex_right(context->ac_right))->node;
            assign_complex_node->op = context->assign_symbol()->getText();
            assign_complex_node->value = any_to_ast_result(visitExpr(context->ac_value))->node;
            return create_ast_result(assign_complex_node);
        }

        std::any visitAssign_complex_left(MavkaParser::Assign_complex_leftContext* context) override {
            if (context->acl_chain) {
                return visitIdentifiers_chain(context->acl_chain);
            }
            if (context->acl_left) {
                const auto get_element_node = new ast::GetElementNode();
                get_element_node->value = any_to_ast_result(visitAssign_complex_left(context->acl_left))->node;
                get_element_node->index = any_to_ast_result(visitExpr(context->acl_element))->node;
                return create_ast_result(get_element_node);
            }
            return create_ast_result(nullptr);
        }

        std::any visitAssign_complex_right(MavkaParser::Assign_complex_rightContext* context) override {
            const auto assign_complex_right_node = new ast::AssignComplexRightNode();
            if (context->acr_identifier) {
                assign_complex_right_node->name = context->acr_identifier->ID()->getText();
            }
            if (context->acr_element) {
                assign_complex_right_node->index = any_to_ast_result(visitExpr(context->acr_element))->node;
            }
            return create_ast_result(assign_complex_right_node);
        }

        std::any visitAssign_array_destruction(MavkaParser::Assign_array_destructionContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitAssign_object_destruction(MavkaParser::Assign_object_destructionContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitAssign_symbol(MavkaParser::Assign_symbolContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitTake_module(MavkaParser::Take_moduleContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitTake_file(MavkaParser::Take_fileContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitTake_remote(MavkaParser::Take_remoteContext* context) override {
            // todo
            return create_ast_result(new ast::ASTNode());
        }

        std::any visitGive(MavkaParser::GiveContext* context) override {
            const auto give_node = new ast::GiveNode();
            for (const auto give_element: context->give_element()) {
                const auto ast_result = any_to_ast_result(visitGive_element(give_element));
                const auto give_element_node = dynamic_cast<ast::GiveElementNode *>(ast_result->node);
                give_node->elements.push_back(give_element_node);
            }
            return create_ast_result(give_node);
        }

        std::any visitGive_element(MavkaParser::Give_elementContext* context) override {
            const auto give_element_node = new ast::GiveElementNode();
            give_element_node->name = context->ge_name->getText();
            if (context->ge_as) {
                give_element_node->as = context->ge_as->getText();
            }
            return create_ast_result(give_element_node);
        }

        std::any visitParams(MavkaParser::ParamsContext* context) override {
            std::vector<ast::ParamNode *> params;
            for (int i = 0; i < context->param().size(); ++i) {
                const auto param = context->param()[i];
                const auto ast_result = any_to_ast_result(visitParam(param));
                params.push_back(dynamic_cast<ast::ParamNode *>(ast_result->node));
            }
            return params;
        }

        std::any visitParam(MavkaParser::ParamContext* context) override {
            const auto param_node = new ast::ParamNode();
            param_node->name = context->p_name->getText();
            if (context->p_type) {
                param_node->type = any_to_ast_result(visitType_value(context->p_type))->node;
            }
            if (context->p_value) {
                param_node->value = any_to_ast_result(visitParam_value(context->p_value))->node;
            }
            return create_ast_result(param_node);
        }

        std::any visitParam_value(MavkaParser::Param_valueContext* context) {
            return create_ast_result(nullptr);
        }

        std::any visitArgs(MavkaParser::ArgsContext* context) override {
            std::vector<ast::ArgNode *> args;
            for (int i = 0; i < context->arg().size(); ++i) {
                const auto arg = context->arg()[i];
                const auto ast_result = any_to_ast_result(visitArg(arg, i));
                args.push_back(dynamic_cast<ast::ArgNode *>(ast_result->node));
            }
            return args;
        }

        std::any visitArg(MavkaParser::ArgContext* context, int index) {
            const auto arg_node = new ast::ArgNode();
            arg_node->index = index;
            arg_node->value = any_to_ast_result(visitExpr(context->a_value))->node;
            return create_ast_result(arg_node);
        }

        std::any visitNamed_args(MavkaParser::Named_argsContext* context) override {
            std::vector<ast::ArgNode *> args;
            for (int i = 0; i < context->named_arg().size(); ++i) {
                const auto arg = context->named_arg()[i];
                const auto ast_result = any_to_ast_result(visitNamed_arg(arg, i));
                args.push_back(dynamic_cast<ast::ArgNode *>(ast_result->node));
            }
            return args;
        }

        std::any visitNamed_arg(MavkaParser::Named_argContext* context, int index) {
            const auto arg_node = new ast::ArgNode();
            arg_node->index = index;
            arg_node->name = context->na_name->getText();
            arg_node->value = any_to_ast_result(visitExpr(context->na_value))->node;
            return create_ast_result(arg_node);
        }

        std::any visitBody(MavkaParser::BodyContext* context) override {
            std::vector<ast::ASTNode *> body;
            for (const auto body_element: context->body_element_or_return()) {
                const auto ast_result = any_to_ast_result(visitBody_element_or_return(body_element));
                body.push_back(ast_result->node);
            }
            return body;
        }

        std::any visitBody_element_or_return(MavkaParser::Body_element_or_returnContext* context) override {
            if (context->body_element()) {
                return visitBody_element(context->body_element());
            }
            if (context->return_body_line()) {
                return visitReturn_body_line(context->return_body_line());
            }
            return create_ast_result(nullptr);
        }

        std::any visitBody_element(MavkaParser::Body_elementContext* context) override {
            if (context->if_()) {
                return visitIf(context->if_());
            }
            if (context->each()) {
                return visitEach(context->each());
            }
            if (context->while_()) {
                return visitWhile(context->while_());
            }
            if (context->try_()) {
                return visitTry(context->try_());
            }
            if (context->expr()) {
                return visitExpr(context->expr());
            }
            if (context->throw_()) {
                return visitThrow(context->throw_());
            }
            if (context->wait_assign()) {
                return visitWait_assign(context->wait_assign());
            }
            if (context->assign()) {
                return visitAssign(context->assign());
            }
            return create_ast_result(nullptr);
        }

        std::any visitReturn_body_line(MavkaParser::Return_body_lineContext* context) override {
            const auto return_node = new ast::ReturnNode();
            return_node->value = any_to_ast_result(visitExpr(context->rbl_value))->node;
            return create_ast_result(return_node);
        }
    };

    class MavkaParserError : public std::exception {
    public:
        size_t line{};
        size_t column{};
        std::string message;
    };

    class MavkaParserErrorListener final : public antlr4::BaseErrorListener {
    public:
        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token* offendingSymbol,
                         size_t line,
                         size_t charPositionInLine,
                         const std::string& msg,
                         std::exception_ptr e) override {
            const auto error = new MavkaParserError();
            error->line = line;
            error->column = charPositionInLine;
            error->message = msg;
            throw error;
        }
    };

    class MavkaParserResult {
    public:
        MavkaParserError* error = nullptr;
        mavka::ast::ProgramNode* program_node = nullptr;
    };

    MavkaParserResult* parse(std::string code) {
        try {
            antlr4::ANTLRInputStream input(code);

            const auto lexer_error_listener = new MavkaParserErrorListener();
            MavkaLexer lexer(&input);
            lexer.removeErrorListeners();
            lexer.addErrorListener(lexer_error_listener);

            antlr4::CommonTokenStream tokens(&lexer);

            const auto parser_error_listener = new MavkaParserErrorListener();
            MavkaParser parser(&tokens);
            parser.removeErrorListeners();
            parser.addErrorListener(parser_error_listener);

            MavkaParser::FileContext* tree = parser.file();

            MavkaASTVisitor visitor;

            const auto ast_result = any_to_ast_result(visitor.visitFile(tree));
            const auto program_node = dynamic_cast<ast::ProgramNode *>(ast_result->node);
            const auto parser_result = new MavkaParserResult();
            parser_result->program_node = program_node;
            return parser_result;
        } catch (MavkaParserError& parser_error) {
            const auto parser_result = new MavkaParserResult();
            parser_result->error = &parser_error;
            return parser_result;
        } catch (antlr4::RuntimeException& e) {
            const auto parser_result = new MavkaParserResult();
            const auto parser_error = new MavkaParserError();
            // todo: handle
            parser_error->message = "antlr4::RuntimeException";
            parser_result->error = parser_error;
            return parser_result;
        }
    }
}