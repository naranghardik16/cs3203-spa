//
// Created by Kai Qi Yong on 29/1/23.
//

#include "Token.h"
using namespace std;

/*
Token::Token(TokenType t, string val) {
  type_ = t;
  value_ = val;
}

TokenType Token::GetType() {
  return type_;
}

string Token::GetValue() {
  return value_;
}

bool Token::Equals(Token *other) {
  return this->type_ == other->GetType() && this->value_.compare(other->GetValue()) == 0;
}
 */

Token::Token(string val) {
  value_ = val;
}

string Token::GetValue() {
  return value_;
}
