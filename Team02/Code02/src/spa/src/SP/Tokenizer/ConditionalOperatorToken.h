#pragma once
#include "Token.h"
using namespace std;

class ConditionalOperatorToken : public Token {
 public:
  ConditionalOperatorToken(string val, TokenType type);
  bool Equals(shared_ptr<Token> other);
};
