#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class ControlFlowStore {
 public:
  ControlFlowStore();

  ~ControlFlowStore();

  void addIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  void addWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  std::shared_ptr<Expression> retrieveIfStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  std::shared_ptr<Expression> retrieveWhileStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllIfStatementsWithCondition(std::shared_ptr<Expression> expression);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllWhileStatementsWithCondition(std::shared_ptr<Expression> expression);

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> if_store_;
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> while_store_;
};

