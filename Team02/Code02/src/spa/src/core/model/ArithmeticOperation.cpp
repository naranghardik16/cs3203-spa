#pragma once
#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(string name,
                                         pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments)
    : Operation(move(name), "arithmetic", arguments) {}

void ArithmeticOperation::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitArithmeticalOperation(shared_from_this());
}

bool ArithmeticOperation::operator==(const Expression &other) const {
  if (!Expression::operator==(other)) {
    return false;
  }
  auto casted_other = dynamic_cast<const ArithmeticOperation &>(other);
  return
      this->GetArguments()->first->operator==(*casted_other.GetArguments()->first)
          && this->GetArguments()->second->operator==(*casted_other.GetArguments()->second);
}