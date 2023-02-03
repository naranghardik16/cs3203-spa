#include "IntegerToken.h"

IntegerToken::IntegerToken(string val) : Token(val, INTEGER) {}

bool IntegerToken::Equals(Token &other) {
  // make sure that the passed type is the same
  IntegerToken *it = dynamic_cast<IntegerToken*>(&other);
  if (it) {
    return this->GetValue() == it->GetValue();
  }
  return false;
}