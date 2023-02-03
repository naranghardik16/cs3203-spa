#pragma once

#include <unordered_set>
#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/KeyValueStore.h"


class EntityStore {
 public:
  void addConstant(PkbTypes::CONSTANT constant);

  PkbTypes::VARIABLE_STORE_INDEX addVariable(PkbTypes::VARIABLE variable);

  PkbTypes::PROCEDURE_STORE_INDEX addProcedure(PkbTypes::PROCEDURE procedure);

  KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX> &getVariableStore();

  KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &getProcedureStore();

  std::unordered_set<PkbTypes::CONSTANT> &getConstantStore();

 protected:
  KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX> variable_store_;
  KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> procedure_store_;
  std::unordered_set<PkbTypes::CONSTANT> constant_store_;
};

