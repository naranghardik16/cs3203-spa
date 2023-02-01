#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "PKB/PKBStores.h"

using namespace std;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB: public PKBStores {
public:
  PKBStores *getStores();

  virtual const VARIABLE_STORE &getVariableStore() const;
  virtual const PROCEDURE_STORE &getProcedureStore() const;
  virtual const CONSTANT_STORE &getConstantStore() const;

  virtual void addConstant(CONSTANT constant);
  virtual VARIABLE_STORE_INDEX addVariable(VARIABLE variable);
  virtual PROCEDURE_STORE_INDEX addProcedure(PROCEDURE procedure);

  //! API For communication with QPS
  virtual std::unordered_set<std::string> GetVariables();
  virtual std::unordered_set<std::string> GetStatements();
  virtual std::unordered_set<std::string> GetReadStatements();
  virtual std::unordered_set<std::string> GetPrintStatements();
  virtual std::unordered_set<std::string> GetCallStatements();
  virtual std::unordered_set<std::string> GetWhileStatements();
  virtual std::unordered_set<std::string> GetIfStatements();
  virtual std::unordered_set<std::string> GetAssignStatements();
  virtual std::unordered_set<std::string> GetConstants();
  virtual std::unordered_set<std::string> GetProcedures();
};