#pragma once

#include <unordered_set>
#include "core/model/Expression.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"

class ExpressionStore {
 public:
  ExpressionStore();

  ~ExpressionStore();

  void addExpression(std::shared_ptr<Expression> expression);

  std::unordered_set<PkbTypes::VARIABLE> retrieveVariablesOfTheExpression(
      std::shared_ptr<Expression> expression);

  std::unordered_set<PkbTypes::CONSTANT> retrieveConstantsOfTheExpression(
      std::shared_ptr<Expression> expression);

 private:
  OneToManyStore<std::shared_ptr<Expression>, PkbTypes::VARIABLE>
      expression_to_variable_store_;
  OneToManyStore<std::shared_ptr<Expression>, PkbTypes::CONSTANT>
      expression_to_constant_store_;
};

