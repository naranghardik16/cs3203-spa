#pragma once

#include <unordered_set>
#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/KeyValueStore.h"

class ModifiesStore {
 public:
  ModifiesStore();
  KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::MODIFIES> &getModifiesStatementStore();
  KeyValueStore<PkbTypes::PROCEDURE , PkbTypes::VARIABLE_SET> &getModifiesProcedureStore();

  void addModifiesStatement(PkbTypes::LINE_NUMBER line_number, PkbTypes::MODIFIES modifies);
  void addModifiesProcedure(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE_SET variable_set);

 protected:
  KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::MODIFIES> modifies_statement_store_;
  KeyValueStore<PkbTypes::PROCEDURE , PkbTypes::VARIABLE_SET> modifies_procedure_store_;
};

