#pragma once
#include <string>
using namespace std;

class Token {
  string value_;
 public:
  Token(string val);
  string GetValue();
  virtual bool Equals(Token &other) = 0;
};