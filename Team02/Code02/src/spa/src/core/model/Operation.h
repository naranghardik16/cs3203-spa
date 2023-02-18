#pragma once

#include "Expression.h"

using namespace std;

class Operation : public Expression {
 public:
  Operation() = default;
  ~Operation() = default;
  explicit Operation(string name,
                     string type,
                     pair<Expression *, Expression *> arguments);
};

