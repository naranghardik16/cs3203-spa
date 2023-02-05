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

  KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX> &GetVariableStore();

  KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &GetProcedureStore();

  std::unordered_set<PkbTypes::CONSTANT> &GetConstantStore();

  //! API for basic Select statements
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

  //! API for Modifies
  //TODO return the Result class instead
  std::vector<std::vector<std::string>> GetModifiesStatementVariablePairs();
  std::vector<std::vector<std::string>> GetModifiesProcedureVariablePairs();
  std::vector<std::vector<std::string>> GetVariablesModifiedByStatement(std::string stmt_num);
  std::vector<std::vector<std::string>> GetVariablesModifiedByProcedure(std::string proc_name);
  std::vector<std::vector<std::string>> GetStatementsModifiesVariable(std::string var_name);
  std::vector<std::vector<std::string>> GetProceduresModifiesVariable(std::string var_name);


};

