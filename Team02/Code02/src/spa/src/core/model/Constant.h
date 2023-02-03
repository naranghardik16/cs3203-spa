#pragma once

#include "Expression.h"

class Constant : public Expression {
 public:
  explicit Constant(std::string name);
};