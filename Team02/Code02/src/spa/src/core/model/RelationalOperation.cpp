#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(string name,
                                         pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments)
    : Operation(move(name), "relational", arguments) {}

void RelationalOperation::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitRelationalOperation(make_shared<RelationalOperation>(*this));
}

bool RelationalOperation::operator==(const Expression &other) const {
  if (!Expression::operator==(other)) {
    return false;
  }
  auto casted_other = dynamic_cast<const RelationalOperation &>(other);
  return
      this->GetArguments()->first->operator==(*casted_other.GetArguments()->first)
          && this->GetArguments()->second->operator==(*casted_other.GetArguments()->second);
}
