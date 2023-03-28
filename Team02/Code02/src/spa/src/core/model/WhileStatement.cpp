#include "WhileStatement.h"

WhileStatement::WhileStatement(int statement_number,
                               shared_ptr<ConditionalOperation> condition,
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

void WhileStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitWhileStatement(make_shared<WhileStatement>(*this));
}

shared_ptr<ConditionalOperation> WhileStatement::GetCondition() const {
  return condition_;
}

WhileStatement::StmtListContainer WhileStatement::GetLoopStatements() const {
  return loop_statements_;
}

