#include "AssignmentStore.h"

AssignmentStore::AssignmentStore() = default;

AssignmentStore::~AssignmentStore() = default;

void AssignmentStore::AddAssignmentExpression(const StatementNumber& statement_number,
                                              const ExpressionPtr& expression) {
  this->statement_number_to_expression_store_.insert(statement_number, expression);
}

AssignmentStore::ExpressionPtr
AssignmentStore::GetExpressionFromStatementNumber(const StatementNumber& statement_number) {
  return this->statement_number_to_expression_store_.retrieveFromKey(statement_number);
}

AssignmentStore::StatementNumberSet
    AssignmentStore::GetStatementNumbersFromExpression(const ExpressionPtr& expression) {
  StatementNumberSet result;

  for (const auto &p: this->statement_number_to_expression_store_.retrieveAll()) {
    if (p.second->operator==(*expression)) {
      result.insert(p.first);
    }
  }

  return result;
}

