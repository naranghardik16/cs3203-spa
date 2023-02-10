#pragma once

#include "Operation.h"

using namespace std;

class ConditionalOperation : public Operation {
 public:
  ConditionalOperation(string name, pair<Expression*, Expression*> arguments);
  void Accept(ParserVisitor *visitor) override;
  bool operator==(const Expression &other) const;
};