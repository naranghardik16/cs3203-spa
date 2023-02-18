#pragma once
#include "Token.h"
using namespace std;

class ArithmeticOperatorToken : public Token {
 public:
  ArithmeticOperatorToken(string val, TokenType type);
  bool Equals(shared_ptr<Token> other);
};