#include "AssignStatement.h"

AssignStatement::AssignStatement(int statement_number, Variable var,
                                 std::string in_scope_of_proc)
    : variable_(std::move(var)), expression_(),
      Statement(statement_number, "assign", std::move(in_scope_of_proc)) {}

void AssignStatement::AddExpression(shared_ptr<Expression> expression) {
  expression_ = expression;
}

Variable AssignStatement::GetVariable() const {
  return variable_;
}

shared_ptr<Expression> AssignStatement::GetExpression() const {
  return expression_;
}

void AssignStatement::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitAssignStatement(make_shared<AssignStatement>(*this));
  expression_->Accept(visitor);
}