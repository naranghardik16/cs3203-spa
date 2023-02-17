#pragma once

#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(string name,
                                         pair<Expression *,
                                              Expression *> arguments)
    : Operation(move(name), "relational", arguments) {}

void RelationalOperation::Accept(ParserVisitor *visitor) {
  visitor->VisitRelationalOperation(this);
}

bool RelationalOperation::operator==(const Expression &other) const {
  if (!Expression::operator==(other)) {
    return false;
  }
  auto casted_other = dynamic_cast<const RelationalOperation &>(other);
  return
      this->GetArguments().first->operator==(*casted_other.GetArguments().first)
          && this->GetArguments().second->operator==(*casted_other.GetArguments().second);
}