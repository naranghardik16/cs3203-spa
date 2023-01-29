//
// Created by Kai Qi Yong on 29/1/23.
//
#include "ArithmeticOperatorToken.h"
using namespace std;

ArithmeticOperatorToken::ArithmeticOperatorToken(string val) : Token(val) {
  if (this->GetValue() == PLUS) {
    type_ = PLUS;
  } else if (this->GetValue() == MINUS) {
    type_ = MINUS;
  } else if (this->GetValue() == DIV) {
    type_ = DIV;
  } else if (this->GetValue() == MULTIPLY) {
    type_ = MULTIPLY;
  } else if (this->GetValue() == MOD) {
    type_ = MOD;
  }
}

string ArithmeticOperatorToken::GetType() {
  return type_;
}

bool ArithmeticOperatorToken::Equals(ArithmeticOperatorToken *other) {
  return this->GetType() == other->GetType() && this->GetValue() == other->GetValue() == 0;
}
