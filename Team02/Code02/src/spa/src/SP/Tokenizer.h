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
#include "./Parser/Parser.h"
#include "General/SpaException/SyntaxErrorException.h"


using namespace std;

class Tokenizer {
  inline static const int NAME_TYPE = 1;
  inline static const int INTEGER_TYPE = 2;
  inline static const int NOT_SET = -1;
  inline static const string ARITHMETIC_OPERATOR_RULE = "[*+-/%]";
  inline static const string CONDITIONAL_OPERATOR_RULE = "(?:(&&)|(!)|(\\|\\|))";
  inline static const string RELATIONAL_OPERATOR_RULE = "(?:(<=)|(<)|(>=)|(>)|(==)|(!=))";
  inline static const string PUNCTUATION_OPERATOR_RULE = "[{}();=\"]";
  inline static const unordered_map<string, TokenType> TOKEN_TYPES = {
      {"{", LEFT_PARENTHESIS},
      {"}", RIGHT_PARENTHESIS},
      {"(", LEFT_BRACE},
      {")", RIGHT_BRACE},
      {";", SEMICOLON},
      {"\"", DOUBLE_QUOTE},
      {"=", SINGLE_EQUAL},
      {"+", PLUS},
      {"-", MINUS},
      {"/", DIV},
      {"*", MULTIPLY},
      {"%", MOD},
      {"<", LT},
      {"<=", LTE},
      {">", GT},
      {">=", GTE},
      {"==", DOUBLE_EQUALS},
      {"!=", NE},
      {"&&", AND},
      {"||", OR},
      {"!", NOT}
  };

  inline static const unordered_map<TokenType, bool> END_OF_LINE_TOKENS = {
      {LEFT_PARENTHESIS, true },
      {RIGHT_PARENTHESIS, true},
      {SEMICOLON, true}
  };

  vector<string> SplitLines(istream & stream);
  Token* MatchOtherToken(int first_char_index, string line, int* skip_index);
  void FormNameOrInteger(int *start_index, int *end_index, int current_index);
  Token* MatchNameOrIntegerToken(LexicalRuleValidator *lrv, string val, int type);
 public:
  Tokenizer();
  Parser::TokenStream* Tokenize(istream &stream);
};


