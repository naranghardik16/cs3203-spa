#include "AssignStatement.h"

AssignStatement::AssignStatement(int statement_number, Variable var,
                                 std::string in_scope_of_proc)
    : variable_(std::move(var)),
      Statement(statement_number, "assign", std::move(in_scope_of_proc)) {}

void AssignStatement::AddExpression(Expression *expression) {
  expression_ = expression;
}

Variable AssignStatement::GetVariable() const {
  return variable_;
}

Expression *AssignStatement::GetExpression() const {
  return expression_;
}

void AssignStatement::Accept(ParserVisitor *visitor) {
  visitor->VisitAssignStatement(this);
  expression_->Accept(visitor);
}