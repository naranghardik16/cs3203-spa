#include "AssignmentStore.h"

#include <utility>

AssignmentStore::AssignmentStore() = default;

AssignmentStore::~AssignmentStore() = default;

void AssignmentStore::addAssignmentExpression(PkbTypes::STATEMENT_NUMBER statement_number,
                                              std::shared_ptr<Expression> expression) {
  this->assignment_store_.insert(std::move(statement_number), expression);
}

std::shared_ptr<Expression>
AssignmentStore::retrieveAssignmentExpressionByStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->assignment_store_.retrieveFromKey(std::move(statement_number));
}

// superficial expression
std::unordered_set<PkbTypes::STATEMENT_NUMBER>
    AssignmentStore::retrieveAllStatementNumbersWhichContainExpression(std::shared_ptr<Expression> expression) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> result;

  for (const auto &p: this->assignment_store_.retrieveAll()) {
    if (p.second->operator==(*expression)) {
      result.insert(p.first);
    }
  }

  return result;
}

