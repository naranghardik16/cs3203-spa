#pragma once

#include "Expression.h"

class Constant : public Expression {
 public:
  explicit Constant(std::string name);
  void Accept(ParserVisitor *visitor) override;
  inline bool IsLeafNodeExpression() override;
};