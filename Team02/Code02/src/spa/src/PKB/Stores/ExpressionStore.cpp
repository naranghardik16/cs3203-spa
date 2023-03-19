#include "ExpressionStore.h"
#include "PKB/Util/ExpressionUtil.h"

ExpressionStore::ExpressionStore() = default;

ExpressionStore::~ExpressionStore() = default;

void ExpressionStore::AddExpression(const ExpressionPtr& expression) {
  for (const auto &p: ExpressionUtil::GetAllVariablesFromExpression(expression)) {
    this->expression_to_variable_store_.insert(expression, p);
  }

  for (const auto &p: ExpressionUtil::GetAllConstantsFromExpression(expression)) {
    this->expression_to_constant_store_.insert(expression, p);
  }
}

ExpressionStore::VariableSet ExpressionStore::GetVariablesFromExpression(const ExpressionPtr& expression) {
  return this->expression_to_variable_store_.retrieveFromKey(expression);
}

ExpressionStore::ConstantSet ExpressionStore::GetConstantsFromExpression(const ExpressionPtr& expression) {
  return this->expression_to_constant_store_.retrieveFromKey(expression);
}
