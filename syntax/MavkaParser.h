
// Generated from MavkaParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaParser : public antlr4::Parser {
public:
  enum {
    NL = 1, WS = 2, KW_END = 3, KW_DIIA = 4, KW_STRUCTURE = 5, KW_FOR = 6, 
    KW_IF = 7, KW_WAIT = 8, KW_TAKE = 9, KW_GIVE = 10, KW_AS = 11, KW_TA = 12, 
    KW_IS = 13, KW_SPEC = 14, KW_RETURN = 15, KW_ASYNC = 16, KW_SUBJECT = 17, 
    KW_AND = 18, KW_OR = 19, KW_TRY = 20, KW_CATCH = 21, KW_ELSE = 22, KW_THROW = 23, 
    KW_WHILE = 24, KW_MODULE = 25, KW_EQ_WORD = 26, KW_GR_WORD = 27, KW_SM_WORD = 28, 
    KW_HAS_IS_WORD = 29, KW_MOCKUP = 30, KW_NOT = 31, KW_JS = 32, KW_PARENT = 33, 
    KW_TSE = 34, EQUAL = 35, GREATER = 36, LESSER = 37, DOT = 38, PLUS = 39, 
    MINUS = 40, MULTIPLY = 41, DIVIDE = 42, MOD = 43, POWER = 44, AND = 45, 
    OR = 46, PAREN_OPEN = 47, PAREN_CLOSE = 48, BRACKET_OPEN = 49, BRACKET_CLOSE = 50, 
    QUESTION = 51, COLON = 52, TILDA = 53, QUOTE = 54, DOUBLE_QUOTE = 55, 
    EXCLAMATION = 56, COMA = 57, INTEGER = 58, FLOAT = 59, HEX = 60, BIN = 61, 
    ID = 62, KWID = 63, STRING_MULTILINE = 64, STRING = 65, COMP_INST_START = 66, 
    COMP_INST_END = 67, COMP_INST_ASSIGN = 68, COMMENT = 69, LINE_COMMENT = 70
  };

  enum {
    RuleWs = 0, RuleWss = 1, RuleNl = 2, RuleNls = 3, RuleNumber_token = 4, 
    RuleString = 5, RuleIdentifier = 6, RuleFile = 7, RuleProgram = 8, RuleProgram_element = 9, 
    RuleModule = 10, RuleModule_body = 11, RuleModule_body_element = 12, 
    RuleStructure = 13, RuleStructure_elements = 14, RuleStructure_element = 15, 
    RuleStructure_param = 16, RuleGenerics = 17, RuleMockup = 18, RuleMockup_module = 19, 
    RuleMockup_module_body = 20, RuleMockup_structure = 21, RuleMockup_structure_body = 22, 
    RuleMockup_structure_body_element = 23, RuleMockup_diia = 24, RuleMockup_subject = 25, 
    RuleDiia = 26, RuleIf = 27, RuleEach = 28, RuleFromto = 29, RuleFromto_simple = 30, 
    RuleFromto_complex = 31, RuleFromto_value = 32, RuleFromto_middle_symbol = 33, 
    RuleFromto_to_symbol = 34, RuleWhile = 35, RuleTry = 36, RuleEval = 37, 
    RuleTake = 38, RuleTake_module_elements = 39, RuleTake_module_element = 40, 
    RuleGive = 41, RuleGive_element = 42, RuleAtom = 43, RuleValue = 44, 
    RuleCall_generics = 45, RuleArray_elements = 46, RuleArray_element = 47, 
    RuleDictionary_args = 48, RuleDictionary_arg = 49, RuleExpr = 50, RuleThrow = 51, 
    RuleAssign = 52, RuleAssign_simple = 53, RuleAssign_by_identifier = 54, 
    RuleAssign_by_element = 55, RuleAssign_symbol = 56, RuleWait_assign = 57, 
    RuleIdentifiers_chain = 58, RuleSuper_identifiers_chain = 59, RuleType_value = 60, 
    RuleType_value_item = 61, RuleType_value_item_simple = 62, RuleType_value_item_generics = 63, 
    RuleType_value_item_array = 64, RuleArgs = 65, RuleArg = 66, RuleNamed_args = 67, 
    RuleNamed_arg = 68, RuleParams = 69, RuleParam = 70, RuleParam_value = 71, 
    RuleBody = 72, RuleBody_element_or_return = 73, RuleBody_element = 74, 
    RuleReturn_body_line = 75, RuleArithmetic_op_mul = 76, RuleArithmetic_op_add = 77, 
    RuleBitwise_op = 78, RuleTest_op = 79, RuleComparison_op = 80, RuleComp_inst_block_program = 81, 
    RuleComp_inst_assign = 82
  };

  explicit MavkaParser(antlr4::TokenStream *input);

  MavkaParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MavkaParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class WsContext;
  class WssContext;
  class NlContext;
  class NlsContext;
  class Number_tokenContext;
  class StringContext;
  class IdentifierContext;
  class FileContext;
  class ProgramContext;
  class Program_elementContext;
  class ModuleContext;
  class Module_bodyContext;
  class Module_body_elementContext;
  class StructureContext;
  class Structure_elementsContext;
  class Structure_elementContext;
  class Structure_paramContext;
  class GenericsContext;
  class MockupContext;
  class Mockup_moduleContext;
  class Mockup_module_bodyContext;
  class Mockup_structureContext;
  class Mockup_structure_bodyContext;
  class Mockup_structure_body_elementContext;
  class Mockup_diiaContext;
  class Mockup_subjectContext;
  class DiiaContext;
  class IfContext;
  class EachContext;
  class FromtoContext;
  class Fromto_simpleContext;
  class Fromto_complexContext;
  class Fromto_valueContext;
  class Fromto_middle_symbolContext;
  class Fromto_to_symbolContext;
  class WhileContext;
  class TryContext;
  class EvalContext;
  class TakeContext;
  class Take_module_elementsContext;
  class Take_module_elementContext;
  class GiveContext;
  class Give_elementContext;
  class AtomContext;
  class ValueContext;
  class Call_genericsContext;
  class Array_elementsContext;
  class Array_elementContext;
  class Dictionary_argsContext;
  class Dictionary_argContext;
  class ExprContext;
  class ThrowContext;
  class AssignContext;
  class Assign_simpleContext;
  class Assign_by_identifierContext;
  class Assign_by_elementContext;
  class Assign_symbolContext;
  class Wait_assignContext;
  class Identifiers_chainContext;
  class Super_identifiers_chainContext;
  class Type_valueContext;
  class Type_value_itemContext;
  class Type_value_item_simpleContext;
  class Type_value_item_genericsContext;
  class Type_value_item_arrayContext;
  class ArgsContext;
  class ArgContext;
  class Named_argsContext;
  class Named_argContext;
  class ParamsContext;
  class ParamContext;
  class Param_valueContext;
  class BodyContext;
  class Body_element_or_returnContext;
  class Body_elementContext;
  class Return_body_lineContext;
  class Arithmetic_op_mulContext;
  class Arithmetic_op_addContext;
  class Bitwise_opContext;
  class Test_opContext;
  class Comparison_opContext;
  class Comp_inst_block_programContext;
  class Comp_inst_assignContext; 

  class  WsContext : public antlr4::ParserRuleContext {
  public:
    WsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WsContext* ws();

  class  WssContext : public antlr4::ParserRuleContext {
  public:
    WssContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WssContext* wss();

  class  NlContext : public antlr4::ParserRuleContext {
  public:
    NlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NL();
    antlr4::tree::TerminalNode* NL(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NlContext* nl();

  class  NlsContext : public antlr4::ParserRuleContext {
  public:
    NlsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NL();
    antlr4::tree::TerminalNode* NL(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NlsContext* nls();

  class  Number_tokenContext : public antlr4::ParserRuleContext {
  public:
    Number_tokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *HEX();
    antlr4::tree::TerminalNode *BIN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Number_tokenContext* number_token();

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *STRING_MULTILINE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringContext* string();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ProgramContext *f_program = nullptr;
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    ProgramContext *program();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Program_elementContext *> program_element();
    Program_elementContext* program_element(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  Program_elementContext : public antlr4::ParserRuleContext {
  public:
    Program_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ModuleContext *module();
    StructureContext *structure();
    MockupContext *mockup();
    DiiaContext *diia();
    IfContext *if_();
    EachContext *each();
    WhileContext *while_();
    TryContext *try_();
    ExprContext *expr();
    ThrowContext *throw_();
    EvalContext *eval();
    Wait_assignContext *wait_assign();
    AssignContext *assign();
    TakeContext *take();
    GiveContext *give();
    Comp_inst_block_programContext *comp_inst_block_program();
    Comp_inst_assignContext *comp_inst_assign();
    NlsContext *nls();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Program_elementContext* program_element();

  class  ModuleContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *m_name = nullptr;
    MavkaParser::Module_bodyContext *m_body = nullptr;
    ModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_MODULE();
    WsContext *ws();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    IdentifierContext *identifier();
    Module_bodyContext *module_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleContext* module();

  class  Module_bodyContext : public antlr4::ParserRuleContext {
  public:
    Module_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Module_body_elementContext *> module_body_element();
    Module_body_elementContext* module_body_element(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Module_bodyContext* module_body();

  class  Module_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Module_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ModuleContext *module();
    StructureContext *structure();
    MockupContext *mockup();
    DiiaContext *diia();
    IfContext *if_();
    EachContext *each();
    WhileContext *while_();
    TryContext *try_();
    ExprContext *expr();
    ThrowContext *throw_();
    EvalContext *eval();
    Wait_assignContext *wait_assign();
    AssignContext *assign();
    GiveContext *give();
    NlsContext *nls();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Module_body_elementContext* module_body_element();

  class  StructureContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *s_name = nullptr;
    MavkaParser::GenericsContext *s_generics = nullptr;
    MavkaParser::Super_identifiers_chainContext *s_parent = nullptr;
    MavkaParser::GenericsContext *s_parent_generics = nullptr;
    MavkaParser::Structure_elementsContext *s_elements = nullptr;
    StructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_STRUCTURE();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    NlsContext *nls();
    antlr4::tree::TerminalNode *KW_END();
    IdentifierContext *identifier();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESSER();
    antlr4::tree::TerminalNode* LESSER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    antlr4::tree::TerminalNode *KW_IS();
    std::vector<GenericsContext *> generics();
    GenericsContext* generics(size_t i);
    Super_identifiers_chainContext *super_identifiers_chain();
    Structure_elementsContext *structure_elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructureContext* structure();

  class  Structure_elementsContext : public antlr4::ParserRuleContext {
  public:
    Structure_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Structure_elementContext *> structure_element();
    Structure_elementContext* structure_element(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Structure_elementsContext* structure_elements();

  class  Structure_elementContext : public antlr4::ParserRuleContext {
  public:
    Structure_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Structure_paramContext *structure_param();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Structure_elementContext* structure_element();

  class  Structure_paramContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *sp_static = nullptr;
    MavkaParser::IdentifierContext *sp_name = nullptr;
    MavkaParser::Type_valueContext *sp_type = nullptr;
    MavkaParser::Param_valueContext *sp_value = nullptr;
    Structure_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    IdentifierContext *identifier();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *KW_SPEC();
    Type_valueContext *type_value();
    Param_valueContext *param_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Structure_paramContext* structure_param();

  class  GenericsContext : public antlr4::ParserRuleContext {
  public:
    GenericsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericsContext* generics();

  class  MockupContext : public antlr4::ParserRuleContext {
  public:
    MockupContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Mockup_moduleContext *mockup_module();
    Mockup_structureContext *mockup_structure();
    Mockup_diiaContext *mockup_diia();
    Mockup_subjectContext *mockup_subject();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MockupContext* mockup();

  class  Mockup_moduleContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *mm_name = nullptr;
    MavkaParser::Mockup_module_bodyContext *mm_elements = nullptr;
    Mockup_moduleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_MOCKUP();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_MODULE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    IdentifierContext *identifier();
    Mockup_module_bodyContext *mockup_module_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_moduleContext* mockup_module();

  class  Mockup_module_bodyContext : public antlr4::ParserRuleContext {
  public:
    Mockup_module_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MockupContext *> mockup();
    MockupContext* mockup(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_module_bodyContext* mockup_module_body();

  class  Mockup_structureContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ms_name = nullptr;
    MavkaParser::GenericsContext *ms_generics = nullptr;
    MavkaParser::Super_identifiers_chainContext *ms_parent = nullptr;
    MavkaParser::GenericsContext *ms_parent_generics = nullptr;
    MavkaParser::Mockup_structure_bodyContext *ms_elements = nullptr;
    Mockup_structureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_MOCKUP();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_STRUCTURE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    IdentifierContext *identifier();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESSER();
    antlr4::tree::TerminalNode* LESSER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    antlr4::tree::TerminalNode *KW_IS();
    std::vector<GenericsContext *> generics();
    GenericsContext* generics(size_t i);
    Super_identifiers_chainContext *super_identifiers_chain();
    Mockup_structure_bodyContext *mockup_structure_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_structureContext* mockup_structure();

  class  Mockup_structure_bodyContext : public antlr4::ParserRuleContext {
  public:
    Mockup_structure_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mockup_structure_body_elementContext *> mockup_structure_body_element();
    Mockup_structure_body_elementContext* mockup_structure_body_element(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_structure_bodyContext* mockup_structure_body();

  class  Mockup_structure_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Mockup_structure_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Structure_paramContext *structure_param();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_structure_body_elementContext* mockup_structure_body_element();

  class  Mockup_diiaContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *md_async = nullptr;
    antlr4::Token *md_static = nullptr;
    MavkaParser::IdentifierContext *md_structure = nullptr;
    MavkaParser::IdentifierContext *md_name = nullptr;
    MavkaParser::GenericsContext *md_generics = nullptr;
    MavkaParser::ParamsContext *md_params = nullptr;
    MavkaParser::Type_valueContext *md_type = nullptr;
    Mockup_diiaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_MOCKUP();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_DIIA();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LESSER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *KW_ASYNC();
    antlr4::tree::TerminalNode *KW_SPEC();
    GenericsContext *generics();
    ParamsContext *params();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_diiaContext* mockup_diia();

  class  Mockup_subjectContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ms_name = nullptr;
    MavkaParser::Type_valueContext *ms_type = nullptr;
    Mockup_subjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_MOCKUP();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_SUBJECT();
    IdentifierContext *identifier();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_subjectContext* mockup_subject();

  class  DiiaContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *d_async = nullptr;
    antlr4::Token *d_static = nullptr;
    MavkaParser::IdentifierContext *d_structure = nullptr;
    MavkaParser::IdentifierContext *d_name = nullptr;
    MavkaParser::GenericsContext *d_generics = nullptr;
    MavkaParser::ParamsContext *d_params = nullptr;
    MavkaParser::Type_valueContext *d_type = nullptr;
    MavkaParser::BodyContext *d_body = nullptr;
    DiiaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_DIIA();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LESSER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *KW_ASYNC();
    antlr4::tree::TerminalNode *KW_SPEC();
    GenericsContext *generics();
    ParamsContext *params();
    Type_valueContext *type_value();
    BodyContext *body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DiiaContext* diia();

  class  IfContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *i_value = nullptr;
    MavkaParser::BodyContext *i_body = nullptr;
    MavkaParser::BodyContext *i_else_body = nullptr;
    MavkaParser::IfContext *i_else_if = nullptr;
    IfContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_IF();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    ExprContext *expr();
    std::vector<BodyContext *> body();
    BodyContext* body(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    antlr4::tree::TerminalNode *KW_ELSE();
    IfContext *if_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfContext* if_();

  class  EachContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::AtomContext *e_iterator = nullptr;
    MavkaParser::FromtoContext *e_fromto = nullptr;
    MavkaParser::IdentifierContext *e_key_name = nullptr;
    MavkaParser::IdentifierContext *e_name = nullptr;
    MavkaParser::BodyContext *e_body = nullptr;
    EachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_FOR();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_AS();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    AtomContext *atom();
    FromtoContext *fromto();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *COMA();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    BodyContext *body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EachContext* each();

  class  FromtoContext : public antlr4::ParserRuleContext {
  public:
    FromtoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Fromto_simpleContext *fromto_simple();
    Fromto_complexContext *fromto_complex();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromtoContext* fromto();

  class  Fromto_simpleContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Fromto_valueContext *fs_from = nullptr;
    MavkaParser::Fromto_to_symbolContext *fs_to_symbol = nullptr;
    MavkaParser::Fromto_valueContext *fs_to = nullptr;
    Fromto_simpleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<Fromto_valueContext *> fromto_value();
    Fromto_valueContext* fromto_value(size_t i);
    Fromto_to_symbolContext *fromto_to_symbol();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fromto_simpleContext* fromto_simple();

  class  Fromto_complexContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Fromto_valueContext *fc_from = nullptr;
    MavkaParser::Fromto_middle_symbolContext *fc_middle_symbol = nullptr;
    MavkaParser::Fromto_valueContext *fc_middle = nullptr;
    MavkaParser::Fromto_to_symbolContext *fc_to_symbol = nullptr;
    MavkaParser::Fromto_valueContext *fc_to = nullptr;
    Fromto_complexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<Fromto_valueContext *> fromto_value();
    Fromto_valueContext* fromto_value(size_t i);
    Fromto_middle_symbolContext *fromto_middle_symbol();
    Fromto_to_symbolContext *fromto_to_symbol();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fromto_complexContext* fromto_complex();

  class  Fromto_valueContext : public antlr4::ParserRuleContext {
  public:
    Fromto_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Fromto_valueContext() = default;
    void copyFrom(Fromto_valueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Fromto_idContext : public Fromto_valueContext {
  public:
    Fromto_idContext(Fromto_valueContext *ctx);

    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Fromto_numberContext : public Fromto_valueContext {
  public:
    Fromto_numberContext(Fromto_valueContext *ctx);

    Number_tokenContext *number_token();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Fromto_nestedContext : public Fromto_valueContext {
  public:
    Fromto_nestedContext(Fromto_valueContext *ctx);

    MavkaParser::ExprContext *fn_value = nullptr;
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Fromto_valueContext* fromto_value();

  class  Fromto_middle_symbolContext : public antlr4::ParserRuleContext {
  public:
    Fromto_middle_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    std::vector<antlr4::tree::TerminalNode *> MULTIPLY();
    antlr4::tree::TerminalNode* MULTIPLY(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);
    antlr4::tree::TerminalNode *MOD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fromto_middle_symbolContext* fromto_middle_symbol();

  class  Fromto_to_symbolContext : public antlr4::ParserRuleContext {
  public:
    Fromto_to_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXCLAMATION();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LESSER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fromto_to_symbolContext* fromto_to_symbol();

  class  WhileContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *w_value = nullptr;
    MavkaParser::BodyContext *w_body = nullptr;
    WhileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_WHILE();
    WsContext *ws();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    ExprContext *expr();
    BodyContext *body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileContext* while_();

  class  TryContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::BodyContext *t_body = nullptr;
    MavkaParser::IdentifierContext *tc_name = nullptr;
    MavkaParser::BodyContext *tc_body = nullptr;
    TryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_TRY();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_CATCH();
    WsContext *ws();
    antlr4::tree::TerminalNode *KW_END();
    std::vector<BodyContext *> body();
    BodyContext* body(size_t i);
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TryContext* try_();

  class  EvalContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::StringContext *e_value = nullptr;
    EvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_JS();
    WsContext *ws();
    StringContext *string();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EvalContext* eval();

  class  TakeContext : public antlr4::ParserRuleContext {
  public:
    TakeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TakeContext() = default;
    void copyFrom(TakeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Take_moduleContext : public TakeContext {
  public:
    Take_moduleContext(TakeContext *ctx);

    antlr4::Token *tm_relative = nullptr;
    MavkaParser::Identifiers_chainContext *tm_name_chain = nullptr;
    MavkaParser::Take_module_elementsContext *tm_elements = nullptr;
    MavkaParser::IdentifierContext *tm_as = nullptr;
    antlr4::tree::TerminalNode *KW_TAKE();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    Identifiers_chainContext *identifiers_chain();
    WssContext *wss();
    antlr4::tree::TerminalNode *DOT();
    Take_module_elementsContext *take_module_elements();
    antlr4::tree::TerminalNode *KW_AS();
    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Take_remoteContext : public TakeContext {
  public:
    Take_remoteContext(TakeContext *ctx);

    antlr4::Token *tr_url = nullptr;
    antlr4::Token *tr_version = nullptr;
    MavkaParser::IdentifierContext *tr_as = nullptr;
    antlr4::tree::TerminalNode *KW_TAKE();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    antlr4::tree::TerminalNode *KW_AS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TakeContext* take();

  class  Take_module_elementsContext : public antlr4::ParserRuleContext {
  public:
    Take_module_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<Take_module_elementContext *> take_module_element();
    Take_module_elementContext* take_module_element(size_t i);
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Take_module_elementsContext* take_module_elements();

  class  Take_module_elementContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *tme_name = nullptr;
    MavkaParser::IdentifierContext *tme_as = nullptr;
    Take_module_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Take_module_elementContext* take_module_element();

  class  GiveContext : public antlr4::ParserRuleContext {
  public:
    GiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_GIVE();
    WsContext *ws();
    std::vector<Give_elementContext *> give_element();
    Give_elementContext* give_element(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GiveContext* give();

  class  Give_elementContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ge_name = nullptr;
    MavkaParser::IdentifierContext *ge_as = nullptr;
    Give_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Give_elementContext* give_element();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AtomContext() = default;
    void copyFrom(AtomContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Get_elementContext : public AtomContext {
  public:
    Get_elementContext(AtomContext *ctx);

    MavkaParser::AtomContext *ge_left = nullptr;
    MavkaParser::ExprContext *ge_element = nullptr;
    WssContext *wss();
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    AtomContext *atom();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ChainContext : public AtomContext {
  public:
    ChainContext(AtomContext *ctx);

    MavkaParser::AtomContext *c_left = nullptr;
    MavkaParser::IdentifierContext *c_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    AtomContext *atom();
    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  String_valueContext : public AtomContext {
  public:
    String_valueContext(AtomContext *ctx);

    StringContext *string();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Pre_incrementContext : public AtomContext {
  public:
    Pre_incrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pi_value = nullptr;
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Bitwise_notContext : public AtomContext {
  public:
    Bitwise_notContext(AtomContext *ctx);

    MavkaParser::AtomContext *bn_value = nullptr;
    antlr4::tree::TerminalNode *TILDA();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Typeless_dictionaryContext : public AtomContext {
  public:
    Typeless_dictionaryContext(AtomContext *ctx);

    MavkaParser::Dictionary_argsContext *d_args = nullptr;
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    Dictionary_argsContext *dictionary_args();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PositiveContext : public AtomContext {
  public:
    PositiveContext(AtomContext *ctx);

    MavkaParser::AtomContext *p_value = nullptr;
    antlr4::tree::TerminalNode *PLUS();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NestedContext : public AtomContext {
  public:
    NestedContext(AtomContext *ctx);

    MavkaParser::ExprContext *n_value = nullptr;
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallContext : public AtomContext {
  public:
    CallContext(AtomContext *ctx);

    MavkaParser::AtomContext *c_value = nullptr;
    MavkaParser::ArgsContext *c_args = nullptr;
    MavkaParser::Named_argsContext *c_named_args = nullptr;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    AtomContext *atom();
    antlr4::tree::TerminalNode *LESSER();
    Call_genericsContext *call_generics();
    antlr4::tree::TerminalNode *GREATER();
    ArgsContext *args();
    Named_argsContext *named_args();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumberContext : public AtomContext {
  public:
    NumberContext(AtomContext *ctx);

    Number_tokenContext *number_token();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegativeContext : public AtomContext {
  public:
    NegativeContext(AtomContext *ctx);

    MavkaParser::AtomContext *n_value = nullptr;
    antlr4::tree::TerminalNode *MINUS();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotContext : public AtomContext {
  public:
    NotContext(AtomContext *ctx);

    MavkaParser::AtomContext *n_value = nullptr;
    antlr4::tree::TerminalNode *EXCLAMATION();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Typeless_arrayContext : public AtomContext {
  public:
    Typeless_arrayContext(AtomContext *ctx);

    MavkaParser::Array_elementsContext *a_elements = nullptr;
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    Array_elementsContext *array_elements();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Pre_decrementContext : public AtomContext {
  public:
    Pre_decrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pd_value = nullptr;
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Post_decrementContext : public AtomContext {
  public:
    Post_decrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pd_value = nullptr;
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdContext : public AtomContext {
  public:
    IdContext(AtomContext *ctx);

    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Post_incrementContext : public AtomContext {
  public:
    Post_incrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pi_value = nullptr;
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AtomContext* atom();
  AtomContext* atom(int precedence);
  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ValueContext() = default;
    void copyFrom(ValueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Arithmetic_mulContext : public ValueContext {
  public:
    Arithmetic_mulContext(ValueContext *ctx);

    MavkaParser::ValueContext *a_left = nullptr;
    MavkaParser::Arithmetic_op_mulContext *a_operation = nullptr;
    MavkaParser::ValueContext *a_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    Arithmetic_op_mulContext *arithmetic_op_mul();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Arithmetic_addContext : public ValueContext {
  public:
    Arithmetic_addContext(ValueContext *ctx);

    MavkaParser::ValueContext *a_left = nullptr;
    MavkaParser::Arithmetic_op_addContext *a_operation = nullptr;
    MavkaParser::ValueContext *a_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    Arithmetic_op_addContext *arithmetic_op_add();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComparisonContext : public ValueContext {
  public:
    ComparisonContext(ValueContext *ctx);

    MavkaParser::ValueContext *c_left = nullptr;
    MavkaParser::Comparison_opContext *c_operation = nullptr;
    MavkaParser::ValueContext *c_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    Comparison_opContext *comparison_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TestContext : public ValueContext {
  public:
    TestContext(ValueContext *ctx);

    MavkaParser::ValueContext *t_left = nullptr;
    MavkaParser::Test_opContext *t_operation = nullptr;
    MavkaParser::ValueContext *t_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    Test_opContext *test_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitwiseContext : public ValueContext {
  public:
    BitwiseContext(ValueContext *ctx);

    MavkaParser::ValueContext *b_left = nullptr;
    MavkaParser::Bitwise_opContext *b_operation = nullptr;
    MavkaParser::ValueContext *b_right = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    Bitwise_opContext *bitwise_op();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Value_atomContext : public ValueContext {
  public:
    Value_atomContext(ValueContext *ctx);

    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ValueContext* value();
  ValueContext* value(int precedence);
  class  Call_genericsContext : public antlr4::ParserRuleContext {
  public:
    Call_genericsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_valueContext *> type_value();
    Type_valueContext* type_value(size_t i);
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Call_genericsContext* call_generics();

  class  Array_elementsContext : public antlr4::ParserRuleContext {
  public:
    Array_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Array_elementContext *> array_element();
    Array_elementContext* array_element(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Array_elementsContext* array_elements();

  class  Array_elementContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *ae_value = nullptr;
    Array_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Array_elementContext* array_element();

  class  Dictionary_argsContext : public antlr4::ParserRuleContext {
  public:
    Dictionary_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Dictionary_argContext *> dictionary_arg();
    Dictionary_argContext* dictionary_arg(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dictionary_argsContext* dictionary_args();

  class  Dictionary_argContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *da_name_id = nullptr;
    antlr4::Token *da_name_string = nullptr;
    MavkaParser::ExprContext *da_value = nullptr;
    Dictionary_argContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dictionary_argContext* dictionary_arg();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Anonymous_diiaContext : public ExprContext {
  public:
    Anonymous_diiaContext(ExprContext *ctx);

    antlr4::Token *d_async = nullptr;
    MavkaParser::GenericsContext *d_generics = nullptr;
    MavkaParser::ParamsContext *d_params = nullptr;
    MavkaParser::Type_valueContext *d_type = nullptr;
    MavkaParser::BodyContext *d_body = nullptr;
    antlr4::tree::TerminalNode *KW_DIIA();
    WssContext *wss();
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *KW_END();
    antlr4::tree::TerminalNode *LESSER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *KW_ASYNC();
    GenericsContext *generics();
    ParamsContext *params();
    Type_valueContext *type_value();
    BodyContext *body();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AsContext : public ExprContext {
  public:
    AsContext(ExprContext *ctx);

    MavkaParser::AtomContext *a_left = nullptr;
    MavkaParser::Type_value_itemContext *a_right = nullptr;
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_AS();
    AtomContext *atom();
    Type_value_itemContext *type_value_item();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WaitContext : public ExprContext {
  public:
    WaitContext(ExprContext *ctx);

    MavkaParser::ValueContext *w_value = nullptr;
    antlr4::tree::TerminalNode *KW_WAIT();
    WsContext *ws();
    ValueContext *value();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Call_parentContext : public ExprContext {
  public:
    Call_parentContext(ExprContext *ctx);

    MavkaParser::IdentifierContext *cp_id = nullptr;
    MavkaParser::ArgsContext *cp_args = nullptr;
    MavkaParser::Named_argsContext *cp_named_args = nullptr;
    antlr4::tree::TerminalNode *KW_PARENT();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *PAREN_OPEN();
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    IdentifierContext *identifier();
    ArgsContext *args();
    Named_argsContext *named_args();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionContext : public ExprContext {
  public:
    FunctionContext(ExprContext *ctx);

    antlr4::Token *f_async = nullptr;
    MavkaParser::ParamsContext *f_params = nullptr;
    MavkaParser::Type_valueContext *f_type = nullptr;
    MavkaParser::ExprContext *f_body = nullptr;
    antlr4::tree::TerminalNode *PAREN_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();
    antlr4::tree::TerminalNode *KW_ASYNC();
    ParamsContext *params();
    Type_valueContext *type_value();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SimpleContext : public ExprContext {
  public:
    SimpleContext(ExprContext *ctx);

    ValueContext *value();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TernaryContext : public ExprContext {
  public:
    TernaryContext(ExprContext *ctx);

    MavkaParser::ValueContext *t_value = nullptr;
    MavkaParser::ExprContext *t_positive = nullptr;
    MavkaParser::ExprContext *t_negative = nullptr;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COLON();
    ValueContext *value();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GodContext : public ExprContext {
  public:
    GodContext(ExprContext *ctx);

    std::vector<AtomContext *> atom();
    AtomContext* atom(size_t i);
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<antlr4::tree::TerminalNode *> KW_TA();
    antlr4::tree::TerminalNode* KW_TA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();

  class  ThrowContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *t_value = nullptr;
    ThrowContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_THROW();
    WsContext *ws();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ThrowContext* throw_();

  class  AssignContext : public antlr4::ParserRuleContext {
  public:
    AssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assign_simpleContext *assign_simple();
    Assign_by_identifierContext *assign_by_identifier();
    Assign_by_elementContext *assign_by_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignContext* assign();

  class  Assign_simpleContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *as_subject = nullptr;
    MavkaParser::IdentifierContext *as_identifier = nullptr;
    MavkaParser::Type_valueContext *as_type = nullptr;
    MavkaParser::Assign_symbolContext *as_symbol = nullptr;
    MavkaParser::ExprContext *as_value = nullptr;
    Assign_simpleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    IdentifierContext *identifier();
    Assign_symbolContext *assign_symbol();
    ExprContext *expr();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    antlr4::tree::TerminalNode *KW_SUBJECT();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_simpleContext* assign_simple();

  class  Assign_by_identifierContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Super_identifiers_chainContext *abi_left = nullptr;
    MavkaParser::IdentifierContext *abi_identifier = nullptr;
    MavkaParser::Assign_symbolContext *abi_symbol = nullptr;
    MavkaParser::ExprContext *abi_value = nullptr;
    Assign_by_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    Super_identifiers_chainContext *super_identifiers_chain();
    IdentifierContext *identifier();
    Assign_symbolContext *assign_symbol();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_by_identifierContext* assign_by_identifier();

  class  Assign_by_elementContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Super_identifiers_chainContext *abe_left = nullptr;
    MavkaParser::ExprContext *abe_index = nullptr;
    MavkaParser::Assign_symbolContext *abe_symbol = nullptr;
    MavkaParser::ExprContext *abe_value = nullptr;
    Assign_by_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    Super_identifiers_chainContext *super_identifiers_chain();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    Assign_symbolContext *assign_symbol();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_by_elementContext* assign_by_element();

  class  Assign_symbolContext : public antlr4::ParserRuleContext {
  public:
    Assign_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_TSE();
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    std::vector<antlr4::tree::TerminalNode *> MULTIPLY();
    antlr4::tree::TerminalNode* MULTIPLY(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);
    antlr4::tree::TerminalNode *MOD();
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESSER();
    antlr4::tree::TerminalNode* LESSER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    antlr4::tree::TerminalNode *POWER();
    std::vector<antlr4::tree::TerminalNode *> QUESTION();
    antlr4::tree::TerminalNode* QUESTION(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_symbolContext* assign_symbol();

  class  Wait_assignContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::AssignContext *wa_assign = nullptr;
    Wait_assignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_WAIT();
    WsContext *ws();
    AssignContext *assign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Wait_assignContext* wait_assign();

  class  Identifiers_chainContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Identifiers_chainContext *ic_left = nullptr;
    MavkaParser::IdentifierContext *ic_identifier = nullptr;
    MavkaParser::IdentifierContext *ic_right = nullptr;
    Identifiers_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    Identifiers_chainContext *identifiers_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Identifiers_chainContext* identifiers_chain();
  Identifiers_chainContext* identifiers_chain(int precedence);
  class  Super_identifiers_chainContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Super_identifiers_chainContext *sic_left = nullptr;
    MavkaParser::IdentifierContext *sic_identifier = nullptr;
    MavkaParser::IdentifierContext *sic_right = nullptr;
    MavkaParser::ExprContext *sic_index = nullptr;
    Super_identifiers_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    Super_identifiers_chainContext *super_identifiers_chain();
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Super_identifiers_chainContext* super_identifiers_chain();
  Super_identifiers_chainContext* super_identifiers_chain(int precedence);
  class  Type_valueContext : public antlr4::ParserRuleContext {
  public:
    Type_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_value_itemContext *> type_value_item();
    Type_value_itemContext* type_value_item(size_t i);
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    std::vector<antlr4::tree::TerminalNode *> KW_OR();
    antlr4::tree::TerminalNode* KW_OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_valueContext* type_value();

  class  Type_value_itemContext : public antlr4::ParserRuleContext {
  public:
    Type_value_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_value_item_simpleContext *type_value_item_simple();
    Type_value_item_arrayContext *type_value_item_array();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_itemContext* type_value_item();

  class  Type_value_item_simpleContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Identifiers_chainContext *tvi_value = nullptr;
    MavkaParser::Type_value_item_genericsContext *tvi_generics = nullptr;
    Type_value_item_simpleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Identifiers_chainContext *identifiers_chain();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *LESSER();
    antlr4::tree::TerminalNode *GREATER();
    Type_value_item_genericsContext *type_value_item_generics();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_item_simpleContext* type_value_item_simple();

  class  Type_value_item_genericsContext : public antlr4::ParserRuleContext {
  public:
    Type_value_item_genericsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_valueContext *> type_value();
    Type_valueContext* type_value(size_t i);
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_item_genericsContext* type_value_item_generics();

  class  Type_value_item_arrayContext : public antlr4::ParserRuleContext {
  public:
    Type_value_item_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    Type_value_itemContext *type_value_item();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_item_arrayContext* type_value_item_array();

  class  ArgsContext : public antlr4::ParserRuleContext {
  public:
    ArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgContext *> arg();
    ArgContext* arg(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgsContext* args();

  class  ArgContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *a_value = nullptr;
    ArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgContext* arg();

  class  Named_argsContext : public antlr4::ParserRuleContext {
  public:
    Named_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Named_argContext *> named_arg();
    Named_argContext* named_arg(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_argsContext* named_args();

  class  Named_argContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *na_name = nullptr;
    MavkaParser::ExprContext *na_value = nullptr;
    Named_argContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    IdentifierContext *identifier();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_argContext* named_arg();

  class  ParamsContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *p_variadic = nullptr;
    MavkaParser::IdentifierContext *p_variadic_name = nullptr;
    MavkaParser::Type_valueContext *p_variadic_type = nullptr;
    ParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParamContext *> param();
    ParamContext* param(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMA();
    antlr4::tree::TerminalNode* COMA(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    IdentifierContext *identifier();
    WsContext *ws();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamsContext* params();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *p_name = nullptr;
    MavkaParser::Type_valueContext *p_type = nullptr;
    MavkaParser::Param_valueContext *p_value = nullptr;
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    WsContext *ws();
    std::vector<WssContext *> wss();
    WssContext* wss(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    Type_valueContext *type_value();
    Param_valueContext *param_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamContext* param();

  class  Param_valueContext : public antlr4::ParserRuleContext {
  public:
    Param_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Param_valueContext() = default;
    void copyFrom(Param_valueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Param_value_empty_listContext : public Param_valueContext {
  public:
    Param_value_empty_listContext(Param_valueContext *ctx);

    antlr4::tree::TerminalNode *BRACKET_OPEN();
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_identifierContext : public Param_valueContext {
  public:
    Param_value_identifierContext(Param_valueContext *ctx);

    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_empty_dictionaryContext : public Param_valueContext {
  public:
    Param_value_empty_dictionaryContext(Param_valueContext *ctx);

    antlr4::tree::TerminalNode *PAREN_OPEN();
    antlr4::tree::TerminalNode *PAREN_CLOSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_numberContext : public Param_valueContext {
  public:
    Param_value_numberContext(Param_valueContext *ctx);

    Number_tokenContext *number_token();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_stringContext : public Param_valueContext {
  public:
    Param_value_stringContext(Param_valueContext *ctx);

    StringContext *string();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Param_valueContext* param_value();

  class  BodyContext : public antlr4::ParserRuleContext {
  public:
    BodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Body_element_or_returnContext *> body_element_or_return();
    Body_element_or_returnContext* body_element_or_return(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BodyContext* body();

  class  Body_element_or_returnContext : public antlr4::ParserRuleContext {
  public:
    Body_element_or_returnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_elementContext *body_element();
    Return_body_lineContext *return_body_line();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_element_or_returnContext* body_element_or_return();

  class  Body_elementContext : public antlr4::ParserRuleContext {
  public:
    Body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfContext *if_();
    EachContext *each();
    WhileContext *while_();
    TryContext *try_();
    ExprContext *expr();
    ThrowContext *throw_();
    Wait_assignContext *wait_assign();
    AssignContext *assign();
    NlsContext *nls();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_elementContext* body_element();

  class  Return_body_lineContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *rbl_value = nullptr;
    Return_body_lineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_RETURN();
    WsContext *ws();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Return_body_lineContext* return_body_line();

  class  Arithmetic_op_mulContext : public antlr4::ParserRuleContext {
  public:
    Arithmetic_op_mulContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> MULTIPLY();
    antlr4::tree::TerminalNode* MULTIPLY(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);
    antlr4::tree::TerminalNode *MOD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Arithmetic_op_mulContext* arithmetic_op_mul();

  class  Arithmetic_op_addContext : public antlr4::ParserRuleContext {
  public:
    Arithmetic_op_addContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Arithmetic_op_addContext* arithmetic_op_add();

  class  Bitwise_opContext : public antlr4::ParserRuleContext {
  public:
    Bitwise_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POWER();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *AND();
    std::vector<antlr4::tree::TerminalNode *> LESSER();
    antlr4::tree::TerminalNode* LESSER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bitwise_opContext* bitwise_op();

  class  Test_opContext : public antlr4::ParserRuleContext {
  public:
    Test_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KW_AND();
    antlr4::tree::TerminalNode *KW_OR();
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Test_opContext* test_op();

  class  Comparison_opContext : public antlr4::ParserRuleContext {
  public:
    Comparison_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    antlr4::tree::TerminalNode *EXCLAMATION();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LESSER();
    antlr4::tree::TerminalNode *KW_IS();
    antlr4::tree::TerminalNode *KW_NOT();
    WsContext *ws();
    antlr4::tree::TerminalNode *KW_EQ_WORD();
    antlr4::tree::TerminalNode *KW_GR_WORD();
    antlr4::tree::TerminalNode *KW_SM_WORD();
    antlr4::tree::TerminalNode *KW_HAS_IS_WORD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Comparison_opContext* comparison_op();

  class  Comp_inst_block_programContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *cibp_name = nullptr;
    antlr4::Token *cibp_value = nullptr;
    MavkaParser::ProgramContext *cibp_program = nullptr;
    Comp_inst_block_programContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMP_INST_START();
    WssContext *wss();
    WsContext *ws();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *COMP_INST_END();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *STRING();
    ProgramContext *program();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Comp_inst_block_programContext* comp_inst_block_program();

  class  Comp_inst_assignContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *cia_name = nullptr;
    antlr4::Token *cia_value = nullptr;
    Comp_inst_assignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMP_INST_ASSIGN();
    WssContext *wss();
    WsContext *ws();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Comp_inst_assignContext* comp_inst_assign();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool atomSempred(AtomContext *_localctx, size_t predicateIndex);
  bool valueSempred(ValueContext *_localctx, size_t predicateIndex);
  bool identifiers_chainSempred(Identifiers_chainContext *_localctx, size_t predicateIndex);
  bool super_identifiers_chainSempred(Super_identifiers_chainContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

