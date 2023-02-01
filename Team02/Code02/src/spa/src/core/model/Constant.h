#pragma once

#include "Expression.h"

class Constant : public Expression {
  explicit Constant(std::string name);
};