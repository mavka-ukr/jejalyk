
// Generated from MavkaLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaLexer : public antlr4::Lexer {
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
    FROMTO = 54, SKIP_SPACES = 55, NL = 56, DECREMENT = 57, INCREMENT = 58, 
    OPEN_PAREN = 59, CLOSE_PAREN = 60, OPEN_ARRAY = 61, CLOSE_ARRAY = 62, 
    COMMA = 63, ASSIGN = 64, ASSIGN_PARENT = 65, ASSIGN_ADD = 66, ASSIGN_SUB = 67, 
    ASSIGN_MUL = 68, ASSIGN_DIV = 69, ASSIGN_DIVDIV = 70, ASSIGN_MOD = 71, 
    ASSIGN_BW_OR = 72, ASSIGN_BW_AND = 73, ASSIGN_BW_SHIFT_LEFT = 74, ASSIGN_BW_SHIFT_RIGHT = 75, 
    ASSIGN_XOR = 76, ASSIGN_POW = 77, ASSIGN_OR = 78, ASSIGN_AND = 79, ASSIGN_IF = 80, 
    PLUS = 81, MINUS = 82, MUL = 83, DIV = 84, COLON = 85, DOT = 86, NOT = 87, 
    TILDA = 88, PERCENT = 89, DIVDIV = 90, POW = 91, XOR = 92, OR_SYM = 93, 
    AND_SYM = 94, OR_BW = 95, AND_BW = 96, BW_SHIFT_LEFT = 97, BW_SHIFT_RIGHT = 98, 
    HEX_START = 99, ID = 100, NUMBER = 101, INTEGER = 102, FLOAT = 103, 
    HEX = 104, HEXUKR = 105, BINNUM = 106, BINNUMUKR = 107, TRIPPLE_QUOTE = 108, 
    STRING_MULTILINE = 109, STRING = 110, COMMENT = 111, LINE_COMMENT = 112, 
    OLD_COMMENT = 113
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

