#include "IfStatement.h"

IfStatement::IfStatement(int statement_number,
                         ConditionalOperation condition,
                         std::string in_scope_of_proc) : Statement(
    statement_number,
    "if",
    std::move(in_scope_of_proc)), condition_(std::move(condition)) {}

IfStatement::~IfStatement() noexcept {
  then_statements_.clear();
  else_statements_.clear();
}

void IfStatement::AddThenStmtList(shared_ptr<Statement> statement) {
  then_statements_.push_back(statement);
}

void IfStatement::AddElseStmtList(shared_ptr<Statement> statement) {
  else_statements_.push_back(statement);
}

void IfStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitIfStatement(make_shared<IfStatement>(*this));
}

ConditionalOperation IfStatement::GetCondition() const {
  return condition_;
}

IfStatement::StmtListContainer IfStatement::GetThenStatements() const {
  return then_statements_;
}

IfStatement::StmtListContainer IfStatement::GetElseStatements() const {
  return else_statements_;
}
