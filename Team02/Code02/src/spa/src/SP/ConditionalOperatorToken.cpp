//
// Created by Kai Qi Yong on 29/1/23.
//
#include "ConditionalOperatorToken.h"
using namespace std;

ConditionalOperatorToken::ConditionalOperatorToken(string val) : Token(val) {
  if (this->GetValue() == AND) {
    type_ = AND;
  } else if (this->GetValue() == OR) {
    type_ = OR;
  } else if (this->GetValue() == NOT) {
    type_ = NOT;
  }
}

string ConditionalOperatorToken::GetType() {
  return type_;
}

bool ConditionalOperatorToken::Equals(ConditionalOperatorToken *other) {
  return this->GetType() == other->GetType() && this->GetValue() == other->GetValue() == 0;
}
