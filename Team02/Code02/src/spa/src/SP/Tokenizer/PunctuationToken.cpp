#include "PunctuationToken.h"
using namespace std;

PunctuationToken::PunctuationToken(string val, TokenType type) : Token(val, type) {}

bool PunctuationToken::Equals(Token &other) {
  // make sure that the passed type is the same
  PunctuationToken *pot = dynamic_cast<PunctuationToken*>(&other);
  if (pot) {
    return this->GetType() == pot->GetType() && this->GetValue() == pot->GetValue();
  }
  return false;
}
