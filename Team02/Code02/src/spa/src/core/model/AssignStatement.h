#pragma once
#include "Statement.h"
#include "Expression.h"
#include "Variable.h"

class AssignStatement : public Statement {
 public:
  AssignStatement(Variable var,
                  int stmt_number,
                  std::string in_scope_of_proc);
  void AddExpression(Expression expression);
  [[nodiscard]]Variable GetVariable() const;

 private:
  Variable variable_;
  Expression expression_;
};