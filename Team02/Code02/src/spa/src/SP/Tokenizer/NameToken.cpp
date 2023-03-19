#include "NameToken.h"

NameToken::NameToken(string val) : Token(val, NAME) {}

bool NameToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<NameToken> nt = dynamic_pointer_cast<NameToken>(other);
  if (nt) {
    return this->GetValue() == nt->GetValue();
  }
  return false;
}
