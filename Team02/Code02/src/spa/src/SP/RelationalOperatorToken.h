#pragma once
#include "Token.h"
using namespace std;

class RelationalOperatorToken : public Token {
 public:
  RelationalOperatorToken(string val, TokenType type);
  bool Equals(Token &other);
};