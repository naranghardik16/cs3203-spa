#pragma once

#include "Expression.h"

class Variable : public Expression, public enable_shared_from_this<Variable> {
 public:
  Variable(std::string name);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  inline bool IsLeafNodeExpression() override;
};