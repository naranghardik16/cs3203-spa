#include "ConditionalOperatorToken.h"
using namespace std;

ConditionalOperatorToken::ConditionalOperatorToken(string val, TokenType type) : Token(val, type) {}

bool ConditionalOperatorToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<ConditionalOperatorToken> cot = dynamic_pointer_cast<ConditionalOperatorToken>(other);
  if (cot) {
    return this->GetType() == cot->GetType() && this->GetValue() == cot->GetValue();
  }
  return false;
}
