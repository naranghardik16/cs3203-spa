#include "IntegerToken.h"

bool IntegerToken::Equals(IntegerToken *other) {
  return this->GetValue() == other->GetValue() == 0;
}