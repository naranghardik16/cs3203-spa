#pragma once

#include "Expression.h"
#include "Entity.h"

class Variable : public Expression, public Entity {
 public:
  Variable(std::string name);
  void Accept(ParserVisitor *visitor) override;
};