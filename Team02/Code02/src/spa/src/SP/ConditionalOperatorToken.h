#pragma once
#include "Token.h"
#include "ConditionalOperatorType.h"
using namespace std;

class ConditionalOperatorToken : public Token {
 private:
  ConditionalOperatorType type_;
 public:
//  inline static const string AND = "&&";
//  inline static const string OR = "||";
//  inline static const string NOT = "!";
  ConditionalOperatorToken(string val, ConditionalOperatorType type);
  ConditionalOperatorType GetType();
  bool Equals(Token &other);
};
