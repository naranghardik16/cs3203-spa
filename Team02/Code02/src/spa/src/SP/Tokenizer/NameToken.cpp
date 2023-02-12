#include "NameToken.h"

NameToken::NameToken(string val) : Token(val, NAME) {}

bool NameToken::Equals(Token &other) {
  // make sure that the passed type is the same
  NameToken *nt = dynamic_cast<NameToken*>(&other);
  if (nt) {
    return this->GetValue() == nt->GetValue();
  }
  return false;
}