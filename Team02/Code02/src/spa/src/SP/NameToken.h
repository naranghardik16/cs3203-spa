#pragma once
#include "Token.h"

class NameToken : public Token {
 public:
  NameToken(string val);
  bool Equals(Token &other);
};