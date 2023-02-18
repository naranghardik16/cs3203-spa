#include "IfStatement.h"

IfStatement::IfStatement(int statement_number,
                         ConditionalOperation &condition,
                         std::string in_scope_of_proc) : Statement(
    statement_number,
    "if",
    std::move(in_scope_of_proc)), condition_(std::move(condition)) {}

IfStatement::~IfStatement() noexcept {
  for (auto stmt : then_statements_) {
    delete stmt;
  }
  then_statements_.clear();

  for (auto stmt : else_statements_) {
    delete stmt;
  }
  else_statements_.clear();
}

void IfStatement::AddThenStmtList(Statement *statement) {
  then_statements_.push_back(statement);
}

void IfStatement::AddElseStmtList(Statement *statement) {
  else_statements_.push_back(statement);
}

// TODO: Add logic for visitor
void IfStatement::Accept(ParserVisitor *visitor) {
  visitor->VisitIfStatement(this);
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



