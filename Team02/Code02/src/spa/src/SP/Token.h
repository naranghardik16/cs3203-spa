#ifndef SPA_SRC_SPA_SRC_TOKEN_H_
#define SPA_SRC_SPA_SRC_TOKEN_H_

#pragma once
#include <string>
using namespace std;

class Token {
  string value_;
 public:
  Token(string val);
  string GetValue();
  virtual bool Equals(Token* other);
};

#endif //SPA_SRC_SPA_SRC_TOKEN_H_
