#include "WhileStatement.h"

WhileStatement::WhileStatement(int statement_number,
                               ConditionalOperation condition,
                               std::string in_scope_of_proc) : Statement(
    statement_number,
    "while",
    std::move(in_scope_of_proc)), condition_(std::move(condition)) {}

void WhileStatement::AddStatement(Statement *stmt) {
  loop_statements_.push_back(stmt);
}

void WhileStatement::Accept(ParserVisitor *visitor) {

}

ConditionalOperation WhileStatement::GetCondition() const {
  return condition_;
}

WhileStatement::StmtListContainer WhileStatement::GetLoopStatements() const {
  return loop_statements_;
}

