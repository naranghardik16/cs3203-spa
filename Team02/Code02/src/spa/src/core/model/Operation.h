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
  [[nodiscard]] pair<Expression *, Expression *> GetArguments() const;
//  bool operator==(const Expression &other) const;
 private:
  pair<Expression *, Expression *> arguments_;
};

