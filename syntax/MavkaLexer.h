
// Generated from MavkaLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaLexer : public antlr4::Lexer {
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

  explicit MavkaLexer(antlr4::CharStream *input);

  ~MavkaLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

