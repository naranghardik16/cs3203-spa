#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/KeyValueStore.h"
#include "PKB/PKB.h"

class PkbReadFacade {
 private:
  PKB& pkb;

 public:
  PkbReadFacade(PKB& pkb);

  ~PkbReadFacade();

  KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX> &getVariableStore();

  KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &getProcedureStore();

  std::unordered_set<PkbTypes::CONSTANT> &getConstantStore();
};

