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

  static std::shared_ptr<PkbReadFacade> create(PKB& pkb);

  KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX> &getVariableStore();

  KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &getProcedureStore();

  std::unordered_set<PkbTypes::CONSTANT> &getConstantStore();

  std::unordered_set<std::string> GetVariables();
  std::unordered_set<std::string> GetStatements();
  std::unordered_set<std::string> GetReadStatements();
  std::unordered_set<std::string> GetPrintStatements();
  std::unordered_set<std::string> GetCallStatements();
  std::unordered_set<std::string> GetWhileStatements();
  std::unordered_set<std::string> GetIfStatements();
  std::unordered_set<std::string> GetAssignStatements();
  std::unordered_set<std::string> GetConstants();
  std::unordered_set<std::string> GetProcedures();
};

