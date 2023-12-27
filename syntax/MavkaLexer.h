
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
    FROMTO = 54, KID = 55, SKIP_SPACES = 56, NL = 57, DECREMENT = 58, INCREMENT = 59, 
    OPEN_PAREN = 60, CLOSE_PAREN = 61, OPEN_ARRAY = 62, CLOSE_ARRAY = 63, 
    COMMA = 64, ASSIGN = 65, ASSIGN_PARENT = 66, ASSIGN_ADD = 67, ASSIGN_SUB = 68, 
    ASSIGN_MUL = 69, ASSIGN_DIV = 70, ASSIGN_DIVDIV = 71, ASSIGN_MOD = 72, 
    ASSIGN_BW_OR = 73, ASSIGN_BW_AND = 74, ASSIGN_BW_SHIFT_LEFT = 75, ASSIGN_BW_SHIFT_RIGHT = 76, 
    ASSIGN_XOR = 77, ASSIGN_POW = 78, ASSIGN_OR = 79, ASSIGN_AND = 80, ASSIGN_IF = 81, 
    PLUS = 82, MINUS = 83, MUL = 84, DIV = 85, COLON = 86, DOT = 87, NOT = 88, 
    TILDA = 89, PERCENT = 90, DIVDIV = 91, POW = 92, XOR = 93, OR_SYM = 94, 
    AND_SYM = 95, OR_BW = 96, AND_BW = 97, HEX_START = 98, ID = 99, NUMBER = 100, 
    INTEGER = 101, FLOAT = 102, HEX = 103, HEXUKR = 104, BINNUM = 105, BINNUMUKR = 106, 
    MML = 107, TRIPPLE_QUOTE = 108, STRING_MULTILINE = 109, STRING = 110, 
    COMMENT = 111, LINE_COMMENT = 112
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

