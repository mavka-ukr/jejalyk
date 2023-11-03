
// Generated from MavkaParser.g4 by ANTLR 4.13.0


#include "MavkaParserListener.h"
#include "MavkaParserVisitor.h"

#include "MavkaParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MavkaParserStaticData final {
  MavkaParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MavkaParserStaticData(const MavkaParserStaticData&) = delete;
  MavkaParserStaticData(MavkaParserStaticData&&) = delete;
  MavkaParserStaticData& operator=(const MavkaParserStaticData&) = delete;
  MavkaParserStaticData& operator=(MavkaParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mavkaparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MavkaParserStaticData *mavkaparserParserStaticData = nullptr;

void mavkaparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mavkaparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(mavkaparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MavkaParserStaticData>(
    std::vector<std::string>{
      "file", "program", "program_element", "module", "module_body", "module_body_element", 
      "structure", "structure_elements", "structure_element", "diia", "if", 
      "each", "fromto", "fromto_value", "fromto_middle", "fromto_symbol", 
      "while", "try", "take", "give", "give_element", "value", "array_elements", 
      "array_element", "dictionary_args", "dictionary_arg", "expr", "throw", 
      "array_destruction", "array_destruction_el", "object_destruction", 
      "object_destruction_el", "assign", "assign_value", "assign_symbol", 
      "wait_assign", "identifier", "extended_identifier", "identifiers_chain", 
      "type_value", "type_value_array", "args", "arg", "named_args", "named_arg", 
      "params", "param", "param_value", "body", "body_element_or_return", 
      "body_element", "return_body_line", "arithmetic_op_mul", "arithmetic_op_add", 
      "bitwise_op", "test_op", "comparison_op", "nl", "nls"
    },
    std::vector<std::string>{
      "", "'\\u043A\\u0456\\u043D\\u0435\\u0446\\u044C'", "'\\u0434\\u0456\\u044F'", 
      "'\\u0441\\u0442\\u0440\\u0443\\u043A\\u0442\\u0443\\u0440\\u0430'", 
      "'\\u043F\\u0435\\u0440\\u0435\\u0431\\u0440\\u0430\\u0442\\u0438'", 
      "'=='", "'!='", "'>='", "'<='", "'>'", "'<'", "'\\u044F\\u043A\\u0449\\u043E'", 
      "'\\u0447\\u0435\\u043A\\u0430\\u0442\\u0438'", "'\\u0432\\u0437\\u044F\\u0442\\u0438'", 
      "'\\u0432\\u0437\\u044F\\u0442\\u0438 \\u043F\\u0430\\u043A'", "'\\u0432\\u0437\\u044F\\u0442\\u0438 \\u0444\\u0430\\u0439\\u043B'", 
      "'\\u0434\\u0430\\u0442\\u0438'", "'\\u044F\\u043A'", "'\\u0454'", 
      "'\\u0432\\u0435\\u0440\\u043D\\u0443\\u0442\\u0438'", "'\\u0442\\u0440\\u0438\\u0432\\u0430\\u043B\\u0430'", 
      "'\\u0456'", "'\\u0430\\u0431\\u043E'", "'\\u0441\\u043F\\u0440\\u043E\\u0431\\u0443\\u0432\\u0430\\u0442\\u0438'", 
      "'\\u0437\\u043B\\u043E\\u0432\\u0438\\u0442\\u0438'", "'\\u0456\\u043D\\u0430\\u043A\\u0448\\u0435'", 
      "'\\u0432\\u043F\\u0430\\u0441\\u0442\\u0438'", "'\\u043F\\u043E\\u043A\\u0438'", 
      "'\\u043C\\u043E\\u0434\\u0443\\u043B\\u044C'", "'\\u003F'", "'\\u0440\\u0456\\u0432\\u043D\\u043E'", 
      "'\\u0431\\u0456\\u043B\\u044C\\u0448\\u0435'", "'\\u043C\\u0435\\u043D\\u0448\\u0435'", 
      "'\\u043D\\u0435 \\u0431\\u0456\\u043B\\u044C\\u0448\\u0435'", "'\\u043D\\u0435 \\u043C\\u0435\\u043D\\u0448\\u0435'", 
      "'\\u043D\\u0435 \\u0440\\u0456\\u0432\\u043D\\u043E'", "'\\u043D\\u0435 \\u0454'", 
      "'\\u043C\\u0456\\u0441\\u0442\\u0438\\u0442\\u044C'", "'\\u043D\\u0435 \\u043C\\u0456\\u0441\\u0442\\u0438\\u0442\\u044C'", 
      "'.*'", "'\\u043C\\u0430\\u043A\\u0435\\u0442'", "'\\u0432\\u0442\\u0456\\u043B\\u044E\\u0454'", 
      "'\\u0432\\u0442\\u0456\\u043B\\u0438\\u0442\\u0438'", "'js'", "'\\u043A\\u043E\\u043B\\u0438'", 
      "'\\u0442\\u0430'", "'...'", "'..'", "", "", "'--'", "'++'", "'('", 
      "')'", "'['", "']'", "','", "'='", "':='", "'+='", "'-='", "'*='", 
      "'/='", "'//='", "'%='", "'|='", "'&='", "'<<='", "'>>='", "'^='", 
      "'**='", "'||='", "'&&='", "'\\u003F\\u003F='", "'+'", "'-'", "'*'", 
      "'/'", "':'", "'.'", "'!'", "'~'", "'%'", "'//'", "'**'", "'^'", "'||'", 
      "'&&'", "'|'", "'&'", "'<<'", "'>>'", "'0x'"
    },
    std::vector<std::string>{
      "", "END", "DIIA", "STRUCTURE", "FOR", "EQ", "NOT_EQ", "GREATER_EQ", 
      "SMALLER_EQ", "GREATER", "SMALLER", "IF", "WAIT", "TAKE", "TAKE_PAK", 
      "TAKE_FILE", "GIVE", "AS", "IS", "RETURN", "ASYNC", "AND", "OR", "TRY", 
      "CATCH", "ELSE", "THROW", "WHILE", "MODULE", "TERNARY", "EQ_WORD", 
      "GR_WORD", "SM_WORD", "NOT_GR_WORD", "NOT_SM_WORD", "NOT_EQ_WORD", 
      "NOT_IS_WORD", "HAS_IS_WORD", "NOT_HAS_IS_WORD", "STAR_ALL", "MOCKUP", 
      "IMPLEMENTS", "IMPLEMENT", "EVAL", "WHEN", "TA", "SPREAD", "FROMTO", 
      "SKIP_SPACES", "NL", "DECREMENT", "INCREMENT", "OPEN_PAREN", "CLOSE_PAREN", 
      "OPEN_ARRAY", "CLOSE_ARRAY", "COMMA", "ASSIGN", "ASSIGN_PARENT", "ASSIGN_ADD", 
      "ASSIGN_SUB", "ASSIGN_MUL", "ASSIGN_DIV", "ASSIGN_DIVDIV", "ASSIGN_MOD", 
      "ASSIGN_BW_OR", "ASSIGN_BW_AND", "ASSIGN_BW_SHIFT_LEFT", "ASSIGN_BW_SHIFT_RIGHT", 
      "ASSIGN_XOR", "ASSIGN_POW", "ASSIGN_OR", "ASSIGN_AND", "ASSIGN_IF", 
      "PLUS", "MINUS", "MUL", "DIV", "COLON", "DOT", "NOT", "TILDA", "PERCENT", 
      "DIVDIV", "POW", "XOR", "OR_SYM", "AND_SYM", "OR_BW", "AND_BW", "BW_SHIFT_LEFT", 
      "BW_SHIFT_RIGHT", "HEX_START", "ID", "NUMBER", "INTEGER", "FLOAT", 
      "HEX", "HEXUKR", "BINNUM", "BINNUMUKR", "STRING", "COMMENT", "LINE_COMMENT", 
      "OLD_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,104,740,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,1,0,1,0,1,0,1,1,1,1,1,1,1,1,5,1,126,8,1,10,1,12,
  	1,129,9,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,
  	145,8,2,1,3,1,3,3,3,149,8,3,1,3,1,3,1,3,1,3,3,3,155,8,3,1,3,1,3,1,3,1,
  	4,1,4,1,4,1,4,5,4,164,8,4,10,4,12,4,167,9,4,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,182,8,5,1,6,1,6,1,6,1,6,1,6,1,6,3,6,190,
  	8,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,5,7,199,8,7,10,7,12,7,202,9,7,1,8,1,8,
  	3,8,206,8,8,1,9,3,9,209,8,9,1,9,1,9,1,9,1,9,3,9,215,8,9,1,9,1,9,1,9,1,
  	9,3,9,221,8,9,1,9,1,9,1,9,1,9,3,9,227,8,9,1,9,1,9,1,9,1,9,3,9,233,8,9,
  	1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,3,10,244,8,10,1,10,1,10,1,10,
  	1,10,3,10,250,8,10,1,10,1,10,1,10,3,10,255,8,10,1,11,1,11,1,11,3,11,260,
  	8,11,1,11,1,11,1,11,1,11,3,11,266,8,11,1,11,3,11,269,8,11,1,11,1,11,1,
  	11,1,11,3,11,275,8,11,1,11,1,11,1,12,1,12,1,12,3,12,282,8,12,1,12,1,12,
  	1,12,3,12,287,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,296,8,13,1,
  	14,1,14,1,14,1,14,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,3,16,310,8,
  	16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,3,17,320,8,17,1,17,1,17,1,
  	17,3,17,325,8,17,1,17,1,17,1,18,1,18,3,18,331,8,18,1,18,1,18,3,18,335,
  	8,18,1,18,1,18,3,18,339,8,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	3,18,349,8,18,3,18,351,8,18,1,19,1,19,1,19,1,19,5,19,357,8,19,10,19,12,
  	19,360,9,19,1,20,1,20,1,20,3,20,365,8,20,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,3,21,393,8,21,1,21,1,21,1,21,1,21,3,21,
  	399,8,21,1,21,1,21,1,21,3,21,404,8,21,1,21,3,21,407,8,21,1,21,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,
  	21,439,8,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,461,8,21,10,21,12,21,
  	464,9,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,5,22,475,8,22,10,
  	22,12,22,478,9,22,1,23,1,23,1,24,1,24,1,24,5,24,485,8,24,10,24,12,24,
  	488,9,24,1,25,1,25,1,25,3,25,493,8,25,1,25,1,25,1,25,1,25,1,26,1,26,1,
  	26,1,26,1,26,3,26,504,8,26,1,26,1,26,3,26,508,8,26,1,26,1,26,1,26,3,26,
  	513,8,26,1,26,1,26,1,26,1,26,3,26,519,8,26,1,26,1,26,1,26,1,26,3,26,525,
  	8,26,1,26,1,26,1,26,1,26,3,26,531,8,26,1,26,1,26,1,26,3,26,536,8,26,1,
  	27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,5,28,551,
  	8,28,10,28,12,28,554,9,28,1,28,1,28,1,29,1,29,1,30,1,30,1,30,1,30,5,30,
  	564,8,30,10,30,12,30,567,9,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,
  	1,32,1,32,1,32,3,32,580,8,32,1,32,1,32,3,32,584,8,32,1,32,1,32,3,32,588,
  	8,32,1,32,1,32,1,32,1,33,1,33,1,34,1,34,1,35,1,35,1,35,1,36,1,36,1,37,
  	1,37,1,38,1,38,1,38,1,38,1,38,1,38,5,38,610,8,38,10,38,12,38,613,9,38,
  	1,39,1,39,3,39,617,8,39,1,39,1,39,1,39,1,39,1,39,1,39,5,39,625,8,39,10,
  	39,12,39,628,9,39,1,40,1,40,1,40,1,41,1,41,1,41,5,41,636,8,41,10,41,12,
  	41,639,9,41,1,42,1,42,3,42,643,8,42,1,42,1,42,1,42,1,43,1,43,1,43,5,43,
  	651,8,43,10,43,12,43,654,9,43,1,44,1,44,1,44,1,44,1,44,1,44,1,45,1,45,
  	1,45,1,45,1,45,1,45,5,45,668,8,45,10,45,12,45,671,9,45,1,46,3,46,674,
  	8,46,1,46,1,46,1,46,3,46,679,8,46,1,46,3,46,682,8,46,1,46,1,46,3,46,686,
  	8,46,1,47,1,47,1,47,3,47,691,8,47,1,48,1,48,1,48,1,48,5,48,697,8,48,10,
  	48,12,48,700,9,48,1,49,1,49,3,49,704,8,49,1,50,1,50,1,50,1,50,1,50,1,
  	50,1,50,1,50,1,50,1,50,1,50,3,50,717,8,50,1,51,1,51,1,51,1,52,1,52,1,
  	53,1,53,1,54,1,54,1,55,1,55,1,56,1,56,1,57,1,57,1,58,5,58,735,8,58,10,
  	58,12,58,738,9,58,1,58,0,3,42,76,78,59,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,
  	70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,
  	112,114,116,0,8,1,0,5,10,1,0,57,73,7,0,1,4,11,13,16,28,30,32,40,41,43,
  	45,93,93,2,0,76,77,82,84,1,0,74,75,2,0,85,85,88,91,2,0,21,22,86,87,3,
  	0,5,10,18,18,30,38,815,0,118,1,0,0,0,2,121,1,0,0,0,4,144,1,0,0,0,6,146,
  	1,0,0,0,8,159,1,0,0,0,10,181,1,0,0,0,12,183,1,0,0,0,14,194,1,0,0,0,16,
  	205,1,0,0,0,18,208,1,0,0,0,20,237,1,0,0,0,22,256,1,0,0,0,24,278,1,0,0,
  	0,26,295,1,0,0,0,28,297,1,0,0,0,30,301,1,0,0,0,32,303,1,0,0,0,34,313,
  	1,0,0,0,36,350,1,0,0,0,38,352,1,0,0,0,40,361,1,0,0,0,42,406,1,0,0,0,44,
  	465,1,0,0,0,46,479,1,0,0,0,48,481,1,0,0,0,50,489,1,0,0,0,52,535,1,0,0,
  	0,54,537,1,0,0,0,56,540,1,0,0,0,58,557,1,0,0,0,60,559,1,0,0,0,62,570,
  	1,0,0,0,64,587,1,0,0,0,66,592,1,0,0,0,68,594,1,0,0,0,70,596,1,0,0,0,72,
  	599,1,0,0,0,74,601,1,0,0,0,76,603,1,0,0,0,78,614,1,0,0,0,80,629,1,0,0,
  	0,82,632,1,0,0,0,84,640,1,0,0,0,86,647,1,0,0,0,88,655,1,0,0,0,90,661,
  	1,0,0,0,92,678,1,0,0,0,94,690,1,0,0,0,96,692,1,0,0,0,98,703,1,0,0,0,100,
  	716,1,0,0,0,102,718,1,0,0,0,104,721,1,0,0,0,106,723,1,0,0,0,108,725,1,
  	0,0,0,110,727,1,0,0,0,112,729,1,0,0,0,114,731,1,0,0,0,116,736,1,0,0,0,
  	118,119,3,2,1,0,119,120,5,0,0,1,120,1,1,0,0,0,121,127,3,4,2,0,122,123,
  	3,114,57,0,123,124,3,4,2,0,124,126,1,0,0,0,125,122,1,0,0,0,126,129,1,
  	0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,3,1,0,0,0,129,127,1,0,0,0,130,
  	145,3,6,3,0,131,145,3,12,6,0,132,145,3,18,9,0,133,145,3,20,10,0,134,145,
  	3,22,11,0,135,145,3,32,16,0,136,145,3,34,17,0,137,145,3,52,26,0,138,145,
  	3,54,27,0,139,145,3,70,35,0,140,145,3,64,32,0,141,145,3,116,58,0,142,
  	145,3,36,18,0,143,145,3,38,19,0,144,130,1,0,0,0,144,131,1,0,0,0,144,132,
  	1,0,0,0,144,133,1,0,0,0,144,134,1,0,0,0,144,135,1,0,0,0,144,136,1,0,0,
  	0,144,137,1,0,0,0,144,138,1,0,0,0,144,139,1,0,0,0,144,140,1,0,0,0,144,
  	141,1,0,0,0,144,142,1,0,0,0,144,143,1,0,0,0,145,5,1,0,0,0,146,148,5,28,
  	0,0,147,149,3,72,36,0,148,147,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,
  	150,154,3,114,57,0,151,152,3,8,4,0,152,153,3,114,57,0,153,155,1,0,0,0,
  	154,151,1,0,0,0,154,155,1,0,0,0,155,156,1,0,0,0,156,157,3,116,58,0,157,
  	158,5,1,0,0,158,7,1,0,0,0,159,165,3,10,5,0,160,161,3,114,57,0,161,162,
  	3,10,5,0,162,164,1,0,0,0,163,160,1,0,0,0,164,167,1,0,0,0,165,163,1,0,
  	0,0,165,166,1,0,0,0,166,9,1,0,0,0,167,165,1,0,0,0,168,182,3,6,3,0,169,
  	182,3,12,6,0,170,182,3,18,9,0,171,182,3,20,10,0,172,182,3,22,11,0,173,
  	182,3,32,16,0,174,182,3,34,17,0,175,182,3,52,26,0,176,182,3,54,27,0,177,
  	182,3,70,35,0,178,182,3,64,32,0,179,182,3,116,58,0,180,182,3,38,19,0,
  	181,168,1,0,0,0,181,169,1,0,0,0,181,170,1,0,0,0,181,171,1,0,0,0,181,172,
  	1,0,0,0,181,173,1,0,0,0,181,174,1,0,0,0,181,175,1,0,0,0,181,176,1,0,0,
  	0,181,177,1,0,0,0,181,178,1,0,0,0,181,179,1,0,0,0,181,180,1,0,0,0,182,
  	11,1,0,0,0,183,184,5,3,0,0,184,185,3,72,36,0,185,189,3,114,57,0,186,187,
  	3,14,7,0,187,188,3,114,57,0,188,190,1,0,0,0,189,186,1,0,0,0,189,190,1,
  	0,0,0,190,191,1,0,0,0,191,192,3,116,58,0,192,193,5,1,0,0,193,13,1,0,0,
  	0,194,200,3,16,8,0,195,196,3,114,57,0,196,197,3,16,8,0,197,199,1,0,0,
  	0,198,195,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,0,200,201,1,0,0,0,201,
  	15,1,0,0,0,202,200,1,0,0,0,203,206,3,92,46,0,204,206,3,116,58,0,205,203,
  	1,0,0,0,205,204,1,0,0,0,206,17,1,0,0,0,207,209,5,20,0,0,208,207,1,0,0,
  	0,208,209,1,0,0,0,209,210,1,0,0,0,210,214,5,2,0,0,211,212,3,72,36,0,212,
  	213,5,79,0,0,213,215,1,0,0,0,214,211,1,0,0,0,214,215,1,0,0,0,215,216,
  	1,0,0,0,216,217,3,72,36,0,217,218,5,52,0,0,218,220,3,116,58,0,219,221,
  	3,90,45,0,220,219,1,0,0,0,220,221,1,0,0,0,221,222,1,0,0,0,222,223,3,116,
  	58,0,223,224,1,0,0,0,224,226,5,53,0,0,225,227,3,78,39,0,226,225,1,0,0,
  	0,226,227,1,0,0,0,227,228,1,0,0,0,228,232,3,114,57,0,229,230,3,96,48,
  	0,230,231,3,114,57,0,231,233,1,0,0,0,232,229,1,0,0,0,232,233,1,0,0,0,
  	233,234,1,0,0,0,234,235,3,116,58,0,235,236,5,1,0,0,236,19,1,0,0,0,237,
  	238,5,11,0,0,238,239,3,52,26,0,239,243,3,114,57,0,240,241,3,96,48,0,241,
  	242,3,114,57,0,242,244,1,0,0,0,243,240,1,0,0,0,243,244,1,0,0,0,244,254,
  	1,0,0,0,245,246,5,25,0,0,246,247,3,96,48,0,247,248,3,114,57,0,248,250,
  	1,0,0,0,249,245,1,0,0,0,249,250,1,0,0,0,250,251,1,0,0,0,251,255,5,1,0,
  	0,252,253,5,25,0,0,253,255,3,20,10,0,254,249,1,0,0,0,254,252,1,0,0,0,
  	255,21,1,0,0,0,256,259,5,4,0,0,257,260,3,52,26,0,258,260,3,24,12,0,259,
  	257,1,0,0,0,259,258,1,0,0,0,260,268,1,0,0,0,261,265,5,17,0,0,262,263,
  	3,72,36,0,263,264,5,56,0,0,264,266,1,0,0,0,265,262,1,0,0,0,265,266,1,
  	0,0,0,266,267,1,0,0,0,267,269,3,72,36,0,268,261,1,0,0,0,268,269,1,0,0,
  	0,269,270,1,0,0,0,270,274,3,114,57,0,271,272,3,96,48,0,272,273,3,114,
  	57,0,273,275,1,0,0,0,274,271,1,0,0,0,274,275,1,0,0,0,275,276,1,0,0,0,
  	276,277,5,1,0,0,277,23,1,0,0,0,278,279,3,26,13,0,279,281,5,47,0,0,280,
  	282,3,30,15,0,281,280,1,0,0,0,281,282,1,0,0,0,282,283,1,0,0,0,283,286,
  	3,26,13,0,284,285,5,47,0,0,285,287,3,28,14,0,286,284,1,0,0,0,286,287,
  	1,0,0,0,287,25,1,0,0,0,288,296,5,94,0,0,289,296,5,101,0,0,290,296,3,72,
  	36,0,291,292,5,52,0,0,292,293,3,42,21,0,293,294,5,53,0,0,294,296,1,0,
  	0,0,295,288,1,0,0,0,295,289,1,0,0,0,295,290,1,0,0,0,295,291,1,0,0,0,296,
  	27,1,0,0,0,297,298,5,52,0,0,298,299,3,42,21,0,299,300,5,53,0,0,300,29,
  	1,0,0,0,301,302,7,0,0,0,302,31,1,0,0,0,303,304,5,27,0,0,304,305,3,52,
  	26,0,305,309,3,114,57,0,306,307,3,96,48,0,307,308,3,114,57,0,308,310,
  	1,0,0,0,309,306,1,0,0,0,309,310,1,0,0,0,310,311,1,0,0,0,311,312,5,1,0,
  	0,312,33,1,0,0,0,313,314,5,23,0,0,314,315,3,114,57,0,315,316,3,96,48,
  	0,316,317,3,114,57,0,317,319,5,24,0,0,318,320,3,72,36,0,319,318,1,0,0,
  	0,319,320,1,0,0,0,320,324,1,0,0,0,321,322,3,96,48,0,322,323,3,114,57,
  	0,323,325,1,0,0,0,324,321,1,0,0,0,324,325,1,0,0,0,325,326,1,0,0,0,326,
  	327,5,1,0,0,327,35,1,0,0,0,328,330,5,13,0,0,329,331,5,79,0,0,330,329,
  	1,0,0,0,330,331,1,0,0,0,331,332,1,0,0,0,332,334,3,76,38,0,333,335,5,39,
  	0,0,334,333,1,0,0,0,334,335,1,0,0,0,335,338,1,0,0,0,336,337,5,17,0,0,
  	337,339,3,72,36,0,338,336,1,0,0,0,338,339,1,0,0,0,339,351,1,0,0,0,340,
  	341,5,15,0,0,341,342,5,101,0,0,342,343,5,17,0,0,343,351,3,72,36,0,344,
  	345,5,13,0,0,345,348,5,101,0,0,346,347,5,17,0,0,347,349,3,72,36,0,348,
  	346,1,0,0,0,348,349,1,0,0,0,349,351,1,0,0,0,350,328,1,0,0,0,350,340,1,
  	0,0,0,350,344,1,0,0,0,351,37,1,0,0,0,352,353,5,16,0,0,353,358,3,40,20,
  	0,354,355,5,56,0,0,355,357,3,40,20,0,356,354,1,0,0,0,357,360,1,0,0,0,
  	358,356,1,0,0,0,358,359,1,0,0,0,359,39,1,0,0,0,360,358,1,0,0,0,361,364,
  	3,72,36,0,362,363,5,17,0,0,363,365,3,72,36,0,364,362,1,0,0,0,364,365,
  	1,0,0,0,365,41,1,0,0,0,366,367,6,21,-1,0,367,407,5,94,0,0,368,407,5,101,
  	0,0,369,407,3,72,36,0,370,371,5,74,0,0,371,407,3,42,21,19,372,373,5,75,
  	0,0,373,407,3,42,21,18,374,375,5,50,0,0,375,407,3,42,21,17,376,377,5,
  	51,0,0,377,407,3,42,21,16,378,379,5,80,0,0,379,407,3,42,21,13,380,381,
  	5,81,0,0,381,407,3,42,21,12,382,383,5,52,0,0,383,384,3,52,26,0,384,385,
  	5,53,0,0,385,407,1,0,0,0,386,387,5,52,0,0,387,388,3,52,26,0,388,389,5,
  	53,0,0,389,392,5,52,0,0,390,393,3,82,41,0,391,393,3,86,43,0,392,390,1,
  	0,0,0,392,391,1,0,0,0,392,393,1,0,0,0,393,394,1,0,0,0,394,395,5,53,0,
  	0,395,407,1,0,0,0,396,398,5,54,0,0,397,399,3,44,22,0,398,397,1,0,0,0,
  	398,399,1,0,0,0,399,400,1,0,0,0,400,407,5,55,0,0,401,403,5,52,0,0,402,
  	404,3,48,24,0,403,402,1,0,0,0,403,404,1,0,0,0,404,405,1,0,0,0,405,407,
  	5,53,0,0,406,366,1,0,0,0,406,368,1,0,0,0,406,369,1,0,0,0,406,370,1,0,
  	0,0,406,372,1,0,0,0,406,374,1,0,0,0,406,376,1,0,0,0,406,378,1,0,0,0,406,
  	380,1,0,0,0,406,382,1,0,0,0,406,386,1,0,0,0,406,396,1,0,0,0,406,401,1,
  	0,0,0,407,462,1,0,0,0,408,409,10,8,0,0,409,410,3,104,52,0,410,411,3,42,
  	21,9,411,461,1,0,0,0,412,413,10,7,0,0,413,414,3,106,53,0,414,415,3,42,
  	21,8,415,461,1,0,0,0,416,417,10,6,0,0,417,418,3,108,54,0,418,419,3,42,
  	21,7,419,461,1,0,0,0,420,421,10,5,0,0,421,422,3,112,56,0,422,423,3,42,
  	21,6,423,461,1,0,0,0,424,425,10,4,0,0,425,426,3,110,55,0,426,427,3,42,
  	21,5,427,461,1,0,0,0,428,429,10,21,0,0,429,430,3,116,58,0,430,431,5,79,
  	0,0,431,432,3,116,58,0,432,433,3,74,37,0,433,461,1,0,0,0,434,435,10,20,
  	0,0,435,438,5,52,0,0,436,439,3,82,41,0,437,439,3,86,43,0,438,436,1,0,
  	0,0,438,437,1,0,0,0,438,439,1,0,0,0,439,440,1,0,0,0,440,461,5,53,0,0,
  	441,442,10,15,0,0,442,461,5,50,0,0,443,444,10,14,0,0,444,461,5,51,0,0,
  	445,446,10,11,0,0,446,447,5,54,0,0,447,448,3,52,26,0,448,449,5,55,0,0,
  	449,461,1,0,0,0,450,451,10,3,0,0,451,452,3,116,58,0,452,453,5,29,0,0,
  	453,454,3,116,58,0,454,455,3,52,26,0,455,456,3,116,58,0,456,457,5,78,
  	0,0,457,458,3,116,58,0,458,459,3,52,26,0,459,461,1,0,0,0,460,408,1,0,
  	0,0,460,412,1,0,0,0,460,416,1,0,0,0,460,420,1,0,0,0,460,424,1,0,0,0,460,
  	428,1,0,0,0,460,434,1,0,0,0,460,441,1,0,0,0,460,443,1,0,0,0,460,445,1,
  	0,0,0,460,450,1,0,0,0,461,464,1,0,0,0,462,460,1,0,0,0,462,463,1,0,0,0,
  	463,43,1,0,0,0,464,462,1,0,0,0,465,466,3,116,58,0,466,467,3,46,23,0,467,
  	476,3,116,58,0,468,469,3,116,58,0,469,470,5,56,0,0,470,471,3,116,58,0,
  	471,472,3,46,23,0,472,473,3,116,58,0,473,475,1,0,0,0,474,468,1,0,0,0,
  	475,478,1,0,0,0,476,474,1,0,0,0,476,477,1,0,0,0,477,45,1,0,0,0,478,476,
  	1,0,0,0,479,480,3,52,26,0,480,47,1,0,0,0,481,486,3,50,25,0,482,483,5,
  	56,0,0,483,485,3,50,25,0,484,482,1,0,0,0,485,488,1,0,0,0,486,484,1,0,
  	0,0,486,487,1,0,0,0,487,49,1,0,0,0,488,486,1,0,0,0,489,492,3,116,58,0,
  	490,493,3,72,36,0,491,493,5,101,0,0,492,490,1,0,0,0,492,491,1,0,0,0,493,
  	494,1,0,0,0,494,495,5,57,0,0,495,496,3,52,26,0,496,497,3,116,58,0,497,
  	51,1,0,0,0,498,536,3,42,21,0,499,500,5,12,0,0,500,536,3,42,21,0,501,503,
  	5,52,0,0,502,504,3,90,45,0,503,502,1,0,0,0,503,504,1,0,0,0,504,505,1,
  	0,0,0,505,507,5,53,0,0,506,508,3,78,39,0,507,506,1,0,0,0,507,508,1,0,
  	0,0,508,509,1,0,0,0,509,510,5,78,0,0,510,536,3,52,26,0,511,513,5,20,0,
  	0,512,511,1,0,0,0,512,513,1,0,0,0,513,514,1,0,0,0,514,515,5,2,0,0,515,
  	516,5,52,0,0,516,518,3,116,58,0,517,519,3,90,45,0,518,517,1,0,0,0,518,
  	519,1,0,0,0,519,520,1,0,0,0,520,521,3,116,58,0,521,522,1,0,0,0,522,524,
  	5,53,0,0,523,525,3,78,39,0,524,523,1,0,0,0,524,525,1,0,0,0,525,526,1,
  	0,0,0,526,530,3,114,57,0,527,528,3,96,48,0,528,529,3,114,57,0,529,531,
  	1,0,0,0,530,527,1,0,0,0,530,531,1,0,0,0,531,532,1,0,0,0,532,533,3,116,
  	58,0,533,534,5,1,0,0,534,536,1,0,0,0,535,498,1,0,0,0,535,499,1,0,0,0,
  	535,501,1,0,0,0,535,512,1,0,0,0,536,53,1,0,0,0,537,538,5,26,0,0,538,539,
  	3,52,26,0,539,55,1,0,0,0,540,541,5,54,0,0,541,542,3,116,58,0,542,543,
  	3,58,29,0,543,552,3,116,58,0,544,545,3,116,58,0,545,546,5,56,0,0,546,
  	547,3,116,58,0,547,548,3,58,29,0,548,549,3,116,58,0,549,551,1,0,0,0,550,
  	544,1,0,0,0,551,554,1,0,0,0,552,550,1,0,0,0,552,553,1,0,0,0,553,555,1,
  	0,0,0,554,552,1,0,0,0,555,556,5,55,0,0,556,57,1,0,0,0,557,558,3,72,36,
  	0,558,59,1,0,0,0,559,560,5,52,0,0,560,565,3,62,31,0,561,562,5,56,0,0,
  	562,564,3,62,31,0,563,561,1,0,0,0,564,567,1,0,0,0,565,563,1,0,0,0,565,
  	566,1,0,0,0,566,568,1,0,0,0,567,565,1,0,0,0,568,569,5,53,0,0,569,61,1,
  	0,0,0,570,571,3,116,58,0,571,572,3,72,36,0,572,573,3,116,58,0,573,63,
  	1,0,0,0,574,579,3,76,38,0,575,576,5,54,0,0,576,577,3,52,26,0,577,578,
  	5,55,0,0,578,580,1,0,0,0,579,575,1,0,0,0,579,580,1,0,0,0,580,588,1,0,
  	0,0,581,583,3,72,36,0,582,584,3,78,39,0,583,582,1,0,0,0,583,584,1,0,0,
  	0,584,588,1,0,0,0,585,588,3,56,28,0,586,588,3,60,30,0,587,574,1,0,0,0,
  	587,581,1,0,0,0,587,585,1,0,0,0,587,586,1,0,0,0,588,589,1,0,0,0,589,590,
  	3,68,34,0,590,591,3,66,33,0,591,65,1,0,0,0,592,593,3,52,26,0,593,67,1,
  	0,0,0,594,595,7,1,0,0,595,69,1,0,0,0,596,597,5,12,0,0,597,598,3,64,32,
  	0,598,71,1,0,0,0,599,600,5,93,0,0,600,73,1,0,0,0,601,602,7,2,0,0,602,
  	75,1,0,0,0,603,604,6,38,-1,0,604,605,3,72,36,0,605,611,1,0,0,0,606,607,
  	10,1,0,0,607,608,5,79,0,0,608,610,3,76,38,2,609,606,1,0,0,0,610,613,1,
  	0,0,0,611,609,1,0,0,0,611,612,1,0,0,0,612,77,1,0,0,0,613,611,1,0,0,0,
  	614,616,6,39,-1,0,615,617,3,80,40,0,616,615,1,0,0,0,616,617,1,0,0,0,617,
  	618,1,0,0,0,618,619,3,76,38,0,619,626,1,0,0,0,620,621,10,1,0,0,621,622,
  	3,110,55,0,622,623,3,78,39,2,623,625,1,0,0,0,624,620,1,0,0,0,625,628,
  	1,0,0,0,626,624,1,0,0,0,626,627,1,0,0,0,627,79,1,0,0,0,628,626,1,0,0,
  	0,629,630,5,54,0,0,630,631,5,55,0,0,631,81,1,0,0,0,632,637,3,84,42,0,
  	633,634,5,56,0,0,634,636,3,84,42,0,635,633,1,0,0,0,636,639,1,0,0,0,637,
  	635,1,0,0,0,637,638,1,0,0,0,638,83,1,0,0,0,639,637,1,0,0,0,640,642,3,
  	116,58,0,641,643,5,46,0,0,642,641,1,0,0,0,642,643,1,0,0,0,643,644,1,0,
  	0,0,644,645,3,52,26,0,645,646,3,116,58,0,646,85,1,0,0,0,647,652,3,88,
  	44,0,648,649,5,56,0,0,649,651,3,88,44,0,650,648,1,0,0,0,651,654,1,0,0,
  	0,652,650,1,0,0,0,652,653,1,0,0,0,653,87,1,0,0,0,654,652,1,0,0,0,655,
  	656,3,116,58,0,656,657,3,72,36,0,657,658,5,57,0,0,658,659,3,52,26,0,659,
  	660,3,116,58,0,660,89,1,0,0,0,661,669,3,92,46,0,662,663,3,116,58,0,663,
  	664,5,56,0,0,664,665,3,116,58,0,665,666,3,92,46,0,666,668,1,0,0,0,667,
  	662,1,0,0,0,668,671,1,0,0,0,669,667,1,0,0,0,669,670,1,0,0,0,670,91,1,
  	0,0,0,671,669,1,0,0,0,672,674,5,46,0,0,673,672,1,0,0,0,673,674,1,0,0,
  	0,674,675,1,0,0,0,675,679,3,72,36,0,676,679,3,56,28,0,677,679,3,60,30,
  	0,678,673,1,0,0,0,678,676,1,0,0,0,678,677,1,0,0,0,679,681,1,0,0,0,680,
  	682,3,78,39,0,681,680,1,0,0,0,681,682,1,0,0,0,682,685,1,0,0,0,683,684,
  	5,57,0,0,684,686,3,94,47,0,685,683,1,0,0,0,685,686,1,0,0,0,686,93,1,0,
  	0,0,687,691,5,94,0,0,688,691,5,101,0,0,689,691,3,72,36,0,690,687,1,0,
  	0,0,690,688,1,0,0,0,690,689,1,0,0,0,691,95,1,0,0,0,692,698,3,98,49,0,
  	693,694,3,114,57,0,694,695,3,98,49,0,695,697,1,0,0,0,696,693,1,0,0,0,
  	697,700,1,0,0,0,698,696,1,0,0,0,698,699,1,0,0,0,699,97,1,0,0,0,700,698,
  	1,0,0,0,701,704,3,100,50,0,702,704,3,102,51,0,703,701,1,0,0,0,703,702,
  	1,0,0,0,704,99,1,0,0,0,705,717,3,12,6,0,706,717,3,18,9,0,707,717,3,20,
  	10,0,708,717,3,22,11,0,709,717,3,32,16,0,710,717,3,34,17,0,711,717,3,
  	52,26,0,712,717,3,54,27,0,713,717,3,70,35,0,714,717,3,64,32,0,715,717,
  	3,116,58,0,716,705,1,0,0,0,716,706,1,0,0,0,716,707,1,0,0,0,716,708,1,
  	0,0,0,716,709,1,0,0,0,716,710,1,0,0,0,716,711,1,0,0,0,716,712,1,0,0,0,
  	716,713,1,0,0,0,716,714,1,0,0,0,716,715,1,0,0,0,717,101,1,0,0,0,718,719,
  	5,19,0,0,719,720,3,100,50,0,720,103,1,0,0,0,721,722,7,3,0,0,722,105,1,
  	0,0,0,723,724,7,4,0,0,724,107,1,0,0,0,725,726,7,5,0,0,726,109,1,0,0,0,
  	727,728,7,6,0,0,728,111,1,0,0,0,729,730,7,7,0,0,730,113,1,0,0,0,731,732,
  	5,49,0,0,732,115,1,0,0,0,733,735,3,114,57,0,734,733,1,0,0,0,735,738,1,
  	0,0,0,736,734,1,0,0,0,736,737,1,0,0,0,737,117,1,0,0,0,738,736,1,0,0,0,
  	72,127,144,148,154,165,181,189,200,205,208,214,220,226,232,243,249,254,
  	259,265,268,274,281,286,295,309,319,324,330,334,338,348,350,358,364,392,
  	398,403,406,438,460,462,476,486,492,503,507,512,518,524,530,535,552,565,
  	579,583,587,611,616,626,637,642,652,669,673,678,681,685,690,698,703,716,
  	736
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mavkaparserParserStaticData = staticData.release();
}

}

MavkaParser::MavkaParser(TokenStream *input) : MavkaParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MavkaParser::MavkaParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MavkaParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mavkaparserParserStaticData->atn, mavkaparserParserStaticData->decisionToDFA, mavkaparserParserStaticData->sharedContextCache, options);
}

MavkaParser::~MavkaParser() {
  delete _interpreter;
}

const atn::ATN& MavkaParser::getATN() const {
  return *mavkaparserParserStaticData->atn;
}

std::string MavkaParser::getGrammarFileName() const {
  return "MavkaParser.g4";
}

const std::vector<std::string>& MavkaParser::getRuleNames() const {
  return mavkaparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& MavkaParser::getVocabulary() const {
  return mavkaparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MavkaParser::getSerializedATN() const {
  return mavkaparserParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

MavkaParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::FileContext::EOF() {
  return getToken(MavkaParser::EOF, 0);
}

MavkaParser::ProgramContext* MavkaParser::FileContext::program() {
  return getRuleContext<MavkaParser::ProgramContext>(0);
}


size_t MavkaParser::FileContext::getRuleIndex() const {
  return MavkaParser::RuleFile;
}

void MavkaParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void MavkaParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}


std::any MavkaParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::FileContext* MavkaParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, MavkaParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    antlrcpp::downCast<FileContext *>(_localctx)->f_program = program();
    setState(119);
    match(MavkaParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramContext ------------------------------------------------------------------

MavkaParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Program_elementContext *> MavkaParser::ProgramContext::program_element() {
  return getRuleContexts<MavkaParser::Program_elementContext>();
}

MavkaParser::Program_elementContext* MavkaParser::ProgramContext::program_element(size_t i) {
  return getRuleContext<MavkaParser::Program_elementContext>(i);
}

std::vector<MavkaParser::NlContext *> MavkaParser::ProgramContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::ProgramContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}


size_t MavkaParser::ProgramContext::getRuleIndex() const {
  return MavkaParser::RuleProgram;
}

void MavkaParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void MavkaParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any MavkaParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ProgramContext* MavkaParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 2, MavkaParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    program_element();
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::NL) {
      setState(122);
      nl();
      setState(123);
      program_element();
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Program_elementContext ------------------------------------------------------------------

MavkaParser::Program_elementContext::Program_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::ModuleContext* MavkaParser::Program_elementContext::module() {
  return getRuleContext<MavkaParser::ModuleContext>(0);
}

MavkaParser::StructureContext* MavkaParser::Program_elementContext::structure() {
  return getRuleContext<MavkaParser::StructureContext>(0);
}

MavkaParser::DiiaContext* MavkaParser::Program_elementContext::diia() {
  return getRuleContext<MavkaParser::DiiaContext>(0);
}

MavkaParser::IfContext* MavkaParser::Program_elementContext::if_() {
  return getRuleContext<MavkaParser::IfContext>(0);
}

MavkaParser::EachContext* MavkaParser::Program_elementContext::each() {
  return getRuleContext<MavkaParser::EachContext>(0);
}

MavkaParser::WhileContext* MavkaParser::Program_elementContext::while_() {
  return getRuleContext<MavkaParser::WhileContext>(0);
}

MavkaParser::TryContext* MavkaParser::Program_elementContext::try_() {
  return getRuleContext<MavkaParser::TryContext>(0);
}

MavkaParser::ExprContext* MavkaParser::Program_elementContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::ThrowContext* MavkaParser::Program_elementContext::throw_() {
  return getRuleContext<MavkaParser::ThrowContext>(0);
}

MavkaParser::Wait_assignContext* MavkaParser::Program_elementContext::wait_assign() {
  return getRuleContext<MavkaParser::Wait_assignContext>(0);
}

MavkaParser::AssignContext* MavkaParser::Program_elementContext::assign() {
  return getRuleContext<MavkaParser::AssignContext>(0);
}

MavkaParser::NlsContext* MavkaParser::Program_elementContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}

MavkaParser::TakeContext* MavkaParser::Program_elementContext::take() {
  return getRuleContext<MavkaParser::TakeContext>(0);
}

MavkaParser::GiveContext* MavkaParser::Program_elementContext::give() {
  return getRuleContext<MavkaParser::GiveContext>(0);
}


size_t MavkaParser::Program_elementContext::getRuleIndex() const {
  return MavkaParser::RuleProgram_element;
}

void MavkaParser::Program_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram_element(this);
}

void MavkaParser::Program_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram_element(this);
}


std::any MavkaParser::Program_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitProgram_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Program_elementContext* MavkaParser::program_element() {
  Program_elementContext *_localctx = _tracker.createInstance<Program_elementContext>(_ctx, getState());
  enterRule(_localctx, 4, MavkaParser::RuleProgram_element);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(130);
      module();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(131);
      structure();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(132);
      diia();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(133);
      if_();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(134);
      each();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(135);
      while_();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(136);
      try_();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(137);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(138);
      throw_();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(139);
      wait_assign();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(140);
      assign();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(141);
      nls();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(142);
      take();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(143);
      give();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleContext ------------------------------------------------------------------

MavkaParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::ModuleContext::MODULE() {
  return getToken(MavkaParser::MODULE, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::ModuleContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::ModuleContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

MavkaParser::NlsContext* MavkaParser::ModuleContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}

tree::TerminalNode* MavkaParser::ModuleContext::END() {
  return getToken(MavkaParser::END, 0);
}

MavkaParser::IdentifierContext* MavkaParser::ModuleContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Module_bodyContext* MavkaParser::ModuleContext::module_body() {
  return getRuleContext<MavkaParser::Module_bodyContext>(0);
}


size_t MavkaParser::ModuleContext::getRuleIndex() const {
  return MavkaParser::RuleModule;
}

void MavkaParser::ModuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule(this);
}

void MavkaParser::ModuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule(this);
}


std::any MavkaParser::ModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitModule(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ModuleContext* MavkaParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 6, MavkaParser::RuleModule);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(MavkaParser::MODULE);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::ID) {
      setState(147);
      antlrcpp::downCast<ModuleContext *>(_localctx)->m_name = identifier();
    }
    setState(150);
    nl();
    setState(154);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(151);
      antlrcpp::downCast<ModuleContext *>(_localctx)->m_body = module_body();
      setState(152);
      nl();
      break;
    }

    default:
      break;
    }
    setState(156);
    nls();
    setState(157);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Module_bodyContext ------------------------------------------------------------------

MavkaParser::Module_bodyContext::Module_bodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Module_body_elementContext *> MavkaParser::Module_bodyContext::module_body_element() {
  return getRuleContexts<MavkaParser::Module_body_elementContext>();
}

MavkaParser::Module_body_elementContext* MavkaParser::Module_bodyContext::module_body_element(size_t i) {
  return getRuleContext<MavkaParser::Module_body_elementContext>(i);
}

std::vector<MavkaParser::NlContext *> MavkaParser::Module_bodyContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::Module_bodyContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}


size_t MavkaParser::Module_bodyContext::getRuleIndex() const {
  return MavkaParser::RuleModule_body;
}

void MavkaParser::Module_bodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule_body(this);
}

void MavkaParser::Module_bodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule_body(this);
}


std::any MavkaParser::Module_bodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitModule_body(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Module_bodyContext* MavkaParser::module_body() {
  Module_bodyContext *_localctx = _tracker.createInstance<Module_bodyContext>(_ctx, getState());
  enterRule(_localctx, 8, MavkaParser::RuleModule_body);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(159);
    module_body_element();
    setState(165);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(160);
        nl();
        setState(161);
        module_body_element(); 
      }
      setState(167);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Module_body_elementContext ------------------------------------------------------------------

MavkaParser::Module_body_elementContext::Module_body_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::ModuleContext* MavkaParser::Module_body_elementContext::module() {
  return getRuleContext<MavkaParser::ModuleContext>(0);
}

MavkaParser::StructureContext* MavkaParser::Module_body_elementContext::structure() {
  return getRuleContext<MavkaParser::StructureContext>(0);
}

MavkaParser::DiiaContext* MavkaParser::Module_body_elementContext::diia() {
  return getRuleContext<MavkaParser::DiiaContext>(0);
}

MavkaParser::IfContext* MavkaParser::Module_body_elementContext::if_() {
  return getRuleContext<MavkaParser::IfContext>(0);
}

MavkaParser::EachContext* MavkaParser::Module_body_elementContext::each() {
  return getRuleContext<MavkaParser::EachContext>(0);
}

MavkaParser::WhileContext* MavkaParser::Module_body_elementContext::while_() {
  return getRuleContext<MavkaParser::WhileContext>(0);
}

MavkaParser::TryContext* MavkaParser::Module_body_elementContext::try_() {
  return getRuleContext<MavkaParser::TryContext>(0);
}

MavkaParser::ExprContext* MavkaParser::Module_body_elementContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::ThrowContext* MavkaParser::Module_body_elementContext::throw_() {
  return getRuleContext<MavkaParser::ThrowContext>(0);
}

MavkaParser::Wait_assignContext* MavkaParser::Module_body_elementContext::wait_assign() {
  return getRuleContext<MavkaParser::Wait_assignContext>(0);
}

MavkaParser::AssignContext* MavkaParser::Module_body_elementContext::assign() {
  return getRuleContext<MavkaParser::AssignContext>(0);
}

MavkaParser::NlsContext* MavkaParser::Module_body_elementContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}

MavkaParser::GiveContext* MavkaParser::Module_body_elementContext::give() {
  return getRuleContext<MavkaParser::GiveContext>(0);
}


size_t MavkaParser::Module_body_elementContext::getRuleIndex() const {
  return MavkaParser::RuleModule_body_element;
}

void MavkaParser::Module_body_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule_body_element(this);
}

void MavkaParser::Module_body_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule_body_element(this);
}


std::any MavkaParser::Module_body_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitModule_body_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Module_body_elementContext* MavkaParser::module_body_element() {
  Module_body_elementContext *_localctx = _tracker.createInstance<Module_body_elementContext>(_ctx, getState());
  enterRule(_localctx, 10, MavkaParser::RuleModule_body_element);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(181);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(168);
      module();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(169);
      structure();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(170);
      diia();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(171);
      if_();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(172);
      each();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(173);
      while_();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(174);
      try_();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(175);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(176);
      throw_();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(177);
      wait_assign();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(178);
      assign();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(179);
      nls();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(180);
      give();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructureContext ------------------------------------------------------------------

MavkaParser::StructureContext::StructureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::StructureContext::STRUCTURE() {
  return getToken(MavkaParser::STRUCTURE, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::StructureContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::StructureContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

MavkaParser::NlsContext* MavkaParser::StructureContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}

tree::TerminalNode* MavkaParser::StructureContext::END() {
  return getToken(MavkaParser::END, 0);
}

MavkaParser::IdentifierContext* MavkaParser::StructureContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Structure_elementsContext* MavkaParser::StructureContext::structure_elements() {
  return getRuleContext<MavkaParser::Structure_elementsContext>(0);
}


size_t MavkaParser::StructureContext::getRuleIndex() const {
  return MavkaParser::RuleStructure;
}

void MavkaParser::StructureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructure(this);
}

void MavkaParser::StructureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructure(this);
}


std::any MavkaParser::StructureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitStructure(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::StructureContext* MavkaParser::structure() {
  StructureContext *_localctx = _tracker.createInstance<StructureContext>(_ctx, getState());
  enterRule(_localctx, 12, MavkaParser::RuleStructure);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(MavkaParser::STRUCTURE);
    setState(184);
    antlrcpp::downCast<StructureContext *>(_localctx)->s_name = identifier();
    setState(185);
    nl();
    setState(189);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(186);
      antlrcpp::downCast<StructureContext *>(_localctx)->s_elements = structure_elements();
      setState(187);
      nl();
      break;
    }

    default:
      break;
    }
    setState(191);
    nls();
    setState(192);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Structure_elementsContext ------------------------------------------------------------------

MavkaParser::Structure_elementsContext::Structure_elementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Structure_elementContext *> MavkaParser::Structure_elementsContext::structure_element() {
  return getRuleContexts<MavkaParser::Structure_elementContext>();
}

MavkaParser::Structure_elementContext* MavkaParser::Structure_elementsContext::structure_element(size_t i) {
  return getRuleContext<MavkaParser::Structure_elementContext>(i);
}

std::vector<MavkaParser::NlContext *> MavkaParser::Structure_elementsContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::Structure_elementsContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}


size_t MavkaParser::Structure_elementsContext::getRuleIndex() const {
  return MavkaParser::RuleStructure_elements;
}

void MavkaParser::Structure_elementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructure_elements(this);
}

void MavkaParser::Structure_elementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructure_elements(this);
}


std::any MavkaParser::Structure_elementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitStructure_elements(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Structure_elementsContext* MavkaParser::structure_elements() {
  Structure_elementsContext *_localctx = _tracker.createInstance<Structure_elementsContext>(_ctx, getState());
  enterRule(_localctx, 14, MavkaParser::RuleStructure_elements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(194);
    structure_element();
    setState(200);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(195);
        nl();
        setState(196);
        structure_element(); 
      }
      setState(202);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Structure_elementContext ------------------------------------------------------------------

MavkaParser::Structure_elementContext::Structure_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::ParamContext* MavkaParser::Structure_elementContext::param() {
  return getRuleContext<MavkaParser::ParamContext>(0);
}

MavkaParser::NlsContext* MavkaParser::Structure_elementContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}


size_t MavkaParser::Structure_elementContext::getRuleIndex() const {
  return MavkaParser::RuleStructure_element;
}

void MavkaParser::Structure_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructure_element(this);
}

void MavkaParser::Structure_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructure_element(this);
}


std::any MavkaParser::Structure_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitStructure_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Structure_elementContext* MavkaParser::structure_element() {
  Structure_elementContext *_localctx = _tracker.createInstance<Structure_elementContext>(_ctx, getState());
  enterRule(_localctx, 16, MavkaParser::RuleStructure_element);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(205);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::SPREAD:
      case MavkaParser::OPEN_PAREN:
      case MavkaParser::OPEN_ARRAY:
      case MavkaParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(203);
        param();
        break;
      }

      case MavkaParser::NL: {
        enterOuterAlt(_localctx, 2);
        setState(204);
        nls();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DiiaContext ------------------------------------------------------------------

MavkaParser::DiiaContext::DiiaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::DiiaContext::DIIA() {
  return getToken(MavkaParser::DIIA, 0);
}

tree::TerminalNode* MavkaParser::DiiaContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::DiiaContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::DiiaContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::DiiaContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

std::vector<MavkaParser::NlsContext *> MavkaParser::DiiaContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::DiiaContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::DiiaContext::END() {
  return getToken(MavkaParser::END, 0);
}

std::vector<MavkaParser::IdentifierContext *> MavkaParser::DiiaContext::identifier() {
  return getRuleContexts<MavkaParser::IdentifierContext>();
}

MavkaParser::IdentifierContext* MavkaParser::DiiaContext::identifier(size_t i) {
  return getRuleContext<MavkaParser::IdentifierContext>(i);
}

tree::TerminalNode* MavkaParser::DiiaContext::DOT() {
  return getToken(MavkaParser::DOT, 0);
}

tree::TerminalNode* MavkaParser::DiiaContext::ASYNC() {
  return getToken(MavkaParser::ASYNC, 0);
}

MavkaParser::Type_valueContext* MavkaParser::DiiaContext::type_value() {
  return getRuleContext<MavkaParser::Type_valueContext>(0);
}

MavkaParser::BodyContext* MavkaParser::DiiaContext::body() {
  return getRuleContext<MavkaParser::BodyContext>(0);
}

MavkaParser::ParamsContext* MavkaParser::DiiaContext::params() {
  return getRuleContext<MavkaParser::ParamsContext>(0);
}


size_t MavkaParser::DiiaContext::getRuleIndex() const {
  return MavkaParser::RuleDiia;
}

void MavkaParser::DiiaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDiia(this);
}

void MavkaParser::DiiaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDiia(this);
}


std::any MavkaParser::DiiaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitDiia(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::DiiaContext* MavkaParser::diia() {
  DiiaContext *_localctx = _tracker.createInstance<DiiaContext>(_ctx, getState());
  enterRule(_localctx, 18, MavkaParser::RuleDiia);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::ASYNC) {
      setState(207);
      antlrcpp::downCast<DiiaContext *>(_localctx)->d_async = match(MavkaParser::ASYNC);
    }
    setState(210);
    match(MavkaParser::DIIA);
    setState(214);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(211);
      antlrcpp::downCast<DiiaContext *>(_localctx)->d_structure = identifier();
      setState(212);
      match(MavkaParser::DOT);
      break;
    }

    default:
      break;
    }
    setState(216);
    antlrcpp::downCast<DiiaContext *>(_localctx)->d_name = identifier();
    setState(217);
    match(MavkaParser::OPEN_PAREN);

    setState(218);
    nls();
    setState(220);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 46) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 46)) & 140737488355649) != 0)) {
      setState(219);
      antlrcpp::downCast<DiiaContext *>(_localctx)->d_params = params();
    }
    setState(222);
    nls();
    setState(224);
    match(MavkaParser::CLOSE_PAREN);
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::OPEN_ARRAY

    || _la == MavkaParser::ID) {
      setState(225);
      antlrcpp::downCast<DiiaContext *>(_localctx)->d_type = type_value(0);
    }
    setState(228);
    nl();
    setState(232);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(229);
      antlrcpp::downCast<DiiaContext *>(_localctx)->d_body = body();
      setState(230);
      nl();
      break;
    }

    default:
      break;
    }
    setState(234);
    nls();
    setState(235);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfContext ------------------------------------------------------------------

MavkaParser::IfContext::IfContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::IfContext::IF() {
  return getToken(MavkaParser::IF, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::IfContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::IfContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

MavkaParser::ExprContext* MavkaParser::IfContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

std::vector<MavkaParser::BodyContext *> MavkaParser::IfContext::body() {
  return getRuleContexts<MavkaParser::BodyContext>();
}

MavkaParser::BodyContext* MavkaParser::IfContext::body(size_t i) {
  return getRuleContext<MavkaParser::BodyContext>(i);
}

tree::TerminalNode* MavkaParser::IfContext::END() {
  return getToken(MavkaParser::END, 0);
}

tree::TerminalNode* MavkaParser::IfContext::ELSE() {
  return getToken(MavkaParser::ELSE, 0);
}

MavkaParser::IfContext* MavkaParser::IfContext::if_() {
  return getRuleContext<MavkaParser::IfContext>(0);
}


size_t MavkaParser::IfContext::getRuleIndex() const {
  return MavkaParser::RuleIf;
}

void MavkaParser::IfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf(this);
}

void MavkaParser::IfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf(this);
}


std::any MavkaParser::IfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitIf(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::IfContext* MavkaParser::if_() {
  IfContext *_localctx = _tracker.createInstance<IfContext>(_ctx, getState());
  enterRule(_localctx, 20, MavkaParser::RuleIf);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    match(MavkaParser::IF);
    setState(238);
    antlrcpp::downCast<IfContext *>(_localctx)->i_value = expr();
    setState(239);
    nl();
    setState(243);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26458648022095900) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & 135790787) != 0)) {
      setState(240);
      antlrcpp::downCast<IfContext *>(_localctx)->i_body = body();
      setState(241);
      nl();
    }
    setState(254);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(249);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::ELSE) {
        setState(245);
        match(MavkaParser::ELSE);
        setState(246);
        antlrcpp::downCast<IfContext *>(_localctx)->i_else_body = body();
        setState(247);
        nl();
      }
      setState(251);
      match(MavkaParser::END);
      break;
    }

    case 2: {
      setState(252);
      match(MavkaParser::ELSE);
      setState(253);
      antlrcpp::downCast<IfContext *>(_localctx)->i_else_if = if_();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EachContext ------------------------------------------------------------------

MavkaParser::EachContext::EachContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::EachContext::FOR() {
  return getToken(MavkaParser::FOR, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::EachContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::EachContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

tree::TerminalNode* MavkaParser::EachContext::END() {
  return getToken(MavkaParser::END, 0);
}

MavkaParser::ExprContext* MavkaParser::EachContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::FromtoContext* MavkaParser::EachContext::fromto() {
  return getRuleContext<MavkaParser::FromtoContext>(0);
}

tree::TerminalNode* MavkaParser::EachContext::AS() {
  return getToken(MavkaParser::AS, 0);
}

std::vector<MavkaParser::IdentifierContext *> MavkaParser::EachContext::identifier() {
  return getRuleContexts<MavkaParser::IdentifierContext>();
}

MavkaParser::IdentifierContext* MavkaParser::EachContext::identifier(size_t i) {
  return getRuleContext<MavkaParser::IdentifierContext>(i);
}

MavkaParser::BodyContext* MavkaParser::EachContext::body() {
  return getRuleContext<MavkaParser::BodyContext>(0);
}

tree::TerminalNode* MavkaParser::EachContext::COMMA() {
  return getToken(MavkaParser::COMMA, 0);
}


size_t MavkaParser::EachContext::getRuleIndex() const {
  return MavkaParser::RuleEach;
}

void MavkaParser::EachContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEach(this);
}

void MavkaParser::EachContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEach(this);
}


std::any MavkaParser::EachContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitEach(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::EachContext* MavkaParser::each() {
  EachContext *_localctx = _tracker.createInstance<EachContext>(_ctx, getState());
  enterRule(_localctx, 22, MavkaParser::RuleEach);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    match(MavkaParser::FOR);
    setState(259);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      setState(257);
      antlrcpp::downCast<EachContext *>(_localctx)->e_iterator = expr();
      break;
    }

    case 2: {
      setState(258);
      antlrcpp::downCast<EachContext *>(_localctx)->e_fromto = fromto();
      break;
    }

    default:
      break;
    }
    setState(268);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::AS) {
      setState(261);
      match(MavkaParser::AS);
      setState(265);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(262);
        antlrcpp::downCast<EachContext *>(_localctx)->e_key_name = identifier();
        setState(263);
        match(MavkaParser::COMMA);
        break;
      }

      default:
        break;
      }
      setState(267);
      antlrcpp::downCast<EachContext *>(_localctx)->e_name = identifier();
    }
    setState(270);
    nl();
    setState(274);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26458648022095900) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & 135790787) != 0)) {
      setState(271);
      antlrcpp::downCast<EachContext *>(_localctx)->e_body = body();
      setState(272);
      nl();
    }
    setState(276);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromtoContext ------------------------------------------------------------------

MavkaParser::FromtoContext::FromtoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MavkaParser::FromtoContext::FROMTO() {
  return getTokens(MavkaParser::FROMTO);
}

tree::TerminalNode* MavkaParser::FromtoContext::FROMTO(size_t i) {
  return getToken(MavkaParser::FROMTO, i);
}

std::vector<MavkaParser::Fromto_valueContext *> MavkaParser::FromtoContext::fromto_value() {
  return getRuleContexts<MavkaParser::Fromto_valueContext>();
}

MavkaParser::Fromto_valueContext* MavkaParser::FromtoContext::fromto_value(size_t i) {
  return getRuleContext<MavkaParser::Fromto_valueContext>(i);
}

MavkaParser::Fromto_symbolContext* MavkaParser::FromtoContext::fromto_symbol() {
  return getRuleContext<MavkaParser::Fromto_symbolContext>(0);
}

MavkaParser::Fromto_middleContext* MavkaParser::FromtoContext::fromto_middle() {
  return getRuleContext<MavkaParser::Fromto_middleContext>(0);
}


size_t MavkaParser::FromtoContext::getRuleIndex() const {
  return MavkaParser::RuleFromto;
}

void MavkaParser::FromtoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto(this);
}

void MavkaParser::FromtoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto(this);
}


std::any MavkaParser::FromtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::FromtoContext* MavkaParser::fromto() {
  FromtoContext *_localctx = _tracker.createInstance<FromtoContext>(_ctx, getState());
  enterRule(_localctx, 24, MavkaParser::RuleFromto);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    antlrcpp::downCast<FromtoContext *>(_localctx)->f_from = fromto_value();
    setState(279);
    match(MavkaParser::FROMTO);
    setState(281);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2016) != 0)) {
      setState(280);
      antlrcpp::downCast<FromtoContext *>(_localctx)->f_symbol = fromto_symbol();
    }
    setState(283);
    antlrcpp::downCast<FromtoContext *>(_localctx)->f_to = fromto_value();
    setState(286);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::FROMTO) {
      setState(284);
      match(MavkaParser::FROMTO);
      setState(285);
      antlrcpp::downCast<FromtoContext *>(_localctx)->f_middle = fromto_middle();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fromto_valueContext ------------------------------------------------------------------

MavkaParser::Fromto_valueContext::Fromto_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MavkaParser::Fromto_valueContext::getRuleIndex() const {
  return MavkaParser::RuleFromto_value;
}

void MavkaParser::Fromto_valueContext::copyFrom(Fromto_valueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Fromto_idContext ------------------------------------------------------------------

MavkaParser::IdentifierContext* MavkaParser::Fromto_idContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Fromto_idContext::Fromto_idContext(Fromto_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Fromto_idContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_id(this);
}
void MavkaParser::Fromto_idContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_id(this);
}

std::any MavkaParser::Fromto_idContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_id(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Fromto_stringContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Fromto_stringContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}

MavkaParser::Fromto_stringContext::Fromto_stringContext(Fromto_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Fromto_stringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_string(this);
}
void MavkaParser::Fromto_stringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_string(this);
}

std::any MavkaParser::Fromto_stringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_string(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Fromto_numberContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Fromto_numberContext::NUMBER() {
  return getToken(MavkaParser::NUMBER, 0);
}

MavkaParser::Fromto_numberContext::Fromto_numberContext(Fromto_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Fromto_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_number(this);
}
void MavkaParser::Fromto_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_number(this);
}

std::any MavkaParser::Fromto_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_number(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Fromto_nestedContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Fromto_nestedContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::Fromto_nestedContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

MavkaParser::ValueContext* MavkaParser::Fromto_nestedContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Fromto_nestedContext::Fromto_nestedContext(Fromto_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Fromto_nestedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_nested(this);
}
void MavkaParser::Fromto_nestedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_nested(this);
}

std::any MavkaParser::Fromto_nestedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_nested(this);
  else
    return visitor->visitChildren(this);
}
MavkaParser::Fromto_valueContext* MavkaParser::fromto_value() {
  Fromto_valueContext *_localctx = _tracker.createInstance<Fromto_valueContext>(_ctx, getState());
  enterRule(_localctx, 26, MavkaParser::RuleFromto_value);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(295);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::NUMBER: {
        _localctx = _tracker.createInstance<MavkaParser::Fromto_numberContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(288);
        match(MavkaParser::NUMBER);
        break;
      }

      case MavkaParser::STRING: {
        _localctx = _tracker.createInstance<MavkaParser::Fromto_stringContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(289);
        match(MavkaParser::STRING);
        break;
      }

      case MavkaParser::ID: {
        _localctx = _tracker.createInstance<MavkaParser::Fromto_idContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(290);
        identifier();
        break;
      }

      case MavkaParser::OPEN_PAREN: {
        _localctx = _tracker.createInstance<MavkaParser::Fromto_nestedContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(291);
        match(MavkaParser::OPEN_PAREN);
        setState(292);
        antlrcpp::downCast<Fromto_nestedContext *>(_localctx)->fn_value = value(0);
        setState(293);
        match(MavkaParser::CLOSE_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fromto_middleContext ------------------------------------------------------------------

MavkaParser::Fromto_middleContext::Fromto_middleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Fromto_middleContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::Fromto_middleContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

MavkaParser::ValueContext* MavkaParser::Fromto_middleContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}


size_t MavkaParser::Fromto_middleContext::getRuleIndex() const {
  return MavkaParser::RuleFromto_middle;
}

void MavkaParser::Fromto_middleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_middle(this);
}

void MavkaParser::Fromto_middleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_middle(this);
}


std::any MavkaParser::Fromto_middleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_middle(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Fromto_middleContext* MavkaParser::fromto_middle() {
  Fromto_middleContext *_localctx = _tracker.createInstance<Fromto_middleContext>(_ctx, getState());
  enterRule(_localctx, 28, MavkaParser::RuleFromto_middle);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(MavkaParser::OPEN_PAREN);
    setState(298);
    antlrcpp::downCast<Fromto_middleContext *>(_localctx)->fi_value = value(0);
    setState(299);
    match(MavkaParser::CLOSE_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fromto_symbolContext ------------------------------------------------------------------

MavkaParser::Fromto_symbolContext::Fromto_symbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::NOT_EQ() {
  return getToken(MavkaParser::NOT_EQ, 0);
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::EQ() {
  return getToken(MavkaParser::EQ, 0);
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::GREATER() {
  return getToken(MavkaParser::GREATER, 0);
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::SMALLER() {
  return getToken(MavkaParser::SMALLER, 0);
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::GREATER_EQ() {
  return getToken(MavkaParser::GREATER_EQ, 0);
}

tree::TerminalNode* MavkaParser::Fromto_symbolContext::SMALLER_EQ() {
  return getToken(MavkaParser::SMALLER_EQ, 0);
}


size_t MavkaParser::Fromto_symbolContext::getRuleIndex() const {
  return MavkaParser::RuleFromto_symbol;
}

void MavkaParser::Fromto_symbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromto_symbol(this);
}

void MavkaParser::Fromto_symbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromto_symbol(this);
}


std::any MavkaParser::Fromto_symbolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFromto_symbol(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Fromto_symbolContext* MavkaParser::fromto_symbol() {
  Fromto_symbolContext *_localctx = _tracker.createInstance<Fromto_symbolContext>(_ctx, getState());
  enterRule(_localctx, 30, MavkaParser::RuleFromto_symbol);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(301);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2016) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileContext ------------------------------------------------------------------

MavkaParser::WhileContext::WhileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::WhileContext::WHILE() {
  return getToken(MavkaParser::WHILE, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::WhileContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::WhileContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

tree::TerminalNode* MavkaParser::WhileContext::END() {
  return getToken(MavkaParser::END, 0);
}

MavkaParser::ExprContext* MavkaParser::WhileContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::BodyContext* MavkaParser::WhileContext::body() {
  return getRuleContext<MavkaParser::BodyContext>(0);
}


size_t MavkaParser::WhileContext::getRuleIndex() const {
  return MavkaParser::RuleWhile;
}

void MavkaParser::WhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile(this);
}

void MavkaParser::WhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile(this);
}


std::any MavkaParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::WhileContext* MavkaParser::while_() {
  WhileContext *_localctx = _tracker.createInstance<WhileContext>(_ctx, getState());
  enterRule(_localctx, 32, MavkaParser::RuleWhile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(303);
    match(MavkaParser::WHILE);
    setState(304);
    antlrcpp::downCast<WhileContext *>(_localctx)->w_value = expr();
    setState(305);
    nl();
    setState(309);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26458648022095900) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & 135790787) != 0)) {
      setState(306);
      antlrcpp::downCast<WhileContext *>(_localctx)->w_body = body();
      setState(307);
      nl();
    }
    setState(311);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryContext ------------------------------------------------------------------

MavkaParser::TryContext::TryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::TryContext::TRY() {
  return getToken(MavkaParser::TRY, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::TryContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::TryContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

tree::TerminalNode* MavkaParser::TryContext::CATCH() {
  return getToken(MavkaParser::CATCH, 0);
}

tree::TerminalNode* MavkaParser::TryContext::END() {
  return getToken(MavkaParser::END, 0);
}

std::vector<MavkaParser::BodyContext *> MavkaParser::TryContext::body() {
  return getRuleContexts<MavkaParser::BodyContext>();
}

MavkaParser::BodyContext* MavkaParser::TryContext::body(size_t i) {
  return getRuleContext<MavkaParser::BodyContext>(i);
}

MavkaParser::IdentifierContext* MavkaParser::TryContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}


size_t MavkaParser::TryContext::getRuleIndex() const {
  return MavkaParser::RuleTry;
}

void MavkaParser::TryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTry(this);
}

void MavkaParser::TryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTry(this);
}


std::any MavkaParser::TryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTry(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::TryContext* MavkaParser::try_() {
  TryContext *_localctx = _tracker.createInstance<TryContext>(_ctx, getState());
  enterRule(_localctx, 34, MavkaParser::RuleTry);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(313);
    match(MavkaParser::TRY);
    setState(314);
    nl();
    setState(315);
    antlrcpp::downCast<TryContext *>(_localctx)->t_body = body();
    setState(316);
    nl();
    setState(317);
    match(MavkaParser::CATCH);
    setState(319);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(318);
      antlrcpp::downCast<TryContext *>(_localctx)->tc_name = identifier();
      break;
    }

    default:
      break;
    }
    setState(324);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26458648022095900) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & 135790787) != 0)) {
      setState(321);
      antlrcpp::downCast<TryContext *>(_localctx)->tc_body = body();
      setState(322);
      nl();
    }
    setState(326);
    match(MavkaParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TakeContext ------------------------------------------------------------------

MavkaParser::TakeContext::TakeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MavkaParser::TakeContext::getRuleIndex() const {
  return MavkaParser::RuleTake;
}

void MavkaParser::TakeContext::copyFrom(TakeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Take_moduleContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Take_moduleContext::TAKE() {
  return getToken(MavkaParser::TAKE, 0);
}

MavkaParser::Identifiers_chainContext* MavkaParser::Take_moduleContext::identifiers_chain() {
  return getRuleContext<MavkaParser::Identifiers_chainContext>(0);
}

tree::TerminalNode* MavkaParser::Take_moduleContext::AS() {
  return getToken(MavkaParser::AS, 0);
}

tree::TerminalNode* MavkaParser::Take_moduleContext::DOT() {
  return getToken(MavkaParser::DOT, 0);
}

tree::TerminalNode* MavkaParser::Take_moduleContext::STAR_ALL() {
  return getToken(MavkaParser::STAR_ALL, 0);
}

MavkaParser::IdentifierContext* MavkaParser::Take_moduleContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Take_moduleContext::Take_moduleContext(TakeContext *ctx) { copyFrom(ctx); }

void MavkaParser::Take_moduleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTake_module(this);
}
void MavkaParser::Take_moduleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTake_module(this);
}

std::any MavkaParser::Take_moduleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTake_module(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Take_fileContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Take_fileContext::TAKE_FILE() {
  return getToken(MavkaParser::TAKE_FILE, 0);
}

tree::TerminalNode* MavkaParser::Take_fileContext::AS() {
  return getToken(MavkaParser::AS, 0);
}

tree::TerminalNode* MavkaParser::Take_fileContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}

MavkaParser::IdentifierContext* MavkaParser::Take_fileContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Take_fileContext::Take_fileContext(TakeContext *ctx) { copyFrom(ctx); }

void MavkaParser::Take_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTake_file(this);
}
void MavkaParser::Take_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTake_file(this);
}

std::any MavkaParser::Take_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTake_file(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Take_remoteContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Take_remoteContext::TAKE() {
  return getToken(MavkaParser::TAKE, 0);
}

tree::TerminalNode* MavkaParser::Take_remoteContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}

tree::TerminalNode* MavkaParser::Take_remoteContext::AS() {
  return getToken(MavkaParser::AS, 0);
}

MavkaParser::IdentifierContext* MavkaParser::Take_remoteContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Take_remoteContext::Take_remoteContext(TakeContext *ctx) { copyFrom(ctx); }

void MavkaParser::Take_remoteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTake_remote(this);
}
void MavkaParser::Take_remoteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTake_remote(this);
}

std::any MavkaParser::Take_remoteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTake_remote(this);
  else
    return visitor->visitChildren(this);
}
MavkaParser::TakeContext* MavkaParser::take() {
  TakeContext *_localctx = _tracker.createInstance<TakeContext>(_ctx, getState());
  enterRule(_localctx, 36, MavkaParser::RuleTake);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MavkaParser::Take_moduleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(328);
      match(MavkaParser::TAKE);
      setState(330);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::DOT) {
        setState(329);
        antlrcpp::downCast<Take_moduleContext *>(_localctx)->tm_absolute = match(MavkaParser::DOT);
      }
      setState(332);
      antlrcpp::downCast<Take_moduleContext *>(_localctx)->tm_elements_chain = identifiers_chain(0);
      setState(334);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::STAR_ALL) {
        setState(333);
        antlrcpp::downCast<Take_moduleContext *>(_localctx)->tm_star = match(MavkaParser::STAR_ALL);
      }
      setState(338);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::AS) {
        setState(336);
        match(MavkaParser::AS);
        setState(337);
        antlrcpp::downCast<Take_moduleContext *>(_localctx)->tm_as = identifier();
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MavkaParser::Take_fileContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(340);
      match(MavkaParser::TAKE_FILE);
      setState(341);
      antlrcpp::downCast<Take_fileContext *>(_localctx)->tf_name = match(MavkaParser::STRING);
      setState(342);
      match(MavkaParser::AS);
      setState(343);
      antlrcpp::downCast<Take_fileContext *>(_localctx)->tf_as = identifier();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MavkaParser::Take_remoteContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(344);
      match(MavkaParser::TAKE);
      setState(345);
      antlrcpp::downCast<Take_remoteContext *>(_localctx)->tr_url = match(MavkaParser::STRING);
      setState(348);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::AS) {
        setState(346);
        match(MavkaParser::AS);
        setState(347);
        antlrcpp::downCast<Take_remoteContext *>(_localctx)->tr_as = identifier();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GiveContext ------------------------------------------------------------------

MavkaParser::GiveContext::GiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::GiveContext::GIVE() {
  return getToken(MavkaParser::GIVE, 0);
}

std::vector<MavkaParser::Give_elementContext *> MavkaParser::GiveContext::give_element() {
  return getRuleContexts<MavkaParser::Give_elementContext>();
}

MavkaParser::Give_elementContext* MavkaParser::GiveContext::give_element(size_t i) {
  return getRuleContext<MavkaParser::Give_elementContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::GiveContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::GiveContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::GiveContext::getRuleIndex() const {
  return MavkaParser::RuleGive;
}

void MavkaParser::GiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGive(this);
}

void MavkaParser::GiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGive(this);
}


std::any MavkaParser::GiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitGive(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::GiveContext* MavkaParser::give() {
  GiveContext *_localctx = _tracker.createInstance<GiveContext>(_ctx, getState());
  enterRule(_localctx, 38, MavkaParser::RuleGive);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(MavkaParser::GIVE);
    setState(353);
    give_element();
    setState(358);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::COMMA) {
      setState(354);
      match(MavkaParser::COMMA);
      setState(355);
      give_element();
      setState(360);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Give_elementContext ------------------------------------------------------------------

MavkaParser::Give_elementContext::Give_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::IdentifierContext *> MavkaParser::Give_elementContext::identifier() {
  return getRuleContexts<MavkaParser::IdentifierContext>();
}

MavkaParser::IdentifierContext* MavkaParser::Give_elementContext::identifier(size_t i) {
  return getRuleContext<MavkaParser::IdentifierContext>(i);
}

tree::TerminalNode* MavkaParser::Give_elementContext::AS() {
  return getToken(MavkaParser::AS, 0);
}


size_t MavkaParser::Give_elementContext::getRuleIndex() const {
  return MavkaParser::RuleGive_element;
}

void MavkaParser::Give_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGive_element(this);
}

void MavkaParser::Give_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGive_element(this);
}


std::any MavkaParser::Give_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitGive_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Give_elementContext* MavkaParser::give_element() {
  Give_elementContext *_localctx = _tracker.createInstance<Give_elementContext>(_ctx, getState());
  enterRule(_localctx, 40, MavkaParser::RuleGive_element);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    antlrcpp::downCast<Give_elementContext *>(_localctx)->ge_name = identifier();
    setState(364);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::AS) {
      setState(362);
      match(MavkaParser::AS);
      setState(363);
      antlrcpp::downCast<Give_elementContext *>(_localctx)->ge_as = identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

MavkaParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MavkaParser::ValueContext::getRuleIndex() const {
  return MavkaParser::RuleValue;
}

void MavkaParser::ValueContext::copyFrom(ValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Arithmetic_mulContext ------------------------------------------------------------------

std::vector<MavkaParser::ValueContext *> MavkaParser::Arithmetic_mulContext::value() {
  return getRuleContexts<MavkaParser::ValueContext>();
}

MavkaParser::ValueContext* MavkaParser::Arithmetic_mulContext::value(size_t i) {
  return getRuleContext<MavkaParser::ValueContext>(i);
}

MavkaParser::Arithmetic_op_mulContext* MavkaParser::Arithmetic_mulContext::arithmetic_op_mul() {
  return getRuleContext<MavkaParser::Arithmetic_op_mulContext>(0);
}

MavkaParser::Arithmetic_mulContext::Arithmetic_mulContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Arithmetic_mulContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmetic_mul(this);
}
void MavkaParser::Arithmetic_mulContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmetic_mul(this);
}

std::any MavkaParser::Arithmetic_mulContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArithmetic_mul(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Get_elementContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Get_elementContext::OPEN_ARRAY() {
  return getToken(MavkaParser::OPEN_ARRAY, 0);
}

tree::TerminalNode* MavkaParser::Get_elementContext::CLOSE_ARRAY() {
  return getToken(MavkaParser::CLOSE_ARRAY, 0);
}

MavkaParser::ValueContext* MavkaParser::Get_elementContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::ExprContext* MavkaParser::Get_elementContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::Get_elementContext::Get_elementContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Get_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGet_element(this);
}
void MavkaParser::Get_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGet_element(this);
}

std::any MavkaParser::Get_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitGet_element(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChainContext ------------------------------------------------------------------

std::vector<MavkaParser::NlsContext *> MavkaParser::ChainContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::ChainContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::ChainContext::DOT() {
  return getToken(MavkaParser::DOT, 0);
}

MavkaParser::ValueContext* MavkaParser::ChainContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Extended_identifierContext* MavkaParser::ChainContext::extended_identifier() {
  return getRuleContext<MavkaParser::Extended_identifierContext>(0);
}

MavkaParser::ChainContext::ChainContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::ChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChain(this);
}
void MavkaParser::ChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChain(this);
}

std::any MavkaParser::ChainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitChain(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Pre_incrementContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Pre_incrementContext::INCREMENT() {
  return getToken(MavkaParser::INCREMENT, 0);
}

MavkaParser::ValueContext* MavkaParser::Pre_incrementContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Pre_incrementContext::Pre_incrementContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Pre_incrementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPre_increment(this);
}
void MavkaParser::Pre_incrementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPre_increment(this);
}

std::any MavkaParser::Pre_incrementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitPre_increment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Arithmetic_addContext ------------------------------------------------------------------

std::vector<MavkaParser::ValueContext *> MavkaParser::Arithmetic_addContext::value() {
  return getRuleContexts<MavkaParser::ValueContext>();
}

MavkaParser::ValueContext* MavkaParser::Arithmetic_addContext::value(size_t i) {
  return getRuleContext<MavkaParser::ValueContext>(i);
}

MavkaParser::Arithmetic_op_addContext* MavkaParser::Arithmetic_addContext::arithmetic_op_add() {
  return getRuleContext<MavkaParser::Arithmetic_op_addContext>(0);
}

MavkaParser::Arithmetic_addContext::Arithmetic_addContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Arithmetic_addContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmetic_add(this);
}
void MavkaParser::Arithmetic_addContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmetic_add(this);
}

std::any MavkaParser::Arithmetic_addContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArithmetic_add(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonContext ------------------------------------------------------------------

std::vector<MavkaParser::ValueContext *> MavkaParser::ComparisonContext::value() {
  return getRuleContexts<MavkaParser::ValueContext>();
}

MavkaParser::ValueContext* MavkaParser::ComparisonContext::value(size_t i) {
  return getRuleContext<MavkaParser::ValueContext>(i);
}

MavkaParser::Comparison_opContext* MavkaParser::ComparisonContext::comparison_op() {
  return getRuleContext<MavkaParser::Comparison_opContext>(0);
}

MavkaParser::ComparisonContext::ComparisonContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::ComparisonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}
void MavkaParser::ComparisonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}

std::any MavkaParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::StringContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}

MavkaParser::StringContext::StringContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::StringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString(this);
}
void MavkaParser::StringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString(this);
}

std::any MavkaParser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Bitwise_notContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Bitwise_notContext::TILDA() {
  return getToken(MavkaParser::TILDA, 0);
}

MavkaParser::ValueContext* MavkaParser::Bitwise_notContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Bitwise_notContext::Bitwise_notContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Bitwise_notContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwise_not(this);
}
void MavkaParser::Bitwise_notContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwise_not(this);
}

std::any MavkaParser::Bitwise_notContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBitwise_not(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TestContext ------------------------------------------------------------------

std::vector<MavkaParser::ValueContext *> MavkaParser::TestContext::value() {
  return getRuleContexts<MavkaParser::ValueContext>();
}

MavkaParser::ValueContext* MavkaParser::TestContext::value(size_t i) {
  return getRuleContext<MavkaParser::ValueContext>(i);
}

MavkaParser::Test_opContext* MavkaParser::TestContext::test_op() {
  return getRuleContext<MavkaParser::Test_opContext>(0);
}

MavkaParser::TestContext::TestContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::TestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTest(this);
}
void MavkaParser::TestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTest(this);
}

std::any MavkaParser::TestContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTest(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Call_exprContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> MavkaParser::Call_exprContext::OPEN_PAREN() {
  return getTokens(MavkaParser::OPEN_PAREN);
}

tree::TerminalNode* MavkaParser::Call_exprContext::OPEN_PAREN(size_t i) {
  return getToken(MavkaParser::OPEN_PAREN, i);
}

std::vector<tree::TerminalNode *> MavkaParser::Call_exprContext::CLOSE_PAREN() {
  return getTokens(MavkaParser::CLOSE_PAREN);
}

tree::TerminalNode* MavkaParser::Call_exprContext::CLOSE_PAREN(size_t i) {
  return getToken(MavkaParser::CLOSE_PAREN, i);
}

MavkaParser::ExprContext* MavkaParser::Call_exprContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::ArgsContext* MavkaParser::Call_exprContext::args() {
  return getRuleContext<MavkaParser::ArgsContext>(0);
}

MavkaParser::Named_argsContext* MavkaParser::Call_exprContext::named_args() {
  return getRuleContext<MavkaParser::Named_argsContext>(0);
}

MavkaParser::Call_exprContext::Call_exprContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Call_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall_expr(this);
}
void MavkaParser::Call_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall_expr(this);
}

std::any MavkaParser::Call_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitCall_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PositiveContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::PositiveContext::PLUS() {
  return getToken(MavkaParser::PLUS, 0);
}

MavkaParser::ValueContext* MavkaParser::PositiveContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::PositiveContext::PositiveContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::PositiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPositive(this);
}
void MavkaParser::PositiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPositive(this);
}

std::any MavkaParser::PositiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitPositive(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NestedContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::NestedContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::NestedContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

MavkaParser::ExprContext* MavkaParser::NestedContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::NestedContext::NestedContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::NestedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNested(this);
}
void MavkaParser::NestedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNested(this);
}

std::any MavkaParser::NestedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNested(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::CallContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::CallContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

MavkaParser::ValueContext* MavkaParser::CallContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::ArgsContext* MavkaParser::CallContext::args() {
  return getRuleContext<MavkaParser::ArgsContext>(0);
}

MavkaParser::Named_argsContext* MavkaParser::CallContext::named_args() {
  return getRuleContext<MavkaParser::Named_argsContext>(0);
}

MavkaParser::CallContext::CallContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::CallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}
void MavkaParser::CallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}

std::any MavkaParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::NumberContext::NUMBER() {
  return getToken(MavkaParser::NUMBER, 0);
}

MavkaParser::NumberContext::NumberContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}
void MavkaParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

std::any MavkaParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegativeContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::NegativeContext::MINUS() {
  return getToken(MavkaParser::MINUS, 0);
}

MavkaParser::ValueContext* MavkaParser::NegativeContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::NegativeContext::NegativeContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::NegativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegative(this);
}
void MavkaParser::NegativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegative(this);
}

std::any MavkaParser::NegativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNegative(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::NotContext::NOT() {
  return getToken(MavkaParser::NOT, 0);
}

MavkaParser::ValueContext* MavkaParser::NotContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::NotContext::NotContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::NotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot(this);
}
void MavkaParser::NotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot(this);
}

std::any MavkaParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DictionaryContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::DictionaryContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::DictionaryContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

MavkaParser::Dictionary_argsContext* MavkaParser::DictionaryContext::dictionary_args() {
  return getRuleContext<MavkaParser::Dictionary_argsContext>(0);
}

MavkaParser::DictionaryContext::DictionaryContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::DictionaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionary(this);
}
void MavkaParser::DictionaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionary(this);
}

std::any MavkaParser::DictionaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitDictionary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::ArrayContext::OPEN_ARRAY() {
  return getToken(MavkaParser::OPEN_ARRAY, 0);
}

tree::TerminalNode* MavkaParser::ArrayContext::CLOSE_ARRAY() {
  return getToken(MavkaParser::CLOSE_ARRAY, 0);
}

MavkaParser::Array_elementsContext* MavkaParser::ArrayContext::array_elements() {
  return getRuleContext<MavkaParser::Array_elementsContext>(0);
}

MavkaParser::ArrayContext::ArrayContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::ArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray(this);
}
void MavkaParser::ArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray(this);
}

std::any MavkaParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Pre_decrementContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Pre_decrementContext::DECREMENT() {
  return getToken(MavkaParser::DECREMENT, 0);
}

MavkaParser::ValueContext* MavkaParser::Pre_decrementContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Pre_decrementContext::Pre_decrementContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Pre_decrementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPre_decrement(this);
}
void MavkaParser::Pre_decrementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPre_decrement(this);
}

std::any MavkaParser::Pre_decrementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitPre_decrement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseContext ------------------------------------------------------------------

std::vector<MavkaParser::ValueContext *> MavkaParser::BitwiseContext::value() {
  return getRuleContexts<MavkaParser::ValueContext>();
}

MavkaParser::ValueContext* MavkaParser::BitwiseContext::value(size_t i) {
  return getRuleContext<MavkaParser::ValueContext>(i);
}

MavkaParser::Bitwise_opContext* MavkaParser::BitwiseContext::bitwise_op() {
  return getRuleContext<MavkaParser::Bitwise_opContext>(0);
}

MavkaParser::BitwiseContext::BitwiseContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::BitwiseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwise(this);
}
void MavkaParser::BitwiseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwise(this);
}

std::any MavkaParser::BitwiseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBitwise(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Post_decrementContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Post_decrementContext::DECREMENT() {
  return getToken(MavkaParser::DECREMENT, 0);
}

MavkaParser::ValueContext* MavkaParser::Post_decrementContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Post_decrementContext::Post_decrementContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Post_decrementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPost_decrement(this);
}
void MavkaParser::Post_decrementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPost_decrement(this);
}

std::any MavkaParser::Post_decrementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitPost_decrement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdContext ------------------------------------------------------------------

MavkaParser::IdentifierContext* MavkaParser::IdContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::IdContext::IdContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::IdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterId(this);
}
void MavkaParser::IdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitId(this);
}

std::any MavkaParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Post_incrementContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Post_incrementContext::INCREMENT() {
  return getToken(MavkaParser::INCREMENT, 0);
}

MavkaParser::ValueContext* MavkaParser::Post_incrementContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::Post_incrementContext::Post_incrementContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Post_incrementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPost_increment(this);
}
void MavkaParser::Post_incrementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPost_increment(this);
}

std::any MavkaParser::Post_incrementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitPost_increment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TernaryContext ------------------------------------------------------------------

std::vector<MavkaParser::NlsContext *> MavkaParser::TernaryContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::TernaryContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::TernaryContext::TERNARY() {
  return getToken(MavkaParser::TERNARY, 0);
}

tree::TerminalNode* MavkaParser::TernaryContext::COLON() {
  return getToken(MavkaParser::COLON, 0);
}

MavkaParser::ValueContext* MavkaParser::TernaryContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

std::vector<MavkaParser::ExprContext *> MavkaParser::TernaryContext::expr() {
  return getRuleContexts<MavkaParser::ExprContext>();
}

MavkaParser::ExprContext* MavkaParser::TernaryContext::expr(size_t i) {
  return getRuleContext<MavkaParser::ExprContext>(i);
}

MavkaParser::TernaryContext::TernaryContext(ValueContext *ctx) { copyFrom(ctx); }

void MavkaParser::TernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernary(this);
}
void MavkaParser::TernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernary(this);
}

std::any MavkaParser::TernaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTernary(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ValueContext* MavkaParser::value() {
   return value(0);
}

MavkaParser::ValueContext* MavkaParser::value(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MavkaParser::ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, parentState);
  MavkaParser::ValueContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, MavkaParser::RuleValue, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(406);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<NumberContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(367);
      match(MavkaParser::NUMBER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<StringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(368);
      match(MavkaParser::STRING);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(369);
      identifier();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PositiveContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(370);
      match(MavkaParser::PLUS);
      setState(371);
      antlrcpp::downCast<PositiveContext *>(_localctx)->p_value = value(19);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<NegativeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(372);
      match(MavkaParser::MINUS);
      setState(373);
      antlrcpp::downCast<NegativeContext *>(_localctx)->n_value = value(18);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<Pre_decrementContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(374);
      match(MavkaParser::DECREMENT);
      setState(375);
      antlrcpp::downCast<Pre_decrementContext *>(_localctx)->pd_value = value(17);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<Pre_incrementContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(376);
      match(MavkaParser::INCREMENT);
      setState(377);
      antlrcpp::downCast<Pre_incrementContext *>(_localctx)->pi_value = value(16);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(378);
      match(MavkaParser::NOT);
      setState(379);
      antlrcpp::downCast<NotContext *>(_localctx)->n_value = value(13);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<Bitwise_notContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(380);
      match(MavkaParser::TILDA);
      setState(381);
      antlrcpp::downCast<Bitwise_notContext *>(_localctx)->bn_value = value(12);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<NestedContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(382);
      match(MavkaParser::OPEN_PAREN);
      setState(383);
      antlrcpp::downCast<NestedContext *>(_localctx)->n_value = expr();
      setState(384);
      match(MavkaParser::CLOSE_PAREN);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<Call_exprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(386);
      match(MavkaParser::OPEN_PAREN);
      setState(387);
      antlrcpp::downCast<Call_exprContext *>(_localctx)->c_value = expr();
      setState(388);
      match(MavkaParser::CLOSE_PAREN);
      setState(389);
      match(MavkaParser::OPEN_PAREN);
      setState(392);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(390);
        antlrcpp::downCast<Call_exprContext *>(_localctx)->c_args = args();
        break;
      }

      case 2: {
        setState(391);
        antlrcpp::downCast<Call_exprContext *>(_localctx)->c_named_args = named_args();
        break;
      }

      default:
        break;
      }
      setState(394);
      match(MavkaParser::CLOSE_PAREN);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<ArrayContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(396);
      match(MavkaParser::OPEN_ARRAY);
      setState(398);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 26458647811854340) != 0) || ((((_la - 74) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 74)) & 135790787) != 0)) {
        setState(397);
        antlrcpp::downCast<ArrayContext *>(_localctx)->a_elements = array_elements();
      }
      setState(400);
      match(MavkaParser::CLOSE_ARRAY);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<DictionaryContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(401);
      match(MavkaParser::OPEN_PAREN);
      setState(403);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 49) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 49)) & 4521191813414913) != 0)) {
        setState(402);
        antlrcpp::downCast<DictionaryContext *>(_localctx)->d_args = dictionary_args();
      }
      setState(405);
      match(MavkaParser::CLOSE_PAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(462);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(460);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<Arithmetic_mulContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->a_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(408);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(409);
          antlrcpp::downCast<Arithmetic_mulContext *>(_localctx)->a_operation = arithmetic_op_mul();
          setState(410);
          antlrcpp::downCast<Arithmetic_mulContext *>(_localctx)->a_right = value(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<Arithmetic_addContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->a_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(412);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(413);
          antlrcpp::downCast<Arithmetic_addContext *>(_localctx)->a_operation = arithmetic_op_add();
          setState(414);
          antlrcpp::downCast<Arithmetic_addContext *>(_localctx)->a_right = value(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BitwiseContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->b_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(416);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(417);
          antlrcpp::downCast<BitwiseContext *>(_localctx)->b_operation = bitwise_op();
          setState(418);
          antlrcpp::downCast<BitwiseContext *>(_localctx)->b_right = value(7);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->c_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(420);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(421);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->c_operation = comparison_op();
          setState(422);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->c_right = value(6);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<TestContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->t_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(424);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(425);
          antlrcpp::downCast<TestContext *>(_localctx)->t_operation = test_op();
          setState(426);
          antlrcpp::downCast<TestContext *>(_localctx)->t_right = value(5);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ChainContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->c_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(428);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(429);
          nls();
          setState(430);
          match(MavkaParser::DOT);
          setState(431);
          nls();
          setState(432);
          antlrcpp::downCast<ChainContext *>(_localctx)->c_right = extended_identifier();
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<CallContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->c_value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(434);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(435);
          match(MavkaParser::OPEN_PAREN);
          setState(438);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
          case 1: {
            setState(436);
            antlrcpp::downCast<CallContext *>(_localctx)->c_args = args();
            break;
          }

          case 2: {
            setState(437);
            antlrcpp::downCast<CallContext *>(_localctx)->c_named_args = named_args();
            break;
          }

          default:
            break;
          }
          setState(440);
          match(MavkaParser::CLOSE_PAREN);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<Post_decrementContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->pd_value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(441);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(442);
          match(MavkaParser::DECREMENT);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<Post_incrementContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->pi_value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(443);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(444);
          match(MavkaParser::INCREMENT);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<Get_elementContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->a_left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(445);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(446);
          match(MavkaParser::OPEN_ARRAY);
          setState(447);
          antlrcpp::downCast<Get_elementContext *>(_localctx)->a_element = expr();
          setState(448);
          match(MavkaParser::CLOSE_ARRAY);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<TernaryContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->t_value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleValue);
          setState(450);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(451);
          nls();
          setState(452);
          match(MavkaParser::TERNARY);
          setState(453);
          nls();
          setState(454);
          antlrcpp::downCast<TernaryContext *>(_localctx)->t_positive = expr();
          setState(455);
          nls();
          setState(456);
          match(MavkaParser::COLON);
          setState(457);
          nls();
          setState(458);
          antlrcpp::downCast<TernaryContext *>(_localctx)->t_negative = expr();
          break;
        }

        default:
          break;
        } 
      }
      setState(464);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Array_elementsContext ------------------------------------------------------------------

MavkaParser::Array_elementsContext::Array_elementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Array_elementsContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Array_elementsContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

std::vector<MavkaParser::Array_elementContext *> MavkaParser::Array_elementsContext::array_element() {
  return getRuleContexts<MavkaParser::Array_elementContext>();
}

MavkaParser::Array_elementContext* MavkaParser::Array_elementsContext::array_element(size_t i) {
  return getRuleContext<MavkaParser::Array_elementContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::Array_elementsContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::Array_elementsContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::Array_elementsContext::getRuleIndex() const {
  return MavkaParser::RuleArray_elements;
}

void MavkaParser::Array_elementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_elements(this);
}

void MavkaParser::Array_elementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_elements(this);
}


std::any MavkaParser::Array_elementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArray_elements(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Array_elementsContext* MavkaParser::array_elements() {
  Array_elementsContext *_localctx = _tracker.createInstance<Array_elementsContext>(_ctx, getState());
  enterRule(_localctx, 44, MavkaParser::RuleArray_elements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    nls();
    setState(466);
    array_element();
    setState(467);
    nls();
    setState(476);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::NL

    || _la == MavkaParser::COMMA) {
      setState(468);
      nls();
      setState(469);
      match(MavkaParser::COMMA);
      setState(470);
      nls();
      setState(471);
      array_element();
      setState(472);
      nls();
      setState(478);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_elementContext ------------------------------------------------------------------

MavkaParser::Array_elementContext::Array_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::ExprContext* MavkaParser::Array_elementContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}


size_t MavkaParser::Array_elementContext::getRuleIndex() const {
  return MavkaParser::RuleArray_element;
}

void MavkaParser::Array_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_element(this);
}

void MavkaParser::Array_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_element(this);
}


std::any MavkaParser::Array_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArray_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Array_elementContext* MavkaParser::array_element() {
  Array_elementContext *_localctx = _tracker.createInstance<Array_elementContext>(_ctx, getState());
  enterRule(_localctx, 46, MavkaParser::RuleArray_element);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(479);
    antlrcpp::downCast<Array_elementContext *>(_localctx)->ae_value = expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dictionary_argsContext ------------------------------------------------------------------

MavkaParser::Dictionary_argsContext::Dictionary_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Dictionary_argContext *> MavkaParser::Dictionary_argsContext::dictionary_arg() {
  return getRuleContexts<MavkaParser::Dictionary_argContext>();
}

MavkaParser::Dictionary_argContext* MavkaParser::Dictionary_argsContext::dictionary_arg(size_t i) {
  return getRuleContext<MavkaParser::Dictionary_argContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::Dictionary_argsContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::Dictionary_argsContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::Dictionary_argsContext::getRuleIndex() const {
  return MavkaParser::RuleDictionary_args;
}

void MavkaParser::Dictionary_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionary_args(this);
}

void MavkaParser::Dictionary_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionary_args(this);
}


std::any MavkaParser::Dictionary_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitDictionary_args(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Dictionary_argsContext* MavkaParser::dictionary_args() {
  Dictionary_argsContext *_localctx = _tracker.createInstance<Dictionary_argsContext>(_ctx, getState());
  enterRule(_localctx, 48, MavkaParser::RuleDictionary_args);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(481);
    dictionary_arg();
    setState(486);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::COMMA) {
      setState(482);
      match(MavkaParser::COMMA);
      setState(483);
      dictionary_arg();
      setState(488);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dictionary_argContext ------------------------------------------------------------------

MavkaParser::Dictionary_argContext::Dictionary_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Dictionary_argContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Dictionary_argContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::Dictionary_argContext::ASSIGN() {
  return getToken(MavkaParser::ASSIGN, 0);
}

MavkaParser::ExprContext* MavkaParser::Dictionary_argContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::IdentifierContext* MavkaParser::Dictionary_argContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

tree::TerminalNode* MavkaParser::Dictionary_argContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}


size_t MavkaParser::Dictionary_argContext::getRuleIndex() const {
  return MavkaParser::RuleDictionary_arg;
}

void MavkaParser::Dictionary_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionary_arg(this);
}

void MavkaParser::Dictionary_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionary_arg(this);
}


std::any MavkaParser::Dictionary_argContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitDictionary_arg(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Dictionary_argContext* MavkaParser::dictionary_arg() {
  Dictionary_argContext *_localctx = _tracker.createInstance<Dictionary_argContext>(_ctx, getState());
  enterRule(_localctx, 50, MavkaParser::RuleDictionary_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(489);
    nls();
    setState(492);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::ID: {
        setState(490);
        antlrcpp::downCast<Dictionary_argContext *>(_localctx)->da_name_id = identifier();
        break;
      }

      case MavkaParser::STRING: {
        setState(491);
        antlrcpp::downCast<Dictionary_argContext *>(_localctx)->da_name_string = match(MavkaParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(494);
    match(MavkaParser::ASSIGN);
    setState(495);
    antlrcpp::downCast<Dictionary_argContext *>(_localctx)->da_value = expr();
    setState(496);
    nls();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MavkaParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MavkaParser::ExprContext::getRuleIndex() const {
  return MavkaParser::RuleExpr;
}

void MavkaParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Anonymous_diiaContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Anonymous_diiaContext::DIIA() {
  return getToken(MavkaParser::DIIA, 0);
}

tree::TerminalNode* MavkaParser::Anonymous_diiaContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::Anonymous_diiaContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

std::vector<MavkaParser::NlContext *> MavkaParser::Anonymous_diiaContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::Anonymous_diiaContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Anonymous_diiaContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Anonymous_diiaContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::Anonymous_diiaContext::END() {
  return getToken(MavkaParser::END, 0);
}

tree::TerminalNode* MavkaParser::Anonymous_diiaContext::ASYNC() {
  return getToken(MavkaParser::ASYNC, 0);
}

MavkaParser::Type_valueContext* MavkaParser::Anonymous_diiaContext::type_value() {
  return getRuleContext<MavkaParser::Type_valueContext>(0);
}

MavkaParser::BodyContext* MavkaParser::Anonymous_diiaContext::body() {
  return getRuleContext<MavkaParser::BodyContext>(0);
}

MavkaParser::ParamsContext* MavkaParser::Anonymous_diiaContext::params() {
  return getRuleContext<MavkaParser::ParamsContext>(0);
}

MavkaParser::Anonymous_diiaContext::Anonymous_diiaContext(ExprContext *ctx) { copyFrom(ctx); }

void MavkaParser::Anonymous_diiaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnonymous_diia(this);
}
void MavkaParser::Anonymous_diiaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnonymous_diia(this);
}

std::any MavkaParser::Anonymous_diiaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitAnonymous_diia(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WaitContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::WaitContext::WAIT() {
  return getToken(MavkaParser::WAIT, 0);
}

MavkaParser::ValueContext* MavkaParser::WaitContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::WaitContext::WaitContext(ExprContext *ctx) { copyFrom(ctx); }

void MavkaParser::WaitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWait(this);
}
void MavkaParser::WaitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWait(this);
}

std::any MavkaParser::WaitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitWait(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::FunctionContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

tree::TerminalNode* MavkaParser::FunctionContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

tree::TerminalNode* MavkaParser::FunctionContext::COLON() {
  return getToken(MavkaParser::COLON, 0);
}

MavkaParser::ExprContext* MavkaParser::FunctionContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::ParamsContext* MavkaParser::FunctionContext::params() {
  return getRuleContext<MavkaParser::ParamsContext>(0);
}

MavkaParser::Type_valueContext* MavkaParser::FunctionContext::type_value() {
  return getRuleContext<MavkaParser::Type_valueContext>(0);
}

MavkaParser::FunctionContext::FunctionContext(ExprContext *ctx) { copyFrom(ctx); }

void MavkaParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}
void MavkaParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

std::any MavkaParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SimpleContext ------------------------------------------------------------------

MavkaParser::ValueContext* MavkaParser::SimpleContext::value() {
  return getRuleContext<MavkaParser::ValueContext>(0);
}

MavkaParser::SimpleContext::SimpleContext(ExprContext *ctx) { copyFrom(ctx); }

void MavkaParser::SimpleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple(this);
}
void MavkaParser::SimpleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple(this);
}

std::any MavkaParser::SimpleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitSimple(this);
  else
    return visitor->visitChildren(this);
}
MavkaParser::ExprContext* MavkaParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 52, MavkaParser::RuleExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(535);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MavkaParser::SimpleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(498);
      value(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MavkaParser::WaitContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(499);
      match(MavkaParser::WAIT);
      setState(500);
      antlrcpp::downCast<WaitContext *>(_localctx)->w_value = value(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MavkaParser::FunctionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(501);
      match(MavkaParser::OPEN_PAREN);
      setState(503);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & 140737488355649) != 0)) {
        setState(502);
        antlrcpp::downCast<FunctionContext *>(_localctx)->f_params = params();
      }
      setState(505);
      match(MavkaParser::CLOSE_PAREN);
      setState(507);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::OPEN_ARRAY

      || _la == MavkaParser::ID) {
        setState(506);
        antlrcpp::downCast<FunctionContext *>(_localctx)->f_type = type_value(0);
      }
      setState(509);
      match(MavkaParser::COLON);
      setState(510);
      antlrcpp::downCast<FunctionContext *>(_localctx)->f_body = expr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MavkaParser::Anonymous_diiaContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(512);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::ASYNC) {
        setState(511);
        antlrcpp::downCast<Anonymous_diiaContext *>(_localctx)->d_async = match(MavkaParser::ASYNC);
      }
      setState(514);
      match(MavkaParser::DIIA);
      setState(515);
      match(MavkaParser::OPEN_PAREN);

      setState(516);
      nls();
      setState(518);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & 140737488355649) != 0)) {
        setState(517);
        antlrcpp::downCast<Anonymous_diiaContext *>(_localctx)->d_params = params();
      }
      setState(520);
      nls();
      setState(522);
      match(MavkaParser::CLOSE_PAREN);
      setState(524);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::OPEN_ARRAY

      || _la == MavkaParser::ID) {
        setState(523);
        antlrcpp::downCast<Anonymous_diiaContext *>(_localctx)->d_type = type_value(0);
      }
      setState(526);
      nl();
      setState(530);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
      case 1: {
        setState(527);
        antlrcpp::downCast<Anonymous_diiaContext *>(_localctx)->d_body = body();
        setState(528);
        nl();
        break;
      }

      default:
        break;
      }
      setState(532);
      nls();
      setState(533);
      match(MavkaParser::END);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowContext ------------------------------------------------------------------

MavkaParser::ThrowContext::ThrowContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::ThrowContext::THROW() {
  return getToken(MavkaParser::THROW, 0);
}

MavkaParser::ExprContext* MavkaParser::ThrowContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}


size_t MavkaParser::ThrowContext::getRuleIndex() const {
  return MavkaParser::RuleThrow;
}

void MavkaParser::ThrowContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrow(this);
}

void MavkaParser::ThrowContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrow(this);
}


std::any MavkaParser::ThrowContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitThrow(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ThrowContext* MavkaParser::throw_() {
  ThrowContext *_localctx = _tracker.createInstance<ThrowContext>(_ctx, getState());
  enterRule(_localctx, 54, MavkaParser::RuleThrow);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
    match(MavkaParser::THROW);
    setState(538);
    antlrcpp::downCast<ThrowContext *>(_localctx)->t_value = expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_destructionContext ------------------------------------------------------------------

MavkaParser::Array_destructionContext::Array_destructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Array_destructionContext::OPEN_ARRAY() {
  return getToken(MavkaParser::OPEN_ARRAY, 0);
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Array_destructionContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Array_destructionContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

std::vector<MavkaParser::Array_destruction_elContext *> MavkaParser::Array_destructionContext::array_destruction_el() {
  return getRuleContexts<MavkaParser::Array_destruction_elContext>();
}

MavkaParser::Array_destruction_elContext* MavkaParser::Array_destructionContext::array_destruction_el(size_t i) {
  return getRuleContext<MavkaParser::Array_destruction_elContext>(i);
}

tree::TerminalNode* MavkaParser::Array_destructionContext::CLOSE_ARRAY() {
  return getToken(MavkaParser::CLOSE_ARRAY, 0);
}

std::vector<tree::TerminalNode *> MavkaParser::Array_destructionContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::Array_destructionContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::Array_destructionContext::getRuleIndex() const {
  return MavkaParser::RuleArray_destruction;
}

void MavkaParser::Array_destructionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_destruction(this);
}

void MavkaParser::Array_destructionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_destruction(this);
}


std::any MavkaParser::Array_destructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArray_destruction(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Array_destructionContext* MavkaParser::array_destruction() {
  Array_destructionContext *_localctx = _tracker.createInstance<Array_destructionContext>(_ctx, getState());
  enterRule(_localctx, 56, MavkaParser::RuleArray_destruction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(540);
    match(MavkaParser::OPEN_ARRAY);
    setState(541);
    nls();
    setState(542);
    array_destruction_el();
    setState(543);
    nls();
    setState(552);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::NL

    || _la == MavkaParser::COMMA) {
      setState(544);
      nls();
      setState(545);
      match(MavkaParser::COMMA);
      setState(546);
      nls();
      setState(547);
      array_destruction_el();
      setState(548);
      nls();
      setState(554);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(555);
    match(MavkaParser::CLOSE_ARRAY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_destruction_elContext ------------------------------------------------------------------

MavkaParser::Array_destruction_elContext::Array_destruction_elContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::IdentifierContext* MavkaParser::Array_destruction_elContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}


size_t MavkaParser::Array_destruction_elContext::getRuleIndex() const {
  return MavkaParser::RuleArray_destruction_el;
}

void MavkaParser::Array_destruction_elContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_destruction_el(this);
}

void MavkaParser::Array_destruction_elContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_destruction_el(this);
}


std::any MavkaParser::Array_destruction_elContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArray_destruction_el(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Array_destruction_elContext* MavkaParser::array_destruction_el() {
  Array_destruction_elContext *_localctx = _tracker.createInstance<Array_destruction_elContext>(_ctx, getState());
  enterRule(_localctx, 58, MavkaParser::RuleArray_destruction_el);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(557);
    antlrcpp::downCast<Array_destruction_elContext *>(_localctx)->ade_id = identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Object_destructionContext ------------------------------------------------------------------

MavkaParser::Object_destructionContext::Object_destructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Object_destructionContext::OPEN_PAREN() {
  return getToken(MavkaParser::OPEN_PAREN, 0);
}

std::vector<MavkaParser::Object_destruction_elContext *> MavkaParser::Object_destructionContext::object_destruction_el() {
  return getRuleContexts<MavkaParser::Object_destruction_elContext>();
}

MavkaParser::Object_destruction_elContext* MavkaParser::Object_destructionContext::object_destruction_el(size_t i) {
  return getRuleContext<MavkaParser::Object_destruction_elContext>(i);
}

tree::TerminalNode* MavkaParser::Object_destructionContext::CLOSE_PAREN() {
  return getToken(MavkaParser::CLOSE_PAREN, 0);
}

std::vector<tree::TerminalNode *> MavkaParser::Object_destructionContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::Object_destructionContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::Object_destructionContext::getRuleIndex() const {
  return MavkaParser::RuleObject_destruction;
}

void MavkaParser::Object_destructionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObject_destruction(this);
}

void MavkaParser::Object_destructionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObject_destruction(this);
}


std::any MavkaParser::Object_destructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitObject_destruction(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Object_destructionContext* MavkaParser::object_destruction() {
  Object_destructionContext *_localctx = _tracker.createInstance<Object_destructionContext>(_ctx, getState());
  enterRule(_localctx, 60, MavkaParser::RuleObject_destruction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(559);
    match(MavkaParser::OPEN_PAREN);
    setState(560);
    object_destruction_el();
    setState(565);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::COMMA) {
      setState(561);
      match(MavkaParser::COMMA);
      setState(562);
      object_destruction_el();
      setState(567);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(568);
    match(MavkaParser::CLOSE_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Object_destruction_elContext ------------------------------------------------------------------

MavkaParser::Object_destruction_elContext::Object_destruction_elContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Object_destruction_elContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Object_destruction_elContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

MavkaParser::IdentifierContext* MavkaParser::Object_destruction_elContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}


size_t MavkaParser::Object_destruction_elContext::getRuleIndex() const {
  return MavkaParser::RuleObject_destruction_el;
}

void MavkaParser::Object_destruction_elContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObject_destruction_el(this);
}

void MavkaParser::Object_destruction_elContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObject_destruction_el(this);
}


std::any MavkaParser::Object_destruction_elContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitObject_destruction_el(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Object_destruction_elContext* MavkaParser::object_destruction_el() {
  Object_destruction_elContext *_localctx = _tracker.createInstance<Object_destruction_elContext>(_ctx, getState());
  enterRule(_localctx, 62, MavkaParser::RuleObject_destruction_el);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(570);
    nls();
    setState(571);
    antlrcpp::downCast<Object_destruction_elContext *>(_localctx)->ode_id = identifier();
    setState(572);
    nls();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignContext ------------------------------------------------------------------

MavkaParser::AssignContext::AssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::Assign_symbolContext* MavkaParser::AssignContext::assign_symbol() {
  return getRuleContext<MavkaParser::Assign_symbolContext>(0);
}

MavkaParser::Assign_valueContext* MavkaParser::AssignContext::assign_value() {
  return getRuleContext<MavkaParser::Assign_valueContext>(0);
}

MavkaParser::IdentifierContext* MavkaParser::AssignContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Array_destructionContext* MavkaParser::AssignContext::array_destruction() {
  return getRuleContext<MavkaParser::Array_destructionContext>(0);
}

MavkaParser::Object_destructionContext* MavkaParser::AssignContext::object_destruction() {
  return getRuleContext<MavkaParser::Object_destructionContext>(0);
}

MavkaParser::Identifiers_chainContext* MavkaParser::AssignContext::identifiers_chain() {
  return getRuleContext<MavkaParser::Identifiers_chainContext>(0);
}

MavkaParser::Type_valueContext* MavkaParser::AssignContext::type_value() {
  return getRuleContext<MavkaParser::Type_valueContext>(0);
}

tree::TerminalNode* MavkaParser::AssignContext::OPEN_ARRAY() {
  return getToken(MavkaParser::OPEN_ARRAY, 0);
}

tree::TerminalNode* MavkaParser::AssignContext::CLOSE_ARRAY() {
  return getToken(MavkaParser::CLOSE_ARRAY, 0);
}

MavkaParser::ExprContext* MavkaParser::AssignContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}


size_t MavkaParser::AssignContext::getRuleIndex() const {
  return MavkaParser::RuleAssign;
}

void MavkaParser::AssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign(this);
}

void MavkaParser::AssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign(this);
}


std::any MavkaParser::AssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitAssign(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::AssignContext* MavkaParser::assign() {
  AssignContext *_localctx = _tracker.createInstance<AssignContext>(_ctx, getState());
  enterRule(_localctx, 64, MavkaParser::RuleAssign);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(574);
      antlrcpp::downCast<AssignContext *>(_localctx)->a_identifiers_chain = identifiers_chain(0);
      setState(579);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::OPEN_ARRAY) {
        setState(575);
        match(MavkaParser::OPEN_ARRAY);
        setState(576);
        antlrcpp::downCast<AssignContext *>(_localctx)->a_set_element = expr();
        setState(577);
        match(MavkaParser::CLOSE_ARRAY);
      }
      break;
    }

    case 2: {
      setState(581);
      antlrcpp::downCast<AssignContext *>(_localctx)->a_identifier = identifier();
      setState(583);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MavkaParser::OPEN_ARRAY

      || _la == MavkaParser::ID) {
        setState(582);
        antlrcpp::downCast<AssignContext *>(_localctx)->a_type = type_value(0);
      }
      break;
    }

    case 3: {
      setState(585);
      antlrcpp::downCast<AssignContext *>(_localctx)->a_array_destruction = array_destruction();
      break;
    }

    case 4: {
      setState(586);
      antlrcpp::downCast<AssignContext *>(_localctx)->a_object_destruction = object_destruction();
      break;
    }

    default:
      break;
    }
    setState(589);
    antlrcpp::downCast<AssignContext *>(_localctx)->a_symbol = assign_symbol();
    setState(590);
    antlrcpp::downCast<AssignContext *>(_localctx)->a_value = assign_value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_valueContext ------------------------------------------------------------------

MavkaParser::Assign_valueContext::Assign_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::ExprContext* MavkaParser::Assign_valueContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}


size_t MavkaParser::Assign_valueContext::getRuleIndex() const {
  return MavkaParser::RuleAssign_value;
}

void MavkaParser::Assign_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign_value(this);
}

void MavkaParser::Assign_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign_value(this);
}


std::any MavkaParser::Assign_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitAssign_value(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Assign_valueContext* MavkaParser::assign_value() {
  Assign_valueContext *_localctx = _tracker.createInstance<Assign_valueContext>(_ctx, getState());
  enterRule(_localctx, 66, MavkaParser::RuleAssign_value);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(592);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_symbolContext ------------------------------------------------------------------

MavkaParser::Assign_symbolContext::Assign_symbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN() {
  return getToken(MavkaParser::ASSIGN, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_PARENT() {
  return getToken(MavkaParser::ASSIGN_PARENT, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_ADD() {
  return getToken(MavkaParser::ASSIGN_ADD, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_SUB() {
  return getToken(MavkaParser::ASSIGN_SUB, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_MUL() {
  return getToken(MavkaParser::ASSIGN_MUL, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_DIV() {
  return getToken(MavkaParser::ASSIGN_DIV, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_DIVDIV() {
  return getToken(MavkaParser::ASSIGN_DIVDIV, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_MOD() {
  return getToken(MavkaParser::ASSIGN_MOD, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_POW() {
  return getToken(MavkaParser::ASSIGN_POW, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_BW_AND() {
  return getToken(MavkaParser::ASSIGN_BW_AND, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_BW_OR() {
  return getToken(MavkaParser::ASSIGN_BW_OR, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_BW_SHIFT_LEFT() {
  return getToken(MavkaParser::ASSIGN_BW_SHIFT_LEFT, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_BW_SHIFT_RIGHT() {
  return getToken(MavkaParser::ASSIGN_BW_SHIFT_RIGHT, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_XOR() {
  return getToken(MavkaParser::ASSIGN_XOR, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_AND() {
  return getToken(MavkaParser::ASSIGN_AND, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_OR() {
  return getToken(MavkaParser::ASSIGN_OR, 0);
}

tree::TerminalNode* MavkaParser::Assign_symbolContext::ASSIGN_IF() {
  return getToken(MavkaParser::ASSIGN_IF, 0);
}


size_t MavkaParser::Assign_symbolContext::getRuleIndex() const {
  return MavkaParser::RuleAssign_symbol;
}

void MavkaParser::Assign_symbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign_symbol(this);
}

void MavkaParser::Assign_symbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign_symbol(this);
}


std::any MavkaParser::Assign_symbolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitAssign_symbol(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Assign_symbolContext* MavkaParser::assign_symbol() {
  Assign_symbolContext *_localctx = _tracker.createInstance<Assign_symbolContext>(_ctx, getState());
  enterRule(_localctx, 68, MavkaParser::RuleAssign_symbol);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(594);
    _la = _input->LA(1);
    if (!(((((_la - 57) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 57)) & 131071) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Wait_assignContext ------------------------------------------------------------------

MavkaParser::Wait_assignContext::Wait_assignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Wait_assignContext::WAIT() {
  return getToken(MavkaParser::WAIT, 0);
}

MavkaParser::AssignContext* MavkaParser::Wait_assignContext::assign() {
  return getRuleContext<MavkaParser::AssignContext>(0);
}


size_t MavkaParser::Wait_assignContext::getRuleIndex() const {
  return MavkaParser::RuleWait_assign;
}

void MavkaParser::Wait_assignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWait_assign(this);
}

void MavkaParser::Wait_assignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWait_assign(this);
}


std::any MavkaParser::Wait_assignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitWait_assign(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Wait_assignContext* MavkaParser::wait_assign() {
  Wait_assignContext *_localctx = _tracker.createInstance<Wait_assignContext>(_ctx, getState());
  enterRule(_localctx, 70, MavkaParser::RuleWait_assign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(596);
    match(MavkaParser::WAIT);
    setState(597);
    antlrcpp::downCast<Wait_assignContext *>(_localctx)->wa_assign = assign();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

MavkaParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::IdentifierContext::ID() {
  return getToken(MavkaParser::ID, 0);
}


size_t MavkaParser::IdentifierContext::getRuleIndex() const {
  return MavkaParser::RuleIdentifier;
}

void MavkaParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void MavkaParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any MavkaParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::IdentifierContext* MavkaParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 72, MavkaParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(599);
    match(MavkaParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Extended_identifierContext ------------------------------------------------------------------

MavkaParser::Extended_identifierContext::Extended_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::ID() {
  return getToken(MavkaParser::ID, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::END() {
  return getToken(MavkaParser::END, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::DIIA() {
  return getToken(MavkaParser::DIIA, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::STRUCTURE() {
  return getToken(MavkaParser::STRUCTURE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::FOR() {
  return getToken(MavkaParser::FOR, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::IF() {
  return getToken(MavkaParser::IF, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::WAIT() {
  return getToken(MavkaParser::WAIT, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::TAKE() {
  return getToken(MavkaParser::TAKE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::GIVE() {
  return getToken(MavkaParser::GIVE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::AS() {
  return getToken(MavkaParser::AS, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::IS() {
  return getToken(MavkaParser::IS, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::RETURN() {
  return getToken(MavkaParser::RETURN, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::ASYNC() {
  return getToken(MavkaParser::ASYNC, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::AND() {
  return getToken(MavkaParser::AND, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::OR() {
  return getToken(MavkaParser::OR, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::TRY() {
  return getToken(MavkaParser::TRY, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::CATCH() {
  return getToken(MavkaParser::CATCH, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::ELSE() {
  return getToken(MavkaParser::ELSE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::THROW() {
  return getToken(MavkaParser::THROW, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::WHILE() {
  return getToken(MavkaParser::WHILE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::MODULE() {
  return getToken(MavkaParser::MODULE, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::EQ_WORD() {
  return getToken(MavkaParser::EQ_WORD, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::GR_WORD() {
  return getToken(MavkaParser::GR_WORD, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::SM_WORD() {
  return getToken(MavkaParser::SM_WORD, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::MOCKUP() {
  return getToken(MavkaParser::MOCKUP, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::IMPLEMENTS() {
  return getToken(MavkaParser::IMPLEMENTS, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::EVAL() {
  return getToken(MavkaParser::EVAL, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::WHEN() {
  return getToken(MavkaParser::WHEN, 0);
}

tree::TerminalNode* MavkaParser::Extended_identifierContext::TA() {
  return getToken(MavkaParser::TA, 0);
}


size_t MavkaParser::Extended_identifierContext::getRuleIndex() const {
  return MavkaParser::RuleExtended_identifier;
}

void MavkaParser::Extended_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtended_identifier(this);
}

void MavkaParser::Extended_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtended_identifier(this);
}


std::any MavkaParser::Extended_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitExtended_identifier(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Extended_identifierContext* MavkaParser::extended_identifier() {
  Extended_identifierContext *_localctx = _tracker.createInstance<Extended_identifierContext>(_ctx, getState());
  enterRule(_localctx, 74, MavkaParser::RuleExtended_identifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64879239051294) != 0) || _la == MavkaParser::ID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Identifiers_chainContext ------------------------------------------------------------------

MavkaParser::Identifiers_chainContext::Identifiers_chainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::IdentifierContext* MavkaParser::Identifiers_chainContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

tree::TerminalNode* MavkaParser::Identifiers_chainContext::DOT() {
  return getToken(MavkaParser::DOT, 0);
}

std::vector<MavkaParser::Identifiers_chainContext *> MavkaParser::Identifiers_chainContext::identifiers_chain() {
  return getRuleContexts<MavkaParser::Identifiers_chainContext>();
}

MavkaParser::Identifiers_chainContext* MavkaParser::Identifiers_chainContext::identifiers_chain(size_t i) {
  return getRuleContext<MavkaParser::Identifiers_chainContext>(i);
}


size_t MavkaParser::Identifiers_chainContext::getRuleIndex() const {
  return MavkaParser::RuleIdentifiers_chain;
}

void MavkaParser::Identifiers_chainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifiers_chain(this);
}

void MavkaParser::Identifiers_chainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifiers_chain(this);
}


std::any MavkaParser::Identifiers_chainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitIdentifiers_chain(this);
  else
    return visitor->visitChildren(this);
}


MavkaParser::Identifiers_chainContext* MavkaParser::identifiers_chain() {
   return identifiers_chain(0);
}

MavkaParser::Identifiers_chainContext* MavkaParser::identifiers_chain(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MavkaParser::Identifiers_chainContext *_localctx = _tracker.createInstance<Identifiers_chainContext>(_ctx, parentState);
  MavkaParser::Identifiers_chainContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, MavkaParser::RuleIdentifiers_chain, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(604);
    antlrcpp::downCast<Identifiers_chainContext *>(_localctx)->ic_identifier = identifier();
    _ctx->stop = _input->LT(-1);
    setState(611);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Identifiers_chainContext>(parentContext, parentState);
        _localctx->ic_left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleIdentifiers_chain);
        setState(606);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(607);
        match(MavkaParser::DOT);
        setState(608);
        antlrcpp::downCast<Identifiers_chainContext *>(_localctx)->ic_right = identifiers_chain(2); 
      }
      setState(613);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Type_valueContext ------------------------------------------------------------------

MavkaParser::Type_valueContext::Type_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::Identifiers_chainContext* MavkaParser::Type_valueContext::identifiers_chain() {
  return getRuleContext<MavkaParser::Identifiers_chainContext>(0);
}

MavkaParser::Type_value_arrayContext* MavkaParser::Type_valueContext::type_value_array() {
  return getRuleContext<MavkaParser::Type_value_arrayContext>(0);
}

std::vector<MavkaParser::Type_valueContext *> MavkaParser::Type_valueContext::type_value() {
  return getRuleContexts<MavkaParser::Type_valueContext>();
}

MavkaParser::Type_valueContext* MavkaParser::Type_valueContext::type_value(size_t i) {
  return getRuleContext<MavkaParser::Type_valueContext>(i);
}

MavkaParser::Test_opContext* MavkaParser::Type_valueContext::test_op() {
  return getRuleContext<MavkaParser::Test_opContext>(0);
}


size_t MavkaParser::Type_valueContext::getRuleIndex() const {
  return MavkaParser::RuleType_value;
}

void MavkaParser::Type_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_value(this);
}

void MavkaParser::Type_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_value(this);
}


std::any MavkaParser::Type_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitType_value(this);
  else
    return visitor->visitChildren(this);
}


MavkaParser::Type_valueContext* MavkaParser::type_value() {
   return type_value(0);
}

MavkaParser::Type_valueContext* MavkaParser::type_value(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MavkaParser::Type_valueContext *_localctx = _tracker.createInstance<Type_valueContext>(_ctx, parentState);
  MavkaParser::Type_valueContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 78;
  enterRecursionRule(_localctx, 78, MavkaParser::RuleType_value, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(616);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::OPEN_ARRAY) {
      setState(615);
      antlrcpp::downCast<Type_valueContext *>(_localctx)->tv_array = type_value_array();
    }
    setState(618);
    antlrcpp::downCast<Type_valueContext *>(_localctx)->tv_single = identifiers_chain(0);
    _ctx->stop = _input->LT(-1);
    setState(626);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Type_valueContext>(parentContext, parentState);
        _localctx->tv_left = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleType_value);
        setState(620);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(621);
        antlrcpp::downCast<Type_valueContext *>(_localctx)->tv_operation = test_op();
        setState(622);
        antlrcpp::downCast<Type_valueContext *>(_localctx)->tv_right = type_value(2); 
      }
      setState(628);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Type_value_arrayContext ------------------------------------------------------------------

MavkaParser::Type_value_arrayContext::Type_value_arrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Type_value_arrayContext::OPEN_ARRAY() {
  return getToken(MavkaParser::OPEN_ARRAY, 0);
}

tree::TerminalNode* MavkaParser::Type_value_arrayContext::CLOSE_ARRAY() {
  return getToken(MavkaParser::CLOSE_ARRAY, 0);
}


size_t MavkaParser::Type_value_arrayContext::getRuleIndex() const {
  return MavkaParser::RuleType_value_array;
}

void MavkaParser::Type_value_arrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_value_array(this);
}

void MavkaParser::Type_value_arrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_value_array(this);
}


std::any MavkaParser::Type_value_arrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitType_value_array(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Type_value_arrayContext* MavkaParser::type_value_array() {
  Type_value_arrayContext *_localctx = _tracker.createInstance<Type_value_arrayContext>(_ctx, getState());
  enterRule(_localctx, 80, MavkaParser::RuleType_value_array);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(629);
    match(MavkaParser::OPEN_ARRAY);
    setState(630);
    match(MavkaParser::CLOSE_ARRAY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

MavkaParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::ArgContext *> MavkaParser::ArgsContext::arg() {
  return getRuleContexts<MavkaParser::ArgContext>();
}

MavkaParser::ArgContext* MavkaParser::ArgsContext::arg(size_t i) {
  return getRuleContext<MavkaParser::ArgContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::ArgsContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::ArgsContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::ArgsContext::getRuleIndex() const {
  return MavkaParser::RuleArgs;
}

void MavkaParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void MavkaParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}


std::any MavkaParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ArgsContext* MavkaParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 82, MavkaParser::RuleArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    arg();
    setState(637);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::COMMA) {
      setState(633);
      match(MavkaParser::COMMA);
      setState(634);
      arg();
      setState(639);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

MavkaParser::ArgContext::ArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlsContext *> MavkaParser::ArgContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::ArgContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

MavkaParser::ExprContext* MavkaParser::ArgContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

tree::TerminalNode* MavkaParser::ArgContext::SPREAD() {
  return getToken(MavkaParser::SPREAD, 0);
}


size_t MavkaParser::ArgContext::getRuleIndex() const {
  return MavkaParser::RuleArg;
}

void MavkaParser::ArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg(this);
}

void MavkaParser::ArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg(this);
}


std::any MavkaParser::ArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArg(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ArgContext* MavkaParser::arg() {
  ArgContext *_localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
  enterRule(_localctx, 84, MavkaParser::RuleArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(640);
    nls();
    setState(642);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::SPREAD) {
      setState(641);
      antlrcpp::downCast<ArgContext *>(_localctx)->a_spread = match(MavkaParser::SPREAD);
    }
    setState(644);
    antlrcpp::downCast<ArgContext *>(_localctx)->a_value = expr();
    setState(645);
    nls();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Named_argsContext ------------------------------------------------------------------

MavkaParser::Named_argsContext::Named_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Named_argContext *> MavkaParser::Named_argsContext::named_arg() {
  return getRuleContexts<MavkaParser::Named_argContext>();
}

MavkaParser::Named_argContext* MavkaParser::Named_argsContext::named_arg(size_t i) {
  return getRuleContext<MavkaParser::Named_argContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::Named_argsContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::Named_argsContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::Named_argsContext::getRuleIndex() const {
  return MavkaParser::RuleNamed_args;
}

void MavkaParser::Named_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamed_args(this);
}

void MavkaParser::Named_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamed_args(this);
}


std::any MavkaParser::Named_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNamed_args(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Named_argsContext* MavkaParser::named_args() {
  Named_argsContext *_localctx = _tracker.createInstance<Named_argsContext>(_ctx, getState());
  enterRule(_localctx, 86, MavkaParser::RuleNamed_args);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(647);
    named_arg();
    setState(652);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MavkaParser::COMMA) {
      setState(648);
      match(MavkaParser::COMMA);
      setState(649);
      named_arg();
      setState(654);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Named_argContext ------------------------------------------------------------------

MavkaParser::Named_argContext::Named_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlsContext *> MavkaParser::Named_argContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::Named_argContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

tree::TerminalNode* MavkaParser::Named_argContext::ASSIGN() {
  return getToken(MavkaParser::ASSIGN, 0);
}

MavkaParser::IdentifierContext* MavkaParser::Named_argContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::ExprContext* MavkaParser::Named_argContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}


size_t MavkaParser::Named_argContext::getRuleIndex() const {
  return MavkaParser::RuleNamed_arg;
}

void MavkaParser::Named_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamed_arg(this);
}

void MavkaParser::Named_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamed_arg(this);
}


std::any MavkaParser::Named_argContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNamed_arg(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Named_argContext* MavkaParser::named_arg() {
  Named_argContext *_localctx = _tracker.createInstance<Named_argContext>(_ctx, getState());
  enterRule(_localctx, 88, MavkaParser::RuleNamed_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(655);
    nls();
    setState(656);
    antlrcpp::downCast<Named_argContext *>(_localctx)->na_name = identifier();
    setState(657);
    match(MavkaParser::ASSIGN);
    setState(658);
    antlrcpp::downCast<Named_argContext *>(_localctx)->na_value = expr();
    setState(659);
    nls();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

MavkaParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::ParamContext *> MavkaParser::ParamsContext::param() {
  return getRuleContexts<MavkaParser::ParamContext>();
}

MavkaParser::ParamContext* MavkaParser::ParamsContext::param(size_t i) {
  return getRuleContext<MavkaParser::ParamContext>(i);
}

std::vector<MavkaParser::NlsContext *> MavkaParser::ParamsContext::nls() {
  return getRuleContexts<MavkaParser::NlsContext>();
}

MavkaParser::NlsContext* MavkaParser::ParamsContext::nls(size_t i) {
  return getRuleContext<MavkaParser::NlsContext>(i);
}

std::vector<tree::TerminalNode *> MavkaParser::ParamsContext::COMMA() {
  return getTokens(MavkaParser::COMMA);
}

tree::TerminalNode* MavkaParser::ParamsContext::COMMA(size_t i) {
  return getToken(MavkaParser::COMMA, i);
}


size_t MavkaParser::ParamsContext::getRuleIndex() const {
  return MavkaParser::RuleParams;
}

void MavkaParser::ParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParams(this);
}

void MavkaParser::ParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParams(this);
}


std::any MavkaParser::ParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitParams(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ParamsContext* MavkaParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 90, MavkaParser::RuleParams);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(661);
    param();
    setState(669);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(662);
        nls();
        setState(663);
        match(MavkaParser::COMMA);
        setState(664);
        nls();
        setState(665);
        param(); 
      }
      setState(671);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

MavkaParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::IdentifierContext* MavkaParser::ParamContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Array_destructionContext* MavkaParser::ParamContext::array_destruction() {
  return getRuleContext<MavkaParser::Array_destructionContext>(0);
}

MavkaParser::Object_destructionContext* MavkaParser::ParamContext::object_destruction() {
  return getRuleContext<MavkaParser::Object_destructionContext>(0);
}

tree::TerminalNode* MavkaParser::ParamContext::ASSIGN() {
  return getToken(MavkaParser::ASSIGN, 0);
}

MavkaParser::Type_valueContext* MavkaParser::ParamContext::type_value() {
  return getRuleContext<MavkaParser::Type_valueContext>(0);
}

MavkaParser::Param_valueContext* MavkaParser::ParamContext::param_value() {
  return getRuleContext<MavkaParser::Param_valueContext>(0);
}

tree::TerminalNode* MavkaParser::ParamContext::SPREAD() {
  return getToken(MavkaParser::SPREAD, 0);
}


size_t MavkaParser::ParamContext::getRuleIndex() const {
  return MavkaParser::RuleParam;
}

void MavkaParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void MavkaParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}


std::any MavkaParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::ParamContext* MavkaParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 92, MavkaParser::RuleParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::SPREAD:
      case MavkaParser::ID: {
        setState(673);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MavkaParser::SPREAD) {
          setState(672);
          antlrcpp::downCast<ParamContext *>(_localctx)->p_spread = match(MavkaParser::SPREAD);
        }
        setState(675);
        antlrcpp::downCast<ParamContext *>(_localctx)->p_name = identifier();
        break;
      }

      case MavkaParser::OPEN_ARRAY: {
        setState(676);
        antlrcpp::downCast<ParamContext *>(_localctx)->p_array_destruction = array_destruction();
        break;
      }

      case MavkaParser::OPEN_PAREN: {
        setState(677);
        antlrcpp::downCast<ParamContext *>(_localctx)->p_object_destruction = object_destruction();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(681);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::OPEN_ARRAY

    || _la == MavkaParser::ID) {
      setState(680);
      antlrcpp::downCast<ParamContext *>(_localctx)->p_type = type_value(0);
    }
    setState(685);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MavkaParser::ASSIGN) {
      setState(683);
      match(MavkaParser::ASSIGN);
      setState(684);
      antlrcpp::downCast<ParamContext *>(_localctx)->p_value = param_value();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_valueContext ------------------------------------------------------------------

MavkaParser::Param_valueContext::Param_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MavkaParser::Param_valueContext::getRuleIndex() const {
  return MavkaParser::RuleParam_value;
}

void MavkaParser::Param_valueContext::copyFrom(Param_valueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Param_value_identifierContext ------------------------------------------------------------------

MavkaParser::IdentifierContext* MavkaParser::Param_value_identifierContext::identifier() {
  return getRuleContext<MavkaParser::IdentifierContext>(0);
}

MavkaParser::Param_value_identifierContext::Param_value_identifierContext(Param_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Param_value_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_value_identifier(this);
}
void MavkaParser::Param_value_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_value_identifier(this);
}

std::any MavkaParser::Param_value_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitParam_value_identifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Param_value_numberContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Param_value_numberContext::NUMBER() {
  return getToken(MavkaParser::NUMBER, 0);
}

MavkaParser::Param_value_numberContext::Param_value_numberContext(Param_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Param_value_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_value_number(this);
}
void MavkaParser::Param_value_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_value_number(this);
}

std::any MavkaParser::Param_value_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitParam_value_number(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Param_value_stringContext ------------------------------------------------------------------

tree::TerminalNode* MavkaParser::Param_value_stringContext::STRING() {
  return getToken(MavkaParser::STRING, 0);
}

MavkaParser::Param_value_stringContext::Param_value_stringContext(Param_valueContext *ctx) { copyFrom(ctx); }

void MavkaParser::Param_value_stringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_value_string(this);
}
void MavkaParser::Param_value_stringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_value_string(this);
}

std::any MavkaParser::Param_value_stringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitParam_value_string(this);
  else
    return visitor->visitChildren(this);
}
MavkaParser::Param_valueContext* MavkaParser::param_value() {
  Param_valueContext *_localctx = _tracker.createInstance<Param_valueContext>(_ctx, getState());
  enterRule(_localctx, 94, MavkaParser::RuleParam_value);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(690);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::NUMBER: {
        _localctx = _tracker.createInstance<MavkaParser::Param_value_numberContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(687);
        match(MavkaParser::NUMBER);
        break;
      }

      case MavkaParser::STRING: {
        _localctx = _tracker.createInstance<MavkaParser::Param_value_stringContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(688);
        match(MavkaParser::STRING);
        break;
      }

      case MavkaParser::ID: {
        _localctx = _tracker.createInstance<MavkaParser::Param_value_identifierContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(689);
        identifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

MavkaParser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::Body_element_or_returnContext *> MavkaParser::BodyContext::body_element_or_return() {
  return getRuleContexts<MavkaParser::Body_element_or_returnContext>();
}

MavkaParser::Body_element_or_returnContext* MavkaParser::BodyContext::body_element_or_return(size_t i) {
  return getRuleContext<MavkaParser::Body_element_or_returnContext>(i);
}

std::vector<MavkaParser::NlContext *> MavkaParser::BodyContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::BodyContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}


size_t MavkaParser::BodyContext::getRuleIndex() const {
  return MavkaParser::RuleBody;
}

void MavkaParser::BodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBody(this);
}

void MavkaParser::BodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBody(this);
}


std::any MavkaParser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::BodyContext* MavkaParser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 96, MavkaParser::RuleBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(692);
    body_element_or_return();
    setState(698);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(693);
        nl();
        setState(694);
        body_element_or_return(); 
      }
      setState(700);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Body_element_or_returnContext ------------------------------------------------------------------

MavkaParser::Body_element_or_returnContext::Body_element_or_returnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::Body_elementContext* MavkaParser::Body_element_or_returnContext::body_element() {
  return getRuleContext<MavkaParser::Body_elementContext>(0);
}

MavkaParser::Return_body_lineContext* MavkaParser::Body_element_or_returnContext::return_body_line() {
  return getRuleContext<MavkaParser::Return_body_lineContext>(0);
}


size_t MavkaParser::Body_element_or_returnContext::getRuleIndex() const {
  return MavkaParser::RuleBody_element_or_return;
}

void MavkaParser::Body_element_or_returnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBody_element_or_return(this);
}

void MavkaParser::Body_element_or_returnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBody_element_or_return(this);
}


std::any MavkaParser::Body_element_or_returnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBody_element_or_return(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Body_element_or_returnContext* MavkaParser::body_element_or_return() {
  Body_element_or_returnContext *_localctx = _tracker.createInstance<Body_element_or_returnContext>(_ctx, getState());
  enterRule(_localctx, 98, MavkaParser::RuleBody_element_or_return);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(703);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MavkaParser::DIIA:
      case MavkaParser::STRUCTURE:
      case MavkaParser::FOR:
      case MavkaParser::IF:
      case MavkaParser::WAIT:
      case MavkaParser::ASYNC:
      case MavkaParser::TRY:
      case MavkaParser::THROW:
      case MavkaParser::WHILE:
      case MavkaParser::NL:
      case MavkaParser::DECREMENT:
      case MavkaParser::INCREMENT:
      case MavkaParser::OPEN_PAREN:
      case MavkaParser::OPEN_ARRAY:
      case MavkaParser::PLUS:
      case MavkaParser::MINUS:
      case MavkaParser::NOT:
      case MavkaParser::TILDA:
      case MavkaParser::ID:
      case MavkaParser::NUMBER:
      case MavkaParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(701);
        body_element();
        break;
      }

      case MavkaParser::RETURN: {
        enterOuterAlt(_localctx, 2);
        setState(702);
        return_body_line();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Body_elementContext ------------------------------------------------------------------

MavkaParser::Body_elementContext::Body_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MavkaParser::StructureContext* MavkaParser::Body_elementContext::structure() {
  return getRuleContext<MavkaParser::StructureContext>(0);
}

MavkaParser::DiiaContext* MavkaParser::Body_elementContext::diia() {
  return getRuleContext<MavkaParser::DiiaContext>(0);
}

MavkaParser::IfContext* MavkaParser::Body_elementContext::if_() {
  return getRuleContext<MavkaParser::IfContext>(0);
}

MavkaParser::EachContext* MavkaParser::Body_elementContext::each() {
  return getRuleContext<MavkaParser::EachContext>(0);
}

MavkaParser::WhileContext* MavkaParser::Body_elementContext::while_() {
  return getRuleContext<MavkaParser::WhileContext>(0);
}

MavkaParser::TryContext* MavkaParser::Body_elementContext::try_() {
  return getRuleContext<MavkaParser::TryContext>(0);
}

MavkaParser::ExprContext* MavkaParser::Body_elementContext::expr() {
  return getRuleContext<MavkaParser::ExprContext>(0);
}

MavkaParser::ThrowContext* MavkaParser::Body_elementContext::throw_() {
  return getRuleContext<MavkaParser::ThrowContext>(0);
}

MavkaParser::Wait_assignContext* MavkaParser::Body_elementContext::wait_assign() {
  return getRuleContext<MavkaParser::Wait_assignContext>(0);
}

MavkaParser::AssignContext* MavkaParser::Body_elementContext::assign() {
  return getRuleContext<MavkaParser::AssignContext>(0);
}

MavkaParser::NlsContext* MavkaParser::Body_elementContext::nls() {
  return getRuleContext<MavkaParser::NlsContext>(0);
}


size_t MavkaParser::Body_elementContext::getRuleIndex() const {
  return MavkaParser::RuleBody_element;
}

void MavkaParser::Body_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBody_element(this);
}

void MavkaParser::Body_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBody_element(this);
}


std::any MavkaParser::Body_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBody_element(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Body_elementContext* MavkaParser::body_element() {
  Body_elementContext *_localctx = _tracker.createInstance<Body_elementContext>(_ctx, getState());
  enterRule(_localctx, 100, MavkaParser::RuleBody_element);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(716);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(705);
      structure();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(706);
      diia();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(707);
      if_();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(708);
      each();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(709);
      while_();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(710);
      try_();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(711);
      expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(712);
      throw_();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(713);
      wait_assign();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(714);
      assign();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(715);
      nls();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_body_lineContext ------------------------------------------------------------------

MavkaParser::Return_body_lineContext::Return_body_lineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Return_body_lineContext::RETURN() {
  return getToken(MavkaParser::RETURN, 0);
}

MavkaParser::Body_elementContext* MavkaParser::Return_body_lineContext::body_element() {
  return getRuleContext<MavkaParser::Body_elementContext>(0);
}


size_t MavkaParser::Return_body_lineContext::getRuleIndex() const {
  return MavkaParser::RuleReturn_body_line;
}

void MavkaParser::Return_body_lineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn_body_line(this);
}

void MavkaParser::Return_body_lineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn_body_line(this);
}


std::any MavkaParser::Return_body_lineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitReturn_body_line(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Return_body_lineContext* MavkaParser::return_body_line() {
  Return_body_lineContext *_localctx = _tracker.createInstance<Return_body_lineContext>(_ctx, getState());
  enterRule(_localctx, 102, MavkaParser::RuleReturn_body_line);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(718);
    match(MavkaParser::RETURN);
    setState(719);
    antlrcpp::downCast<Return_body_lineContext *>(_localctx)->rbl = body_element();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arithmetic_op_mulContext ------------------------------------------------------------------

MavkaParser::Arithmetic_op_mulContext::Arithmetic_op_mulContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Arithmetic_op_mulContext::MUL() {
  return getToken(MavkaParser::MUL, 0);
}

tree::TerminalNode* MavkaParser::Arithmetic_op_mulContext::DIV() {
  return getToken(MavkaParser::DIV, 0);
}

tree::TerminalNode* MavkaParser::Arithmetic_op_mulContext::PERCENT() {
  return getToken(MavkaParser::PERCENT, 0);
}

tree::TerminalNode* MavkaParser::Arithmetic_op_mulContext::DIVDIV() {
  return getToken(MavkaParser::DIVDIV, 0);
}

tree::TerminalNode* MavkaParser::Arithmetic_op_mulContext::POW() {
  return getToken(MavkaParser::POW, 0);
}


size_t MavkaParser::Arithmetic_op_mulContext::getRuleIndex() const {
  return MavkaParser::RuleArithmetic_op_mul;
}

void MavkaParser::Arithmetic_op_mulContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmetic_op_mul(this);
}

void MavkaParser::Arithmetic_op_mulContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmetic_op_mul(this);
}


std::any MavkaParser::Arithmetic_op_mulContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArithmetic_op_mul(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Arithmetic_op_mulContext* MavkaParser::arithmetic_op_mul() {
  Arithmetic_op_mulContext *_localctx = _tracker.createInstance<Arithmetic_op_mulContext>(_ctx, getState());
  enterRule(_localctx, 104, MavkaParser::RuleArithmetic_op_mul);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(721);
    _la = _input->LA(1);
    if (!(((((_la - 76) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 76)) & 451) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arithmetic_op_addContext ------------------------------------------------------------------

MavkaParser::Arithmetic_op_addContext::Arithmetic_op_addContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Arithmetic_op_addContext::PLUS() {
  return getToken(MavkaParser::PLUS, 0);
}

tree::TerminalNode* MavkaParser::Arithmetic_op_addContext::MINUS() {
  return getToken(MavkaParser::MINUS, 0);
}


size_t MavkaParser::Arithmetic_op_addContext::getRuleIndex() const {
  return MavkaParser::RuleArithmetic_op_add;
}

void MavkaParser::Arithmetic_op_addContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmetic_op_add(this);
}

void MavkaParser::Arithmetic_op_addContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmetic_op_add(this);
}


std::any MavkaParser::Arithmetic_op_addContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitArithmetic_op_add(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Arithmetic_op_addContext* MavkaParser::arithmetic_op_add() {
  Arithmetic_op_addContext *_localctx = _tracker.createInstance<Arithmetic_op_addContext>(_ctx, getState());
  enterRule(_localctx, 106, MavkaParser::RuleArithmetic_op_add);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(723);
    _la = _input->LA(1);
    if (!(_la == MavkaParser::PLUS

    || _la == MavkaParser::MINUS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bitwise_opContext ------------------------------------------------------------------

MavkaParser::Bitwise_opContext::Bitwise_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Bitwise_opContext::XOR() {
  return getToken(MavkaParser::XOR, 0);
}

tree::TerminalNode* MavkaParser::Bitwise_opContext::OR_BW() {
  return getToken(MavkaParser::OR_BW, 0);
}

tree::TerminalNode* MavkaParser::Bitwise_opContext::AND_BW() {
  return getToken(MavkaParser::AND_BW, 0);
}

tree::TerminalNode* MavkaParser::Bitwise_opContext::BW_SHIFT_LEFT() {
  return getToken(MavkaParser::BW_SHIFT_LEFT, 0);
}

tree::TerminalNode* MavkaParser::Bitwise_opContext::BW_SHIFT_RIGHT() {
  return getToken(MavkaParser::BW_SHIFT_RIGHT, 0);
}


size_t MavkaParser::Bitwise_opContext::getRuleIndex() const {
  return MavkaParser::RuleBitwise_op;
}

void MavkaParser::Bitwise_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwise_op(this);
}

void MavkaParser::Bitwise_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwise_op(this);
}


std::any MavkaParser::Bitwise_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitBitwise_op(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Bitwise_opContext* MavkaParser::bitwise_op() {
  Bitwise_opContext *_localctx = _tracker.createInstance<Bitwise_opContext>(_ctx, getState());
  enterRule(_localctx, 108, MavkaParser::RuleBitwise_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(725);
    _la = _input->LA(1);
    if (!(((((_la - 85) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 85)) & 121) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Test_opContext ------------------------------------------------------------------

MavkaParser::Test_opContext::Test_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Test_opContext::AND() {
  return getToken(MavkaParser::AND, 0);
}

tree::TerminalNode* MavkaParser::Test_opContext::OR() {
  return getToken(MavkaParser::OR, 0);
}

tree::TerminalNode* MavkaParser::Test_opContext::OR_SYM() {
  return getToken(MavkaParser::OR_SYM, 0);
}

tree::TerminalNode* MavkaParser::Test_opContext::AND_SYM() {
  return getToken(MavkaParser::AND_SYM, 0);
}


size_t MavkaParser::Test_opContext::getRuleIndex() const {
  return MavkaParser::RuleTest_op;
}

void MavkaParser::Test_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTest_op(this);
}

void MavkaParser::Test_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTest_op(this);
}


std::any MavkaParser::Test_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitTest_op(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Test_opContext* MavkaParser::test_op() {
  Test_opContext *_localctx = _tracker.createInstance<Test_opContext>(_ctx, getState());
  enterRule(_localctx, 110, MavkaParser::RuleTest_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(727);
    _la = _input->LA(1);
    if (!(_la == MavkaParser::AND

    || _la == MavkaParser::OR || _la == MavkaParser::OR_SYM

    || _la == MavkaParser::AND_SYM)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comparison_opContext ------------------------------------------------------------------

MavkaParser::Comparison_opContext::Comparison_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::Comparison_opContext::EQ() {
  return getToken(MavkaParser::EQ, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_EQ() {
  return getToken(MavkaParser::NOT_EQ, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::GREATER() {
  return getToken(MavkaParser::GREATER, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::SMALLER() {
  return getToken(MavkaParser::SMALLER, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::GREATER_EQ() {
  return getToken(MavkaParser::GREATER_EQ, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::SMALLER_EQ() {
  return getToken(MavkaParser::SMALLER_EQ, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::IS() {
  return getToken(MavkaParser::IS, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_IS_WORD() {
  return getToken(MavkaParser::NOT_IS_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::EQ_WORD() {
  return getToken(MavkaParser::EQ_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_EQ_WORD() {
  return getToken(MavkaParser::NOT_EQ_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::GR_WORD() {
  return getToken(MavkaParser::GR_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_GR_WORD() {
  return getToken(MavkaParser::NOT_GR_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::SM_WORD() {
  return getToken(MavkaParser::SM_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_SM_WORD() {
  return getToken(MavkaParser::NOT_SM_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::HAS_IS_WORD() {
  return getToken(MavkaParser::HAS_IS_WORD, 0);
}

tree::TerminalNode* MavkaParser::Comparison_opContext::NOT_HAS_IS_WORD() {
  return getToken(MavkaParser::NOT_HAS_IS_WORD, 0);
}


size_t MavkaParser::Comparison_opContext::getRuleIndex() const {
  return MavkaParser::RuleComparison_op;
}

void MavkaParser::Comparison_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison_op(this);
}

void MavkaParser::Comparison_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison_op(this);
}


std::any MavkaParser::Comparison_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitComparison_op(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::Comparison_opContext* MavkaParser::comparison_op() {
  Comparison_opContext *_localctx = _tracker.createInstance<Comparison_opContext>(_ctx, getState());
  enterRule(_localctx, 112, MavkaParser::RuleComparison_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(729);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 548682336224) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NlContext ------------------------------------------------------------------

MavkaParser::NlContext::NlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MavkaParser::NlContext::NL() {
  return getToken(MavkaParser::NL, 0);
}


size_t MavkaParser::NlContext::getRuleIndex() const {
  return MavkaParser::RuleNl;
}

void MavkaParser::NlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNl(this);
}

void MavkaParser::NlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNl(this);
}


std::any MavkaParser::NlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNl(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::NlContext* MavkaParser::nl() {
  NlContext *_localctx = _tracker.createInstance<NlContext>(_ctx, getState());
  enterRule(_localctx, 114, MavkaParser::RuleNl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(731);
    match(MavkaParser::NL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NlsContext ------------------------------------------------------------------

MavkaParser::NlsContext::NlsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MavkaParser::NlContext *> MavkaParser::NlsContext::nl() {
  return getRuleContexts<MavkaParser::NlContext>();
}

MavkaParser::NlContext* MavkaParser::NlsContext::nl(size_t i) {
  return getRuleContext<MavkaParser::NlContext>(i);
}


size_t MavkaParser::NlsContext::getRuleIndex() const {
  return MavkaParser::RuleNls;
}

void MavkaParser::NlsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNls(this);
}

void MavkaParser::NlsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MavkaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNls(this);
}


std::any MavkaParser::NlsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MavkaParserVisitor*>(visitor))
    return parserVisitor->visitNls(this);
  else
    return visitor->visitChildren(this);
}

MavkaParser::NlsContext* MavkaParser::nls() {
  NlsContext *_localctx = _tracker.createInstance<NlsContext>(_ctx, getState());
  enterRule(_localctx, 116, MavkaParser::RuleNls);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(736);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(733);
        nl(); 
      }
      setState(738);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MavkaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 21: return valueSempred(antlrcpp::downCast<ValueContext *>(context), predicateIndex);
    case 38: return identifiers_chainSempred(antlrcpp::downCast<Identifiers_chainContext *>(context), predicateIndex);
    case 39: return type_valueSempred(antlrcpp::downCast<Type_valueContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MavkaParser::valueSempred(ValueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);
    case 4: return precpred(_ctx, 4);
    case 5: return precpred(_ctx, 21);
    case 6: return precpred(_ctx, 20);
    case 7: return precpred(_ctx, 15);
    case 8: return precpred(_ctx, 14);
    case 9: return precpred(_ctx, 11);
    case 10: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool MavkaParser::identifiers_chainSempred(Identifiers_chainContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool MavkaParser::type_valueSempred(Type_valueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void MavkaParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mavkaparserParserInitialize();
#else
  ::antlr4::internal::call_once(mavkaparserParserOnceFlag, mavkaparserParserInitialize);
#endif
}
