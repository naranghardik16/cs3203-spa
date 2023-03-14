#include "Token.h"

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

bool Token::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  return this->GetValue() == other->GetValue();
}
