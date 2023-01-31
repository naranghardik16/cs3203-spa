#include "ConditionalOperatorToken.h"
using namespace std;

ConditionalOperatorToken::ConditionalOperatorToken(string val, ConditionalOperatorType type) : Token(val) {
  type_ = type;
}

ConditionalOperatorType ConditionalOperatorToken::GetType() {
  return type_;
}

bool ConditionalOperatorToken::Equals(Token &other) {
  // make sure that the passed type is the same
  ConditionalOperatorToken *cot = dynamic_cast<ConditionalOperatorToken*>(&other);
  if (cot) {
    return this->GetType() == cot->GetType() && this->GetValue() == cot->GetValue();
  }
  return false;
}
