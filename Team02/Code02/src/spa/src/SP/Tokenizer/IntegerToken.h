#pragma once
#include "Token.h"

class IntegerToken : public Token {
 public:
  IntegerToken(string val);
  bool Equals(shared_ptr<Token> other);
};