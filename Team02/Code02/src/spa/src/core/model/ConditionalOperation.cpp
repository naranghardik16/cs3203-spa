#pragma once
#include "ConditionalOperation.h"

ConditionalOperation::ConditionalOperation(string name, pair<Expression *, Expression *> arguments) : Operation(move(name), "conditional", arguments) {}

void ConditionalOperation::Accept(ParserVisitor *visitor) {

}

bool ConditionalOperation::operator==(const Expression &other) const {
  if (!Expression::operator==(other)) {
    return false;
  }
  auto casted_other = dynamic_cast<const ConditionalOperation&>(other);
  return this->GetArguments().first->operator==(*casted_other.GetArguments().first) && this->GetArguments().second->operator==(*casted_other.GetArguments().second);
}