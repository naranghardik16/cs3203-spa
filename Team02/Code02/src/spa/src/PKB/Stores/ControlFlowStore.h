#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class ControlFlowStore {
 public:
  ControlFlowStore();

  ~ControlFlowStore();

  void addIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, Expression* expression);

  void addWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, Expression* expression);

  Expression* retrieveIfStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  Expression* retrieveWhileStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllIfStatementsWithCondition(Expression* expression);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllWhileStatementsWithCondition(Expression* expression);

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, Expression*> if_store_;
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, Expression*> while_store_;
};

