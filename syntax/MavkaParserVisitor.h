
// Generated from MavkaParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "MavkaParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MavkaParser.
 */
class  MavkaParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MavkaParser.
   */
    virtual std::any visitFile(MavkaParser::FileContext *context) = 0;

    virtual std::any visitProgram(MavkaParser::ProgramContext *context) = 0;

    virtual std::any visitProgram_element(MavkaParser::Program_elementContext *context) = 0;

    virtual std::any visitModule(MavkaParser::ModuleContext *context) = 0;

    virtual std::any visitModule_body(MavkaParser::Module_bodyContext *context) = 0;

    virtual std::any visitModule_body_element(MavkaParser::Module_body_elementContext *context) = 0;

    virtual std::any visitMethod_declaration(MavkaParser::Method_declarationContext *context) = 0;

    virtual std::any visitStructure(MavkaParser::StructureContext *context) = 0;

    virtual std::any visitStructure_elements(MavkaParser::Structure_elementsContext *context) = 0;

    virtual std::any visitStructure_element(MavkaParser::Structure_elementContext *context) = 0;

    virtual std::any visitStructure_param(MavkaParser::Structure_paramContext *context) = 0;

    virtual std::any visitMockup(MavkaParser::MockupContext *context) = 0;

    virtual std::any visitMockup_module(MavkaParser::Mockup_moduleContext *context) = 0;

    virtual std::any visitMockup_structure(MavkaParser::Mockup_structureContext *context) = 0;

    virtual std::any visitMockup_diia(MavkaParser::Mockup_diiaContext *context) = 0;

    virtual std::any visitMockup_subject(MavkaParser::Mockup_subjectContext *context) = 0;

    virtual std::any visitMockup_object(MavkaParser::Mockup_objectContext *context) = 0;

    virtual std::any visitMockup_body(MavkaParser::Mockup_bodyContext *context) = 0;

    virtual std::any visitMockup_body_element(MavkaParser::Mockup_body_elementContext *context) = 0;

    virtual std::any visitDiia(MavkaParser::DiiaContext *context) = 0;

    virtual std::any visitIf(MavkaParser::IfContext *context) = 0;

    virtual std::any visitEach(MavkaParser::EachContext *context) = 0;

    virtual std::any visitFromto(MavkaParser::FromtoContext *context) = 0;

    virtual std::any visitFromto_simple(MavkaParser::Fromto_simpleContext *context) = 0;

    virtual std::any visitFromto_complex(MavkaParser::Fromto_complexContext *context) = 0;

    virtual std::any visitFromto_number(MavkaParser::Fromto_numberContext *context) = 0;

    virtual std::any visitFromto_string(MavkaParser::Fromto_stringContext *context) = 0;

    virtual std::any visitFromto_id(MavkaParser::Fromto_idContext *context) = 0;

    virtual std::any visitFromto_nested(MavkaParser::Fromto_nestedContext *context) = 0;

    virtual std::any visitFromto_middle_symbol(MavkaParser::Fromto_middle_symbolContext *context) = 0;

    virtual std::any visitFromto_to_symbol(MavkaParser::Fromto_to_symbolContext *context) = 0;

    virtual std::any visitWhile(MavkaParser::WhileContext *context) = 0;

    virtual std::any visitTry(MavkaParser::TryContext *context) = 0;

    virtual std::any visitEval(MavkaParser::EvalContext *context) = 0;

    virtual std::any visitTake_module(MavkaParser::Take_moduleContext *context) = 0;

    virtual std::any visitTake_file(MavkaParser::Take_fileContext *context) = 0;

    virtual std::any visitTake_remote(MavkaParser::Take_remoteContext *context) = 0;

    virtual std::any visitGive(MavkaParser::GiveContext *context) = 0;

    virtual std::any visitGive_element(MavkaParser::Give_elementContext *context) = 0;

    virtual std::any visitString(MavkaParser::StringContext *context) = 0;

    virtual std::any visitPre_increment(MavkaParser::Pre_incrementContext *context) = 0;

    virtual std::any visitArithmetic_add(MavkaParser::Arithmetic_addContext *context) = 0;

    virtual std::any visitBitwise_not(MavkaParser::Bitwise_notContext *context) = 0;

    virtual std::any visitNested(MavkaParser::NestedContext *context) = 0;

    virtual std::any visitNumber(MavkaParser::NumberContext *context) = 0;

    virtual std::any visitNegative(MavkaParser::NegativeContext *context) = 0;

    virtual std::any visitNot(MavkaParser::NotContext *context) = 0;

    virtual std::any visitArray(MavkaParser::ArrayContext *context) = 0;

    virtual std::any visitBitwise(MavkaParser::BitwiseContext *context) = 0;

    virtual std::any visitPost_decrement(MavkaParser::Post_decrementContext *context) = 0;

    virtual std::any visitId(MavkaParser::IdContext *context) = 0;

    virtual std::any visitArithmetic_mul(MavkaParser::Arithmetic_mulContext *context) = 0;

    virtual std::any visitGet_element(MavkaParser::Get_elementContext *context) = 0;

    virtual std::any visitChain(MavkaParser::ChainContext *context) = 0;

    virtual std::any visitString_value(MavkaParser::String_valueContext *context) = 0;

    virtual std::any visitComparison(MavkaParser::ComparisonContext *context) = 0;

    virtual std::any visitTest(MavkaParser::TestContext *context) = 0;

    virtual std::any visitCall_expr(MavkaParser::Call_exprContext *context) = 0;

    virtual std::any visitPositive(MavkaParser::PositiveContext *context) = 0;

    virtual std::any visitCall(MavkaParser::CallContext *context) = 0;

    virtual std::any visitAs(MavkaParser::AsContext *context) = 0;

    virtual std::any visitDictionary(MavkaParser::DictionaryContext *context) = 0;

    virtual std::any visitPre_decrement(MavkaParser::Pre_decrementContext *context) = 0;

    virtual std::any visitPost_increment(MavkaParser::Post_incrementContext *context) = 0;

    virtual std::any visitTernary(MavkaParser::TernaryContext *context) = 0;

    virtual std::any visitGod(MavkaParser::GodContext *context) = 0;

    virtual std::any visitArray_elements(MavkaParser::Array_elementsContext *context) = 0;

    virtual std::any visitArray_element(MavkaParser::Array_elementContext *context) = 0;

    virtual std::any visitDictionary_args(MavkaParser::Dictionary_argsContext *context) = 0;

    virtual std::any visitDictionary_arg(MavkaParser::Dictionary_argContext *context) = 0;

    virtual std::any visitSimple(MavkaParser::SimpleContext *context) = 0;

    virtual std::any visitWait(MavkaParser::WaitContext *context) = 0;

    virtual std::any visitFunction(MavkaParser::FunctionContext *context) = 0;

    virtual std::any visitAnonymous_diia(MavkaParser::Anonymous_diiaContext *context) = 0;

    virtual std::any visitThrow(MavkaParser::ThrowContext *context) = 0;

    virtual std::any visitArray_destruction(MavkaParser::Array_destructionContext *context) = 0;

    virtual std::any visitArray_destruction_el(MavkaParser::Array_destruction_elContext *context) = 0;

    virtual std::any visitObject_destruction(MavkaParser::Object_destructionContext *context) = 0;

    virtual std::any visitObject_destruction_el(MavkaParser::Object_destruction_elContext *context) = 0;

    virtual std::any visitAssign(MavkaParser::AssignContext *context) = 0;

    virtual std::any visitAssign_simple(MavkaParser::Assign_simpleContext *context) = 0;

    virtual std::any visitAssign_complex(MavkaParser::Assign_complexContext *context) = 0;

    virtual std::any visitAssign_complex_left(MavkaParser::Assign_complex_leftContext *context) = 0;

    virtual std::any visitAssign_complex_right(MavkaParser::Assign_complex_rightContext *context) = 0;

    virtual std::any visitAssign_array_destruction(MavkaParser::Assign_array_destructionContext *context) = 0;

    virtual std::any visitAssign_object_destruction(MavkaParser::Assign_object_destructionContext *context) = 0;

    virtual std::any visitAssign_symbol(MavkaParser::Assign_symbolContext *context) = 0;

    virtual std::any visitWait_assign(MavkaParser::Wait_assignContext *context) = 0;

    virtual std::any visitIdentifier(MavkaParser::IdentifierContext *context) = 0;

    virtual std::any visitExtended_identifier(MavkaParser::Extended_identifierContext *context) = 0;

    virtual std::any visitIdentifiers_chain(MavkaParser::Identifiers_chainContext *context) = 0;

    virtual std::any visitType_value(MavkaParser::Type_valueContext *context) = 0;

    virtual std::any visitType_value_array(MavkaParser::Type_value_arrayContext *context) = 0;

    virtual std::any visitArgs(MavkaParser::ArgsContext *context) = 0;

    virtual std::any visitArg(MavkaParser::ArgContext *context) = 0;

    virtual std::any visitNamed_args(MavkaParser::Named_argsContext *context) = 0;

    virtual std::any visitNamed_arg(MavkaParser::Named_argContext *context) = 0;

    virtual std::any visitParams(MavkaParser::ParamsContext *context) = 0;

    virtual std::any visitParam(MavkaParser::ParamContext *context) = 0;

    virtual std::any visitParam_value_number(MavkaParser::Param_value_numberContext *context) = 0;

    virtual std::any visitParam_value_string(MavkaParser::Param_value_stringContext *context) = 0;

    virtual std::any visitParam_value_identifier(MavkaParser::Param_value_identifierContext *context) = 0;

    virtual std::any visitParam_value_empty_dictionary(MavkaParser::Param_value_empty_dictionaryContext *context) = 0;

    virtual std::any visitParam_value_empty_list(MavkaParser::Param_value_empty_listContext *context) = 0;

    virtual std::any visitBody(MavkaParser::BodyContext *context) = 0;

    virtual std::any visitBody_element_or_return(MavkaParser::Body_element_or_returnContext *context) = 0;

    virtual std::any visitBody_element(MavkaParser::Body_elementContext *context) = 0;

    virtual std::any visitReturn_body_line(MavkaParser::Return_body_lineContext *context) = 0;

    virtual std::any visitArithmetic_op_mul(MavkaParser::Arithmetic_op_mulContext *context) = 0;

    virtual std::any visitArithmetic_op_add(MavkaParser::Arithmetic_op_addContext *context) = 0;

    virtual std::any visitBitwise_op(MavkaParser::Bitwise_opContext *context) = 0;

    virtual std::any visitTest_op(MavkaParser::Test_opContext *context) = 0;

    virtual std::any visitComparison_op(MavkaParser::Comparison_opContext *context) = 0;

    virtual std::any visitNl(MavkaParser::NlContext *context) = 0;

    virtual std::any visitNls(MavkaParser::NlsContext *context) = 0;


};

