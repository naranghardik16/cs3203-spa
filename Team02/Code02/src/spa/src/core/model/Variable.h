#pragma once

#include "Expression.h"

class Variable : public Expression {
 public:
  Variable(std::string name);
  void Accept(ParserVisitor *visitor) override;
  inline bool IsLeafNodeExpression() override;
};