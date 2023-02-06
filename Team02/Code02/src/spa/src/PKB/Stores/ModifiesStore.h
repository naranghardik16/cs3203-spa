#pragma once

#include <unordered_set>
#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class ModifiesStore {
 public:
  ModifiesStore();
  ~ModifiesStore();

  void addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);
  void addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);


 protected:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE> modifies_statement_variable_;
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE> modifies_procedure_variable_;
};

