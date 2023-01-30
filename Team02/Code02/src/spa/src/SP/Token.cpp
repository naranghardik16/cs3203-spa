#include "Token.h"
using namespace std;

Token::Token(string val) {
  value_ = val;
}

string Token::GetValue() {
  return value_;
}
