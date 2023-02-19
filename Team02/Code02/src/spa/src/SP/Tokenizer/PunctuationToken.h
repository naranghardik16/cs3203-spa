#pragma once
#include "Token.h"
using namespace std;

class PunctuationToken : public Token {
 public:
  PunctuationToken(string val, TokenType type);
  bool Equals(shared_ptr<Token> other);
};