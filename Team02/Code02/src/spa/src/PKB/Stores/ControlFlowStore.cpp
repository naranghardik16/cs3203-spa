
#include "ControlFlowStore.h"

#include <utility>

ControlFlowStore::ControlFlowStore() = default;

ControlFlowStore::~ControlFlowStore() = default;

void ControlFlowStore::addIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                  std::shared_ptr<Expression> expression) {
  this->if_store_.insert(std::move(statement_number), expression);
}

void ControlFlowStore::addWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                     std::shared_ptr<Expression> expression) {
  this->while_store_.insert(std::move(statement_number), expression);
}

std::shared_ptr<Expression>
    ControlFlowStore::retrieveIfStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->if_store_.retrieveFromKey(std::move(statement_number));
}

std::shared_ptr<Expression>
    ControlFlowStore::retrieveWhileStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->while_store_.retrieveFromKey(std::move(statement_number));
}

// superficial expression
std::unordered_set<PkbTypes::STATEMENT_NUMBER>
    ControlFlowStore::retrieveAllIfStatementsWithCondition(std::shared_ptr<Expression> expression) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> result;

  for (const auto &p: this->if_store_.retrieveAll()) {
    if (p.second->operator==(*expression)) {
      result.insert(p.first);
    }
  }

  return result;
}

// superficial expression
std::unordered_set<PkbTypes::STATEMENT_NUMBER>
    ControlFlowStore::retrieveAllWhileStatementsWithCondition(std::shared_ptr<Expression> expression) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> result;

  for (const auto &p: this->while_store_.retrieveAll()) {
    if (p.second == expression) {
      result.insert(p.first);
    }
  }

  return result;
}
