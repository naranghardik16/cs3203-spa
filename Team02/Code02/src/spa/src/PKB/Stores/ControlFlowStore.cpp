#include "ControlFlowStore.h"

ControlFlowStore::ControlFlowStore() = default;

ControlFlowStore::~ControlFlowStore() = default;

void ControlFlowStore::AddIfStatementAndExpression(const StatementNumber& statement_number,
                                                   const ExpressionPtr& expression) {
  this->if_store_.insert(statement_number, expression);
}

void ControlFlowStore::AddWhileStatementAndExpression(const StatementNumber& statement_number,
                                                      const ExpressionPtr& expression) {
  this->while_store_.insert(statement_number, expression);
}

std::shared_ptr<Expression>
    ControlFlowStore::GetExpressionFromIfStatement(const StatementNumber& statement_number) {
  return this->if_store_.retrieveFromKey(statement_number);
}

std::shared_ptr<Expression>
    ControlFlowStore::GetExpressionFromWhileStatement(const StatementNumber& statement_number) {
  return this->while_store_.retrieveFromKey(statement_number);
}

ControlFlowStore::StatementNumberSet
ControlFlowStore::GetIfStatementsFromExpression(const ExpressionPtr& expression) {
  StatementNumberSet result;

  for (const auto &p: this->if_store_.retrieveAll()) {
    if (p.second->operator==(*expression)) {
      result.insert(p.first);
    }
  }

  return result;
}

ControlFlowStore::StatementNumberSet
ControlFlowStore::GetWhileStatementsFromExpression(const ExpressionPtr& expression) {
  StatementNumberSet result;

  for (const auto &p: this->while_store_.retrieveAll()) {
    if (p.second == expression) {
      result.insert(p.first);
    }
  }

  return result;
}
