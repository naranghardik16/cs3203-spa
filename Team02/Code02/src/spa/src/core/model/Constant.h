#pragma once

#include "Expression.h"
#include "Entity.h"

class Constant : public Expression, public Entity {
 public:
  explicit Constant(std::string name);
  void Accept(ParserVisitor *visitor);
};