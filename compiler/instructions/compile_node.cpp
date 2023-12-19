#include "compile_node.h"

#include <stdexcept>

#include "compile_anon_diia_node.h"
#include "compile_arg_node.h"
#include "compile_arithmetic_node.h"
#include "compile_array_node.h"
#include "compile_assign_by_element_node.h"
#include "compile_assign_by_identifier_node.h"
#include "compile_assign_simple_node.h"
#include "compile_as_node.h"
#include "compile_bitwise_node.h"
#include "compile_bitwise_not_node.h"
#include "compile_call_node.h"
#include "compile_chain_node.h"
#include "compile_comparison_node.h"
#include "compile_continue_node.h"
#include "compile_dictionary_node.h"
#include "compile_diia_node.h"
#include "compile_each_node.h"
#include "compile_eval_node.h"
#include "compile_from_to_complex_node.h"
#include "compile_from_to_simple_node.h"
#include "compile_function_node.h"
#include "compile_get_element_node.h"
#include "compile_give_node.h"
#include "compile_god_node.h"
#include "compile_identifier_node.h"
#include "compile_if_node.h"
#include "compile_mockup_diia_node.h"
#include "compile_mockup_module_node.h"
#include "compile_mockup_object_node.h"
#include "compile_mockup_structure_node.h"
#include "compile_mockup_subject_node.h"
#include "compile_module_node.h"
#include "compile_negative_node.h"
#include "compile_not_node.h"
#include "compile_number_node.h"
#include "compile_positive_node.h"
#include "compile_post_decrement_node.h"
#include "compile_post_increment_node.h"
#include "compile_pre_decrement_node.h"
#include "compile_pre_increment_node.h"
#include "compile_return_node.h"
#include "compile_string_node.h"
#include "compile_structure_node.h"
#include "compile_take_module_node.h"
#include "compile_take_pak_node.h"
#include "compile_ternary_node.h"
#include "compile_test_node.h"
#include "compile_throw_node.h"
#include "compile_try_node.h"
#include "compile_type_value_node.h"
#include "compile_type_value_single_node.h"
#include "compile_wait_node.h"
#include "compile_while_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options) {
        if (jejalyk::tools::instanceof<mavka::ast::AnonDiiaNode>(node)) {
            return compile_anon_diia_node(dynamic_cast<mavka::ast::AnonDiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArithmeticNode>(node)) {
            return compile_arithmetic_node(dynamic_cast<mavka::ast::ArithmeticNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArrayNode>(node)) {
            return compile_array_node(dynamic_cast<mavka::ast::ArrayNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AsNode>(node)) {
            return compile_as_node(dynamic_cast<mavka::ast::AsNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignByIdentifierNode>(node)) {
            return compile_assign_by_identifier_node(dynamic_cast<mavka::ast::AssignByIdentifierNode *>(node), scope,
                                                     options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignByElementNode>(node)) {
            return compile_assign_by_element_node(dynamic_cast<mavka::ast::AssignByElementNode *>(node), scope,
                                                  options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignSimpleNode>(node)) {
            return compile_assign_simple_node(dynamic_cast<mavka::ast::AssignSimpleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNode>(node)) {
            return compile_bitwise_node(dynamic_cast<mavka::ast::BitwiseNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNotNode>(node)) {
            return compile_bitwise_not_node(dynamic_cast<mavka::ast::BitwiseNotNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::CallNode>(node)) {
            return compile_call_node(dynamic_cast<mavka::ast::CallNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArgNode>(node)) {
            return compile_arg_node(dynamic_cast<mavka::ast::ArgNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ChainNode>(node)) {
            return compile_chain_node(dynamic_cast<mavka::ast::ChainNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ComparisonNode>(node)) {
            return compile_comparison_node(dynamic_cast<mavka::ast::ComparisonNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ContinueNode>(node)) {
            return compile_continue_node(dynamic_cast<mavka::ast::ContinueNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::DiiaNode>(node)) {
            return compile_diia_node(dynamic_cast<mavka::ast::DiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::EachNode>(node)) {
            return compile_each_node(dynamic_cast<mavka::ast::EachNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::EvalNode>(node)) {
            return compile_eval_node(dynamic_cast<mavka::ast::EvalNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FunctionNode>(node)) {
            return compile_function_node(dynamic_cast<mavka::ast::FunctionNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FromToSimpleNode>(node)) {
            return compile_from_to_simple_node(dynamic_cast<mavka::ast::FromToSimpleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FromToComplexNode>(node)) {
            return compile_from_to_complex_node(dynamic_cast<mavka::ast::FromToComplexNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GetElementNode>(node)) {
            return compile_get_element_node(dynamic_cast<mavka::ast::GetElementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GiveNode>(node)) {
            return compile_give_node(dynamic_cast<mavka::ast::GiveNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GodNode>(node)) {
            return compile_god_node(dynamic_cast<mavka::ast::GodNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(node)) {
            return compile_identifier_node(dynamic_cast<mavka::ast::IdentifierNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::IfNode>(node)) {
            return compile_if_node(dynamic_cast<mavka::ast::IfNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ModuleNode>(node)) {
            return compile_module_node(dynamic_cast<mavka::ast::ModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupDiiaNode>(node)) {
            return compile_mockup_diia_node(dynamic_cast<mavka::ast::MockupDiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupModuleNode>(node)) {
            return compile_mockup_module_node(dynamic_cast<mavka::ast::MockupModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupObjectNode>(node)) {
            return compile_mockup_object_node(dynamic_cast<mavka::ast::MockupObjectNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupStructureNode>(node)) {
            return compile_mockup_structure_node(dynamic_cast<mavka::ast::MockupStructureNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupSubjectNode>(node)) {
            return compile_mockup_subject_node(dynamic_cast<mavka::ast::MockupSubjectNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NegativeNode>(node)) {
            return compile_negative_node(dynamic_cast<mavka::ast::NegativeNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NotNode>(node)) {
            return compile_not_node(dynamic_cast<mavka::ast::NotNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NumberNode>(node)) {
            return compile_number_node(dynamic_cast<mavka::ast::NumberNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PositiveNode>(node)) {
            return compile_positive_node(dynamic_cast<mavka::ast::PositiveNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostDecrementNode>(node)) {
            return compile_post_decrement_node(dynamic_cast<mavka::ast::PostDecrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostIncrementNode>(node)) {
            return compile_post_increment_node(dynamic_cast<mavka::ast::PostIncrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreDecrementNode>(node)) {
            return compile_pre_decrement_node(dynamic_cast<mavka::ast::PreDecrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreIncrementNode>(node)) {
            return compile_pre_increment_node(dynamic_cast<mavka::ast::PreIncrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::DictionaryNode>(node)) {
            return compile_dictionary_node(dynamic_cast<mavka::ast::DictionaryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ReturnNode>(node)) {
            return compile_return_node(dynamic_cast<mavka::ast::ReturnNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::StringNode>(node)) {
            return compile_string_node(dynamic_cast<mavka::ast::StringNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::StructureNode>(node)) {
            return compile_structure_node(dynamic_cast<mavka::ast::StructureNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakeModuleNode>(node)) {
            return compile_take_module_node(dynamic_cast<mavka::ast::TakeModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakePakNode>(node)) {
            return compile_take_pak_node(dynamic_cast<mavka::ast::TakePakNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TernaryNode>(node)) {
            return compile_ternary_node(dynamic_cast<mavka::ast::TernaryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TestNode>(node)) {
            return compile_test_node(dynamic_cast<mavka::ast::TestNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ThrowNode>(node)) {
            return compile_throw_node(dynamic_cast<mavka::ast::ThrowNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TryNode>(node)) {
            return compile_try_node(dynamic_cast<mavka::ast::TryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueNode>(node)) {
            return compile_type_value_node(dynamic_cast<mavka::ast::TypeValueNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueSingleNode>(node)) {
            return compile_type_value_single_node(dynamic_cast<mavka::ast::TypeValueSingleNode *>(node), scope,
                                                  options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::WaitNode>(node)) {
            return compile_wait_node(dynamic_cast<mavka::ast::WaitNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::WhileNode>(node)) {
            return compile_while_node(dynamic_cast<mavka::ast::WhileNode *>(node), scope, options);
        }

        if (node == nullptr) {
            const auto node_compilation_result = new NodeCompilationResult();
            node_compilation_result->result = "";
            return node_compilation_result;
        }

        throw std::runtime_error("Unknown node type");
    }
}
