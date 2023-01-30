#include "NameToken.h"

bool NameToken::Equals(NameToken *other) {
  return this->GetValue() == other->GetValue() == 0;
}