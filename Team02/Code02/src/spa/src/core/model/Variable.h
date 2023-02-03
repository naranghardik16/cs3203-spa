#pragma once

#include "Expression.h"
class Variable : public Expression {
 public:
  Variable(std::string_view name);
};