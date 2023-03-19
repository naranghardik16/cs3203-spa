#include "PunctuationToken.h"

PunctuationToken::PunctuationToken(string val, TokenType type) : Token(val, type) {}

bool PunctuationToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<PunctuationToken> pot = dynamic_pointer_cast<PunctuationToken>(other);
  if (pot) {
    return this->GetType() == pot->GetType() && this->GetValue() == pot->GetValue();
  }
  return false;
}
