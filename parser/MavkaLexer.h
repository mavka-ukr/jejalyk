
// Generated from MavkaLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaLexer : public antlr4::Lexer {
public:
  enum {
    END = 1, DIIA = 2, STRUCTURE = 3, FOR = 4, EQ = 5, NOT_EQ = 6, GREATER_EQ = 7, 
    SMALLER_EQ = 8, GREATER = 9, SMALLER = 10, IF = 11, WAIT = 12, TAKE = 13, 
    TAKE_PAK = 14, TAKE_FILE = 15, GIVE = 16, AS = 17, IS = 18, RETURN = 19, 
    ASYNC = 20, AND = 21, OR = 22, TRY = 23, CATCH = 24, ELSE = 25, THROW = 26, 
    WHILE = 27, MODULE = 28, TERNARY = 29, EQ_WORD = 30, GR_WORD = 31, SM_WORD = 32, 
    NOT_GR_WORD = 33, NOT_SM_WORD = 34, NOT_EQ_WORD = 35, NOT_IS_WORD = 36, 
    HAS_IS_WORD = 37, NOT_HAS_IS_WORD = 38, STAR_ALL = 39, MOCKUP = 40, 
    IMPLEMENTS = 41, IMPLEMENT = 42, EVAL = 43, WHEN = 44, TA = 45, SPREAD = 46, 
    FROMTO = 47, SKIP_SPACES = 48, NL = 49, DECREMENT = 50, INCREMENT = 51, 
    OPEN_PAREN = 52, CLOSE_PAREN = 53, OPEN_ARRAY = 54, CLOSE_ARRAY = 55, 
    COMMA = 56, ASSIGN = 57, ASSIGN_PARENT = 58, ASSIGN_ADD = 59, ASSIGN_SUB = 60, 
    ASSIGN_MUL = 61, ASSIGN_DIV = 62, ASSIGN_DIVDIV = 63, ASSIGN_MOD = 64, 
    ASSIGN_BW_OR = 65, ASSIGN_BW_AND = 66, ASSIGN_BW_SHIFT_LEFT = 67, ASSIGN_BW_SHIFT_RIGHT = 68, 
    ASSIGN_XOR = 69, ASSIGN_POW = 70, ASSIGN_OR = 71, ASSIGN_AND = 72, ASSIGN_IF = 73, 
    PLUS = 74, MINUS = 75, MUL = 76, DIV = 77, COLON = 78, DOT = 79, NOT = 80, 
    TILDA = 81, PERCENT = 82, DIVDIV = 83, POW = 84, XOR = 85, OR_SYM = 86, 
    AND_SYM = 87, OR_BW = 88, AND_BW = 89, BW_SHIFT_LEFT = 90, BW_SHIFT_RIGHT = 91, 
    HEX_START = 92, ID = 93, NUMBER = 94, INTEGER = 95, FLOAT = 96, HEX = 97, 
    HEXUKR = 98, BINNUM = 99, BINNUMUKR = 100, STRING = 101, COMMENT = 102, 
    LINE_COMMENT = 103, OLD_COMMENT = 104
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

