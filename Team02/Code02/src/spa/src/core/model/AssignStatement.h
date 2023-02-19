#pragma once
#include "Statement.h"
#include "Expression.h"
#include "Variable.h"

class AssignStatement : public Statement {
 public:
  AssignStatement(int statement_number, Variable var,
                  std::string in_scope_of_proc);
//  ~AssignStatement() noexcept override;
  virtual ~AssignStatement() = default;
  void AddExpression(shared_ptr<Expression> expression);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]]Variable GetVariable() const;
  [[nodiscard]]shared_ptr<Expression> GetExpression() const;

 private:
  Variable variable_;
  shared_ptr<Expression> expression_;
};