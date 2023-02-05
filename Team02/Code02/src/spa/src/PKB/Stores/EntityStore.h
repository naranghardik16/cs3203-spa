#pragma once

#include <unordered_set>
#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"

class EntityStore {
 public:
  EntityStore() = default ;

//  ~EntityStore();

  PkbTypes::INDEX addConstant(PkbTypes::CONSTANT constant);

  PkbTypes::INDEX addVariable(PkbTypes::VARIABLE variable);

  PkbTypes::INDEX addProcedure(PkbTypes::PROCEDURE procedure);

  std::unordered_set<PkbTypes::VARIABLE> getVariables();

  std::unordered_set<PkbTypes::PROCEDURE> getProcedures();

  std::unordered_set<PkbTypes::CONSTANT> getConstants();

 protected:
  OneToOneStore<PkbTypes::VARIABLE, PkbTypes::INDEX> variable_store_;
  OneToOneStore<PkbTypes::PROCEDURE, PkbTypes::INDEX> procedure_store_;
  OneToOneStore<PkbTypes::CONSTANT, PkbTypes::INDEX> constant_store_;
};

