#include "Token.h"
using namespace std;

Token::Token(string val) {
  value_ = val;
}

string Token::GetValue() {
  return value_;
}

bool Token::Equals(Token &other) {
  // make sure that the passed type is the same
  return this->GetValue() == other.GetValue();
}