#pragma once
#include "Token.h"
#include "PunctuationType.h"
using namespace std;

class PunctuationToken : public Token {
 private:
  PunctuationType type_;
 public:
//  inline static const string LEFT_PARENTHESIS = "{";
//  inline static const string RIGHT_PARENTHESIS = "}";
//  inline static const string LEFT_BRACE = "(";
//  inline static const string RIGHT_BRACE = ")";
//  inline static const string SEMICOLON = ";";
//  inline static const string DOUBLE_QUOTE = "\"";
//  inline static const string EQUAL = "=";
  PunctuationToken(string val, PunctuationType type);
  PunctuationType GetType();
  bool Equals(Token &other);
};