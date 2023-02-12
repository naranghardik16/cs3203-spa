#pragma once
#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(string name, pair<Expression *, Expression *> arguments) : Operation(move(name), "arithmetic", arguments) {}

void ArithmeticOperation::Accept(ParserVisitor *visitor) {

}


bool ArithmeticOperation::operator==(const Expression &other) const {
  if (!Expression::operator==(other)) {
    return false;
  }
  auto casted_other = dynamic_cast<const ArithmeticOperation&>(other);
  return this->GetArguments().first->operator==(*casted_other.GetArguments().first) && this->GetArguments().second->operator==(*casted_other.GetArguments().second);
}