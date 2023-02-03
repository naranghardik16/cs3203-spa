#include "AssignStatement.h"

AssignStatement::AssignStatement(Variable var,
                                 int stmt_number,
                                 std::string in_scope_of_proc)
    : variable_(std::move(var)),
      Statement(stmt_number, "assign", std::move(in_scope_of_proc)) {}

void AssignStatement::AddExpression(Expression expression) {
  expression_ = std::move(expression);
}

Variable AssignStatement::GetVariable() const {
  return variable_;
}

Expression AssignStatement::GetExpression() const {
  return expression_;
}