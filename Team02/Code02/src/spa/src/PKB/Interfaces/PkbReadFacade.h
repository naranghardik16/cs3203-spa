#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"

class PkbReadFacade {
 private:
  PKB& pkb;

 public:
  PkbReadFacade(PKB& pkb);

  ~PkbReadFacade();

//  virtual bool modifies(LineNumber line, String variableName);
//  virtual NAME_SET modifies(LineNumber line, Variable variable);
//  virtual bool modifies(LineNumber line, Underscore underscore);
//  virtual LINE_SET modifies(Statement statement, String variableName);
//  virtual LINE_NAME_PAIRS modifies(Statement statement, Variable variable);
//  virtual LINE_SET modifies(Statement, Underscore underscore);
//  virtual bool modifies(String procedureName, String variableName);
//  virtual NAME_SET modifies(String procedureName, Variable variable);
//  virtual bool modifies(String procedureName, Underscore underscore);
//  virtual NAME_SET modifies(Procedure, String variableName);
//  virtual NAME_NAME_PAIRS modifies(Procedure, Variable variable);
//  virtual NAME_SET modifies(Procedure, Underscore underscore);

  std::unordered_set<std::string> GetVariables();
  std::unordered_set<std::string> GetConstants();
  std::unordered_set<std::string> GetProcedures();


  std::unordered_set<std::string> GetStatements();
  std::unordered_set<std::string> GetReadStatements();
  std::unordered_set<std::string> GetPrintStatements();
  std::unordered_set<std::string> GetCallStatements();
  std::unordered_set<std::string> GetWhileStatements();
  std::unordered_set<std::string> GetIfStatements();
  std::unordered_set<std::string> GetAssignStatements();


};

