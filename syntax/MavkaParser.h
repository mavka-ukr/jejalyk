
// Generated from MavkaParser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaParser : public antlr4::Parser {
public:
  enum {
    END = 1, DIIA = 2, STRUCTURE = 3, FOR = 4, EQ = 5, NOT_EQ = 6, GREATER_EQ = 7, 
    SMALLER_EQ = 8, GREATER = 9, SMALLER = 10, IF = 11, WAIT = 12, TAKE = 13, 
    TAKE_PAK = 14, TAKE_FILE = 15, GIVE = 16, AS = 17, TA = 18, IS = 19, 
    EE = 20, RETURN = 21, ASYNC = 22, SUBJECT = 23, AND = 24, OR = 25, TRY = 26, 
    CATCH = 27, ELSE = 28, THROW = 29, WHILE = 30, MODULE = 31, TERNARY = 32, 
    EQ_WORD = 33, GR_WORD = 34, SM_WORD = 35, NOT_GR_WORD = 36, NOT_SM_WORD = 37, 
    NOT_EQ_WORD = 38, NOT_IS_WORD = 39, HAS_IS_WORD = 40, NOT_HAS_IS_WORD = 41, 
    STAR_ALL = 42, MOCKUP = 43, IMPLEMENTS = 44, IMPLEMENT = 45, EVAL = 46, 
    WHEN = 47, ALSO = 48, PARENT = 49, TSE = 50, TEST = 51, IY = 52, SPREAD = 53, 
    FROMTO = 54, KID = 55, SKIP_SPACES = 56, NL = 57, DECREMENT = 58, INCREMENT = 59, 
    OPEN_PAREN = 60, CLOSE_PAREN = 61, OPEN_ARRAY = 62, CLOSE_ARRAY = 63, 
    COMMA = 64, ASSIGN = 65, ASSIGN_PARENT = 66, ASSIGN_ADD = 67, ASSIGN_SUB = 68, 
    ASSIGN_MUL = 69, ASSIGN_DIV = 70, ASSIGN_DIVDIV = 71, ASSIGN_MOD = 72, 
    ASSIGN_BW_OR = 73, ASSIGN_BW_AND = 74, ASSIGN_BW_SHIFT_LEFT = 75, ASSIGN_BW_SHIFT_RIGHT = 76, 
    ASSIGN_XOR = 77, ASSIGN_POW = 78, ASSIGN_OR = 79, ASSIGN_AND = 80, ASSIGN_IF = 81, 
    PLUS = 82, MINUS = 83, MUL = 84, DIV = 85, COLON = 86, DOT = 87, NOT = 88, 
    TILDA = 89, PERCENT = 90, DIVDIV = 91, POW = 92, XOR = 93, OR_SYM = 94, 
    AND_SYM = 95, OR_BW = 96, AND_BW = 97, BW_SHIFT_LEFT = 98, BW_SHIFT_RIGHT = 99, 
    HEX_START = 100, ID = 101, NUMBER = 102, INTEGER = 103, FLOAT = 104, 
    HEX = 105, HEXUKR = 106, BINNUM = 107, BINNUMUKR = 108, TRIPPLE_QUOTE = 109, 
    STRING_MULTILINE = 110, STRING = 111, COMMENT = 112, LINE_COMMENT = 113, 
    OLD_COMMENT = 114
  };

  enum {
    RuleFile = 0, RuleProgram = 1, RuleProgram_element = 2, RuleModule = 3, 
    RuleModule_body = 4, RuleModule_body_element = 5, RuleMethod_declaration = 6, 
    RuleStructure = 7, RuleStructure_elements = 8, RuleStructure_element = 9, 
    RuleStructure_param = 10, RuleGenerics = 11, RuleMockup = 12, RuleMockup_module = 13, 
    RuleMockup_structure = 14, RuleMockup_diia = 15, RuleMockup_subject = 16, 
    RuleMockup_object = 17, RuleMockup_body = 18, RuleMockup_body_element = 19, 
    RuleDiia = 20, RuleIf = 21, RuleEach = 22, RuleFromto = 23, RuleFromto_simple = 24, 
    RuleFromto_complex = 25, RuleFromto_value = 26, RuleFromto_middle_symbol = 27, 
    RuleFromto_to_symbol = 28, RuleWhile = 29, RuleTry = 30, RuleEval = 31, 
    RuleTake = 32, RuleGive = 33, RuleGive_element = 34, RuleString = 35, 
    RuleAtom = 36, RuleValue = 37, RuleCall_generics = 38, RuleArray_elements = 39, 
    RuleArray_element = 40, RuleDictionary_args = 41, RuleDictionary_arg = 42, 
    RuleExpr = 43, RuleThrow = 44, RuleArray_destruction = 45, RuleArray_destruction_el = 46, 
    RuleObject_destruction = 47, RuleObject_destruction_el = 48, RuleAssign = 49, 
    RuleAssign_simple = 50, RuleAssign_by_identifier = 51, RuleAssign_by_element = 52, 
    RuleAssign_array_destruction = 53, RuleAssign_object_destruction = 54, 
    RuleAssign_symbol = 55, RuleWait_assign = 56, RuleIdentifier = 57, RuleIdentifiers_chain = 58, 
    RuleSuper_identifiers_chain = 59, RuleType_value = 60, RuleType_value_item = 61, 
    RuleType_value_item_generics = 62, RuleArgs = 63, RuleArg = 64, RuleNamed_args = 65, 
    RuleNamed_arg = 66, RuleParams = 67, RuleParam = 68, RuleParam_value = 69, 
    RuleBody = 70, RuleBody_element_or_return = 71, RuleBody_element = 72, 
    RuleReturn_body_line = 73, RuleArithmetic_op_mul = 74, RuleArithmetic_op_add = 75, 
    RuleBitwise_op = 76, RuleTest_op = 77, RuleComparison_op = 78, RuleNl = 79, 
    RuleNls = 80
  };

  explicit MavkaParser(antlr4::TokenStream *input);

  MavkaParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MavkaParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class ProgramContext;
  class Program_elementContext;
  class ModuleContext;
  class Module_bodyContext;
  class Module_body_elementContext;
  class Method_declarationContext;
  class StructureContext;
  class Structure_elementsContext;
  class Structure_elementContext;
  class Structure_paramContext;
  class GenericsContext;
  class MockupContext;
  class Mockup_moduleContext;
  class Mockup_structureContext;
  class Mockup_diiaContext;
  class Mockup_subjectContext;
  class Mockup_objectContext;
  class Mockup_bodyContext;
  class Mockup_body_elementContext;
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
  class GiveContext;
  class Give_elementContext;
  class StringContext;
  class AtomContext;
  class ValueContext;
  class Call_genericsContext;
  class Array_elementsContext;
  class Array_elementContext;
  class Dictionary_argsContext;
  class Dictionary_argContext;
  class ExprContext;
  class ThrowContext;
  class Array_destructionContext;
  class Array_destruction_elContext;
  class Object_destructionContext;
  class Object_destruction_elContext;
  class AssignContext;
  class Assign_simpleContext;
  class Assign_by_identifierContext;
  class Assign_by_elementContext;
  class Assign_array_destructionContext;
  class Assign_object_destructionContext;
  class Assign_symbolContext;
  class Wait_assignContext;
  class IdentifierContext;
  class Identifiers_chainContext;
  class Super_identifiers_chainContext;
  class Type_valueContext;
  class Type_value_itemContext;
  class Type_value_item_genericsContext;
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
  class NlContext;
  class NlsContext; 

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
    antlr4::tree::TerminalNode *MODULE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    NlsContext *nls();
    antlr4::tree::TerminalNode *END();
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

  class  Method_declarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *md_static = nullptr;
    antlr4::Token *md_async = nullptr;
    MavkaParser::IdentifierContext *md_name = nullptr;
    MavkaParser::GenericsContext *md_generics = nullptr;
    MavkaParser::ParamsContext *md_params = nullptr;
    MavkaParser::Type_valueContext *md_type = nullptr;
    Method_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    IdentifierContext *identifier();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *EE();
    antlr4::tree::TerminalNode *ASYNC();
    GenericsContext *generics();
    Type_valueContext *type_value();
    ParamsContext *params();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Method_declarationContext* method_declaration();

  class  StructureContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *s_name = nullptr;
    MavkaParser::GenericsContext *s_generics = nullptr;
    MavkaParser::Super_identifiers_chainContext *s_parent = nullptr;
    MavkaParser::GenericsContext *s_parent_generics = nullptr;
    MavkaParser::Structure_elementsContext *s_elements = nullptr;
    StructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCTURE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    NlsContext *nls();
    antlr4::tree::TerminalNode *END();
    IdentifierContext *identifier();
    std::vector<antlr4::tree::TerminalNode *> SMALLER();
    antlr4::tree::TerminalNode* SMALLER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    antlr4::tree::TerminalNode *IS();
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
    NlsContext *nls();

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
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *EE();
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
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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
    Mockup_objectContext *mockup_object();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MockupContext* mockup();

  class  Mockup_moduleContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *mm_name = nullptr;
    MavkaParser::Mockup_bodyContext *mm_elements = nullptr;
    Mockup_moduleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOCKUP();
    antlr4::tree::TerminalNode *MODULE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *END();
    IdentifierContext *identifier();
    Mockup_bodyContext *mockup_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_moduleContext* mockup_module();

  class  Mockup_structureContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ms_name = nullptr;
    MavkaParser::GenericsContext *ms_generics = nullptr;
    MavkaParser::Super_identifiers_chainContext *ms_parent = nullptr;
    MavkaParser::GenericsContext *ms_parent_generics = nullptr;
    MavkaParser::Mockup_bodyContext *ms_elements = nullptr;
    Mockup_structureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOCKUP();
    antlr4::tree::TerminalNode *STRUCTURE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *END();
    IdentifierContext *identifier();
    std::vector<antlr4::tree::TerminalNode *> SMALLER();
    antlr4::tree::TerminalNode* SMALLER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    antlr4::tree::TerminalNode *IS();
    std::vector<GenericsContext *> generics();
    GenericsContext* generics(size_t i);
    Super_identifiers_chainContext *super_identifiers_chain();
    Mockup_bodyContext *mockup_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_structureContext* mockup_structure();

  class  Mockup_diiaContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *md_static = nullptr;
    antlr4::Token *md_async = nullptr;
    MavkaParser::IdentifierContext *md_name = nullptr;
    MavkaParser::GenericsContext *md_generics = nullptr;
    MavkaParser::ParamsContext *md_params = nullptr;
    MavkaParser::Type_valueContext *md_type = nullptr;
    Mockup_diiaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOCKUP();
    antlr4::tree::TerminalNode *DIIA();
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    IdentifierContext *identifier();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *EE();
    antlr4::tree::TerminalNode *ASYNC();
    GenericsContext *generics();
    Type_valueContext *type_value();
    ParamsContext *params();

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
    antlr4::tree::TerminalNode *MOCKUP();
    antlr4::tree::TerminalNode *SUBJECT();
    IdentifierContext *identifier();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_subjectContext* mockup_subject();

  class  Mockup_objectContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *mo_name = nullptr;
    MavkaParser::Mockup_bodyContext *mo_elements = nullptr;
    Mockup_objectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOCKUP();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *END();
    IdentifierContext *identifier();
    Mockup_bodyContext *mockup_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_objectContext* mockup_object();

  class  Mockup_bodyContext : public antlr4::ParserRuleContext {
  public:
    Mockup_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mockup_body_elementContext *> mockup_body_element();
    Mockup_body_elementContext* mockup_body_element(size_t i);
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_bodyContext* mockup_body();

  class  Mockup_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Mockup_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Structure_paramContext *structure_param();
    Method_declarationContext *method_declaration();
    NlsContext *nls();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mockup_body_elementContext* mockup_body_element();

  class  DiiaContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *d_static = nullptr;
    antlr4::Token *d_async = nullptr;
    MavkaParser::IdentifierContext *d_structure = nullptr;
    MavkaParser::IdentifierContext *d_name = nullptr;
    MavkaParser::GenericsContext *d_generics = nullptr;
    MavkaParser::ParamsContext *d_params = nullptr;
    MavkaParser::Type_valueContext *d_type = nullptr;
    MavkaParser::BodyContext *d_body = nullptr;
    DiiaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DIIA();
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *END();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *EE();
    antlr4::tree::TerminalNode *ASYNC();
    GenericsContext *generics();
    Type_valueContext *type_value();
    BodyContext *body();
    ParamsContext *params();

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
    antlr4::tree::TerminalNode *IF();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    ExprContext *expr();
    std::vector<BodyContext *> body();
    BodyContext* body(size_t i);
    antlr4::tree::TerminalNode *END();
    antlr4::tree::TerminalNode *ELSE();
    IfContext *if_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfContext* if_();

  class  EachContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::ExprContext *e_iterator = nullptr;
    MavkaParser::FromtoContext *e_fromto = nullptr;
    MavkaParser::IdentifierContext *e_key_name = nullptr;
    MavkaParser::IdentifierContext *e_name = nullptr;
    MavkaParser::BodyContext *e_body = nullptr;
    EachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *AS();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *END();
    ExprContext *expr();
    FromtoContext *fromto();
    antlr4::tree::TerminalNode *COMMA();
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
    antlr4::tree::TerminalNode *FROMTO();
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
    std::vector<antlr4::tree::TerminalNode *> FROMTO();
    antlr4::tree::TerminalNode* FROMTO(size_t i);
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

  class  Fromto_stringContext : public Fromto_valueContext {
  public:
    Fromto_stringContext(Fromto_valueContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Fromto_numberContext : public Fromto_valueContext {
  public:
    Fromto_numberContext(Fromto_valueContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Fromto_nestedContext : public Fromto_valueContext {
  public:
    Fromto_nestedContext(Fromto_valueContext *ctx);

    MavkaParser::ExprContext *fn_value = nullptr;
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
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
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PERCENT();
    antlr4::tree::TerminalNode *DIVDIV();
    antlr4::tree::TerminalNode *POW();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fromto_middle_symbolContext* fromto_middle_symbol();

  class  Fromto_to_symbolContext : public antlr4::ParserRuleContext {
  public:
    Fromto_to_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT_EQ();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER_EQ();
    antlr4::tree::TerminalNode *SMALLER_EQ();

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
    antlr4::tree::TerminalNode *WHILE();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *END();
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
    antlr4::tree::TerminalNode *TRY();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    antlr4::tree::TerminalNode *CATCH();
    antlr4::tree::TerminalNode *END();
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
    MavkaParser::ValueContext *e_value = nullptr;
    EvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EVAL();
    ValueContext *value();

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
    MavkaParser::Identifiers_chainContext *tm_elements_chain = nullptr;
    MavkaParser::IdentifierContext *tm_as = nullptr;
    antlr4::tree::TerminalNode *TAKE();
    Identifiers_chainContext *identifiers_chain();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *DOT();
    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Take_fileContext : public TakeContext {
  public:
    Take_fileContext(TakeContext *ctx);

    antlr4::Token *tf_name = nullptr;
    MavkaParser::IdentifierContext *tf_as = nullptr;
    antlr4::tree::TerminalNode *TAKE_FILE();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *STRING();
    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Take_remoteContext : public TakeContext {
  public:
    Take_remoteContext(TakeContext *ctx);

    antlr4::Token *tr_url = nullptr;
    MavkaParser::IdentifierContext *tr_as = nullptr;
    antlr4::tree::TerminalNode *TAKE();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *AS();
    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TakeContext* take();

  class  GiveContext : public antlr4::ParserRuleContext {
  public:
    GiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GIVE();
    std::vector<Give_elementContext *> give_element();
    Give_elementContext* give_element(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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
    antlr4::tree::TerminalNode *AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Give_elementContext* give_element();

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
    antlr4::tree::TerminalNode *OPEN_ARRAY();
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
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
    antlr4::tree::TerminalNode *INCREMENT();
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
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
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
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    AtomContext *atom();
    antlr4::tree::TerminalNode *SMALLER();
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

    antlr4::tree::TerminalNode *NUMBER();
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
    antlr4::tree::TerminalNode *NOT();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Pre_decrementContext : public AtomContext {
  public:
    Pre_decrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pd_value = nullptr;
    antlr4::tree::TerminalNode *DECREMENT();
    AtomContext *atom();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Post_decrementContext : public AtomContext {
  public:
    Post_decrementContext(AtomContext *ctx);

    MavkaParser::AtomContext *pd_value = nullptr;
    antlr4::tree::TerminalNode *DECREMENT();
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
    antlr4::tree::TerminalNode *INCREMENT();
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
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Call_genericsContext* call_generics();

  class  Array_elementsContext : public antlr4::ParserRuleContext {
  public:
    Array_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<Array_elementContext *> array_element();
    Array_elementContext* array_element(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *ASSIGN();
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
    MavkaParser::ParamsContext *d_params = nullptr;
    MavkaParser::Type_valueContext *d_type = nullptr;
    MavkaParser::BodyContext *d_body = nullptr;
    antlr4::tree::TerminalNode *DIIA();
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *END();
    antlr4::tree::TerminalNode *ASYNC();
    Type_valueContext *type_value();
    BodyContext *body();
    ParamsContext *params();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AsContext : public ExprContext {
  public:
    AsContext(ExprContext *ctx);

    MavkaParser::ValueContext *a_left = nullptr;
    MavkaParser::ValueContext *a_right = nullptr;
    antlr4::tree::TerminalNode *AS();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WaitContext : public ExprContext {
  public:
    WaitContext(ExprContext *ctx);

    MavkaParser::ValueContext *w_value = nullptr;
    antlr4::tree::TerminalNode *WAIT();
    ValueContext *value();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DictionaryContext : public ExprContext {
  public:
    DictionaryContext(ExprContext *ctx);

    MavkaParser::ExprContext *d_key_type = nullptr;
    MavkaParser::ExprContext *d_value_type = nullptr;
    MavkaParser::Dictionary_argsContext *d_args = nullptr;
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *GREATER();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    Dictionary_argsContext *dictionary_args();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayContext : public ExprContext {
  public:
    ArrayContext(ExprContext *ctx);

    MavkaParser::ExprContext *a_type = nullptr;
    MavkaParser::Array_elementsContext *a_elements = nullptr;
    antlr4::tree::TerminalNode *OPEN_ARRAY();
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER();
    ExprContext *expr();
    Array_elementsContext *array_elements();
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
    antlr4::tree::TerminalNode *PARENT();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
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
    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    antlr4::tree::TerminalNode *COLON();
    ExprContext *expr();
    antlr4::tree::TerminalNode *ASYNC();
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
    antlr4::tree::TerminalNode *TERNARY();
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

    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TA();
    antlr4::tree::TerminalNode* TA(size_t i);
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
    antlr4::tree::TerminalNode *THROW();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ThrowContext* throw_();

  class  Array_destructionContext : public antlr4::ParserRuleContext {
  public:
    Array_destructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_ARRAY();
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    std::vector<Array_destruction_elContext *> array_destruction_el();
    Array_destruction_elContext* array_destruction_el(size_t i);
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Array_destructionContext* array_destruction();

  class  Array_destruction_elContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ade_id = nullptr;
    Array_destruction_elContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Array_destruction_elContext* array_destruction_el();

  class  Object_destructionContext : public antlr4::ParserRuleContext {
  public:
    Object_destructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_PAREN();
    std::vector<Object_destruction_elContext *> object_destruction_el();
    Object_destruction_elContext* object_destruction_el(size_t i);
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Object_destructionContext* object_destruction();

  class  Object_destruction_elContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *ode_id = nullptr;
    Object_destruction_elContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Object_destruction_elContext* object_destruction_el();

  class  AssignContext : public antlr4::ParserRuleContext {
  public:
    AssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assign_simpleContext *assign_simple();
    Assign_by_identifierContext *assign_by_identifier();
    Assign_by_elementContext *assign_by_element();
    Assign_array_destructionContext *assign_array_destruction();
    Assign_object_destructionContext *assign_object_destruction();

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
    IdentifierContext *identifier();
    Assign_symbolContext *assign_symbol();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SUBJECT();
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
    antlr4::tree::TerminalNode *DOT();
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
    antlr4::tree::TerminalNode *OPEN_ARRAY();
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
    Super_identifiers_chainContext *super_identifiers_chain();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    Assign_symbolContext *assign_symbol();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_by_elementContext* assign_by_element();

  class  Assign_array_destructionContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Array_destructionContext *aad_array_destruction = nullptr;
    MavkaParser::ExprContext *aad_value = nullptr;
    Assign_array_destructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    Array_destructionContext *array_destruction();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_array_destructionContext* assign_array_destruction();

  class  Assign_object_destructionContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Object_destructionContext *aod_object_destruction = nullptr;
    MavkaParser::ExprContext *aod_value = nullptr;
    Assign_object_destructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    Object_destructionContext *object_destruction();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_object_destructionContext* assign_object_destruction();

  class  Assign_symbolContext : public antlr4::ParserRuleContext {
  public:
    Assign_symbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TSE();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *ASSIGN_PARENT();
    antlr4::tree::TerminalNode *ASSIGN_ADD();
    antlr4::tree::TerminalNode *ASSIGN_SUB();
    antlr4::tree::TerminalNode *ASSIGN_MUL();
    antlr4::tree::TerminalNode *ASSIGN_DIV();
    antlr4::tree::TerminalNode *ASSIGN_DIVDIV();
    antlr4::tree::TerminalNode *ASSIGN_MOD();
    antlr4::tree::TerminalNode *ASSIGN_POW();
    antlr4::tree::TerminalNode *ASSIGN_BW_AND();
    antlr4::tree::TerminalNode *ASSIGN_BW_OR();
    antlr4::tree::TerminalNode *ASSIGN_BW_SHIFT_LEFT();
    antlr4::tree::TerminalNode *ASSIGN_BW_SHIFT_RIGHT();
    antlr4::tree::TerminalNode *ASSIGN_XOR();
    antlr4::tree::TerminalNode *ASSIGN_AND();
    antlr4::tree::TerminalNode *ASSIGN_OR();
    antlr4::tree::TerminalNode *ASSIGN_IF();

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
    antlr4::tree::TerminalNode *WAIT();
    AssignContext *assign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Wait_assignContext* wait_assign();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *KID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  Identifiers_chainContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Identifiers_chainContext *ic_left = nullptr;
    MavkaParser::IdentifierContext *ic_identifier = nullptr;
    MavkaParser::IdentifierContext *ic_right = nullptr;
    Identifiers_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
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
    antlr4::tree::TerminalNode *OPEN_ARRAY();
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
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
    std::vector<antlr4::tree::TerminalNode *> OR_BW();
    antlr4::tree::TerminalNode* OR_BW(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_valueContext* type_value();

  class  Type_value_itemContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::Identifiers_chainContext *tvi_value = nullptr;
    MavkaParser::Type_value_item_genericsContext *tvi_generics = nullptr;
    Type_value_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Identifiers_chainContext *identifiers_chain();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER();
    Type_value_item_genericsContext *type_value_item_generics();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_itemContext* type_value_item();

  class  Type_value_item_genericsContext : public antlr4::ParserRuleContext {
  public:
    Type_value_item_genericsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_value_item_genericsContext* type_value_item_generics();

  class  ArgsContext : public antlr4::ParserRuleContext {
  public:
    ArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgContext *> arg();
    ArgContext* arg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgsContext* args();

  class  ArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *a_spread = nullptr;
    MavkaParser::ExprContext *a_value = nullptr;
    ArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    ExprContext *expr();
    antlr4::tree::TerminalNode *SPREAD();

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
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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
    std::vector<NlsContext *> nls();
    NlsContext* nls(size_t i);
    antlr4::tree::TerminalNode *ASSIGN();
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
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *SPREAD();
    IdentifierContext *identifier();
    Type_valueContext *type_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamsContext* params();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    MavkaParser::IdentifierContext *p_name = nullptr;
    MavkaParser::Array_destructionContext *p_array_destruction = nullptr;
    MavkaParser::Object_destructionContext *p_object_destruction = nullptr;
    MavkaParser::Type_valueContext *p_type = nullptr;
    MavkaParser::Param_valueContext *p_value = nullptr;
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    Array_destructionContext *array_destruction();
    Object_destructionContext *object_destruction();
    antlr4::tree::TerminalNode *ASSIGN();
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

    antlr4::tree::TerminalNode *OPEN_ARRAY();
    antlr4::tree::TerminalNode *CLOSE_ARRAY();
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

    antlr4::tree::TerminalNode *OPEN_PAREN();
    antlr4::tree::TerminalNode *CLOSE_PAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_numberContext : public Param_valueContext {
  public:
    Param_value_numberContext(Param_valueContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Param_value_stringContext : public Param_valueContext {
  public:
    Param_value_stringContext(Param_valueContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *STRING_MULTILINE();
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
    antlr4::tree::TerminalNode *RETURN();
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
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PERCENT();
    antlr4::tree::TerminalNode *DIVDIV();
    antlr4::tree::TerminalNode *POW();

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
    antlr4::tree::TerminalNode *XOR();
    antlr4::tree::TerminalNode *OR_BW();
    antlr4::tree::TerminalNode *AND_BW();
    antlr4::tree::TerminalNode *BW_SHIFT_LEFT();
    antlr4::tree::TerminalNode *BW_SHIFT_RIGHT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bitwise_opContext* bitwise_op();

  class  Test_opContext : public antlr4::ParserRuleContext {
  public:
    Test_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *OR_SYM();
    antlr4::tree::TerminalNode *AND_SYM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Test_opContext* test_op();

  class  Comparison_opContext : public antlr4::ParserRuleContext {
  public:
    Comparison_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NOT_EQ();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *SMALLER();
    antlr4::tree::TerminalNode *GREATER_EQ();
    antlr4::tree::TerminalNode *SMALLER_EQ();
    antlr4::tree::TerminalNode *IS();
    antlr4::tree::TerminalNode *NOT_IS_WORD();
    antlr4::tree::TerminalNode *EQ_WORD();
    antlr4::tree::TerminalNode *NOT_EQ_WORD();
    antlr4::tree::TerminalNode *GR_WORD();
    antlr4::tree::TerminalNode *NOT_GR_WORD();
    antlr4::tree::TerminalNode *SM_WORD();
    antlr4::tree::TerminalNode *NOT_SM_WORD();
    antlr4::tree::TerminalNode *HAS_IS_WORD();
    antlr4::tree::TerminalNode *NOT_HAS_IS_WORD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Comparison_opContext* comparison_op();

  class  NlContext : public antlr4::ParserRuleContext {
  public:
    NlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NlContext* nl();

  class  NlsContext : public antlr4::ParserRuleContext {
  public:
    NlsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NlContext *> nl();
    NlContext* nl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NlsContext* nls();


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

