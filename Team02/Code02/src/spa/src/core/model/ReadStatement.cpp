#include "ReadStatement.h"

ReadStatement::ReadStatement(int statement_number,
                             Variable var,
                             std::string in_scope_proc) : variable_(std::move(
    var)), Statement(
    statement_number,
    "read",
    in_scope_proc) {}

Variable ReadStatement::GetVariable() const {
  return variable_;
}

void ReadStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitReadStatement(make_shared<ReadStatement>(*this));
}