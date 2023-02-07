#pragma once

#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "General/StatementTypeEnum.h"

class StatementStore {
 public:
  ~StatementStore();

  void addStatementAndField(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::FIELD field);
  void addStatementForAType(StatementType statement_type, PkbTypes::STATEMENT_NUMBER statement_number);

  StatementType getStatementTypeByNumber(PkbTypes::STATEMENT_NUMBER statementNumber);
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> getStatementsFromType(StatementType statement_type);
  std::unordered_set<StatementType> getAllStatementTypes();
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> getAllStatements();
  std::unordered_set<PkbTypes::FIELD> getFieldsForStatement(PkbTypes::STATEMENT_NUMBER statement_number);

 protected:
  OneToManyStore<StatementType, PkbTypes::STATEMENT_NUMBER> type_statement_store;
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::FIELD> statement_field_store;
};

