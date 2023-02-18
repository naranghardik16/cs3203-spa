#pragma once
#include "Token.h"

class NameToken : public Token {
 public:
  NameToken(string val);
  bool Equals(shared_ptr<Token> other);
};