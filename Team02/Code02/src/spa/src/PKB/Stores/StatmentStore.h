#pragma once

#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"

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

  getStatementsByType();

  getAllStatementTypes();

  getAllStatements();

  addStatement();

 protected:
  OneToOneStore<PkbTypes::LINE_NUMBER, StatementType> statement_type_store_;
};

