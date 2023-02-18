#pragma once

#include "Operation.h"

using namespace std;

class RelationalOperation : public Operation {
 public:
  RelationalOperation(string name, pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  bool operator==(const Expression &other) const override;
};

