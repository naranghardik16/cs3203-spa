#include "NameToken.h"

bool NameToken::Equals(Token &other) {
  // make sure that the passed type is the same
  NameToken *nt = dynamic_cast<NameToken*>(&other);
  if (nt) {
    return this->GetValue() == nt->GetValue();
  }
  return false;
}