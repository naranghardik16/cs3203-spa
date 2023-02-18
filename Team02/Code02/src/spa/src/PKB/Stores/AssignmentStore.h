#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class AssignmentStore {
 public:
  AssignmentStore();

  ~AssignmentStore();

  void addAssignmentExpression(PkbTypes::STATEMENT_NUMBER statement_number, Expression* expression);

  Expression* retrieveAssignmentExpressionByStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllStatementNumbersWhichContainExpression(Expression* expression);

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, Expression*> assignment_store_;
};

