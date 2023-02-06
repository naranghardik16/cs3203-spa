//! Preserving the stub written previously
/*
#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

class StubPkbReadFacade : public PkbReadFacade {
 public:
  StubPkbReadFacade(PKB& pkb) : PKBReadFacade(pkb);

  ~StubPkbReadFacade();

  std::unordered_set<std::string> GetVariables();
  std::unordered_set<std::string> GetConstants();
  std::unordered_set<std::string> GetProcedures();

  //! API for basic Select statements
  std::unordered_set<std::string> GetStatements();
  std::unordered_set<std::string> GetReadStatements();
  std::unordered_set<std::string> GetPrintStatements();
  std::unordered_set<std::string> GetCallStatements();
  std::unordered_set<std::string> GetWhileStatements();
  std::unordered_set<std::string> GetIfStatements();
  std::unordered_set<std::string> GetAssignStatements();

  //! API for Modifies
  //TODO return the Result class instead
  std::vector<std::vector<std::string>> GetModifiesStatementVariablePairs();
  std::vector<std::vector<std::string>> GetModifiesProcedureVariablePairs();
  std::vector<std::vector<std::string>> GetVariablesModifiedByStatement(std::string stmt_num);
  std::vector<std::vector<std::string>> GetVariablesModifiedByProcedure(std::string proc_name);
  std::vector<std::vector<std::string>> GetStatementsModifiesVariable(std::string var_name);
  std::vector<std::vector<std::string>> GetProceduresModifiesVariable(std::string var_name);


};
*/