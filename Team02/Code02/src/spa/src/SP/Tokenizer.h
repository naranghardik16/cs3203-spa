#ifndef SPA_SRC_SPA_SRC_TOKENIZER_H_
#define SPA_SRC_SPA_SRC_TOKENIZER_H_

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
using namespace std;

class Tokenizer {
  inline static const string ARITHMETIC_OPERATOR_RULE = "[*+-/%]";
  inline static const string CONDITIONAL_OPERATOR_RULE = "(?:(&&)|(!)|(\\|\\|))";
  inline static const string RELATIONAL_OPERATOR_RULE = "(?:(<=)|(<)|(>=)|(>)|(==)|(!=))";
  inline static const string PUNCTUATION_OPERATOR_RULE = "[{}();_=\"]";
  inline static const unordered_map<string, PunctuationType> PUNCTUATION_TYPES = {
      {"{", LEFT_PARENTHESIS},
      {"}", RIGHT_PARENTHESIS},
      {"(", LEFT_BRACE},
      {")", RIGHT_BRACE},
      {";", SEMICOLON},
      {"_", UNDERSCORE},
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
  vector<string> SplitLines(istream & stream);
 public:
  Tokenizer();
  Token* MatchToken(int first_char_index, string line, int* skip_index);
  vector<vector<Token>>* Tokenize(istream &stream);
};
#endif //SPA_SRC_SPA_SRC_TOKENIZER_H_



