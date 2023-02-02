#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include "NameToken.h"
#include "IntegerToken.h"
#include "PunctuationToken.h"
#include "ArithmeticOperatorToken.h"
#include "RelationalOperatorToken.h"
#include "ConditionalOperatorToken.h"
#include "General/LexicalRuleValidator.h"
#include "./General/StringUtil.h"
#include "./General/Utilities.h"
#include "./Parser/Parser.h"

using namespace std;

class Tokenizer {
  inline static const int NAME_TYPE = 1;
  inline static const int INTEGER_TYPE = 2;
  inline static const string ARITHMETIC_OPERATOR_RULE = "[*+-/%]";
  inline static const string CONDITIONAL_OPERATOR_RULE = "(?:(&&)|(!)|(\\|\\|))";
  inline static const string RELATIONAL_OPERATOR_RULE = "(?:(<=)|(<)|(>=)|(>)|(==)|(!=))";
  inline static const string PUNCTUATION_OPERATOR_RULE = "[{}();=\"]";
  inline static const unordered_map<string, PunctuationType> PUNCTUATION_TYPES = {
      {"{", LEFT_PARENTHESIS},
      {"}", RIGHT_PARENTHESIS},
      {"(", LEFT_BRACE},
      {")", RIGHT_BRACE},
      {";", SEMICOLON},
      {"\"", DOUBLE_QUOTE},
      {"=", SINGLE_EQUAL},
  };
  inline static const unordered_map<string, ArithmeticOperatorType> ARITHMETIC_OPERATOR_TYPES = {
      {"+", PLUS},
      {"-", MINUS},
      {"/", DIV},
      {"*", MULTIPLY},
      {"%", MOD}
  };
  inline static const unordered_map<string, RelationalOperatorType> RELATIONAL_OPERATOR_TYPES = {
      {"<", LT},
      {"<=", LTE},
      {">", GT},
      {">=", GTE},
      {"==", DOUBLE_EQUALS},
      {"!=", NE}
  };
  inline static const unordered_map<string, ConditionalOperatorType> CONDITONAL_OPERATOR_TYPES = {
      {"&&", AND},
      {"||", OR},
      {"!", NOT}
  };
  inline static const unordered_map<PunctuationType, bool> END_OF_LINE_TOKENS = {
      {LEFT_PARENTHESIS, true },
      {RIGHT_PARENTHESIS, true},
      {SEMICOLON, true}
  };
  vector<string> SplitLines(istream & stream);
 public:
  Tokenizer();
  Token* MatchOtherToken(int first_char_index, string line, int* skip_index);
  Token* MatchNameOrIntegerToken(LexicalRuleValidator *lrv, string val, int type);
  Parser::TokenStream* Tokenize(istream &stream);
};


