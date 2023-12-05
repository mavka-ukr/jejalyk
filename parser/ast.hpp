#include <vector>
#include "MavkaParserBaseVisitor.h"
#include "../nlohmann/json.hpp"

namespace mavka {
    namespace ast {
        using json = nlohmann::json;

        template<typename Base, typename T>
        inline bool instanceof(const T* ptr) {
            return dynamic_cast<const Base *>(ptr) != nullptr;
        }

        // base
        class ASTNode {
        public:
            std::string TYPE = "ASTNode";
            int start_line = 0;
            int start_column = 0;
            int end_line = 0;
            int end_column = 0;

            virtual ~ASTNode() = default;
        };

        // anon diia
        class ParamNode final : public ASTNode {
        public:
            std::string TYPE = "ParamNode";

            std::string name;
            ASTNode* type;
            ASTNode* value;
        };

        class AnonDiiaNode final : public ASTNode {
        public:
            std::string TYPE = "AnonDiiaNode";

            bool async;
            std::vector<ParamNode *> params;
            ASTNode* type;
            std::vector<ASTNode *> body;
        };

        // arg
        class ArgNode final : public ASTNode {
        public:
            std::string TYPE = "ArgNode";

            int index;
            std::string name;
            ASTNode* value;
        };

        // arithmetic
        class ArithmeticNode final : public ASTNode {
        public:
            std::string TYPE = "ArithmeticNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
        };

        // array
        class ArrayNode final : public ASTNode {
        public:
            std::string TYPE = "ArrayNode";

            std::vector<ASTNode *> elements;
        };

        // as
        class AsNode final : public ASTNode {
        public:
            std::string TYPE = "AsNode";

            ASTNode* left;
            ASTNode* right;
        };

        // assign complex
        class AssignComplexRightNode final : public ASTNode {
        public:
            std::string TYPE = "AssignComplexRightNode";

            std::string name;
            ASTNode* index;
        };

        class AssignComplexNode final : public ASTNode {
        public:
            std::string TYPE = "AssignComplexNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
            ASTNode* value;
        };

        // assign simple
        class AssignSimpleNode final : public ASTNode {
        public:
            std::string TYPE = "AssignSimpleNode";

            std::string name;
            ASTNode* type;
            std::string op;
            ASTNode* value;
        };

        // bitwise
        class BitwiseNode final : public ASTNode {
        public:
            std::string TYPE = "BitwiseNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
        };

        // bitwise not
        class BitwiseNotNode final : public ASTNode {
        public:
            std::string TYPE = "BitwiseNotNode";

            ASTNode* value;
        };

        // break
        class BreakNode final : public ASTNode {
        public:
            std::string TYPE = "BreakNode";
        };

        // call
        class CallNode final : public ASTNode {
        public:
            std::string TYPE = "CallNode";

            ASTNode* value;
            std::vector<ArgNode *> args;
        };

        // chain
        class ChainNode final : public ASTNode {
        public:
            std::string TYPE = "ChainNode";

            ASTNode* left;
            ASTNode* right;
        };

        // comparison
        class ComparisonNode final : public ASTNode {
        public:
            std::string TYPE = "ComparisonNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
        };

        // continue
        class ContinueNode final : public ASTNode {
        public:
            std::string TYPE = "ContinueNode";
        };

        // dictionary
        class DictionaryNode final : public ASTNode {
        public:
            std::string TYPE = "DictionaryNode";

            std::map<ASTNode *, ASTNode *> elements;
        };

        // diia
        class DiiaNode final : public ASTNode {
        public:
            std::string TYPE = "DiiaNode";

            bool async;
            std::string structure;
            std::string name;
            std::vector<ParamNode *> params;
            ASTNode* type;
            std::vector<ASTNode *> body;
        };

        // each
        class EachNode final : public ASTNode {
        public:
            std::string TYPE = "EachNode";

            ASTNode* value;
            std::string keyName;
            std::string name;
            std::vector<ASTNode *> body;
        };

        // eval
        class EvalNode final : public ASTNode {
        public:
            std::string TYPE = "EvalNode";

            ASTNode* value;
        };

        // function
        class FunctionNode final : public ASTNode {
        public:
            std::string TYPE = "FunctionNode";

            bool async;
            std::vector<ParamNode *> params;
            ASTNode* type;
            std::vector<ASTNode *> body;
        };

        // get element
        class GetElementNode final : public ASTNode {
        public:
            std::string TYPE = "GetElementNode";

            ASTNode* value;
            ASTNode* index;
        };

        // give
        class GiveElementNode final : public ASTNode {
        public:
            std::string TYPE = "GiveElementNode";

            std::string name;
            std::string as;
        };

        class GiveNode final : public ASTNode {
        public:
            std::string TYPE = "GiveNode";

            std::vector<GiveElementNode *> elements;
        };

        // god
        class GodNode final : public ASTNode {
        public:
            std::string TYPE = "GodNode";

            std::vector<ASTNode *> elements;
        };

        // identifier
        class IdentifierNode final : public ASTNode {
        public:
            std::string TYPE = "IdentifierNode";

            std::string name;
        };

        // if
        class IfNode final : public ASTNode {
        public:
            std::string TYPE = "IfNode";

            ASTNode* condition;
            std::vector<ASTNode *> body;
            std::vector<ASTNode *> else_body;
        };

        // mockup
        class MockupDiiaNode final : public ASTNode {
        public:
            bool async;
            std::string name;
            std::vector<ASTNode *> params;
            ASTNode* result;
        };

        class MockupModuleNode final : public ASTNode {
        public:
            std::string name;
            std::vector<ASTNode *> elements;
        };

        class MockupObjectNode final : public ASTNode {
        public:
            std::string name;
            std::vector<ASTNode *> elements;
        };

        class MockupStructureNode final : public ASTNode {
        public:
            std::string name;
            std::vector<ASTNode *> params;
        };

        class MockupSubjectNode final : public ASTNode {
        public:
            std::string name;
            ASTNode* type;
        };

        // module
        class ModuleNode final : public ASTNode {
        public:
            std::string TYPE = "ModuleNode";

            std::string name;
            std::vector<ASTNode *> body;
        };

        // negative
        class NegativeNode final : public ASTNode {
        public:
            std::string TYPE = "NegativeNode";

            ASTNode* value;
        };

        // not
        class NotNode final : public ASTNode {
        public:
            std::string TYPE = "NotNode";

            ASTNode* value;
        };

        // number
        class NumberNode final : public ASTNode {
        public:
            std::string TYPE = "NumberNode";

            std::string value;
        };

        // positive
        class PositiveNode final : public ASTNode {
        public:
            std::string TYPE = "PositiveNode";

            ASTNode* value;
        };

        // post decrement
        class PostDecrementNode final : public ASTNode {
        public:
            std::string TYPE = "PostDecrementNode";

            ASTNode* value;
        };

        // post increment
        class PostIncrementNode final : public ASTNode {
        public:
            std::string TYPE = "PostIncrementNode";

            ASTNode* value;
        };

        // pre decrement
        class PreDecrementNode final : public ASTNode {
        public:
            std::string TYPE = "PreDecrementNode";

            ASTNode* value;
        };

        // pre increment
        class PreInrementNode final : public ASTNode {
        public:
            std::string TYPE = "PreInrementNode";

            ASTNode* value;
        };

        // program
        class ProgramNode final : public ASTNode {
        public:
            std::string TYPE = "ProgramNode";

            std::vector<ASTNode *> body;
        };

        // return
        class ReturnNode final : public ASTNode {
        public:
            std::string TYPE = "ReturnNode";

            ASTNode* value;
        };

        // string
        class StringNode final : public ASTNode {
        public:
            std::string TYPE = "StringNode";

            std::string value;
        };

        // structure
        class StructureParamNode final : public ASTNode {
        public:
            std::string TYPE = "StructureParamNode";

            std::string name;
            ASTNode* type;
            ASTNode* value;
        };

        class StructureNode final : public ASTNode {
        public:
            std::string TYPE = "StructureNode";

            std::string name;
            std::vector<StructureParamNode *> params;
        };

        // take module
        class TakeModuleNode final : public ASTNode {
        public:
            std::string TYPE = "TakeModuleNode";

            std::string name;
            std::string as;
        };

        // take pak
        class TakePakNode final : public ASTNode {
        public:
            std::string TYPE = "TakePakNode";

            std::string name;
            std::string as;
        };

        // ternary
        class TernaryNode final : public ASTNode {
        public:
            std::string TYPE = "TernaryNode";

            ASTNode* condition;
            std::vector<ASTNode *> body;
            std::vector<ASTNode *> else_body;
        };

        // test
        class TestNode final : public ASTNode {
        public:
            std::string TYPE = "TestNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
        };

        // throw
        class ThrowNode final : public ASTNode {
        public:
            std::string TYPE = "ThrowNode";

            ASTNode* value;
        };

        // try
        class TryNode final : public ASTNode {
        public:
            std::string TYPE = "TryNode";

            std::vector<ASTNode *> body;
            std::string name;
            std::vector<ASTNode *> catch_body;
        };

        // type value
        class TypeValueNode final : public ASTNode {
        public:
            std::string TYPE = "TypeValueNode";

            ASTNode* left;
            ASTNode* right;
            std::string op;
        };

        // type value sinlge
        class TypeValueSingleNode final : public ASTNode {
        public:
            std::string TYPE = "TypeValueSingleNode";

            bool is_array;
            ASTNode* value;
        };

        // wait
        class WaitNode final : public ASTNode {
        public:
            std::string TYPE = "WaitNode";

            ASTNode* value;
        };

        // while
        class WhileNode final : public ASTNode {
        public:
            std::string TYPE = "WhileNode";

            ASTNode* condition;
            std::vector<ASTNode *> body;
        };

        class ASTResult {
        public:
            ASTNode* node;
        };

        ASTResult* any_to_ast_result(std::any any) {
            return std::any_cast<ASTResult *>(any);
        }

        ASTResult* create_ast_result(ASTNode* node) {
            const auto ast_result = new ASTResult();
            ast_result->node = node;
            return ast_result;
        }

        std::vector<ASTNode *> processASTBody(const std::vector<ASTNode *>& body) {
            std::vector<ASTNode *> result;
            for (auto& item: body) {
                if (instanceof<IdentifierNode>(item)) {
                    const auto identifier_node = dynamic_cast<IdentifierNode *>(item);
                    if (identifier_node->name == "break") {
                        result.push_back(new BreakNode());
                        continue;
                    }
                    if (identifier_node->name == "continue") {
                        result.push_back(new ContinueNode());
                        continue;
                    }
                }

                result.push_back(item);
            }
            return result;
        }

        class MavkaASTVisitor final : public MavkaParserBaseVisitor {
        public:
            std::any visitFile(MavkaParser::FileContext* ctx) override {
                return visitProgram(ctx->f_program);
            }

            std::any visitProgram(MavkaParser::ProgramContext* context) override {
                std::vector<ASTNode *> body;
                for (const auto program_element: context->program_element()) {
                    const auto ast_result = any_to_ast_result(visitProgram_element(program_element));
                    body.push_back(ast_result->node);
                }
                body = processASTBody(body);
                const auto program_node = new ProgramNode();
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
                return create_ast_result(new ASTNode());
            }

            std::any visitModule(MavkaParser::ModuleContext* context) override {
                const auto module_node = new ModuleNode();
                module_node->name = context->m_name->getText();
                if (context->module_body()) {
                    std::any module_body = visitModule_body(context->module_body());
                    module_node->body = std::any_cast<std::vector<ASTNode *>>(module_body);
                }
                return create_ast_result(module_node);
            }

            std::any visitModule_body(MavkaParser::Module_bodyContext* context) override {
                std::vector<ASTNode *> body;
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
                return create_ast_result(new ASTNode());
            }

            std::any visitStructure(MavkaParser::StructureContext* context) override {
                const std::string name = context->s_name->getText();
                const std::vector<ASTNode *> params = std::any_cast<std::vector<ASTNode *>>(
                    visitStructure_elements(context->structure_elements())
                );
                const auto structure_node = new StructureNode();
                structure_node->name = name;
                structure_node->params = std::vector<StructureParamNode *>();
                for (auto& param: params) {
                    if (instanceof<StructureParamNode>(param)) {
                        structure_node->params.push_back(dynamic_cast<StructureParamNode *>(param));
                    }
                }
                return create_ast_result(structure_node);
            }

            std::any visitStructure_elements(MavkaParser::Structure_elementsContext* context) override {
                std::vector<ASTNode *> elements;
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
                return create_ast_result(new ASTNode());
            }

            std::any visitStructure_param(MavkaParser::Structure_paramContext* context) override {
                const std::string name = context->sp_name->getText();
                ASTNode* type = nullptr;
                if (context->sp_type) {
                    type = any_to_ast_result(visitType_value(context->sp_type))->node;
                }
                ASTNode* value = nullptr;
                if (context->sp_value) {
                    value = any_to_ast_result(visitParam_value(context->sp_value))->node;
                }
                const auto structure_param_node = new StructureParamNode();
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
                return create_ast_result(new ASTNode());
            }

            std::any visitMockup_module(MavkaParser::Mockup_moduleContext* context) override {
                const auto mockup_module_node = new MockupModuleNode();
                mockup_module_node->name = context->mm_name->getText();
                if (context->mm_elements) {
                    mockup_module_node->elements = std::any_cast<std::vector<ASTNode *>>(
                        visitMockup_body(context->mm_elements)
                    );
                }
                return create_ast_result(mockup_module_node);
            }

            std::any visitMockup_structure(MavkaParser::Mockup_structureContext* context) override {
                const auto mockup_structure_node = new MockupStructureNode();
                mockup_structure_node->name = context->ms_name->getText();
                if (context->ms_elements) {
                    mockup_structure_node->params = std::any_cast<std::vector<ASTNode *>>(
                        visitMockup_body(context->ms_elements)
                    );
                }
                return create_ast_result(mockup_structure_node);
            }

            std::any visitMockup_diia(MavkaParser::Mockup_diiaContext* context) override {
                const auto mockup_diia_node = new MockupDiiaNode();
                mockup_diia_node->async = context->md_async != nullptr;
                mockup_diia_node->name = context->md_name->getText();
                if (context->md_params) {
                    mockup_diia_node->params = std::any_cast<std::vector<ASTNode *>>(
                        visitParams(context->md_params)
                    );
                }
                if (context->md_type) {
                    mockup_diia_node->result = any_to_ast_result(visitType_value(context->md_type))->node;
                }
                return create_ast_result(mockup_diia_node);
            }

            std::any visitMockup_subject(MavkaParser::Mockup_subjectContext* context) override {
                const auto mockup_subject_node = new MockupSubjectNode();
                mockup_subject_node->name = context->ms_name->getText();
                mockup_subject_node->type = any_to_ast_result(visitType_value(context->ms_type))->node;
                return create_ast_result(mockup_subject_node);
            }

            std::any visitMockup_object(MavkaParser::Mockup_objectContext* context) override {
                const auto mockup_object_node = new MockupObjectNode();
                mockup_object_node->name = context->mo_name->getText();
                if (context->mo_elements) {
                    mockup_object_node->elements = std::any_cast<std::vector<ASTNode *>>(
                        visitMockup_body(context->mo_elements)
                    );
                }
                return create_ast_result(mockup_object_node);
            }

            std::any visitDiia(MavkaParser::DiiaContext* context) override {
                const auto diia_node = new DiiaNode();
                diia_node->async = context->d_async != nullptr;
                diia_node->structure = context->d_structure->getText();
                diia_node->name = context->d_name->getText();
                if (context->d_params) {
                    diia_node->params = std::any_cast<std::vector<ParamNode *>>(
                        visitParams(context->d_params)
                    );
                }
                if (context->d_type) {
                    diia_node->type = any_to_ast_result(visitType_value(context->d_type))->node;
                }
                if (context->d_body) {
                    diia_node->body = std::any_cast<std::vector<ASTNode *>>(
                        visitBody(context->d_body)
                    );
                }
                return create_ast_result(diia_node);
            }

            std::any visitIf(MavkaParser::IfContext* context) override {
                const auto if_node = new IfNode();
                if_node->condition = any_to_ast_result(visitExpr(context->i_value))->node;
                if_node->body = std::any_cast<std::vector<ASTNode *>>(
                    visitBody(context->i_body)
                );
                if (context->i_else_body) {
                    if_node->else_body = std::any_cast<std::vector<ASTNode *>>(
                        visitBody(context->i_else_body)
                    );
                }
                return create_ast_result(if_node);
            }

            std::any visitEach(MavkaParser::EachContext* context) override {
                const auto each_node = new EachNode();
                if (context->e_iterator) {
                    each_node->value = any_to_ast_result(visitExpr(context->e_iterator))->node;
                }
                if (context->e_fromto) {
                    each_node->value = any_to_ast_result(visitFromto(context->e_fromto))->node;
                }
                each_node->keyName = context->e_key_name->getText();
                each_node->name = context->e_name->getText();
                each_node->body = std::any_cast<std::vector<ASTNode *>>(
                    visitBody(context->e_body)
                );
                return create_ast_result(each_node);
            }

            // todo: fromto

            std::any visitWhile(MavkaParser::WhileContext* context) override {
                const auto while_node = new WhileNode();
                while_node->condition = any_to_ast_result(visitExpr(context->w_value))->node;
                while_node->body = std::any_cast<std::vector<ASTNode *>>(
                    visitBody(context->w_body)
                );
                return create_ast_result(while_node);
            }

            std::any visitTry(MavkaParser::TryContext* context) override {
                const auto try_node = new TryNode();
                try_node->body = std::any_cast<std::vector<ASTNode *>>(
                    visitBody(context->t_body)
                );
                try_node->name = context->tc_name->getText();
                try_node->catch_body = std::any_cast<std::vector<ASTNode *>>(
                    visitBody(context->tc_body)
                );
                return create_ast_result(try_node);
            }

            std::any visitExpr(MavkaParser::ExprContext* context) {
                if (instanceof<MavkaParser::SimpleContext>(context)) {
                    const auto simple_context = dynamic_cast<MavkaParser::SimpleContext *>(context);
                    return visitValue(simple_context->value());
                }
                if (instanceof<MavkaParser::WaitContext>(context)) {
                    const auto wait_context = dynamic_cast<MavkaParser::WaitContext *>(context);
                    return visitWait(wait_context);
                }
                if (instanceof<MavkaParser::FunctionContext>(context)) {
                    const auto function_context = dynamic_cast<MavkaParser::FunctionContext *>(context);
                    return visitFunction(function_context);
                }
                if (instanceof<MavkaParser::Anonymous_diiaContext>(context)) {
                    const auto anonymous_diia_context = dynamic_cast<MavkaParser::Anonymous_diiaContext *>(context);
                    return visitAnonymous_diia(anonymous_diia_context);
                }
                return create_ast_result(new ASTNode());
            }

            std::any visitValue(MavkaParser::ValueContext* context) {
                if (instanceof<MavkaParser::NumberContext>(context)) {
                    return visitNumber(dynamic_cast<MavkaParser::NumberContext *>(context));
                }
                if (instanceof<MavkaParser::String_valueContext>(context)) {
                    return visitString_value(dynamic_cast<MavkaParser::String_valueContext *>(context));
                }
                if (instanceof<MavkaParser::IdContext>(context)) {
                    return visitId(dynamic_cast<MavkaParser::IdContext *>(context));
                }
                if (instanceof<MavkaParser::ChainContext>(context)) {
                    return visitChain(dynamic_cast<MavkaParser::ChainContext *>(context));
                }
                if (instanceof<MavkaParser::CallContext>(context)) {
                    return visitCall(dynamic_cast<MavkaParser::CallContext *>(context));
                }
                if (instanceof<MavkaParser::Get_elementContext>(context)) {
                    return visitGet_element(dynamic_cast<MavkaParser::Get_elementContext *>(context));
                }
                if (instanceof<MavkaParser::PositiveContext>(context)) {
                    return visitPositive(dynamic_cast<MavkaParser::PositiveContext *>(context));
                }
                if (instanceof<MavkaParser::NegativeContext>(context)) {
                    return visitNegative(dynamic_cast<MavkaParser::NegativeContext *>(context));
                }
                if (instanceof<MavkaParser::Pre_decrementContext>(context)) {
                    return visitPre_decrement(dynamic_cast<MavkaParser::Pre_decrementContext *>(context));
                }
                if (instanceof<MavkaParser::Pre_incrementContext>(context)) {
                    return visitPre_increment(dynamic_cast<MavkaParser::Pre_incrementContext *>(context));
                }
                if (instanceof<MavkaParser::Post_decrementContext>(context)) {
                    return visitPost_decrement(dynamic_cast<MavkaParser::Post_decrementContext *>(context));
                }
                if (instanceof<MavkaParser::Post_incrementContext>(context)) {
                    return visitPost_increment(dynamic_cast<MavkaParser::Post_incrementContext *>(context));
                }
                if (instanceof<MavkaParser::NotContext>(context)) {
                    return visitNot(dynamic_cast<MavkaParser::NotContext *>(context));
                }
                if (instanceof<MavkaParser::Bitwise_notContext>(context)) {
                    return visitBitwise_not(dynamic_cast<MavkaParser::Bitwise_notContext *>(context));
                }
                if (instanceof<MavkaParser::NestedContext>(context)) {
                    return visitNested(dynamic_cast<MavkaParser::NestedContext *>(context));
                }
                if (instanceof<MavkaParser::Call_exprContext>(context)) {
                    return visitCall_expr(dynamic_cast<MavkaParser::Call_exprContext *>(context));
                }
                if (instanceof<MavkaParser::AsContext>(context)) {
                    return visitAs(dynamic_cast<MavkaParser::AsContext *>(context));
                }
                if (instanceof<MavkaParser::Arithmetic_mulContext>(context)) {
                    return visitArithmetic_mul(dynamic_cast<MavkaParser::Arithmetic_mulContext *>(context));
                }
                if (instanceof<MavkaParser::Arithmetic_addContext>(context)) {
                    return visitArithmetic_add(dynamic_cast<MavkaParser::Arithmetic_addContext *>(context));
                }
                if (instanceof<MavkaParser::BitwiseContext>(context)) {
                    return visitBitwise(dynamic_cast<MavkaParser::BitwiseContext *>(context));
                }
                if (instanceof<MavkaParser::ComparisonContext>(context)) {
                    return visitComparison(dynamic_cast<MavkaParser::ComparisonContext *>(context));
                }
                if (instanceof<MavkaParser::TestContext>(context)) {
                    return visitTest(dynamic_cast<MavkaParser::TestContext *>(context));
                }
                if (instanceof<MavkaParser::TernaryContext>(context)) {
                    return visitTernary(dynamic_cast<MavkaParser::TernaryContext *>(context));
                }
                if (instanceof<MavkaParser::ArrayContext>(context)) {
                    return visitArray(dynamic_cast<MavkaParser::ArrayContext *>(context));
                }
                if (instanceof<MavkaParser::DictionaryContext>(context)) {
                    return visitDictionary(dynamic_cast<MavkaParser::DictionaryContext *>(context));
                }
                if (instanceof<MavkaParser::GodContext>(context)) {
                    return visitGod(dynamic_cast<MavkaParser::GodContext *>(context));
                }
                return create_ast_result(new ASTNode());
            }

            std::any visitNumber(MavkaParser::NumberContext* context) override {
                const auto number_node = new NumberNode();
                number_node->value = context->getText();
                return create_ast_result(number_node);
            }

            std::any visitString_value(MavkaParser::String_valueContext* context) override {
                const auto string_node = new StringNode();
                string_node->value = context->getText();
                if (string_node->value.starts_with(R"(""")")) {
                    string_node->value = string_node->value.substr(3, string_node->value.length() - 6);
                } else {
                    string_node->value = string_node->value.substr(1, string_node->value.length() - 2);
                }
                return create_ast_result(string_node);
            }

            std::any visitId(MavkaParser::IdContext* context) override {
                const auto identifier_node = new IdentifierNode();
                identifier_node->name = context->getText();
                return create_ast_result(identifier_node);
            }

            std::any visitIdentifier(MavkaParser::IdentifierContext* context) override {
                const auto identifier_node = new IdentifierNode();
                identifier_node->name = context->getText();
                return create_ast_result(identifier_node);
            }

            std::any visitExtended_identifier(MavkaParser::Extended_identifierContext* context) override {
                const auto identifier_node = new IdentifierNode();
                identifier_node->name = context->getText();
                return create_ast_result(identifier_node);
            }

            std::any visitChain(MavkaParser::ChainContext* context) override {
                const auto chain_node = new ChainNode();
                chain_node->left = any_to_ast_result(visitValue(context->c_left))->node;
                chain_node->right = any_to_ast_result(visitExtended_identifier(context->c_right))->node;
                return create_ast_result(chain_node);
            }

            std::any visitCall(MavkaParser::CallContext* context) override {
                const auto call_node = new CallNode();
                call_node->value = any_to_ast_result(visitValue(context->c_value))->node;
                if (context->c_args) {
                    call_node->args = std::any_cast<std::vector<ArgNode *>>(
                        visitArgs(context->c_args)
                    );
                }
                if (context->c_named_args) {
                    call_node->args = std::any_cast<std::vector<ArgNode *>>(
                        visitNamed_args(context->c_named_args)
                    );
                }
                return create_ast_result(call_node);
            }

            std::any visitNested(MavkaParser::NestedContext* context) override {
                return visitExpr(context->n_value);
            }

            std::any visitArithmetic_mul(MavkaParser::Arithmetic_mulContext* context) override {
                const auto arithmetic_node = new ArithmeticNode();
                arithmetic_node->left = any_to_ast_result(visitValue(context->a_left))->node;
                arithmetic_node->right = any_to_ast_result(visitValue(context->a_right))->node;
                arithmetic_node->op = context->a_operation->getText();
                return create_ast_result(arithmetic_node);
            }

            std::any visitArithmetic_add(MavkaParser::Arithmetic_addContext* context) override {
                const auto arithmetic_node = new ArithmeticNode();
                arithmetic_node->left = any_to_ast_result(visitValue(context->a_left))->node;
                arithmetic_node->right = any_to_ast_result(visitValue(context->a_right))->node;
                arithmetic_node->op = context->a_operation->getText();
                return create_ast_result(arithmetic_node);
            }

            std::any visitWait(MavkaParser::WaitContext* context) override {
                const auto wait_node = new WaitNode();
                wait_node->value = any_to_ast_result(visitValue(context->w_value))->node;
                return create_ast_result(wait_node);
            }

            std::any visitFunction(MavkaParser::FunctionContext* context) override {
                const auto function_node = new FunctionNode();
                function_node->async = context->f_async != nullptr;
                if (context->f_params) {
                    function_node->params = std::any_cast<std::vector<ParamNode *>>(
                        visitParams(context->f_params)
                    );
                }
                if (context->f_type) {
                    function_node->type = any_to_ast_result(visitType_value(context->f_type))->node;
                }
                if (context->f_body) {
                    const auto function_node_body = std::any_cast<ASTNode *>(
                        visitExpr(context->f_body)
                    );
                    function_node->body.push_back(function_node_body);
                }
                return create_ast_result(function_node);
            }

            std::any visitAnonymous_diia(MavkaParser::Anonymous_diiaContext* context) override {
                const auto function_node = new AnonDiiaNode();
                function_node->async = context->d_async != nullptr;
                if (context->d_params) {
                    function_node->params = std::any_cast<std::vector<ParamNode *>>(
                        visitParams(context->d_params)
                    );
                }
                if (context->d_type) {
                    function_node->type = any_to_ast_result(visitType_value(context->d_type))->node;
                }
                if (context->d_body) {
                    function_node->body = std::any_cast<std::vector<ASTNode *>>(
                        visitBody(context->d_body)
                    );
                }
                return create_ast_result(function_node);
            }

            std::any visitThrow(MavkaParser::ThrowContext* context) override {
                const auto throw_node = new ThrowNode();
                throw_node->value = any_to_ast_result(visitExpr(context->t_value))->node;
                return create_ast_result(throw_node);
            }

            std::any visitEval(MavkaParser::EvalContext* context) override {
                const auto eval_node = new EvalNode();
                eval_node->value = any_to_ast_result(visitValue(context->e_value))->node;
                return create_ast_result(eval_node);
            }

            std::any visitWait_assign(MavkaParser::Wait_assignContext* context) override {
                // const auto assign_node = visitAssign(context->wa_assign);
                // const auto wait_node = new WaitNode();
                // wait_node->value = any_to_ast_result(assign_node)->node;
                // assign_node->node = wait_node;
                // return create_ast_result(assign_node);
                return create_ast_result(new ASTNode());
            }

            std::any visitAssign(MavkaParser::AssignContext* context) override {
                if (context->assign_simple()) {
                    return visitAssign_simple(context->assign_simple());
                }
                if (context->assign_complex()) {
                    return visitAssign_complex(context->assign_complex());
                }
                return create_ast_result(new ASTNode());
            }

            std::any visitAssign_simple(MavkaParser::Assign_simpleContext* context) override {
                const auto assign_simple_node = new AssignSimpleNode();
                assign_simple_node->name = context->as_identifier->ID()->getText();
                if (context->as_type) {
                    assign_simple_node->type = any_to_ast_result(visitType_value(context->as_type))->node;
                }
                assign_simple_node->op = context->assign_symbol()->getText();
                assign_simple_node->value = any_to_ast_result(visitExpr(context->as_value))->node;
                return create_ast_result(assign_simple_node);
            }

            std::any visitAssign_complex(MavkaParser::Assign_complexContext* context) override {
                const auto assign_complex_node = new AssignComplexNode();
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
                    const auto get_element_node = new GetElementNode();
                    get_element_node->value = any_to_ast_result(visitAssign_complex_left(context->acl_left))->node;
                    get_element_node->index = any_to_ast_result(visitExpr(context->acl_element))->node;
                    return create_ast_result(get_element_node);
                }
                return create_ast_result(new ASTNode());
            }

            std::any visitAssign_complex_right(MavkaParser::Assign_complex_rightContext* context) override {
                const auto assign_complex_right_node = new AssignComplexRightNode();
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
                return create_ast_result(new ASTNode());
            }

            std::any visitAssign_object_destruction(MavkaParser::Assign_object_destructionContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitAssign_symbol(MavkaParser::Assign_symbolContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitTake_module(MavkaParser::Take_moduleContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitTake_file(MavkaParser::Take_fileContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitTake_remote(MavkaParser::Take_remoteContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitGive(MavkaParser::GiveContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitGive_element(MavkaParser::Give_elementContext* context) override {
                // todo
                return create_ast_result(new ASTNode());
            }

            std::any visitParams(MavkaParser::ParamsContext* context) override {
                std::vector<ParamNode *> params;
                for (int i = 0; i < context->param().size(); ++i) {
                    const auto param = context->param()[i];
                    const auto ast_result = any_to_ast_result(visitParam(param));
                    params.push_back(dynamic_cast<ParamNode *>(ast_result->node));
                }
                return params;
            }

            std::any visitParam(MavkaParser::ParamContext* context) override {
                const auto param_node = new ParamNode();
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
                return create_ast_result(new ASTNode());
            }

            std::any visitArgs(MavkaParser::ArgsContext* context) override {
                std::vector<ArgNode *> args;
                for (int i = 0; i < context->arg().size(); ++i) {
                    const auto arg = context->arg()[i];
                    const auto ast_result = any_to_ast_result(visitArg(arg, i));
                    args.push_back(dynamic_cast<ArgNode *>(ast_result->node));
                }
                return args;
            }

            std::any visitArg(MavkaParser::ArgContext* context, int index) {
                const auto arg_node = new ArgNode();
                arg_node->index = index;
                arg_node->value = any_to_ast_result(visitExpr(context->a_value))->node;
                return create_ast_result(arg_node);
            }

            std::any visitNamed_args(MavkaParser::Named_argsContext* context) override {
                std::vector<ArgNode *> args;
                for (int i = 0; i < context->named_arg().size(); ++i) {
                    const auto arg = context->named_arg()[i];
                    const auto ast_result = any_to_ast_result(visitNamed_arg(arg, i));
                    args.push_back(dynamic_cast<ArgNode *>(ast_result->node));
                }
                return args;
            }

            std::any visitNamed_arg(MavkaParser::Named_argContext* context, int index) {
                const auto arg_node = new ArgNode();
                arg_node->index = index;
                arg_node->name = context->na_name->getText();
                arg_node->value = any_to_ast_result(visitExpr(context->na_value))->node;
                return create_ast_result(arg_node);
            }
        };
    }
}
