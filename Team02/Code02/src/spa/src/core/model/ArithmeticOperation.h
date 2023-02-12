#pragma once

#include "Operation.h"

using namespace std;

class ArithmeticOperation : public Operation {
 public:
  ArithmeticOperation(string name, pair<Expression*, Expression*> arguments);
  void Accept(ParserVisitor *visitor) override;
  bool operator==(const Expression &other) const override;
};