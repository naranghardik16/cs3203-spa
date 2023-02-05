#pragma once

#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/KeyValueStore.h"

enum StatementType {
  IF,
  READ,
  PRINT,
  CALL,
  UNK,
  ASSIGN,
  WHILE
};

class StatementStore {
 public:
  StatementStore();

  KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::PROCEDURE> &getStatementProcedureStore();

  KeyValueStore<PkbTypes::LINE_NUMBER, StatementType> &getStatementTypeStore();

  void addStatementProcedure(PkbTypes::LINE_NUMBER line_number, PkbTypes::PROCEDURE statement_procedure);

  void addStatementType(PkbTypes::LINE_NUMBER line_number, StatementType statement_type);

 protected:
  KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::PROCEDURE> statement_procedure_store_;
  KeyValueStore<PkbTypes::LINE_NUMBER, StatementType> statement_type_store_;

};

