#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class AssignmentStore {
 public:
  AssignmentStore();

  ~AssignmentStore();

  void addAssignmentExpression(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  std::shared_ptr<Expression> retrieveAssignmentExpressionByStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllStatementNumbersWhichContainExpression(std::shared_ptr<Expression> expression);

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> assignment_store_;
};

