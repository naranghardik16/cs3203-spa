#include "ArithmeticOperatorToken.h"
using namespace std;

ArithmeticOperatorToken::ArithmeticOperatorToken(string val, ArithmeticOperatorType type) : Token(val) {
  type_ = type;
}

ArithmeticOperatorType ArithmeticOperatorToken::GetType() {
  return type_;
}

bool ArithmeticOperatorToken::Equals(Token &other) {
  // make sure that the passed type is the same
  ArithmeticOperatorToken *aot = dynamic_cast<ArithmeticOperatorToken*>(&other);
  if (aot) {
    return this->GetType() == aot->GetType() && this->GetValue() == aot->GetValue();
  }
  return false;
}
