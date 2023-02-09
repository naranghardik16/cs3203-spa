#pragma once

#include "Operation.h"

using namespace std;

class RelationalOperation : public Operation {
 public:
  RelationalOperation(string name, pair<Expression*, Expression*> arguments);
  void Accept(ParserVisitor *visitor) override;
  bool operator==(const Expression &other) const;
};

