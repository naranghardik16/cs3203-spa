#include "AssignStatement.h"

AssignStatement::AssignStatement(std::string_view var_name,
                                 int stmt_number,
                                 std::string in_scope_of_proc)
    : var_name_(var_name),
      Statement(stmt_number, "assign", std::move(in_scope_of_proc)) {}

void AssignStatement::AddExpression(Expression expression) {
  expression_ = std::move(expression);
}