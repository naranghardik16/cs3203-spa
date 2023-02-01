#pragma once
#include "Token.h"

class IntegerToken : public Token {
 public:
  IntegerToken(string val);
  bool Equals(Token &other);
};