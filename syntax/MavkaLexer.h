
// Generated from MavkaLexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class  MavkaLexer : public antlr4::Lexer {
public:
  enum {
    END = 1, DIIA = 2, STRUCTURE = 3, FOR = 4, EQ = 5, NOT_EQ = 6, GREATER_EQ = 7, 
    SMALLER_EQ = 8, GREATER = 9, SMALLER = 10, IF = 11, WAIT = 12, TAKE = 13, 
    TAKE_PAK = 14, TAKE_FILE = 15, GIVE = 16, AS = 17, TA = 18, IS = 19, 
    SPEC = 20, RETURN = 21, ASYNC = 22, SUBJECT = 23, AND = 24, OR = 25, 
    TRY = 26, CATCH = 27, ELSE = 28, THROW = 29, WHILE = 30, MODULE = 31, 
    TERNARY = 32, EQ_WORD = 33, GR_WORD = 34, SM_WORD = 35, NOT_GR_WORD = 36, 
    NOT_SM_WORD = 37, NOT_EQ_WORD = 38, NOT_IS_WORD = 39, HAS_IS_WORD = 40, 
    NOT_HAS_IS_WORD = 41, STAR_ALL = 42, MOCKUP = 43, IMPLEMENTS = 44, IMPLEMENT = 45, 
    EVAL = 46, WHEN = 47, ALSO = 48, PARENT = 49, TSE = 50, SPREAD = 51, 
    FROMTO = 52, KID = 53, SKIP_SPACES = 54, NL = 55, DECREMENT = 56, INCREMENT = 57, 
    OPEN_PAREN = 58, CLOSE_PAREN = 59, OPEN_ARRAY = 60, CLOSE_ARRAY = 61, 
    COMMA = 62, ASSIGN = 63, ASSIGN_PARENT = 64, ASSIGN_ADD = 65, ASSIGN_SUB = 66, 
    ASSIGN_MUL = 67, ASSIGN_DIV = 68, ASSIGN_DIVDIV = 69, ASSIGN_MOD = 70, 
    ASSIGN_BW_OR = 71, ASSIGN_BW_AND = 72, ASSIGN_BW_SHIFT_LEFT = 73, ASSIGN_BW_SHIFT_RIGHT = 74, 
    ASSIGN_XOR = 75, ASSIGN_POW = 76, ASSIGN_OR = 77, ASSIGN_AND = 78, ASSIGN_IF = 79, 
    PLUS = 80, MINUS = 81, MUL = 82, DIV = 83, COLON = 84, DOT = 85, NOT = 86, 
    TILDA = 87, PERCENT = 88, DIVDIV = 89, POW = 90, XOR = 91, OR_SYM = 92, 
    AND_SYM = 93, OR_BW = 94, AND_BW = 95, HEX_START = 96, ID = 97, NUMBER = 98, 
    INTEGER = 99, FLOAT = 100, HEX = 101, HEXUKR = 102, BINNUM = 103, BINNUMUKR = 104, 
    MML = 105, TRIPPLE_QUOTE = 106, STRING_MULTILINE = 107, STRING = 108, 
    COMMENT = 109, LINE_COMMENT = 110
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

