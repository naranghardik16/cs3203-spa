#include "ExpressionStore.h"

#include "PKB/Util/ExpressionUtil.h"

ExpressionStore::ExpressionStore() = default;

ExpressionStore::~ExpressionStore() = default;

void ExpressionStore::addExpression(std::shared_ptr<Expression> expression) {
  for (const auto &p: ExpressionUtil::retrieveAllVariablesFromExpression(expression)) {
    this->expression_to_variable_store_.insert(expression, p);
  }

  for (const auto &p: ExpressionUtil::retrieveAllConstantsFromExpression(expression)) {
    this->expression_to_constant_store_.insert(expression, p);
  }
}

std::unordered_set<PkbTypes::VARIABLE> ExpressionStore::retrieveVariablesOfTheExpression(std::shared_ptr<Expression> expression) {
  return this->expression_to_variable_store_.retrieveFromKey(expression);
}

std::unordered_set<PkbTypes::CONSTANT> ExpressionStore::retrieveConstantsOfTheExpression(std::shared_ptr<Expression> expression) {
  return this->expression_to_constant_store_.retrieveFromKey(expression);
}
