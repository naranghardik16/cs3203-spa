#include "Token.h"
using namespace std;

Token::Token(string val, TokenType type) {
  value_ = val;
  type_ = type;
}

string Token::GetValue() {
  return value_;
}

TokenType Token::GetType() {
  return type_;
}

bool Token::Equals(Token &other) {
  // make sure that the passed type is the same
  return this->GetValue() == other.GetValue();
}