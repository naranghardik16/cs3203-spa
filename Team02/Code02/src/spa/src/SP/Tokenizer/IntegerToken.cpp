#include "IntegerToken.h"

IntegerToken::IntegerToken(string val) : Token(val, INTEGER) {}

bool IntegerToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<IntegerToken> it = dynamic_pointer_cast<IntegerToken>(other);
  if (it) {
    return this->GetValue() == it->GetValue();
  }
  return false;
}
