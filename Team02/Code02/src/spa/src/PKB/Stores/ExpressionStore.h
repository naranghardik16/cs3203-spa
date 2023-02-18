#pragma once

#include "core/model/Expression.h"

class ExpressionStore {
 public:
  ExpressionStore();

  ~ExpressionStore();

  void addExpression(Expression* expression);

  std::unordered_set<PkbTypes::VARIABLE> retrieveVariablesOfTheExpression(Expression* expression);

  std::unordered_set<PkbTypes::CONSTANT> retrieveConstantsOfTheExpression(Expression* expression);

 private:
  OneToManyStore<Expression*, PkbTypes::VARIABLE> expression_to_variable_store_;
  OneToManyStore<Expression*, PkbTypes::CONSTANT> expression_to_constant_store_;
};

