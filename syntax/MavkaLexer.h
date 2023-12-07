
// Generated from MavkaLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaLexer : public antlr4::Lexer {
public:
  enum {
    END = 1, DIIA = 2, STRUCTURE = 3, FOR = 4, EQ = 5, NOT_EQ = 6, GREATER_EQ = 7, 
    SMALLER_EQ = 8, GREATER = 9, SMALLER = 10, IF = 11, WAIT = 12, TAKE = 13, 
    TAKE_PAK = 14, TAKE_FILE = 15, GIVE = 16, AS = 17, TA = 18, IS = 19, 
    RETURN = 20, ASYNC = 21, SUBJECT = 22, AND = 23, OR = 24, TRY = 25, 
    CATCH = 26, ELSE = 27, THROW = 28, WHILE = 29, MODULE = 30, TERNARY = 31, 
    EQ_WORD = 32, GR_WORD = 33, SM_WORD = 34, NOT_GR_WORD = 35, NOT_SM_WORD = 36, 
    NOT_EQ_WORD = 37, NOT_IS_WORD = 38, HAS_IS_WORD = 39, NOT_HAS_IS_WORD = 40, 
    STAR_ALL = 41, MOCKUP = 42, IMPLEMENTS = 43, IMPLEMENT = 44, EVAL = 45, 
    WHEN = 46, ALSO = 47, TSE = 48, TEST = 49, IY = 50, SPREAD = 51, FROMTO = 52, 
    SKIP_SPACES = 53, NL = 54, DECREMENT = 55, INCREMENT = 56, OPEN_PAREN = 57, 
    CLOSE_PAREN = 58, OPEN_ARRAY = 59, CLOSE_ARRAY = 60, COMMA = 61, ASSIGN = 62, 
    ASSIGN_PARENT = 63, ASSIGN_ADD = 64, ASSIGN_SUB = 65, ASSIGN_MUL = 66, 
    ASSIGN_DIV = 67, ASSIGN_DIVDIV = 68, ASSIGN_MOD = 69, ASSIGN_BW_OR = 70, 
    ASSIGN_BW_AND = 71, ASSIGN_BW_SHIFT_LEFT = 72, ASSIGN_BW_SHIFT_RIGHT = 73, 
    ASSIGN_XOR = 74, ASSIGN_POW = 75, ASSIGN_OR = 76, ASSIGN_AND = 77, ASSIGN_IF = 78, 
    PLUS = 79, MINUS = 80, MUL = 81, DIV = 82, COLON = 83, DOT = 84, NOT = 85, 
    TILDA = 86, PERCENT = 87, DIVDIV = 88, POW = 89, XOR = 90, OR_SYM = 91, 
    AND_SYM = 92, OR_BW = 93, AND_BW = 94, BW_SHIFT_LEFT = 95, BW_SHIFT_RIGHT = 96, 
    HEX_START = 97, ID = 98, NUMBER = 99, INTEGER = 100, FLOAT = 101, HEX = 102, 
    HEXUKR = 103, BINNUM = 104, BINNUMUKR = 105, TRIPPLE_QUOTE = 106, STRING_MULTILINE = 107, 
    STRING = 108, COMMENT = 109, LINE_COMMENT = 110, OLD_COMMENT = 111
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

