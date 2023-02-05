#pragma once
#include "Statement.h"
#include "Expression.h"
#include "Variable.h"

class AssignStatement : public Statement, public Entity {
 public:
  AssignStatement(int statement_number, Variable var,
                  std::string in_scope_of_proc);
  void AddExpression(Expression *expression);
  void Accept(ParserVisitor *visitor);
  [[nodiscard]]Variable GetVariable() const;
  [[nodiscard]]Expression *GetExpression() const;

 private:
  Variable variable_;
  Expression *expression_;
};