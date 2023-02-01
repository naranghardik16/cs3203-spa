#pragma once
#include "Statement.h"
#include "Expression.h"

class AssignStatement : public Statement {
 public:
  AssignStatement(std::string_view var_name,
                  int stmt_number,
                  std::string in_scope_of_proc);
  void AddExpression(Expression expression);

 private:
  const std::string var_name_;
  Expression expression_;
};