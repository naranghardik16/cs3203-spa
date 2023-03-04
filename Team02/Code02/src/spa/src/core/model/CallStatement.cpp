#include "CallStatement.h"

CallStatement::CallStatement(int statement_number,
                             Procedure proc,
                             std::string in_scope_proc) : procedure_(std::move(
    proc)), Statement(
    statement_number,
    "call",
    in_scope_proc) {}

string CallStatement::GetProcedureName() const {
  return procedure_.GetProcedureName();
}

void CallStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitCallStatement(make_shared<CallStatement>(*this));
}
