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
  virtual const VARIABLE_STORE &getVariableStore() const;
  virtual const PROCEDURE_STORE &getProcedureStore() const;
  virtual const CONSTANT_STORE &getConstantStore() const;
  virtual void addConstant(CONSTANT constant);
  virtual VARIABLE_STORE_INDEX addVariable(VARIABLE variable);
  virtual PROCEDURE_STORE_INDEX addProcedure(PROCEDURE procedure);
};