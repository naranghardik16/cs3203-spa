#include "PunctuationToken.h"
using namespace std;

PunctuationToken::PunctuationToken(string val) : Token(val) {
  if (this->GetValue() == LEFT_PARENTHESIS) {
    type_ = LEFT_PARENTHESIS;
  } else if (this->GetValue() == RIGHT_PARENTHESIS) {
    type_ = RIGHT_PARENTHESIS;
  } else if (this->GetValue() == LEFT_BRACE) {
    type_ = LEFT_BRACE;
  } else if (this->GetValue() == RIGHT_BRACE) {
    type_ = RIGHT_BRACE;
  } else if (this->GetValue() == SEMICOLON) {
    type_ = SEMICOLON;
  } else if (this->GetValue() == UNDERSCORE) {
    type_ = UNDERSCORE;
  } else if (this->GetValue() == DOUBLE_QUOTE) {
    type_ = DOUBLE_QUOTE;
  } else if (this->GetValue() == EQUAL) {
    type_ = EQUAL;
  }
}

string PunctuationToken::GetType() {
  return type_;
}

bool PunctuationToken::Equals(PunctuationToken *other) {
  return this->GetType() == other->GetType() && this->GetValue() == other->GetValue() == 0;
}
