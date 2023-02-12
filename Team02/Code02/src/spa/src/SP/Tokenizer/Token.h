#pragma once
#include <string>
#include "TokenType.h"
using namespace std;

class Token {
  string value_;
  TokenType type_;
 public:
  Token(string val, TokenType type);
  string GetValue();
  TokenType GetType();
  virtual bool Equals(Token &other) = 0;
};