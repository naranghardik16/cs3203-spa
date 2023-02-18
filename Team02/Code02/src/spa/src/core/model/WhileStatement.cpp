#include "WhileStatement.h"

WhileStatement::WhileStatement(int statement_number,
                               ConditionalOperation condition,
                               std::string in_scope_of_proc) : Statement(
    statement_number,
    "while",
    std::move(in_scope_of_proc)), condition_(std::move(condition)) {}

WhileStatement::~WhileStatement() noexcept {
  loop_statements_.clear();
}

void WhileStatement::AddStatement(shared_ptr<Statement> stmt) {
  loop_statements_.push_back(stmt);
}

// TODO: implement accept for the visitor pattern
void WhileStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitWhileStatement(shared_from_this());
}

ConditionalOperation WhileStatement::GetCondition() const {
  return condition_;
}

WhileStatement::StmtListContainer WhileStatement::GetLoopStatements() const {
  return loop_statements_;
}

